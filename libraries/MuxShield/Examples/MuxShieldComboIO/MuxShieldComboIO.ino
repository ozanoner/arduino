/*This example shows how to use the Mux Shield for a combination of 
analog inputs, digital inputs, and digital outputs.
*/
#include <MuxShield.h>

//Initialize the Mux Shield
MuxShield muxShield;

void setup()
{
  muxShield.setMode(1,DIGITAL_IN_PULLUP);  //set I/O 1 as digital in with pullup
  muxShield.setMode(2,DIGITAL_OUT);        //set I/O 2 as digital output
  muxShield.setMode(3,ANALOG_IN);          //set I/O 3 as analog input
  
  Serial.begin(28800);
}
//Arrays to store input values
int digital1, digital2;
int analog1, analog2;

void loop()
{
  //Sample a few inputs from IO1
  digital1 = muxShield.digitalReadMS(1,0);  //IO1, pin 0
  digital2 = muxShield.digitalReadMS(1,1);  //IO1, pin 1
  
  //Set a few outputs on IO2
  muxShield.digitalWriteMS(2,2,HIGH);  //IO2, pin 2
  muxShield.digitalWriteMS(2,3,HIGH);  //IO2, pin 3
  
  //Read analog inputs on IO3
  analog1 = muxShield.analogReadMS(3,14);  //IO3, pin 14
  analog2 = muxShield.analogReadMS(3,15);  //IO1, pin 15
  
  //Print the results
  Serial.print("digital1: ");Serial.print(digital1);Serial.print('\t');
  Serial.print("digital2: ");Serial.print(digital2);Serial.print('\t');
  Serial.print("analog1: ");Serial.print(analog1);Serial.print('\t');
  Serial.print("analog2: ");Serial.print(analog2);Serial.println();
  
}
  
