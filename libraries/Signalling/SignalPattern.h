
/*
 * by Ozan Oner
 * signal pattern class which uses signal sources 
 * to create a signal effect
 *
 */

#ifndef _SIGNALPATTERN_H_
#define _SIGNALPATTERN_H_

#include "Arduino.h"
#include "Timer.h"
#include "SignalSource.h"

class SignalPattern {
private:
	// pattern id, set 0 for the first pattern
	int id;
	// signal sources for the pattern
	SignalSource *signalSources[5];
	// number of signal sources
	int cnt; 
	// event id returned by timer call
	int timerId;
	// provides trigger functionality for the pattern
	Timer *timer;
	// start function for the timer
	// returns event id
	int (*startProc)(void);

public:
	SignalPattern(int id, Timer *timer, int (*startProc)(void));
	//add a signal source
	void addSignalSource(SignalSource *ss);

	// starts pattern
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
