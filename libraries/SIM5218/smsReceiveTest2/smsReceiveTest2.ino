#include "SIM5218.h"

SIM5218 sim(&Serial);

void setup() {
  sim.initialize();

  Serial.println("calling wake up ..");
  if(sim.wakeup(60L*1000)) {
    Serial.println("wakeup failed");
  } 
  else if(sim.waitNetworkReg(60L*1000)) {
    Serial.println("sim.waitNetworkReg(60*1000) failed");
    sim.printError(&Serial);
  }
  /*
  else if(sim.initializeSMS()) {
    Serial.println("sim.initializeSMS() failed");
    sim.printError(&Serial);
  } 
  */
  else {
    int ret = 0;
    
    ret = sim.sendCmd("AT+CPMS=\"SM\",\"SM\",\"SM\"", "OK", 2000);
    if(ret)
      Serial.println(">>AT+CPMS=\"SM\",\"SM\",\"SM\" failed");
    sim.printError(&Serial);
    delay(1000);
    
    ret = sim.sendCmd("AT+CMGF=1", "OK", 2000);
    if(ret)
      Serial.println(">>AT+CMGF=1 failed");
    sim.printError(&Serial);
    delay(10000);
    
    ret = sim.sendCmd("AT+CMGR=1", "OK", 2000);
    if(ret)
      Serial.println(">>AT+CMGR=1 failed");
    sim.printError(&Serial);
  }
}

void loop() {
}

