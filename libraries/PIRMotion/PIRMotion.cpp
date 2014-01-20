/*
 * by Ozan Oner
 * PIRMotion class implementation
 */

#include <Arduino.h>
#include "PIRMotion.h"

PIRMotion::PIRMotion(int port, uint8_t useInternalPullup) {
	this->port = port;
	pinMode(port, INPUT);
	if(useInternalPullup)
		digitalWrite(port, HIGH); // set pullup 
	this->nextRead = 0;
	this->timeLag = 0;
}

void PIRMotion::update() {
	unsigned long now = millis();
	if(this->nextRead > now)
		return;
	if(digitalRead(this->port) == LOW) {
		if(this->callback != NULL)
			this->callback();
		this->nextRead = now + PIRM_SCAN_INTERVAL + this->timeLag;
	}
	else {
		this->nextRead = now + PIRM_SCAN_INTERVAL;
	}
}

void PIRMotion::setMotionCallback(void (*callback)(void)) {
	this->callback = callback;
}

void PIRMotion::setLagAfterMotion(int secs) {
	this->timeLag = secs * 1000;
}
