#include <SoftwareSerial.h>
#include "CLcd2.h"

CLcd2 lcd;

void setup() {
  delay(5000);
  
  lcd.initialize();
  
  for(int i=0; i<10; i++) {
    lcd.clr();
    lcd.setCursor(0);
    lcd.print(i);
    delay(2000);
  }
}

void loop() {
}
