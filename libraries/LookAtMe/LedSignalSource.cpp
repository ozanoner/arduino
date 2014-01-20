
#include <LedSignalSource.h>

LedSignalSource::LedSignalSource(int pin, int onOffset, int offOffset):\
	SignalSource(onOffset, offOffset) 
{
	this->pin = pin;
}

void LedSignalSource::on() {
	if(this->isOn)
		return;
	SignalSource::on();
	digitalWrite(pin, HIGH);
}

void LedSignalSource::off() {
	if(!this->isOn)
		return;
	digitalWrite(pin, LOW);
	SignalSource::off();
}
