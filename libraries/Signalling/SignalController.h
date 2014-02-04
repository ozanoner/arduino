
#ifndef _SIGNALCONTROLLER_H_
#define _SIGNALCONTROLLER_H_

#include "Arduino.h"
#include "SignalPattern.h"

class SignalController {
private:
	SignalPattern *signalPatterns[MAX_SIGNAL_PATTERN];
	SignalPattern *activePattern;

	SignalController(); // private constructor
	SignalController(SignalController const&) {}; // copy disabled
	void operator=(SignalController const&) {}; // assignment disabled
public:
	static SignalController* getInstance() {
		static SignalController s;
		return &s;
	};

	SignalPattern* getPattern(int idx);
	void setPattern(int idx, SignalPattern *pattern);
	
	// start a pattern
	void startPattern(int idx);
	// immidiate stop to activePattern
	void stopPattern();


	void update();
};

#endif

