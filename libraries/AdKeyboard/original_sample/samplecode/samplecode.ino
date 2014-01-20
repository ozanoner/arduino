//ADKeyboard Module
int adc_key_val[5] ={
  50, 200, 400, 600, 800 };
int NUM_KEYS = 5;
int adc_key_in;
int key=-1;
int oldkey=-1;
void setup()
{
  pinMode(13, OUTPUT);  //we'll use the debug LED to output a heartbeat
  Serial.begin(9600); // 9600 bps
}
void loop()
{
  adc_key_in = analogRead(0);    // read the value from the sensor 
  digitalWrite(13,LOW); 
  key = get_key(adc_key_in);  // convert into key press

  if (key != oldkey)   // if keypress is detected
  {
    delay(50);  // wait for debounce time
    adc_key_in = analogRead(0);    // read the value from the sensor 
    key = get_key(adc_key_in);    // convert into key press
    if (key != oldkey)    
    {   
      oldkey = key;
      Serial.print("val=");
      Serial.println(adc_key_in);

      if (key >=0){
        digitalWrite(13,HIGH);
        switch(key)
        {
        case 0:
          Serial.println("S1 OK");   
          break;
        case 1:
          Serial.println("S2 OK");   
          break;
        case 2:
          Serial.println("S3 OK");   
          break;
        case 3:
          Serial.println("S4 OK");   
          break;      
        case 4:
          Serial.println("S5 OK");   
          break;  
        }                
      }
    }
  }
  delay(100);
}
// Convert ADC value to key number
int get_key(unsigned int input)
{
  int k;
  for (k = 0; k < NUM_KEYS; k++)
  {
    if (input < adc_key_val[k])
    {
      return k;
    }
  }
  if (k >= NUM_KEYS)k = -1;  // No valid key pressed
  return k;
}
