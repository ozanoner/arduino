//This example shows how to use the Mux Shield for digital inputs
#include <MuxShield.h>

//Initialize the Mux Shield
MuxShield muxShield;

void setup()
{
    //Set IO1, IO2, and IO3 as digital inputs
    muxShield.setMode(1,DIGITAL_IN_PULLUP);
    //use DIGITAL_IN in place of DIGITAL_IN_PULLUP if internal pullups are not needed
    muxShield.setMode(2,DIGITAL_IN_PULLUP);
    muxShield.setMode(3,DIGITAL_IN_PULLUP);
    
    Serial.begin(28800);
}

//Arrays to store digital values
int IO1DigitalVals[16];
int IO2DigitalVals[16];
int IO3DigitalVals[16];

void loop()
{
  for (int i=0; i<16; i++)
  {
    //Digital read on all 16 inputs on IO1, IO2, and IO3
    IO1DigitalVals[i] = muxShield.digitalReadMS(1,i);
    IO2DigitalVals[i] = muxShield.digitalReadMS(2,i);
    IO3DigitalVals[i] = muxShield.digitalReadMS(3,i);
  }
  
  //Print IO 1 values for inspection
  Serial.print("IO1 analog values: ");
  for (int i=0; i<16; i++)
  {
    Serial.print(IO1DigitalVals[i]);
    Serial.print('\t');
  }
  Serial.println();
}
