
/*
 * by Ozan Oner
 *
 * unified input device.
 * matrix keypad & adkeyboard
 */


#ifndef _MFK_INPUTDEVICE_H_
#define _MFK_INPUTDEVICE_H_


#include "Arduino.h"
#include "MFK_Pins.h"
#include "Keypad2.h"
#include "AdKeyboard.h"
#include "MFK_InputDeviceClient.h"
#include "ClientOwner.h"


#define IDLE_INTERVAL 60000  // in ms (1mins)

// keys & values
#define KEY_0 '0'
#define KEY_1 '1'
#define KEY_2 '2'
#define KEY_3 '3'
#define KEY_4 '4'
#define KEY_5 '5'
#define KEY_6 '6'
#define KEY_7 '7'
#define KEY_8 '8'
#define KEY_9 '9'

#define KEY_ENTER 0x0D // '#' from keypad
#define KEY_ESC   0x1B // '*' from keypad
#define KEY_BS    0x08 // btn1 from adkeyboard

#define KEY_F1 0x80  // btn2 from adkeyboard
#define KEY_F2 0x81  // btn3 from adkeyboard
#define KEY_F3 0x82  // btn4 from adkeyboard
#define KEY_F4 0x83  // btn5 from adkeyboard

// connect to keypad pins 2,7,6,4 respectively
const int MFK_RowPins[4] = \
	{MFK_KP_R0, MFK_KP_R1, MFK_KP_R2, MFK_KP_R3}; 
// connect to keypad pins 3,1,5 respectively
const int MFK_ColPins[3] = \
	{MFK_KP_C0, MFK_KP_C1, MFK_KP_C2}; 

const char MFK_KeypadLayout[4][3] = {
  	{'1','2','3'},
  	{'4','5','6'},
  	{'7','8','9'},
  	{KEY_ESC,'0',KEY_ENTER}
};



template<class T> class MFK_InputDevice;

template<>
class MFK_InputDevice<MFK_InputDeviceClient>:\
		public ClientOwner<MFK_InputDeviceClient>,\
		public AdKeyboardClient,\
	  	public Keypad2Client {
private:
	Keypad2<Keypad2Client> *keypad; // initialized in constructor
	AdKeyboard<AdKeyboardClient> *adKeyboard; // connected to analog0

	// to detect idle
	unsigned long lastKeypress;

	void keypadKeypressHandler(char key, uint8_t updown);
	void adkeyboardClickHandler(int i);

	void informClients(char);
public:
	MFK_InputDevice();
	// update in loop
	void update() {
		this->keypad->update();
		this->adKeyboard->update();
	};
	// checks if any user interaction exists
	uint8_t isIdle();

	// overrides AdKeyboardClient.invokeAdClickCallback
	void invokeAdClickCallback(int b) {
		this->adkeyboardClickHandler(b);
	};
	// overrides Keypad2Client.invokeKp2PressCallback
	void invokeKp2PressCallback(char key, uint8_t kstate) {
		this->keypadKeypressHandler(key, kstate);
	};
};

uint8_t mfkIsPrintable(char);

#endif
