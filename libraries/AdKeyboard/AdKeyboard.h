/*
 * by Ozan Oner
 * a library for:
 * http://www.cooking-hacks.com/adkeyboard-module
*/

#ifndef _ADKEYBOARD_H_
#define _ADKEYBOARD_H_

#include <Arduino.h>

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

class AdKeyboard {
public:
	// constructor
	AdKeyboard(int analogPort);

	// main method which does the job. use it in 'loop' function
	void update();

	// sets timeout value for long press
	void setPressTimeout(int val);

	// short press handler for button
	void setClickCallback(void (*callback)(int but));

	// long press handler for button
	void setPressCallback(void (*callback)(int but));

	// handler for two-button press at the same time.
	// but a button with a greater index must be pressed first to able to detect it
	// since lower-indexed button masks higher-indexed one.
	void setTwoPressCallback(void (*callback)(int but1, int but2));

private:
	int port; // analog port
	int pressTimeout; // timeout value for hold to change state from 'On'->'Pressed'
	int keyState[5]; // state holder for each key
	unsigned long lastTime; // last reading time 
	int lastVal; // last value 
	int handled; // if any callback executed 

	void (*clickCallback)(int but);
	void (*pressCallback)(int but);
	void (*twoPressCallback)(int but1, int but2);

	int getKey(int val);
};

#endif
