/*
 * by Ozan Oner
 *
 * base class for MFK_InputDevice clients
 */

#ifndef _MFK_InputDeviceClient_H_
#define _MFK_InputDeviceClient_H_


class MFK_InputDeviceClient {
public:
	MFK_InputDeviceClient() {};
	void setKeyPressCallback(void (*cb)(char)) {
		this->keyPressCallback=cb;
	};
	virtual void invokeMFKInputCallback(char c) {
		if(this->keyPressCallback!=NULL)
			this->keyPressCallback(c);
	};
protected:
	void (*keyPressCallback)(char);
};


#endif
