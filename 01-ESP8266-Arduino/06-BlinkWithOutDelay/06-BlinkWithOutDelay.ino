#define INTERVAL 1000

int ledState = LOW;
long lastMillis = 0;

void setup() {
  pinMode(D3, OUTPUT);
}

void loop() {
  long currentMillis = millis();
  if(currentMillis - previousMillis > INTERVAL) {
    previousMillis = currentMillis;   
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
    digitalWrite(D3, ledState);
  }
}