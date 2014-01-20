//This example shows how to use the Mux Shield for digital outputs
#include <MuxShield.h>

//Initialize the Mux Shield
MuxShield muxShield;

void setup()
{
    //Set I/O 1, I/O 2, and I/O 3 as digital outputs
    muxShield.setMode(1,DIGITAL_OUT);  
    muxShield.setMode(2,DIGITAL_OUT);
    muxShield.setMode(3,DIGITAL_OUT);
}

int toggle = LOW;

void loop()
{
  //loop to toggle all IO 1 outputs
  for (int i=0; i<16; i++)
  {
    muxShield.digitalWriteMS(1,i,toggle);
    delay(100);
  }
  
  //loop to toggle all IO 2 outputs
  for (int i=0; i<16; i++)
  {
    muxShield.digitalWriteMS(2,i,toggle);
    delay(100);
  }
  
  //loop to toggle all IO 3 outputs
  for (int i=0; i<16; i++)
  {
    muxShield.digitalWriteMS(3,i,toggle);
    delay(100);
  }
  delay(1000);
  
  //flip the toggle
  if (toggle == LOW)
    toggle = HIGH;
  else
    toggle = LOW;

}
