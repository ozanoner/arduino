
#include <Arduino.h>
#include <AdKeyboardClient.h>
#include <AdKeyboard.h>
#include "MyClient.h"
#include <ClientOwner.h>

AdKeyboard<AdKeyboardClient> kb(0);
AdKeyboardClient cl;
MyClient cl2;

void adClicked(int i) {
  Serial.print("adClicked: ");
  Serial.println(i);
}

void myClientClickHandler(int i) {
  Serial.print("myClientClickHandler: ");
  Serial.println(i);
}

void myClientPressHandler(int i) {
  Serial.print("myClientPressHandler: ");
  Serial.println(i);
}

void setup() {
 Serial.begin(9600);
 int id=kb.registerClient(&cl);
 cl.setClickCallback(adClicked);
 
 int id2=kb.registerClient(&cl2);
 cl2.setPressCallback(myClientPressHandler);
 cl2.setClickCallback(myClientClickHandler);
}

void loop() {
  kb.update();
}
