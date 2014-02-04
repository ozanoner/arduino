/*
Ozan Oner
example for keypad library usage.
default keypad is: http://www.cooking-hacks.com/keypad-12-button
*/

#include <Keypad2.h>

/*
// custom layout for testing
char layout[4][3] = {
  {'A','B','C'},
  {'D','E','F'},
  {'G','I','J'},
  {'K','L','M'}
};
uint8_t stateHolder[3] = {0, 0, 0};

int rowpin[4] = {2,3,4,5}; // connect to keypad pins 2,7,6,4 respectively
int colpin[3] = {6,7,8};   // connect to keypad pins 3,1,5 respectively
*/

// custom keypad.
// to use this, uncomment layout definition and set it in setup
// Keypad2 kp(0);

// default keypad
Keypad2 kp(1);

void setup() {
	Serial.begin(9600);
	// setting custom layout
	// kp.setLayout(4, 3, (char **)layout, (uint8_t *)stateHolder, (int *)rowpin, (int *)colpin, 1);
	kp.setPressCallback(kpPressCallback);
	kp.printLayout();
}

void loop() {
	kp.update();
}

void kpPressCallback(char c, uint8_t state) {
	Serial.print(c);
	Serial.print(" ");
	Serial.print(state == KP2_KEYUP ? "up":"down");
	Serial.println();
}
