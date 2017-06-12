int interval1,interval2;
bool S1=0,S2=0;

void setup() {
  pinMode(D0,OUTPUT);
  pinMode(D4,OUTPUT);
  interval1=millis();
  interval2=millis();
}

void loop() {
  //blinking D0 at 500ms interval
  if (millis()>interval1+500){
      interval1=millis();
    if(S1) {
      digitalWrite(D0,HIGH);
      S1=0;
    }
    else{
      digitalWrite(D0,LOW);
      S1=1;
    }
  }

  //blinking D4 at 1000ms interval
  if (millis()>interval2+1000) {
    interval2=millis();
    if(S2){digitalWrite(D4,HIGH);S2=0;}
    else {
      digitalWrite(D4,LOW);
      S2=1;
    }
  }
}
