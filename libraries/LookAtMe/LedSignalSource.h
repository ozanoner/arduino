
#include <Arduino.h>
#include <SignalSource.h>

#ifndef _LED_SIGNALSOURCE_H_
#define _LED_SIGNALSOURCE_H_

class LedSignalSource: public SignalSource {
private:
	int pin;
public:
	LedSignalSource(int pin, int onOffset, int offOffset);
	void on();
	void off();
};

#endif
