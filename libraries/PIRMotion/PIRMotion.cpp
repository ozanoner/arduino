/*
 * by Ozan Oner
 * PIRMotion class implementation
 */

#include <Arduino.h>
#include "PIRMotion.h"

PIRMotion<PIRMotionClient>::PIRMotion(int port, uint8_t useInternalPullup): \
		ClientOwner<PIRMotionClient>() {
	this->port = port;
	pinMode(port, INPUT);
	if(useInternalPullup)
		digitalWrite(port, HIGH); // set pullup 
	this->nextRead = 0;
	this->timeLag = 0;
}

void PIRMotion<PIRMotionClient>::update() {
	unsigned long now = millis();
	if(this->nextRead > now)
		return;
	if(digitalRead(this->port) == LOW) {
		this->informClients();
		this->nextRead = now + PIRM_SCAN_INTERVAL + this->timeLag;
	}
	else {
		this->nextRead = now + PIRM_SCAN_INTERVAL;
	}
}

void PIRMotion<PIRMotionClient>::setLagAfterMotion(int secs) {
	this->timeLag = secs * 1000;
}

void PIRMotion<PIRMotionClient>::informClients() {
	for(int i=0; i<5; i++)
		this->client[i]->invokePMotCallback();
}
