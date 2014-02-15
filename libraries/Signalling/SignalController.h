
/*
 * by Ozan Oner
 * top level class for signalling.
 * holds signal patterns.
 * singleton pattern
 */

#ifndef _SIGNALCONTROLLER_H_
#define _SIGNALCONTROLLER_H_

#include "Arduino.h"
#include "SignalPattern.h"

class SignalController {
public:
	// access to singleton instance
	static SignalController* getInstance() {
		static SignalController s;
		return &s;
	};

	SignalPattern* getPattern(int idx);
	void setPattern(int idx, SignalPattern *pattern);
	
	// start a pattern
	void start(int idx);
	// immidiate stop to activePattern
	void stop();

	// update in loop
	void update();

	const SignalPattern* operator[](unsigned int idx) const {
		if(idx>=MAX_SIGNAL_PATTERN)
			return NULL;
		return this->signalPatterns[idx];
	};

private:
	SignalPattern* signalPatterns[MAX_SIGNAL_PATTERN];
	SignalPattern* activePattern;

	SignalController(); // private constructor
	SignalController(SignalController const&) {}; // copy disabled
	void operator=(SignalController const&) {}; // assignment disabled

};

#endif

