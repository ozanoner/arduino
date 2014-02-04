

#include "Keypad2Client.h"

class MyClient: public Keypad2Client {
public:
	void invokeKp2PressCallback(char i, uint8_t kstate) {
		Serial.print("invokeKp2PressCallback: ");
		Serial.println(i);
	}
};
