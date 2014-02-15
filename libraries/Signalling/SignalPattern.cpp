
#include "SignalPattern.h"

SignalPattern::SignalPattern(int id, Timer *timer, \
		int (*startProc)(void)) {
	if(id<0 || id>=MAX_SIGNAL_PATTERN)
		return;
	this->id=id;

	for(int i=0; i<5; i++) 
		this->signalSources[i]=NULL;
	this->cnt=0;
	this->timer = timer;
	this->startProc = startProc;
}

void SignalPattern::addSignalSource(SignalSource *ss) {
	if(ss==NULL)
		return;
	if(this->cnt<5)
		this->signalSources[this->cnt++] = ss;
}

void SignalPattern::start() {
	if(this->startProc == NULL)
		return;
	for(int i=0; i<this->cnt; i++)
		this->signalSources[i]->activate(this->id);
	this->timerId = this->startProc();
	Serial.print(F("signalPattern.start: "));
	Serial.println(this->timerId);
}

void SignalPattern::stop() {
	Serial.println(F("signalPattern::stop"));
	this->timer->stop(this->timerId);
	for(int i=0; i<this->cnt; i++)
		this->signalSources[i]->disable();
}

void SignalPattern::trigger() {
	for(int i=0; i<this->cnt; i++) 
		this->signalSources[i]->trigger();
}

void SignalPattern::update() {
	for(int i=0; i<this->cnt; i++) 
		this->signalSources[i]->update();
}
