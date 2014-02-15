/*
 * by Ozan Oner
 * base class for Keypad2 clients
 */

#ifndef _KEYPAD2_CLIENT_H_
#define _KEYPAD2_CLIENT_H_

class Keypad2Client {
public:
	Keypad2Client() { };

	void setPressCallback(void (*cb)(char, uint8_t)) {
		this->pressCallback=cb;
	};

	virtual void invokeKp2PressCallback(char i, uint8_t kstate) {
		if(this->pressCallback!=NULL)
			this->pressCallback(i, kstate);
	};

protected:
	void (*pressCallback)(char, uint8_t);
};

#endif
