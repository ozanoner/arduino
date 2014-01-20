#ifndef _C3BUT_H_
#define _C3BUT_H_

#define C3BUT_DEFAULT_PRESSDUR 2000
#define C3BUT_DEBOUNCE_TIMEOUT 50

#define C3BUT_OFF 1
#define C3BUT_ON 2
#define C3BUT_PENDING 3
#define C3BUT_PRESSED 4

#include "Arduino.h"

class C3But {
	public:
		// any pin number less than 3 will be discarded
		C3But(int p1, int p2, int p3, unsigned long pressDur);
		C3But(int p1, int p2, int p3);

		// sets pin mode & pull-up resistors
		// call this in setup
		void initialize();

		void setPressCallback(void (*callback)(int pinNum));
		void setTwoPressCallback(void (*callback)(int pinNum1, int pinNum2));

		void update();
	protected:
		unsigned long pressDuration;
		void (*pressCallback)(int pinNum);
		void (*twoPressCallback)(int pinNum1, int pinNum2);
		
		int pinNum[3];
		int state[3];
		unsigned long pressTime[3];
		
		int8_t getOnButton(int skip);
};

#endif
