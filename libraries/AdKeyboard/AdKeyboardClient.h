
#ifndef _ADKEYBOARD_CLIENT_H_
#define _ADKEYBOARD_CLIENT_H_

#include "Arduino.h"

// you can directy set a callback 
// or derive a subclass overriding invoke functions
class AdKeyboardClient {
public:
	AdKeyboardClient() { };
	
	// short press handler for button
	void setClickCallback(void (*cb)(int)) {
		this->clickCallback=cb;
	};
	// called by AdKeyboard
	// you can override it within sub-classes
	virtual void invokeAdClickCallback(int i) {
		if(this->clickCallback!=NULL)
			this->clickCallback(i);
	};

	// long press handler for button
	void setPressCallback(void (*cb)(int)) {
		this->pressCallback=cb;
	};
	virtual void invokeAdPressCallback(int i) {
		if(this->pressCallback!=NULL)
			this->pressCallback(i);
	};

	// handler for two-button press at the same time.
	// but a button with a greater index must be pressed first to able to detect it
	// since lower-indexed button masks higher-indexed one.
	void setTwoPressCallback(void (*cb)(int, int)) {
		this->twoPressCallback=cb;
	};
	virtual void invokeAdTwoPressCallback(int b1, int b2) {
		if(this->twoPressCallback!=NULL)
			this->twoPressCallback(b1, b2);
	};
protected:
	void (*clickCallback)(int);
	void (*pressCallback)(int);
	void (*twoPressCallback)(int, int);

};

#endif
