/*
  ==============================================================================

    KrushSync.cpp
    Created: 22 Nov 2018 4:10:18pm
    Author:  rkubiak

  ==============================================================================
*/

#include "KrushSync.h"

KrushSync::KrushSync()
	: internalSync(true),
	Thread("KrushSync"),
	currentTransportState(Stopped),
	outputMidiClock(false)
{
	
}

KrushSync::~KrushSync()
{
	stop();
}

void KrushSync::run()
{
	currentTransportState = Playing;
	timeTick = 0;
	while (!threadShouldExit())
	{
		wait(currentSleepMs);
		timeTick++;

		if (timeTick % 24 == 0)
		{
			listeners.call(&Listener::realtimeEvent, ClockQuarterNote);
			eventQueue.add(ClockQuarterNote);
		}

		if (outputMidiClock)
		{
		}

		if (timeTick == 96)
			timeTick = 0;

		listeners.call(&Listener::realtimeEvent, ClockTick);
		eventQueue.add(ClockTick);

		triggerAsyncUpdate();
	}
}

void KrushSync::setTempo(double bpm)
{
	ScopedLock sl(syncLock);
	currentSleepMs = (60.0 * 1000.0) / (bpm * 24.0);
	DBG("KrushSync::setTempo bpm=" + _S(bpm) + " currentSleepMs=" + _S(currentSleepMs));
}

void KrushSync::start()
{
	if (internalSync)
	{
		startThread();
	}
	else
	{
		ScopedLock sl(syncLock);
		currentTransportState = Playing;
	}
}

void KrushSync::pause()
{
	ScopedLock sl(syncLock);
	currentTransportState = Paused;
}

void KrushSync::stop()
{
	if (internalSync)
	{
		ScopedLock sl(syncLock);
		currentTransportState = Stopping;
		signalThreadShouldExit();
		waitForThreadToExit(150);
		currentTransportState = Stopped;
	}
}

void KrushSync::addListener(KrushSync::Listener *l)
{
	ScopedLock sl(syncLock);
	listeners.add(l);
}

void KrushSync::removeListener(KrushSync::Listener *l)
{
	ScopedLock sl(syncLock);
	listeners.remove(l);
}

void KrushSync::handleAsyncUpdate()
{
	for (int i = 0; i < eventQueue.size(); i++)
	{
		listeners.call(&Listener::realtimeEventAsync, eventQueue[i]);
	}
	eventQueue.clear();
}