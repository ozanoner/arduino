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

void setup() {
	Serial.begin(9600);
	inp.registerClient(&cl);
	cl.setKeyPressCallback(keyPressHandler);
}

void loop() {
	inp.update();
}

void keyPressHandler(char c) {
	if(mfkIsPrintable(c))
		Serial.println(c);
	else {
          switch(c) {
            case KEY_ENTER:
              Serial.println("KEY_ENTER");
              break;
            case KEY_ESC:
              Serial.println("KEY_ESC");
              break;
            case KEY_BS:
              Serial.println("KEY_BS");
              break;
            case KEY_F1:
              Serial.println("KEY_F1");
              break;
            case KEY_F2:
              Serial.println("KEY_F2");
              break;
            case KEY_F3:
              Serial.println("KEY_F3");
              break;
            case KEY_F4:
              Serial.println("KEY_F4");
              break;

          }
        }
}

