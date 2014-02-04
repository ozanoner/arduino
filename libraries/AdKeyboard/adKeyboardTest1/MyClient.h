
#include "Arduino.h"
#include "AdKeyboardClient.h"

class MyClient: public AdKeyboardClient {
public:
	void invokeClickCallback(int b) {
		Serial.print("MyClient.invokeClickCallback: ");
		Serial.println(b);
	};
};
