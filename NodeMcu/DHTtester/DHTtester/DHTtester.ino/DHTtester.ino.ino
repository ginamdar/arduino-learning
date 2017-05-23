#include "dht.h"
#define DHT_APIN  A0 // Analog pin sensor connected to

dht DHT;

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("DHT11 humidity & temprature sensor\n\n");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  DHT.read11(DHT_APIN);
  Serial.print("Current Humidity: ");
  Serial.print(DHT.humidity);
  Serial.print("%  ");
  Serial.print("Temp: ");
  Serial.print(DHT.temperature);
  Serial.println("C ");

  delay(5000); //Wait 5 sec before accessing sensor again

}
