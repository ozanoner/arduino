

#include "MFK_InputDevice.h"

MFK_InputDevice<MFK_InputDeviceClient>::MFK_InputDevice(): \
		ClientOwner<MFK_InputDeviceClient>() {
	this->keypad = new Keypad2<Keypad2Client>(0);
	this->keypad->setLayout(4,3, (char**)MFK_KeypadLayout, \
			(uint8_t*)kp2DefaultStateHolder, (int*)MFK_RowPins, \
			(int*)MFK_ColPins, 1);
	this->keypad->registerClient(this);

	this->adKeyboard = new AdKeyboard<AdKeyboardClient>(MFK_ADKEYBOARD_PIN);
	this->adKeyboard->registerClient(this);
	this->lastKeypress=0;
}


void MFK_InputDevice<MFK_InputDeviceClient>::keypadKeypressHandler(char key,\
		uint8_t updown) {
	if(updown!=KP2_KEYUP)
		return;
	this->informClients(key);
}

void MFK_InputDevice<MFK_InputDeviceClient>::adkeyboardClickHandler(int i) {
	// Serial.println(i);
	if(i==0)
		this->informClients(KEY_BS);
	else 
		this->informClients((char)(KEY_F1+(byte)i-1));
}

uint8_t MFK_InputDevice<MFK_InputDeviceClient>::isIdle() {
	return (millis()-this->lastKeypress)>IDLE_INTERVAL? 1:0;
}

void MFK_InputDevice<MFK_InputDeviceClient>::informClients(char c) {
	this->lastKeypress = millis();
	for(int i=0; i<5; i++) {
		if(this->client[i]!=NULL)
			this->client[i]->invokeMFKInputCallback(c);
	}
}

uint8_t mfkIsPrintable(char c) {
	return (c<KEY_0 || c>KEY_9)? 0:1;
}
