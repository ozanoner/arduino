/*
 * by Ozan Oner
 * a library for keypad.
 * http://www.cooking-hacks.com/keypad-12-button
 */

#ifndef _KEYPAD2_H_
#define _KEYPAD2_H_

#include <Arduino.h>

// keypad scan interval
// update function is executed with this period
#define KP2_SCAN_INTERVAL 50

// key states
#define KP2_KEYUP 0
#define KP2_PENDING 1
#define KP2_KEYDOWN 2

// default layout for http://www.cooking-hacks.com/keypad-12-button
const char kp2DefaultLayout[4][3] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
// 2 bits for each key to store its state
// 12*2/8 = 3 bytes for default layout
const uint8_t kp2DefaultStateHolder[3] = {0, 0, 0};

const int kp2RowPins[4] = {2,3,4,5}; // connect to keypad pins 2,7,6,4 respectively
const int kp2ColPins[3] = {6,7,8};   // connect to keypad pins 3,1,5 respectively
// end of default layout

class Keypad2 {
public:
	// internal pullups are used if default layout is selected
	Keypad2(uint8_t useDefaultLayout);

	// initialize hardware layout, both keypad & arduino
	// if not called, default layout should be used in constructor
	// parameters:
	// 1- row count
	// 2- column count
	// 3- keypad layout
	// 4- key states (2 bits for each key)
	// 5- row pins
	// 6- column pins
	// 7- internal pullup usage (0 for external pullups. they must be connected to the rows)
	void setLayout(int rowc, int colc, char **layout, uint8_t *keyState, \
			int *rowp, int *colp, uint8_t useInternalPullup);

	// main method which does the job. use it in 'loop' function
	void update();

	// press handler for key
	void setPressCallback(void (*callback)(char keyChar, uint8_t updown));

	// show keyboard layout
	// dont forget Serial.begin() before
	void printLayout();
private:
	int rowc; // row count
	int colc; // column count
	char *layout; // keypad characters
	int *rowp; // row pins
	int *colp; // column pins
	uint8_t *keyState; // state pointer

	unsigned long nextTime; // last reading time

	// user provided press handler
	void (*pressCallback)(char keyChar, uint8_t state);

	// internal wrapper to call pressCallback
	void callPressCallback(int r, int c, uint8_t state);

	// filters state from keyState accd. to stateIdx
	uint8_t getKeyState(int stateIdx);
	// sets state on keyState
	void setKeyState(int stateIdx, uint8_t state);
};

#endif
