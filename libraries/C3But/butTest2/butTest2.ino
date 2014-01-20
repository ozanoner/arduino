#include "C3But.h"

const int P1=5;
const int P2=6;
const int P3=7;

const int LEDPIN=13;

C3But btn(P1, P2, P3);

void setup() {
  Serial.begin(9600);
  btn.initialize();
  btn.setPressCallback(btnPressed);
  btn.setTwoPressCallback(twoBtnPressed);
}

void loop() {
  btn.update();
}

void btnPressed(int p1) {
  Serial.print("btnPressed:");
  Serial.println(p1);
}

void twoBtnPressed(int p1, int p2) {
  Serial.print("twoBtnPressed:");
  Serial.print(p1);
  Serial.println(p2);
}


