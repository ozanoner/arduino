
#ifndef _SIGNALPATTERN_H_
#define _SIGNALPATTERN_H_

#include "Arduino.h"
#include "Timer.h"
#include "SignalSource.h"

class SignalPattern {
private:
	int id;
	SignalSource *signalSources[5];
	int cnt; // count of signalSources
	int timerId;
	Timer *timer;
	int (*startProc)(void);

public:
	SignalPattern(int id, Timer *timer, int (*startProc)(void));
	void addSignalSource(SignalSource *ss);


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
