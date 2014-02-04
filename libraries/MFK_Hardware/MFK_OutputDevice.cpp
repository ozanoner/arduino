

#include "MFK_OutputDevice.h"

MFK_OutputDevice::MFK_OutputDevice(Stream *stream): \
		SerialLcd(stream) {
}

void MFK_OutputDevice::print(char *txt, uint8_t clr, uint8_t cursorOn) {
	if(clr)
		SerialLcd::clr();
	if(txt==NULL || *txt==0)
		return;
	SerialLcd::print(txt);
	SerialLcd::showBlinkCursor(cursorOn);
}

void MFK_OutputDevice::print(char *txt, uint8_t clr) {
	this->print(txt, clr, 1);
}

void MFK_OutputDevice::print(char *txt) {
	this->print(txt, 1, 1);
}

// 0-9 accepted
void MFK_OutputDevice::write(char c) {
	if(c>='0' && c<='9')
		SerialLcd::sendChar((uint8_t)c);
}

void MFK_OutputDevice::del() {
	SerialLcd::sendChar(SL_CMD_BCK);
}
