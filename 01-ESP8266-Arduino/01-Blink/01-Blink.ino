void setup() {
  pinMode(D0,OUTPUT);
}

void loop() {
  digitalWrite(D0,1);
  delay(500);
  digitalWrite(D0,0);
  delay(500);
}
