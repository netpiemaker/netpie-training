#define SWPIN   D1                 // Define D1 as switch pin
#define LEDPIN  D3             // Define D3 as LED pin
int st_sw1 = 0;

void setup(){
  pinMode(ledPin1, OUTPUT);    // Set pin as output
  pinMode(sw1, INPUT);         // set pin as input
}

void loop(){
  if(digitalRead(SWPIN)){
    digitalWrite(LEDPIN,0); 
  }
  else{
    digitalWrite(LEDPIN,1);
  }
}
