#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  Serial.println("Starting setup");

  Serial.print("Scan start ... ");
  int n = WiFi.scanNetworks();
  Serial.print(n);
  Serial.println(" network(s) found");
  for (int i = 0; i < n; i++)
  {
    Serial.println(WiFi.SSID(i));
  }
  Serial.println();

  WiFi.disconnect(true);
  WiFi.setAutoConnect(false);
  WiFi.setPhyMode(WIFI_PHY_MODE_11G);
  WiFi.begin("Zion", "Nostromo14");
  WiFi.printDiag(Serial);
  Serial.println(WiFi.getPhyMode());

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  delay(2000);
}

void loop(){
  return;
}

