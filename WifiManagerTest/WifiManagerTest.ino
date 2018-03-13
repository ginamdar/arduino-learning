#include "Config.h"

#define DEBUG

void configModeCallback (WiFiManager *myWiFiManager) {
  logMessage("Entered config mode", false);
  //  logMessage(String(WiFi.softAPIP()), false);
  //if you used auto generated SSID, print it
  logMessage(myWiFiManager->getConfigPortalSSID(), false);
  shouldSaveConfig = true;
}


void setup() {
#ifdef DEBUG
  Serial.begin(115200);
  delay(1);
#endif
  SPIFFS.format();
  readSPI2MQTT();
  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  //reset settings - for testing
//  wifiManager.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

  addWifiParameters(wifiManager);
//  wifiManager.setMinimumSignalQuality(40);
#ifndef DEBUG
  wifiManager.setDebugOutput(false);
#endif


  //fetches ssid and pass and tries to connect

  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect("AutoConnectAP")) {
    logMessage("failed to connect and hit timeout", false);
    //reset and try again, or maybe put it to deep sleep
    delay(1000);
    ESP.reset();
    delay(5000);
  }

  //if you get here you have connected to the WiFi
  logMessage("connected", false);
  if (shouldSaveConfig) {
    strcpy(mqtt_server, adafruit_server.getValue());
    strcpy(mqtt_token, adafruit_key.getValue());
    strcpy(mqtt_username, adafruit_username.getValue());
    strcpy(mqtt_mainFeed, adafruit_mainFeed.getValue());
    strcpy(mqtt_batteryFeed, adafruit_batteryFeed.getValue());
    saveMQTT2SPIFF();
  }
}

void addWifiParameters(WiFiManager &wifiManager) {

  //add all your parameters here
  wifiManager.addParameter(&adafruit_server);
  wifiManager.addParameter(&adafruit_key);
  wifiManager.addParameter(&adafruit_username);
  wifiManager.addParameter(&adafruit_mainFeed);
  wifiManager.addParameter(&adafruit_batteryFeed);
}

boolean saveMQTT2SPIFF() {
  boolean didSave = true;
  logMessage("saving config", false);
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["mqtt_server"] = mqtt_server;
  json["mqtt_username"] = mqtt_username;
  json["mqtt_token"] = mqtt_token;
  json["mqtt_mainFeed"] = mqtt_mainFeed;
  json["mqtt_batteryFeed"] = mqtt_batteryFeed;

  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    didSave = false;
    logMessage("failed to open config file for writing", false);
    return didSave;
  }
#ifdef DEBUG
  json.printTo(Serial);
#endif
  json.printTo(configFile);
  configFile.close();
  return didSave;
}

boolean readSPI2MQTT() {
  boolean didRead = false;
  logMessage("mounting FS...", false);

  if (SPIFFS.begin()) {
    logMessage("mounted file system", false);
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      logMessage("reading config file", false);
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        logMessage("opened config file", false);
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          logMessage("\nparsed json", false);

          strcpy(mqtt_server, json["mqtt_server"]);
          strcpy(mqtt_username, json["mqtt_username"]);
          strcpy(mqtt_token, json["mqtt_token"]);
          strcpy(mqtt_mainFeed, json["mqtt_mainFeed"]);
          strcpy(mqtt_batteryFeed, json["mqtt_batteryFeed"]);
          didRead = true;

        } else {
          logMessage("failed to load json config", false);
        }
      }
    }
  } else {
    logMessage("failed to mount FS", false);
  }
  return didRead;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("MQTT Server:" + String(mqtt_server));
  Serial.println("MQTT Username:" + String(mqtt_username));
  Serial.println("MQTT Key:" + String(mqtt_token));
  Serial.println("MQTT MainFeed:" + String(mqtt_mainFeed));
  Serial.println("MQTT batteryFeed:" + String(mqtt_batteryFeed));
  delay(3000);
}
