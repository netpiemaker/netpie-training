#include <WiFiManager.h>
#define ACCESSPOINT_NAME  "MyAccesspoint"

WiFiManager wifiManager;
int LEDPin=D0; 
int SWPin=D7; 

void setup(){
  pinMode(LEDPin, OUTPUT); 
  pinMode(SWPin, INPUT);
  Serial.begin(115200); 
  if(!digitalRead(SWPin)) {
    wifiManager.resetSettings(); 
  } 
  wifiManager.autoConnect(ACCESSPOINT_NAME);
  Serial.println("connected... :)"); 
  digitalWrite(LEDPin, HIGH); 
}

void loop(){
}
