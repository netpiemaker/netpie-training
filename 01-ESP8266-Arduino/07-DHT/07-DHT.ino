#include <DHT.h> 
#define DHTTYPE DHT22 
#define DHTPIN D4 

DHT dht(DHTPIN, DHTTYPE, 15); 
  void setup(){
  dht.begin(); 
  Serial.begin(115200); 
}

void loop(){
  int humid = dht.readHumidity(); 
  int temp = dht.readTemperature(); 
  char str[] = "";
  sprintf(str,"H = %d : T = %d",humid,temp);
  Serial.println(str); 
  delay(300); 
}
