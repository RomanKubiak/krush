/*
  ==============================================================================

    krush.h
    Created: 21 Nov 2018 1:38:58pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#define KRUSH_MIDI_PITCH_ZERO	0x40
#define KRUSH_MAX_SAMPLE_LENGTH	4
#define KRUSH_VOICES 16
#define KRUSH_MIDI_RESOLUTION 96

#define _S(x) String(x)
namespace Config
{
	static const char *sampleFolder = "sampleFolder";
};

enum RealtimeEvent
{
	ClockTick,
	ClockQuarterNote
};

enum TransportState
{
	Stopped,
	Playing,
	Paused,
	Stopping,
	Unknown
};