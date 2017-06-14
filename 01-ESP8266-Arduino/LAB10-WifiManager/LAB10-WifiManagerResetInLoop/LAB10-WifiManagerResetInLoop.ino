#include <ESP8266WiFi.h>         
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#define ACCESSPOINT_NAME  "MyAccesspoint"

WiFiManager wifiManager;
int LEDPIN = D3;
int SWPIN  = D1;
int lastTimeReset = 0;
int timeout = 10000;

void setup(){
  pinMode(LEDPIN, OUTPUT);
  pinMode(SWPIN, INPUT);
  Serial.begin(115200);
  wifiManager.autoConnect(ACCESSPOINT_NAME);
  Serial.println("connected... :)");
  digitalWrite(LEDPIN, HIGH);
}

void loop(){
  if(digitalRead(SWPIN)==LOW && millis()-lastTimeReset>timeout){  // สถานะมีการกดปุ่ม และเวลาเกิน 10วินาที สามารถกด resetconfig ได้ 1 ครั้ง
    lastTimeReset = millis();
    wifiManager.resetSettings();
  }
}
