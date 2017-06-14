#include <ESP8266WiFi.h>
const char* ssid     = "YOUR_WIFI_SSI";
const char* password = "YOUR_WIFI_PASSWORD"; 

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {    
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
}
