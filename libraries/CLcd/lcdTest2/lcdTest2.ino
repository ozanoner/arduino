#include <SoftwareSerial.h>

SoftwareSerial lcd(2, 3);

void setup()
{
  Serial.begin(9600);  // start serial monitor serial
  lcd.begin(9600);  // start lcd serial
}

void loop()
{
  while(Serial.available())  // If serial data is available do this
    lcd.print((char) Serial.read());
}
