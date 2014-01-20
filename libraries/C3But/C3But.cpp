// C3But class implementation

#include "C3But.h"

C3But::C3But(int p1, int p2, int p3, unsigned long pressDur) {
	this->pinNum[0]=p1;
	this->pinNum[1]=p2;
	this->pinNum[2]=p3;
	this->pressDuration = pressDur>0? pressDur: C3BUT_DEFAULT_PRESSDUR;
}

C3But::C3But(int p1, int p2, int p3) {
	this->pinNum[0]=p1;
	this->pinNum[1]=p2;
	this->pinNum[2]=p3;
	this->pressDuration = C3BUT_DEFAULT_PRESSDUR;
}

void C3But::initialize() {
	this->pressCallback = NULL;
	this->twoPressCallback = NULL;
	for(int i=0; i<3; i++) {
		this->state[i]=C3BUT_OFF;
		this->pressTime[i]=0;
		if(pinNum[i]>2) {
			pinMode(pinNum[i], INPUT);
			digitalWrite(pinNum[i], HIGH);
		}
	}
}

void C3But::update() {
	unsigned long now = millis();

	int8_t pressed=-1;

	for(int i=0; i<3; i++) {
		if(pinNum[i]<3)
			continue;


		// pressed
		if(digitalRead(pinNum[i]) == LOW) {
			switch(this->state[i]) {
				case C3BUT_OFF:
					this->state[i] = C3BUT_PENDING;
					this->pressTime[i] = now;
					break;
				case C3BUT_ON:
					if((now-pressTime[i])>this->pressDuration) {
						this->state[i] = C3BUT_PRESSED;
						pressed=i;
					}
					break;
				case C3BUT_PENDING:
					if((now-pressTime[i])>C3BUT_DEBOUNCE_TIMEOUT) {
						this->state[i] = C3BUT_ON;
					}
					break;
				case C3BUT_PRESSED:
					break;
				default:
					break;
			}
		}
		else {
			switch(this->state[i]) {
				case C3BUT_OFF:
					this->pressTime[i] = 0;
					break;
				case C3BUT_PRESSED:
				case C3BUT_ON:
					this->pressTime[i] = 0;
					this->state[i]=C3BUT_OFF;
					break;
				case C3BUT_PENDING:
					if((now-pressTime[i])>C3BUT_DEBOUNCE_TIMEOUT) {
						this->pressTime[i] = 0;
						this->state[i]=C3BUT_OFF;
					}
					break;
				default:
					break;
			}
		}
	}

	if(pressed>=0) {
		int onBtn = getOnButton(pressed);
		if(onBtn>=0) {
			if(state[onBtn] == C3BUT_PRESSED && this->twoPressCallback != NULL) {
				this->twoPressCallback(this->pinNum[pressed], this->pinNum[onBtn]);
			}
		}
		else if(this->pressCallback != NULL) {
			this->pressCallback(this->pinNum[pressed]);
		}
	}
}

int8_t C3But::getOnButton(int skip) {
	for(int i=0; i<3; i++) {
		if(i == skip)
			continue;
		if(this->state[i] == C3BUT_ON || this->state[i] == C3BUT_PRESSED)
			return i;
	}
	return -1;
}

void C3But::setPressCallback(void (*callback)(int pinNum)) {
	this->pressCallback=callback;
}

void C3But::setTwoPressCallback(void (*callback)(int pinNum1, int pinNum2)) {
	this->twoPressCallback=callback;
}
