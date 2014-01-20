
#include "CLcd.h"

CLcd::CLcd() {
	this->rx = 3;
	this->tx = 4;
}

CLcd::CLcd(int rxPin, int txPin) {
	this->rx = rxPin;
	this->tx = txPin;
}

void CLcd::initialize() {
	this->softSer = new SoftwareSerial(this->rx, this->tx);
	this->softSer->begin(9600);
}

void CLcd::setBacklight(int8_t b) {
	this->softSer->write(0x80);
	this->softSer->write(b);
}

void CLcd::clr() {
	this->softSer->write(0xFE);
	this->softSer->write(0x01);
}

void CLcd::setCursor(int8_t pos) {
	this->softSer->write(0xFE);
	this->softSer->write(0x80);
	this->softSer->write(pos);
}

void CLcd::print(char *text) {
	this->softSer->print(text);
}
