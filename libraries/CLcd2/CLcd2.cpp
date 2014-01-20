
#include "CLcd2.h"

CLcd2::CLcd2() : SoftwareSerial(3,4) {
	this->rx = 3;
	this->tx = 4;
}

CLcd2::CLcd2(int rxPin, int txPin) : SoftwareSerial(rxPin, txPin) {
	this->rx = rxPin;
	this->tx = txPin;
}

void CLcd2::initialize() {
	this->begin(9600);
	this->listen();
}

void CLcd2::setBacklight(int8_t b) {
	this->write(0x80);
	this->write(b);
}

void CLcd2::clr() {
	this->write(0xFE);
	this->write(0x01);
}

void CLcd2::setCursor(int8_t pos) {
	this->write(0xFE);
	this->write(0x80);
	this->write(pos);
}

