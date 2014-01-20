
#include <BuzzerSignalSource.h>

BuzzerSignalSource::BuzzerSignalSource(uint8_t pin, \
		Timer *timer, int onOffset, int offOffset): \
		SignalSource(onOffset, offOffset)
{
	this->pin = pin;
	this->timer = timer;
}

void BuzzerSignalSource::on() {
	if(this->isOn)
		return;
	SignalSource::on();
	this->timerId = this->timer->oscillate(this->pin, 1, 1);
}

void BuzzerSignalSource::off() {
	if(!this->isOn)
		return;
	this->timer->stop(this->timerId);
	SignalSource::off();
}

