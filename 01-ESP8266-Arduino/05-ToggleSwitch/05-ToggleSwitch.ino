#define SWPIN D1            // Define D1 as switch pin
#define LEDPIN D3           // Define D3 as LED pin

int buttonState = 0;
int ledState = 0;

void setup() {
  pinMode(LEDPIN, OUTPUT);  // Set pin as output
  pinMode(SWPIN, INPUT);    // set pin as input
}

void loop(){
  int  reading = digitalRead(SWPIN);
  if(buttonState != reading) {
      delay(100);
      buttonState=reading;
      if (buttonState == HIGH) {
          ledState = !ledState;
      }
   }
   digitalWrite(LEDPIN,ledState);
}
