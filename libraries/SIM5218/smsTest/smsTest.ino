#include "PgmDebug.h"
#include "SIM5218.h"


SIM5218 sim(&Serial1);

void setup() {
  Serial.begin(19200);
  sim.initialize();

  Serial.println("calling wake up ..");
  if(sim.wakeup(60L*1000)) {
    Serial.println("wakeup failed");
  }
  else if(sim.waitNetworkReg(60L*1000)) {
    Serial.println("sim.waitNetworkReg(60*1000) failed");
  }
  /*
  else if(sim.setSMSMessFmt(SIM5218_SMS_MESS_FMT_TEXT)) {
    Serial.println("sim.setSMSMessFmt(SIM5218_SMS_MESS_FMT_TEXT) failed");
  }
  */
  else if(sim.initializeSMS()) {
    Serial.println("sim.initializeSMS failed");
//    sim.printError(&Serial);
  }
  else if(sim.sendSMS("05332101466", "test")) {
  //  sim.printError(&Serial);
    Serial.println("sim.sendSMS failed");
  }
  else {
    Serial.println("success");
  }


}

void loop() {
  while(1);
}
