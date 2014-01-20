
#include <SignalController.h>


/*
static SignalController* SignalController::getInstance() {
	static SignalController scInstance;
	return &scInstance;
}
*/

SignalController::SignalController() {
	this->activePattern = NULL;
	for(int i=0; i<10; i++)
		this->signalPatterns[i]=NULL;
}

void SignalController::setPattern(int idx, SignalPattern *pattern) {
	this->signalPatterns[idx] = pattern;
}

void SignalController::startPattern(int idx) {
	if(this->signalPatterns[idx] == NULL)
		return;
	if(this->activePattern != NULL)
		this->activePattern->stop();
	this->activePattern = this->signalPatterns[idx];
	this->activePattern->start();
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
