#define sw1 D1                 // Define D1 as switch pin
#define ledPin1 D3             // Define D3 as LED pin
int st_sw1 = 0;

void setup(){
  pinMode(ledPin1, OUTPUT);    // Set pin as output
  pinMode(sw1, INPUT);         // set pin as input
}

void loop(){
  if(digitalRead(sw1)){
    digitalWrite(ledPin1,0); 
  }
  else{
    digitalWrite(ledPin1,1);
  }
}
