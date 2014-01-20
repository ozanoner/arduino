/*
 * by Ozan Oner
 * implementation for AdKeyboard class
 * http://www.cooking-hacks.com/adkeyboard-module
*/

#include "AdKeyboard.h"

AdKeyboard::AdKeyboard(int analogPort) {
	this->port = analogPort;
	this->lastTime = 0;
	this->lastVal = 1023;
	this->handled = 0;
	this->clickCallback = NULL;
	this->pressCallback = NULL;
	this->twoPressCallback = NULL;
	this->pressTimeout = ADKEY_PRESS_TIMEOUT;
	for(int i=0; i<5; i++) {
		this->keyState[i]=0;
	}
}

void AdKeyboard::setPressTimeout(int val) {
	this->pressTimeout = val;
}

void AdKeyboard::update() {
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
					if(this->twoPressCallback != NULL)
						this->twoPressCallback(key, i);
					this->handled = 1;
					break;
				}
			}
			if(!this->handled) {
				if(this->pressCallback != NULL)
					this->pressCallback(key);
				this->handled =1;
			}
		}
	}
	else if(this->lastVal<1023) { // released
		// check for short press (click)
		if(!this->handled) {
			for(int i=0; i<5; i++) {
				if(this->keyState[i]==AdOn) {
					if(this->clickCallback!=NULL)
						this->clickCallback(i);
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

void AdKeyboard::setClickCallback(void (*callback)(int but)) {
	this->clickCallback = callback;
}

void AdKeyboard::setPressCallback(void (*callback)(int but)) {
	this->pressCallback = callback;
}

void AdKeyboard::setTwoPressCallback(void (*callback)(int but1, int but2)) {
	this->twoPressCallback = callback;
}

int AdKeyboard::getKey(int val) {
	for(int i=0; i<5; i++) {
		if(val<ADKEY_KEY_VALUE[i])
			return i;
	}
	return -1;
}
