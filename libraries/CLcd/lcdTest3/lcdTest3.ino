#include <SoftwareSerial.h>
#include "CLcd.h"

CLcd lcd(3,4);

char buffer[50];
int idx;

void setup() {
  lcd.initialize();
  Serial.begin(9600);
  idx=0;
}


void loop() {
  if(Serial.available()) {
    char c = Serial.read();
    if(c == '\n') {
      if(!strcmp(buffer, "clr")) {
        lcd.clr();
      } 
      else if(!strncmp(buffer, "go", 2)) {
        int pos = atoi(buffer+2);
        if(pos>=0)
          lcd.setCursor(pos);
      } 
      else {
        lcd.print(buffer);
      }
      idx=0;
      memset(buffer, 0, 50);
    }
    else {
      buffer[idx++]=c;
    }
  }
}
