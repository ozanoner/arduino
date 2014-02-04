/*
 * by Ozan Oner
 * implementation for AdKeyboard class
 * http://www.cooking-hacks.com/adkeyboard-module
*/

#include "AdKeyboard.h"

AdKeyboard<AdKeyboardClient>::AdKeyboard(int analogPort): ClientOwner<AdKeyboardClient>() {
	this->port = analogPort;
	this->lastTime = 0;
	this->lastVal = 1023;
	this->handled = 0;
	this->pressTimeout = ADKEY_PRESS_TIMEOUT;
	for(int i=0; i<5; i++) {
		this->keyState[i]=0;
	}
}

void AdKeyboard<AdKeyboardClient>::setPressTimeout(int val) {
	this->pressTimeout = val;
}

void AdKeyboard<AdKeyboardClient>::update() {
	unsigned long now = millis();
	unsigned long interval = now - this->lastTime;
	
	// debounce handling
	if(interval <50) { 
		return;
	}

	int val = analogRead(this->port);

	// a button pressed
	if(val<1023) {
		// skips when press has already been handled
		if(this->handled)
			return;

		// get which key is pressed
		int key = this->getKey(val);

		// unexpected key reading
		if(key<0)
			return;

		// set state
		switch(this->keyState[key]) {
			case AdOff:
				this->keyState[key] = AdPending;
				this->lastTime = now;
				break;
			case AdPending:
				this->keyState[key] = AdOn;
				this->lastTime = now;
				break;
			case AdOn:
				if(interval>this->pressTimeout) {
					this->keyState[key] = AdPressed;
					this->lastTime = now;
				}
				break;
			default:
				break;
		}

		// call handler
		if(this->keyState[key] == AdPressed) {
			for(int i=0; i<5; i++) {
				if(i==key)
					continue;
				if(this->keyState[i] == AdOn)
				{
					this->informTwoPress(key, i);
					this->handled = 1;
					break;
				}
			}
			if(!this->handled) {
				this->informPress(key);
				this->handled =1;
			}
		}
	}
	else if(this->lastVal<1023) { // released
		// check for short press (click)
		if(!this->handled) {
			for(int i=0; i<5; i++) {
				if(this->keyState[i]==AdOn) {
					this->informClick(i);
					break;
				}
			}
		}
		// reset states & other variables
		for(int i=0; i<5; i++) {
			this->keyState[i] = AdOff;
		}
		this->handled = 0;
		this->lastTime = 0;
	}

	// store last analog reading
	this->lastVal = val;
}

int AdKeyboard<AdKeyboardClient>::getKey(int val) {
	for(int i=0; i<5; i++) {
		if(val<ADKEY_KEY_VALUE[i])
			return i;
	}
	return -1;
}

void AdKeyboard<AdKeyboardClient>::informClick(int b) {
	for(int i=0; i<5; i++) {
		if(this->client[i]!=NULL)
			this->client[i]->invokeAdClickCallback(b);
	}
}

void AdKeyboard<AdKeyboardClient>::informPress(int b) {
	for(int i=0; i<5; i++) {
		if(this->client[i]!=NULL)
			this->client[i]->invokeAdPressCallback(b);
	}
}

void AdKeyboard<AdKeyboardClient>::informTwoPress(int b1, int b2) {
	for(int i=0; i<5; i++) {
		if(this->client[i]!=NULL)
			this->client[i]->invokeAdTwoPressCallback(b1, b2);
	}
}
