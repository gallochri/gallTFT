#ifndef GALLTFT_UTILS_H
#define GALLTFT_UTILS_H

#include <Arduino.h>
#include <FS.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

// Load WiFi configuration
boolean loadWiFiSavedConfig();

// Wi-Fi check connection
boolean checkWiFiConnection();

// Wi-Fi access point list
String ssidList();

// HTML Page maker
String makePage(String device_title, String page_title, String contents);

// Decode URL
String urlDecode(String input);

//Read configs from Json on SPIFFS
boolean loadJsonParam(const char *service);
const char *loadJsonParam(const char *service, const char *param);

//Write config to Json on SPIFFS
boolean saveJsonConfig(const char *service, const char *param, const char *config);
boolean saveJsonConfig(const char *service, const char *param, boolean status);

//DEBUG Print SPIFFS content to serial
void debugSPIFFS();

#endif //GALLTFT_UTILS_H
