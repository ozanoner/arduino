/*
 * 
 *
 */

#include <SignalSource.h>

SignalSource::SignalSource(int onOffset, int offOffset) {
	this->onOffset = onOffset;
	this->offOffset = offOffset;
}

void SignalSource::trigger() {
	unsigned long now=millis();
	this->isDisabled = 0;
	this->nextOn = now + this->onOffset;
	if(this->offOffset>this->onOffset)
		this->nextOff = now + this->offOffset;
}

void SignalSource::update() {
	if(this->isDisabled) {
		if(this->isOn)
			this->off();
		return;
	}
	unsigned long now = millis();
	if(this->isOn) {
	   if(this->offOffset>this->onOffset && this->nextOff<now) {
		   this->off();
	   }
	}
	else {
		if(this->nextOn<now) {
			this->on();
		}
	}
}
