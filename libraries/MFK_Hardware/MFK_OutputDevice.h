/*
 * by Ozan Oner
 *
 * output device for MFK project
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
