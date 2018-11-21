#include "MainComponent.h"


MainComponent::MainComponent()
	: Thread ("Background Thread")
{
	

	krushConfigOptions.applicationName = ProjectInfo::projectName;
	krushConfigOptions.folderName = ProjectInfo::projectName;
	krushConfigOptions.filenameSuffix = ".settings";
	krushConfigOptions.commonToAllUsers = false;
	krushConfig = new PropertiesFile(krushConfigOptions);

	krushMain = new KrushMain();
	addAndMakeVisible(krushMain);

	DBG("MainComponent krushConfig file:" + krushConfigOptions.getDefaultFile().getFullPathName());
    setSize (320, 240);
	formatManager.registerBasicFormats();
    setAudioChannels (0, 2);
	startThread();
	midiNotesRangeForSample.setRange (0, 126, true);
	loadAllSamples();
	pitch = velo = 0;
	startTimer(10);
}

MainComponent::~MainComponent()
{
	krushConfig->save();
	synth.clearSounds();
	stopThread (4000);
    shutdownAudio();
}

void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
	synth.setCurrentPlaybackSampleRate (sampleRate);
	midiCollector.reset(sampleRate);
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
	MidiBuffer midiData;
	midiCollector.removeNextBlockOfMessages(midiData, bufferToFill.numSamples);
	synth.renderNextBlock (*bufferToFill.buffer, midiData, bufferToFill.startSample, bufferToFill.numSamples);
}

void MainComponent::releaseResources()
{
}

void MainComponent::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void MainComponent::resized()
{
	if (krushMain)
		krushMain->setBounds(0, 0, getWidth(), getHeight());
}

void MainComponent::loadAllSamples()
{
	File sampleFolder(krushConfig->getValue(Config::sampleFolder));

	if (sampleFolder.isDirectory())
	{
		synth.clearVoices();

		for (int i = 0; i < KRUSH_VOICES; i++)
			synth.addVoice(new SamplerVoice());

		Array<File> sampleFiles;
		if (sampleFolder.findChildFiles(sampleFiles, File::TypesOfFileToFind::findFiles, "*") > 0)
		{
			for (int i = 0; i < sampleFiles.size(); i++)
			{
				DBG("loadAllSamples loading file" + sampleFiles[i].getFullPathName());
				ScopedPointer <AudioFormatReader> reader = formatManager.createReaderFor(sampleFiles[i]);
				if (reader.get() != nullptr)
				{
					SamplerSound *sound = new SamplerSound(
						sampleFiles[i].getFullPathName(),
						*reader, midiNotesRangeForSample,
						KRUSH_MIDI_PITCH_ZERO,
						0.0,
						0.0,
						KRUSH_MAX_SAMPLE_LENGTH);

					synth.addSound(sound);
				}
			}
		}
	}
	else
	{
		krushConfig->setValue(Config::sampleFolder, "/samples");
		krushConfig->save();
	}
}

void MainComponent::run()
{
}

void MainComponent::mouseMove(const MouseEvent &e)
{
	const float divY = (float)e.y / (float)getHeight();
	const float divX = (float)e.x / (float)getWidth();
	pitch = divY * 0x7f;
	velo = divX * 0x7f;
}

void MainComponent::mouseDown(const MouseEvent &e)
{
	
	DBG("mouseDown generate noteOn pitch="+String(pitch) + " vel=" + String(velo));
	
	MidiMessage m = MidiMessage::noteOn(1, pitch, velo);
	m.setTimeStamp(0.1);
	midiCollector.addMessageToQueue(m);
}

void MainComponent::timerCallback()
{
	repaint();
}