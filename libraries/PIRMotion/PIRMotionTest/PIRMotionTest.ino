/*
  by Ozan Oner
  PIRMotion class test
*/

#define LED_PIN 3

// include library
#include <PIRMotion.h>
// connected to digital2, use internal pullup
PIRMotion pirm(2, 1); 

void setup() {
	Serial.begin(9600);
	pirm.setMotionCallback(pirmCallback);
	pinMode(LED_PIN, OUTPUT);

	// pirm.setLagAfterMotion(5);
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
