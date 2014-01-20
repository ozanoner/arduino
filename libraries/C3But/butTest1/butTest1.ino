const int P1=3;
const int P2=4;
const int P3=5;

const int LEDPIN=13;

void setup() {
  Serial.begin(9600);
  pinMode(P1, INPUT);
  digitalWrite(P1, HIGH);
  pinMode(P2, INPUT);
  digitalWrite(P2, HIGH);
  pinMode(P3, INPUT);
  digitalWrite(P3, HIGH);
  
  
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  int8_t p=HIGH;
  p &= digitalRead(P1);
  p &= digitalRead(P2);
  p &= digitalRead(P3);

  digitalWrite(LEDPIN, p);
}
