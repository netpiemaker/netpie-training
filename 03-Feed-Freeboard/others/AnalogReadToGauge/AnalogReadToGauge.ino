#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid     = "SSID"; // ใส่ชื่อของ WiFi ที่ใช้งาน
const char* password = "PASSWORD"; // ใส่รหัสของ WiFi ที่ใช้งาน

#define APPID   "YOUR_APPID" // ใส่ AppID (Application ID)
#define KEY     "YOUR_KEY" // ใส่ Key
#define SECRET  "YOUR_SECRET" // ใส่ Secret
#define ALIAS   "piedht" // ตั้งชื่ออุปกรณ์ของเรา Alias Name

WiFiClient client; // สร้าง client ขึ้นมา
MicroGear microgear(client); // นำ client ที่สร้างขึ้นมาเชื่อมต่อกับ netpie

#define ANALOGPIN A0
int analogValue = 0;

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
  Serial.print("Incoming message --> ");
  msg[msglen] = '\0';
  Serial.println((char *)msg);
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.println("Connected to NETPIE...");
  microgear.setAlias(ALIAS);
}

void setup() {
  microgear.on(MESSAGE,onMsghandler);
  microgear.on(CONNECTED,onConnected);
  
  Serial.begin(115200);
  Serial.println("Starting...");

  if (WiFi.begin(ssid, password)) {
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
  }

  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  microgear.init(KEY,SECRET,ALIAS);
  microgear.connect(APPID);
}

void loop() {
  analogValue = analogRead(ANALOGPIN);
  Serial.print("Analog input0 = ");
  Serial.println(analogValue);
  if (microgear.connected()) {
    Serial.println("connected");
    microgear.chat("freeboard",analogValue);
    microgear.loop();    
  } else {
    Serial.println("connection lost, reconnect...");
    microgear.connect(APPID);
  }
  delay(1000);
}
