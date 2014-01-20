#define DEBUG
#include "PgmDebug.h"
#include <stdarg.h>




PDString(s1) = "progmem string1";
PDString(s2) = "progmem string2 %s";



void setup() {
  Serial.begin(9600);
  
  PDPrintlnParams(s2, "test");
  PDPrintln(s1);

  PDPrintParams(s2, "test");
  PDPrint(s1);

  Serial.println("setup completed");
//  PgmDebug::__PD_Print(s1);
}

void loop() {
  while(1);
}

