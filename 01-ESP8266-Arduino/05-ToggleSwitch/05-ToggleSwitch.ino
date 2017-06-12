#define sw1 D1               // Define D1 as switch pin
#define ledPin1 D3           // Define D3 as LED pin
int buttonState=0;
int ledState=0;

void setup() {
  pinMode(ledPin1, OUTPUT);  // Set pin as output
  pinMode(sw1, INPUT);       // set pin as input
}

void loop(){
  int  reading = digitalRead(sw1);
  if(buttonState != reading) {
      delay(100);
      buttonState=reading;
      if (buttonState == HIGH) {
          ledState = !ledState;
      }
   }
   digitalWrite(ledPin1,ledState);
}
