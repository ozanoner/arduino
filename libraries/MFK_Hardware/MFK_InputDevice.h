
/*
 * Facade pattern.
 * AdKeyboard and Keypad2 are hidden for the clients.
 *
 * Observer pattern.
 * clients registers/unregisters to MFK_InputDevice and
 * MFK_InputDevice informs them when an input comes.
 */


#ifndef _MFK_INPUTDEVICE_H_
#define _MFK_INPUTDEVICE_H_


#include "Arduino.h"
#include "Keypad2.h"
#include "AdKeyboard.h"
#include "MFK_InputDeviceClient.h"
#include "ClientOwner.h"


#define MFK_ADKEYBOARD_PIN 0

#define IDLE_INTERVAL 300000 // 5 minutes

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

const char MFK_KeypadLayout[4][3] = {
  	{'1','2','3'},
  	{'4','5','6'},
  	{'7','8','9'},
  	{KEY_ESC,'0',KEY_ENTER}
};



template<class T> class MFK_InputDevice;

template<>
class MFK_InputDevice<MFK_InputDeviceClient>: public AdKeyboardClient, 
	  public Keypad2Client, public ClientOwner<MFK_InputDeviceClient> {
private:
	Keypad2<Keypad2Client> *keypad; // initialized in constructor
	AdKeyboard<AdKeyboardClient> *adKeyboard; // connected to analog0

	unsigned long lastKeypress;

	void keypadKeypressHandler(char key, uint8_t updown);
	void adkeyboardClickHandler(int i);

	void informClients(char);

public:
	MFK_InputDevice();
	void update() {
		this->keypad->update();
		this->adKeyboard->update();
	};
	uint8_t isIdle();

	void invokeAdClickCallback(int b) {
		this->adkeyboardClickHandler(b);
	};
	void invokeKp2PressCallback(char key, uint8_t kstate) {
		this->keypadKeypressHandler(key, kstate);
	};
};

uint8_t mfkIsPrintable(char);

#endif
