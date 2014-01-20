
#include <SignalPattern.h>

SignalPattern::SignalPattern(Timer *timer, int (*startProc)(void)) {
	for(int i=0; i<5; i++) 
		this->signalSources[i]=NULL;
	this->cnt=0;
	this->timer = timer;
	this->startProc = startProc;
}

void SignalPattern::addSignalSource(SignalSource *ss) {
	if(this->cnt<5)
		this->signalSources[this->cnt++] = ss;
}

void SignalPattern::start() {
	if(this->startProc == NULL)
		return;
	this->timerId = this->startProc();
}

void SignalPattern::stop() {
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
