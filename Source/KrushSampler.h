#include "krush.h"

	class  KrushSound : public SynthesiserSound
	{
	public:
		//==============================================================================
		/** Creates a sampled sound from an audio reader.

		This will attempt to load the audio from the source into memory and store
		it in this object.

		@param name         a name for the sample
		@param source       the audio to load. This object can be safely deleted by the
		caller after this constructor returns
		@param midiNotes    the set of midi keys that this sound should be played on. This
		is used by the SynthesiserSound::appliesToNote() method
		@param midiNoteForNormalPitch   the midi note at which the sample should be played
		with its natural rate. All other notes will be pitched
		up or down relative to this one
		@param attackTimeSecs   the attack (fade-in) time, in seconds
		@param releaseTimeSecs  the decay (fade-out) time, in seconds
		@param maxSampleLengthSeconds   a maximum length of audio to read from the audio
		source, in seconds
		*/
		KrushSound (const String& name,
			AudioFormatReader& source,
			const BigInteger& midiNotes,
			int midiNoteForNormalPitch,
			double attackTimeSecs,
			double releaseTimeSecs,
			double maxSampleLengthSeconds);

		/** Destructor. */
		~KrushSound();

		//==============================================================================
		/** Returns the sample's name */
		const String& getName() const noexcept { return name; }

		/** Returns the audio sample data.
		This could return nullptr if there was a problem loading the data.
		*/
		AudioBuffer<float>* getAudioData() const noexcept { return data.get(); }


		//==============================================================================
		bool appliesToNote (int midiNoteNumber) override;
		bool appliesToChannel (int midiChannel) override;


	private:
		//==============================================================================
		friend class KrushVoice;

		String name;
		std::unique_ptr<AudioBuffer<float>> data;
		double sourceSampleRate;
		BigInteger midiNotes;
		int length = 0, attackSamples = 0, releaseSamples = 0;
		int midiRootNote = 0;

		JUCE_LEAK_DETECTOR (KrushSound)
	};


	//==============================================================================
	/**
	A subclass of SynthesiserVoice that can play a SamplerSound.

	To use it, create a Synthesiser, add some SamplerVoice objects to it, then
	give it some SampledSound objects to play.

	@see SamplerSound, Synthesiser, SynthesiserVoice

	@tags{Audio}
	*/
	class KrushVoice : public SynthesiserVoice
	{
	public:
		//==============================================================================
		/** Creates a SamplerVoice. */
		KrushVoice();

		/** Destructor. */
		~KrushVoice();

		//==============================================================================
		bool canPlaySound (SynthesiserSound*) override;

		void startNote (int midiNoteNumber, float velocity, SynthesiserSound*, int pitchWheel) override;
		void stopNote (float velocity, bool allowTailOff) override;

		void pitchWheelMoved (int newValue) override;
		void controllerMoved (int controllerNumber, int newValue) override;

		void renderNextBlock (AudioBuffer<float>&, int startSample, int numSamples) override;


	private:
		//==============================================================================
		double pitchRatio = 0;
		double sourceSamplePosition = 0;
		float lgain = 0, rgain = 0, attackReleaseLevel = 0, attackDelta = 0, releaseDelta = 0;
		bool isInAttack = false, isInRelease = false;

		JUCE_LEAK_DETECTOR (KrushVoice)
	};
