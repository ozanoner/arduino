#include <Arduino.h>
#include <AdKeyboard.h>
#include <AdKeyboardClient.h>
#include <Keypad2.h>
#include <Keypad2Client.h>
#include <ClientOwner.h>
#include <MFK_InputDevice.h>
#include <MFK_InputDeviceClient.h>
#include <SoftwareSerial.h>
#include <SerialLcd.h>

#include <Timer.h>
#include <SignalController.h>
#include <SignalPattern.h>
#include <BuzzerSignalSource.h>
#include <LedSignalSource.h>
#include <PIRMotion.h>

#include <ContentFactory.h>
#include <Book.h>
#include <Chapter.h>
#include <Menu.h>
#include <Page.h>
#include <ContentProvider.h>
#include <VisualItem.h>

MFK_InputDevice<MFK_InputDeviceClient> inp;
MFK_InputDeviceClient cl;

MFK_OutputDevice *outp;

void setup() {
	Serial.begin(9600);
	inp.registerClient(&cl);
	cl.setKeyPressCallback(keyPressHandler);
	SoftwareSerial *ss = new SoftwareSerial(9,10);
	outp = new MFK_OutputDevice(ss);
	ss->begin(9600);
}

void loop() {
	inp.update();
}

void keyPressHandler(char c) {
	if(mfkIsPrintable(c)) {
		Serial.println(c);
		outp->write(c);
	}
	else {
          switch(c) {
            case KEY_ENTER:
              Serial.println("KEY_ENTER");
			  outp->print("KEY_ENTER", 1);
              break;
            case KEY_ESC:
              Serial.println("KEY_ESC");
			  outp->print("KEY_ESC", 1);
              break;
            case KEY_BS:
              Serial.println("KEY_BS");
			  outp->del();
              break;
            case KEY_F1:
              Serial.println("KEY_F1");
			  outp->print("KEY_F1", 1);
              break;
            case KEY_F2:
              Serial.println("KEY_F2");
			  outp->print("KEY_F2", 1);
              break;
            case KEY_F3:
              Serial.println("KEY_F3");
			  outp->print("KEY_F3", 1);
              break;
            case KEY_F4:
              Serial.println("KEY_F4");
			  outp->print("KEY_F4", 1);
              break;

          }
        }
}

