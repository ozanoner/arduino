/*
Ozan Oner
Library test for http://www.cooking-hacks.com/adkeyboard-module

Connections (ADKeyboard-Arduino)
VCC-5v
GND-GND
S-A0
*/

#include <Arduino.h>
#include <AdKeyboard.h>

AdKeyboard adKeyboard(0);

void setup() {
  Serial.begin(9600);
  adKeyboard.setClickCallback(clickHandler);  
  adKeyboard.setPressCallback(pressHandler);  
  adKeyboard.setTwoPressCallback(twoPressHandler);  
}

void loop() {
  adKeyboard.update();
}

void clickHandler(int key) {
  Serial.print("clickHandler: ");
  Serial.println(key);
}

void pressHandler(int key) {
  Serial.print("pressHandler: ");
  Serial.println(key);
}

void twoPressHandler(int k1, int k2) {
  Serial.print("twoPressHandler: ");
  Serial.print(k1);
  Serial.print(" ");
  Serial.println(k2);
}

