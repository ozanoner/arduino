/*
 * by Ozan Oner
 * a library for:
 * http://www.cooking-hacks.com/adkeyboard-module
*/

#ifndef _ADKEYBOARD_H_
#define _ADKEYBOARD_H_

#include "Arduino.h"
#include "AdKeyboardClient.h"
#include "ClientOwner.h"

// timeout for long press
#define ADKEY_PRESS_TIMEOUT 2000

// limits for button readings
// each button gives a value below its corresponding entry
const int ADKEY_KEY_VALUE[] = {50, 200, 400, 600, 800};

// internal states of buttons
enum AdStateEnum {
	AdOff,      // released
	AdPending,  // in debounce interval
	AdOn,       // pressed, duration <= this->pressTimeout
	AdPressed   // pressed, duration > this->pressTimeout
};

// template declaration
template<class T> class AdKeyboard;

// specialized definition
template<>
class AdKeyboard<AdKeyboardClient>: public ClientOwner<AdKeyboardClient> {
public:
	// constructor
	AdKeyboard(int analogPort);

	// main method which does the job. use it in 'loop' function
	void update();

	// sets timeout value for long press
	void setPressTimeout(int val);

private:
	int port; // analog port
	int pressTimeout; // timeout value for hold to change state from 'On'->'Pressed'
	int keyState[5]; // state holder for each key
	unsigned long lastTime; // last reading time 
	int lastVal; // last value 
	int handled; // if any callback executed 

	int getKey(int val);

	void informClick(int);
	void informPress(int);
	void informTwoPress(int, int);
};

#endif
