int pirPin = 2; //digital 2
int dispPin = 3;

void setup(){
 Serial.begin(9600); 
 pinMode(pirPin, INPUT);
 pinMode(dispPin, OUTPUT);
}


void loop(){
  int pirVal = digitalRead(pirPin);

  if(pirVal == LOW){ //was motion detected
    Serial.println("Motion Detected"); 
	digitalWrite(dispPin, HIGH);
    delay(2000); 
  }
  else {
	digitalWrite(dispPin, LOW);
  }

}

