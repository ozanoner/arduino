#ifndef _CLCD_H_
#define _CLCD_H_

#include <SoftwareSerial.h>
#include "Arduino.h"

class CLcd {
	public:
		// default rx, tx is 3,4
		CLcd();
		CLcd(int rxPin, int txPin);
		void initialize();
		void setBacklight(int8_t b);
		void clr();
		void setCursor(int8_t pos);
		void print(char *text);
	protected:
		int rx;
		int tx;
		SoftwareSerial *softSer;
};


#endif
