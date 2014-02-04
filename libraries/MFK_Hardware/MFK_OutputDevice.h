/*
 * Almost adapter pattern.
 * Provides output functions needed in that kind of projects.
 * If you declare a class with pure functions 
 * and client code refers to that class
 * and MFK_OutputDevice implements that pure functions,
 * then MFK_OutputDevice becomes an example of adapter pattern.
 * However, it is unnecessary for this time.
 */

#ifndef _MFK_OUTPUTDEVICE_H_
#define _MFK_OUTPUTDEVICE_H_

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "SerialLcd.h"

class MFK_OutputDevice: public SerialLcd {
private:
public:
	MFK_OutputDevice(Stream *);

	void print(char *txt, uint8_t clr, uint8_t cursorOn);
	void print(char *txt, uint8_t clr);
	void print(char *txt);
	void write(char);
	void del();
};

#endif
