
#include <Arduino.h>
#include <SignalPattern.h>

#ifndef _SIGNALCONTROLLER_H_
#define _SIGNALCONTROLLER_H_

class SignalController {
private:
	// static SignalController *instance;
	SignalPattern *signalPatterns[10];
	SignalPattern *activePattern;

	SignalController(); // private constructor
	SignalController(SignalController const&) {}; // copy disabled
	void operator=(SignalController const&) {}; // assignment disabled
public:
	static SignalController* getInstance() {
		static SignalController s;
		return &s;
	};

	void setPattern(int idx, SignalPattern *pattern);
	// start a pattern
	void startPattern(int idx);
	// immidiate stop to activePattern
	void stopPattern();

	void update();
};

#endif

