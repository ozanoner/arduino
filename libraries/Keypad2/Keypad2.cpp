/*
 * by Ozan Oner
 * Keypad2 class implementation
 */

#include "Keypad2.h"

Keypad2::Keypad2(uint8_t useDefaultLayout) {
	this->pressCallback = NULL;
	this->nextTime =0;

	if(useDefaultLayout) {
		this->setLayout(4, 3, (char **)kp2DefaultLayout, (uint8_t *)kp2DefaultStateHolder, \
				(int *)kp2RowPins, (int *)kp2ColPins, 1);
	} 
};

void Keypad2::setLayout(int rowc, int colc, char **l, uint8_t *keyState, \
		int *rowp, int *colp, uint8_t useInternalPullup) {
	this->rowc = rowc;
	this->colc = colc;
	this->layout = (char *)l;
	this->keyState = keyState;
	this->rowp = rowp;
	this->colp = colp;

	// set row pins as INPUT
	for(int i=0; i<this->rowc; i++) {
		pinMode(this->rowp[i], INPUT);
		if(useInternalPullup)
			digitalWrite(this->rowp[i], HIGH); // set pullups
	}

	// set column pins as OUTPUT
	for(int i=0; i<this->colc; i++) {
		pinMode(this->colp[i], OUTPUT);
		digitalWrite(this->colp[i], HIGH); // set high on column pin
	}
	this->nextTime = millis()+KP2_SCAN_INTERVAL;
}

void Keypad2::setPressCallback(void (*callback)(char keyChar, uint8_t updown)) {
	this->pressCallback = callback;
}

void Keypad2::update() {
	if(millis() < this->nextTime)
		return;

	uint8_t state;

	for(int c=0, stateIdx=0; c<this->colc; c++) {
		// send LOW on the column, and check for LOW on every row
		digitalWrite(this->colp[c], LOW);

		for(int r=0; r<this->rowc; r++, stateIdx+=2) {
			// get state for key[r,c]
			state = this->getKeyState(stateIdx);
			// key[r,c] is not pressed
			if(digitalRead(this->rowp[r])) {
				if(state == KP2_KEYDOWN) 
					this->callPressCallback(r, c, KP2_KEYUP);
				if(state != KP2_KEYUP)
					this->setKeyState(stateIdx, KP2_KEYUP);
			}
			else { // pressed
				if(state == KP2_KEYUP) 
					this->setKeyState(stateIdx, KP2_PENDING);
				else if(state == KP2_PENDING) {
					this->setKeyState(stateIdx, KP2_KEYDOWN);
					this->callPressCallback(r, c, KP2_KEYDOWN);
				}
			}
		}

		// set column to HIGH again
		digitalWrite(this->colp[c], HIGH);
	}

	this->nextTime = millis()+KP2_SCAN_INTERVAL;
}

void Keypad2::callPressCallback(int r, int c, uint8_t updown) {
	// call press callback if exists
	if(this->pressCallback != NULL) {
		char keyChar = this->layout[r*this->colc+c];
		this->pressCallback(keyChar, updown);
	}
}

uint8_t Keypad2::getKeyState(int stateIdx) {
	uint8_t sb = this->keyState[stateIdx/8];
	int pos = stateIdx%8;
	return (sb>>pos)&0x03;
}

void Keypad2::setKeyState(int stateIdx, uint8_t state) {
	uint8_t *sb = this->keyState+stateIdx/8;
	int pos = stateIdx%8;
	bitWrite(*sb, pos, bitRead(state, 0));
	bitWrite(*sb, pos+1, bitRead(state, 1));
}

void Keypad2::printLayout() {
	Serial.println();
	Serial.print("row count: "); 
	Serial.print(this->rowc);
	Serial.print(" column count: ");
	Serial.println(this->colc);

	for(int r=0; r<this->rowc; r++) {
		for(int c=0; c<this->colc; c++) {
			Serial.print(this->layout[r*this->colc+c]);
			Serial.print(" ");
		}
		Serial.println();
	}
}
