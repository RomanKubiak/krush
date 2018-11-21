/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "krush.h"
#include "KrushMain.h"
class MainComponent   : public AudioAppComponent, public Thread, public Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
	void mouseDown(const MouseEvent &e) override;
	void mouseMove(const MouseEvent &e) override;
    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
	void addSampeToPlay();
	void checkForBuffersToFree();
	void run();
	void loadAllSamples();
	void timerCallback();
private:
    //==============================================================================
    // Your private member variables go here...
	AudioFormatManager formatManager;
	OwnedArray<AudioSampleBuffer> sampleDataBuffer;
	BigInteger midiNotesRangeForSample;
	ScopedPointer<PropertiesFile> krushConfig;
	PropertiesFile::Options krushConfigOptions;
	Synthesiser synth;
	MidiMessageCollector midiCollector;
	int pitch;
	uint8_t velo;
	ScopedPointer <KrushMain> krushMain;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

