/*
 * by Ozan Oner
 * PIRMotion class implementation
 */

#include <Arduino.h>
#include "PIRMotion.h"

PIRMotion<PIRMotionClient>::PIRMotion(int pin, uint8_t useInternalPullup): \
		ClientOwner<PIRMotionClient>() {
	this->pin = pin;
	pinMode(pin, INPUT);
	if(useInternalPullup)
		digitalWrite(pin, HIGH); // set pullup 

	this->nextRead = 0;
	this->nextReport = 0;
	this->timeLag = 60000;
	this->reportState = 1;
	this->reportInterval = PIRM_SCAN_INTERVAL;
}

void PIRMotion<PIRMotionClient>::update() {
	unsigned long now = millis();
	if(this->nextRead<now) {
		if(digitalRead(this->pin)==LOW && this->reportState>0) {
			this->reportState++;
		}
		this->nextRead = now + PIRM_SCAN_INTERVAL;
	}
	if(this->nextReport<now) {
		if(this->reportState>1) {
			this->informClients();
		}
		now = millis();
		Serial.print(F("timelag: ")); Serial.println(this->timeLag);
		Serial.print(F("reportState: ")); Serial.println(this->reportState);
		if(this->timeLag>0 && this->reportState>1) {
			this->nextReport = now+this->timeLag+this->reportInterval;
			this->reportState=0;
			Serial.print(F("pir reporting disabled: "));
			Serial.println(now);
		}
		else {
			this->nextReport = now + this->reportInterval;
			this->reportState=1;
			Serial.print(F("pir reporting enabled: "));
			Serial.println(now);
		}
	}
}

void PIRMotion<PIRMotionClient>::informClients() {
	for(int i=0; i<5; i++) {
		if(this->client[i]!=NULL)
			this->client[i]->invokePMotCallback();
	}
}
