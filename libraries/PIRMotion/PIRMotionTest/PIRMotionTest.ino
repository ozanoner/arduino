/*
  by Ozan Oner
  PIRMotion class test
*/

#define LED_PIN 3

// include library
#include <PIRMotion.h>
#include <PIRMotionClient.h>
#include <ClientOwner.h>
// connected to digital2, use internal pullup
PIRMotion<PIRMotionClient> pirm(2, 1); 
PIRMotionClient cl;

void setup() {
	Serial.begin(9600);
	pinMode(LED_PIN, OUTPUT);

	// pirm.setLagAfterMotion(5);

	pirm.registerClient(&cl);
	cl.setCallback(pirmCallback);
}

void loop() {
	pirm.update();
}

void pirmCallback(void) {
	Serial.println("motion");
	digitalWrite(LED_PIN, HIGH);
	delay(1000);
	digitalWrite(LED_PIN, LOW);
}
