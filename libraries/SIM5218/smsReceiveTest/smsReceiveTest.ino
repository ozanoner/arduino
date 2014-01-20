#include "SIM5218.h"

SIM5218 sim(&Serial);

void setup() {
  sim.initialize();

  Serial.println("calling wake up ..");
  if(sim.wakeup(60L*1000)) {
    Serial.println("wakeup failed");
  }
  else {
    Serial.println("ready");
    delay(3000);
    if(sim.waitNetworkReg(60L*1000)) {
      Serial.println("sim.waitNetworkReg(60*1000) failed");
      sim.printError(&Serial);
    }
    else if(sim.initializeSMS()) {
      Serial.println("sim.initializeSMS() failed");
      sim.printError(&Serial);
    } 
    else if(sim.querySMS(5000, 15000, smsCallback)) {
      Serial.println("sim.querySMS() failed");
      sim.printError(&Serial);
    }
  }

}

void loop() {
  sim.update();
}

void smsCallback(char *content, int csize, int8_t err) {
  if(err) {
    Serial.print("smsCallback: error: ");
    Serial.println(err);
    Serial.print("last message:");
    Serial.println(sim.getSMSBuffer());
    sim.printError(&Serial);
  } else {
    Serial.print("smsCallback: content received: ");
    Serial.println(content);
    sim.printError(&Serial);
  }
}

