#include <ESP8266WiFi.h>
#include <MicroGear.h>
#include <math.h>

const char* ssid     = "@A4MY_wifi";                  // ชื่อ ssid
const char* password = "88888888";              // รหัสผ่าน wifi

#define APPID   "armydev"                              // ให้แทนที่ด้วย AppID
#define KEY     "5B1qJc8XO4cDVDI"                                // ให้แทนที่ด้วย Key
#define SECRET  "tagjjnUiuLdWRkXt0cAHzPTKZ"                             // ให้แทนที่ด้วย Secret
#define ALIAS   "esp8266"                              // ชื่ออุปกรณ์

#define LEDPIN D0                                         // LED pin
#define TTC104_PIN A0
#define topicPublish "/ttc104"                      // topic ที่ต้องการ publish ส่งข้อความ
unsigned long lastTimeReadAnalog = 0;
int temperature = -999;

WiFiClient client;
int timer = 0;
MicroGear microgear(client);

double Thermister(int RawADC) {
  double Temp;
  // See http://en.wikipedia.org/wiki/Thermistor for explanation of formula
  Temp = log(((10240000/RawADC) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;           // Convert Kelvin to Celcius
  return Temp;
}

void readTemp(void) {
  double fTemp;
  double temp = Thermister(analogRead(TTC104_PIN));  // Read sensor
  Serial.print("Temperature is:");
  Serial.print(temp);
  Serial.print(" C / ");
  temperature = temp;
  fTemp = (temp * 1.8) + 32.0;    // Convert to USA
  Serial.print(fTemp);
  Serial.print(" F");
}

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);

    // สถานะ LED บน NodeMCU ที่แสดงผล จะติดก็ต่อเมื่อสั่ง LOW 
    // แต่ถ้าเป็น LED ที่ต่อแยก จะต้องสั่งเป็น HIGH 
    if(*(char *)msg == '1'){
        digitalWrite(LEDPIN, HIGH); // LED on
    }else{
        digitalWrite(LEDPIN, LOW); // LED off
    }
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    microgear.setAlias(ALIAS);
}


void setup(void) {
    // กำหนดฟังก์ชั้นสำหรับรับ event callback 
    microgear.on(MESSAGE,onMsghandler);
    microgear.on(CONNECTED,onConnected);

    // กำหนด baud rate สำหรับการสื่อสาร
    Serial.begin(115200);
    Serial.println("Starting...");

    // กำหนดชนิดของ PIN (ขาI/O) เช่น INPUT, OUTPUT เป็นต้น
    pinMode(LEDPIN, OUTPUT);          // LED pin mode กำหนดค่า

    // เชื่อมต่อ wifi
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.print(".");
        }
    }

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    microgear.init(KEY,SECRET,ALIAS);   // กำหนดค่าตันแปรเริ่มต้นให้กับ microgear
    microgear.connect(APPID);           // ฟังก์ชั่นสำหรับเชื่อมต่อ NETPIE

}

void loop(void) {
  if (microgear.connected()) { // microgear.connected() เป็นฟังก์ชั่นสำหรับตรวจสอบสถานะการเชื่อมต่อ
    // microgear.loop() เป็นฟังก์ชั่นสำหรับทวนสถานะการเชื่อมต่อกับ NETPIE (จำเป็นต้องมีใช้ loop)
    microgear.loop();
    timer = 0;
    
    if(millis()-lastTimeReadAnalog > 1000){
      readTemp();
      lastTimeReadAnalog = millis();
      Serial.print("Sending --> ");
      Serial.println(temperature);
      microgear.publish(topicPublish,temperature);
    }
  }else {
    Serial.println("connection lost, reconnect...");
    if (timer >= 5000) {
      microgear.connect(APPID); 
      timer = 0;
    }
    else timer += 100;
    delay(100);
  }
}
