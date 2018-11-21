/*
  ==============================================================================

    KrushSync.h
    Created: 22 Nov 2018 4:10:18pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "krush.h"



class KrushSync : public Thread, public AsyncUpdater
{
	public:
		KrushSync();
		~KrushSync();
		void start();
		void run();
		void setTempo(double bpm);
		void stop();
		void pause();
		
		class Listener
		{
			public:
				virtual void realtimeEvent(const RealtimeEvent e) {}
				virtual void realtimeEventAsync(const RealtimeEvent e) {}
		};

		void addListener(KrushSync::Listener *l);
		void removeListener(KrushSync::Listener *l);
		void handleAsyncUpdate();
	private:
		CriticalSection syncLock;
		MidiInput *currentMidiIn;
		bool internalSync;
		double currentSleepMs;
		bool outputMidiClock;
		TransportState currentTransportState;
		int timeTick;
		ListenerList<Listener> listeners;
		Array<RealtimeEvent, CriticalSection> eventQueue;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KrushSync)
};