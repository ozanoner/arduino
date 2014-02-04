
#include "SignalSource.h"

SignalSource::SignalSource(int onOffset, int offOffset) {
	for(int i=1; i<MAX_SIGNAL_PATTERN; i++) {
		this->offset[i]=NULL;
	}
	this->offset[0]=new SigOffset;
	this->offset[0]->onOffset=onOffset;
	this->offset[0]->offOffset=offOffset;
}

void SignalSource::addSigOffset(int sigIdx, int onOffset, int offOffset) {
	if(sigIdx<0 || sigIdx>=MAX_SIGNAL_PATTERN)
		return;
	this->offset[sigIdx]=new SigOffset;
	this->offset[sigIdx]->onOffset=onOffset;
	this->offset[sigIdx]->offOffset=offOffset;
}

void SignalSource::activate(int sigIdx) {
	if(sigIdx<0 || sigIdx>=MAX_SIGNAL_PATTERN)
		return;
	if(this->offset[sigIdx]==NULL)
		return;
	this->onOffset = this->offset[sigIdx]->onOffset;
	this->offOffset = this->offset[sigIdx]->offOffset;
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
	if(this->nextOn<now && this->nextOff<now) {
		this->isDisabled=1;
		this->off();
		return;
	}
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
