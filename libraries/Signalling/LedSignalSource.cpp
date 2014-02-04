
#include "LedSignalSource.h"

LedSignalSource::LedSignalSource(int pin, int onOffset, int offOffset):\
	SignalSource(onOffset, offOffset) 
{
	this->pin = pin;
	pinMode(pin, OUTPUT);
}

void LedSignalSource::on() {
	if(this->isOn)
		return;
	SignalSource::on();
	// Serial.println(F("LedSignalSource on"));
	digitalWrite(pin, HIGH);
}

void LedSignalSource::off() {
	if(!this->isOn)
		return;
	digitalWrite(pin, LOW);
	// Serial.println(F("LedSignalSource off"));
	SignalSource::off();
}
