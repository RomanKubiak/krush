#include "KrushSampler.h"

KrushSound::KrushSound (const String& soundName,
		AudioFormatReader& source,
		const BigInteger& notes,
		int midiNoteForNormalPitch,
		double attackTimeSecs,
		double releaseTimeSecs,
		double maxSampleLengthSeconds)
		: name (soundName),
		sourceSampleRate (source.sampleRate),
		midiNotes (notes),
		midiRootNote (midiNoteForNormalPitch)
	{
		if (sourceSampleRate > 0 && source.lengthInSamples > 0)
		{
			length = jmin ((int)source.lengthInSamples,
				(int)(maxSampleLengthSeconds * sourceSampleRate));

			data.reset (new AudioBuffer<float> (jmin (2, (int)source.numChannels), length + 4));

			source.read (data.get(), 0, length + 4, 0, true, true);

			attackSamples = roundToInt (attackTimeSecs  * sourceSampleRate);
			releaseSamples = roundToInt (releaseTimeSecs * sourceSampleRate);
		}
	}

	KrushSound::~KrushSound()
	{
	}

	bool KrushSound::appliesToNote (int midiNoteNumber)
	{
		return midiNotes[midiNoteNumber];
	}

	bool KrushSound::appliesToChannel (int /*midiChannel*/)
	{
		return true;
	}

	//==============================================================================
	KrushVoice::KrushVoice() {}
	KrushVoice::~KrushVoice() {}

	bool KrushVoice::canPlaySound (SynthesiserSound* sound)
	{
		return dynamic_cast<const KrushSound*> (sound) != nullptr;
	}

	void KrushVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound* s, int /*currentPitchWheelPosition*/)
	{
		if (auto* sound = dynamic_cast<const KrushSound*> (s))
		{
			pitchRatio = std::pow (2.0, (midiNoteNumber - sound->midiRootNote) / 12.0)
				* sound->sourceSampleRate / getSampleRate();

			sourceSamplePosition = 0.0;
			lgain = velocity;
			rgain = velocity;

			isInAttack = (sound->attackSamples > 0);
			isInRelease = false;

			if (isInAttack)
			{
				attackReleaseLevel = 0.0f;
				attackDelta = (float)(pitchRatio / sound->attackSamples);
			}
			else
			{
				attackReleaseLevel = 1.0f;
				attackDelta = 0.0f;
			}

			if (sound->releaseSamples > 0)
				releaseDelta = (float)(-pitchRatio / sound->releaseSamples);
			else
				releaseDelta = -1.0f;
		}
		else
		{
			jassertfalse; // this object can only play SamplerSounds!
		}
	}

	void KrushVoice::stopNote (float /*velocity*/, bool allowTailOff)
	{
		if (allowTailOff)
		{
			isInAttack = false;
			isInRelease = true;
		}
		else
		{
			clearCurrentNote();
		}
	}

	void KrushVoice::pitchWheelMoved (int /*newValue*/) {}
	void KrushVoice::controllerMoved (int /*controllerNumber*/, int /*newValue*/) {}

	//==============================================================================
	void KrushVoice::renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
	{
		if (auto* playingSound = static_cast<KrushSound*> (getCurrentlyPlayingSound().get()))
		{
			auto& data = *playingSound->data;
			const float* const inL = data.getReadPointer (0);
			const float* const inR = data.getNumChannels() > 1 ? data.getReadPointer (1) : nullptr;

			float* outL = outputBuffer.getWritePointer (0, startSample);
			float* outR = outputBuffer.getNumChannels() > 1 ? outputBuffer.getWritePointer (1, startSample) : nullptr;

			while (--numSamples >= 0)
			{
				auto pos = (int)sourceSamplePosition;
				auto alpha = (float)(sourceSamplePosition - pos);
				auto invAlpha = 1.0f - alpha;

				// just using a very simple linear interpolation here..
				float l = (inL[pos] * invAlpha + inL[pos + 1] * alpha);
				float r = (inR != nullptr) ? (inR[pos] * invAlpha + inR[pos + 1] * alpha)
					: l;

				l *= lgain;
				r *= rgain;

				if (isInAttack)
				{
					l *= attackReleaseLevel;
					r *= attackReleaseLevel;

					attackReleaseLevel += attackDelta;

					if (attackReleaseLevel >= 1.0f)
					{
						attackReleaseLevel = 1.0f;
						isInAttack = false;
					}
				}
				else if (isInRelease)
				{
					l *= attackReleaseLevel;
					r *= attackReleaseLevel;

					attackReleaseLevel += releaseDelta;

					if (attackReleaseLevel <= 0.0f)
					{
						stopNote (0.0f, false);
						break;
					}
				}

				if (outR != nullptr)
				{
					*outL++ += l;
					*outR++ += r;
				}
				else
				{
					*outL++ += (l + r) * 0.5f;
				}

				sourceSamplePosition += pitchRatio;

				if (sourceSamplePosition > playingSound->length)
				{
					stopNote (0.0f, false);
					break;
				}
			}
		}
	}
