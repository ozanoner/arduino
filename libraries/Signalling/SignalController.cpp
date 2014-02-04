
#include "SignalController.h"


SignalController::SignalController() {
	this->activePattern = NULL;
	for(int i=0; i<10; i++)
		this->signalPatterns[i]=NULL;
}

SignalPattern* SignalController::getPattern(int idx) {
	if(idx<0 || idx>=10)
		return NULL;
	return this->signalPatterns[idx];
}

void SignalController::setPattern(int idx, SignalPattern *pattern) {
	if(idx<0 || idx>=10)
		return;
	this->signalPatterns[idx] = pattern;
	// Serial.print(F("setPattern: "));
	// Serial.println(idx);
}

void SignalController::startPattern(int idx) {
	if(idx<0 || idx>=10)
		return;
	if(this->signalPatterns[idx] == NULL) {
		// Serial.println(F("startPattern: no signal pattern"));
		return;
	}
	if(this->activePattern != NULL)
		this->activePattern->stop();
	this->activePattern = this->signalPatterns[idx];
	this->activePattern->start();
	// Serial.print(F("startPattern"));
}

void SignalController::stopPattern() {
	if(this->activePattern == NULL)
		return;
	this->activePattern->stop();
	this->activePattern = NULL;
}

void SignalController::update() {
	for(int i=0; i<10; i++) {
		if(this->signalPatterns[i] != NULL)
			this->signalPatterns[i]->update();
	}
}
