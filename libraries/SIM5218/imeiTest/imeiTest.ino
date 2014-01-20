#include "SIM5218.h"

SIM5218 sim(&Serial);

void setup() {
  sim.initialize();

  Serial.println("calling wake up ..");
  if(sim.wakeup(60*1000)) {
    Serial.println("wakeup failed");
  }
  else {
    
    sim.readIMEI();
    sim.printError(&Serial);
    

    /*    
    sim.setIMEI("358246020052780");
    sim.printError(&Serial);
    */
  }
}

void loop() {
  while(1) {};
}
