#ifndef _CLCD_H_
#define _CLCD_H_

#include <SoftwareSerial.h>
#include "Arduino.h"

class CLcd2: public SoftwareSerial {
	public:
		// default rx, tx is 3,4
		CLcd2();
		CLcd2(int rxPin, int txPin);
		void initialize();
		void setBacklight(int8_t b);
		void clr();
		void setCursor(int8_t pos);
	protected:
		int rx;
		int tx;
};


#endif
