
/*
 * by Ozan Oner
 * LED signal by using simple LED and a resistor
 */

#ifndef _LED_SIGNALSOURCE_H_
#define _LED_SIGNALSOURCE_H_

#include "Arduino.h"
#include "SignalSource.h"

class LedSignalSource: public SignalSource {
private:
	int pin;
public:
	LedSignalSource(int pin, int onOffset, int offOffset);
	void on();
	void off();
};

#endif
