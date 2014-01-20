/*
 * by Ozan Oner
 * SerialLcd library test
 */



#include <SoftwareSerial.h>
#include <SerialLcd.h>


SoftwareSerial ss(3,4);
SerialLcd lcd(&ss);

void setup() {
	ss.begin(9600);
  
	lcd.clr();
	lcd.println("first line");
	lcd.println("second line");
	delay(3000);

	lcd.clr();
	lcd.print("setCursorPos(20)");
	lcd.setCursorPos(20);
	lcd.print("X");
	delay(3000);

	lcd.clr();
	lcd.println("sendChar(0xF7)");
	lcd.sendChar(0xF7);
	delay(3000);

	lcd.clr();
	lcd.println("moveCursor");
	for(int i=0; i<3; i++) {
		lcd.moveCursor(SL_DIRECTION_RIGHT);
		lcd.print("R");
		delay(1000);
	}
	for(int i=0; i<3; i++) {
		lcd.moveCursor(SL_DIRECTION_LEFT);
		lcd.print("L");
		delay(1000);
	}

	lcd.clr();
	lcd.println("showUnderlineCursor");
	lcd.showUnderlineCursor(1);
	delay(3000);
	lcd.showUnderlineCursor(0);

	lcd.clr();
	lcd.println("showBlinkCursor");
	lcd.showBlinkCursor(1);
	delay(3000);
	lcd.showBlinkCursor(0);

	lcd.clr();
	lcd.println("scrollScreen");
	lcd.println("second line");
	for(int i=0; i<3; i++) {
		lcd.scrollScreen(SL_DIRECTION_RIGHT);
		delay(1000);
	}
	for(int i=0; i<3; i++) {
		lcd.scrollScreen(SL_DIRECTION_LEFT);
		delay(1000);
	}

	lcd.clr();
	lcd.println("displayOn(0) for 3 secs");
	delay(3000);
	lcd.displayOn(0);
	delay(3000);
	lcd.displayOn(1);

	lcd.clr();
	lcd.print("toggleSplash next start");
	lcd.toggleSplash();
	delay(3000);

	lcd.clr();
	lcd.print("> tests completed!");
}

void loop() {
}
