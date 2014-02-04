
#include "BuzzerSignalSource.h"

BuzzerSignalSource::BuzzerSignalSource(uint8_t pin, \
		Timer *timer, int onOffset, int offOffset): \
		SignalSource(onOffset, offOffset)
{
	this->pin = pin;
	pinMode(pin, OUTPUT);
	this->timer = timer;
}

void BuzzerSignalSource::on() {
	if(this->isOn)
		return;
	SignalSource::on();
	// Serial.println(F("BuzzerSignalSource on"));
	this->timerId = this->timer->oscillate(this->pin, 5, 1);
}

void BuzzerSignalSource::off() {
	if(!this->isOn)
		return;
	this->timer->stop(this->timerId);
	digitalWrite(this->pin, LOW);
	Serial.println(F("BuzzerSignalSource off"));
	SignalSource::off();
}

