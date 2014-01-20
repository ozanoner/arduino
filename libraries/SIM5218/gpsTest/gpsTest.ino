#include "SIM5218.h"

SIM5218 sim(&Serial);

void setup() {
  sim.initialize();

  Serial.println("calling wake up ..");
  if(sim.wakeup(60*1000)) {
    Serial.println("wakeup failed");
  }
  else if(sim.startGPS()) {
    sim.printError(&Serial);
  }
  else if(sim.queryGPS(5000, 10000, GPSCallback)) {
    sim.printError(&Serial);
  }

}

void loop() {
  sim.update();
}


void GPSCallback(float n, float e, int8_t err) {
  if(err) {
    sim.printError(&Serial);
  }
  else {
    Serial.print("north: ");
    Serial.print(n, 6);
    Serial.print("east: ");
    Serial.println(e, 6);
  }
}


