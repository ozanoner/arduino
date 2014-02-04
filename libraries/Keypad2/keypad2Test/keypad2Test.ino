
#include <Arduino.h>
#include <Keypad2.h>
#include <Keypad2Client.h>
#include <ClientOwner.h>
#include "MyClient.h"

Keypad2<Keypad2Client> kp(1);
Keypad2Client cl;
MyClient cl2;

void pressCallback(char c, uint8_t kstate) {
	Serial.print("pressCallback: ");
	Serial.print(c);
	Serial.println(kstate == KP2_KEYUP? "up":"down");
}

void setup() {
	Serial.begin(9600);
	kp.registerClient(&cl);
	cl.setPressCallback(pressCallback);
	kp.registerClient(&cl2);
}

void loop() {
	kp.update();
}

