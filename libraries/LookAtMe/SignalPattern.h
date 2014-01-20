
#include <Arduino.h>
#include <Timer.h>
#include <SignalSource.h>

#ifndef _SIGNALPATTERN_H_
#define _SIGNALPATTERN_H_

class SignalPattern {
private:
	SignalSource *signalSources[5];
	int cnt; // count of signalSources
	int timerId;
	Timer *timer;
	int (*startProc)(void);

public:
	SignalPattern(Timer *timer, int (*startProc)(void));
	void addSignalSource(SignalSource *ss);

	/*
	void setTimerId(int timerId);
	int getTimerId();
	*/

	// calls (*startProc), set timerId
	void start();
	// stops timer for timerId
	// disables signal sources
	// stop timerId & call signalSources.disable()
	void stop(); 
	// informs each signal source for the start of a period
	// called by timer.callback
	// calls signalSources.trigger();
	void trigger(); 

	// calls signalSources.update
	void update();
};

#endif
