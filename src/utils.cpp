#include "utils.h"

boolean loadWiFiSavedConfig() {
    String ssid = loadJsonParam("wifi", "ssid");
    if (ssid == "") {
        Serial.println("WARNING: WiFi configuration not found");
        return (boolean) false;
    }
    String password = loadJsonParam("wifi", "password");
    if (WiFi.begin(ssid.c_str(), password.c_str())) {
        Serial.println("SSID: " + ssid);
        Serial.println("Password: " + password);
        return (boolean) true;
    }
    Serial.println("WARNING: WiFi configuration not found");
    return (boolean) false;
}

// Wi-Fi check connection
boolean checkWiFiConnection() {
    int count = 0;
    Serial.print("Waiting to connect to WiFi network");
    while (count < 20) {
        delay(1000);
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println();
            Serial.println("Connected!");
            return (boolean) true;
        }
        Serial.print(".");
        count++;
    }
    Serial.println("Timed out.");
    Serial.println("ERROR: Connection lost");
    return (boolean) false;
}

// Wi-Fi access point list
String ssidList() {
    String ssid_list;
    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; ++i) {
        ssid_list += "\n<option value=\"";
        ssid_list += WiFi.SSID((uint8_t) i);
        ssid_list += "\">";
        ssid_list += WiFi.SSID((uint8_t) i);
        ssid_list += "</option>";
    }
    return ssid_list;
}

// HTML Page maker
String makePage(String device_title, String page_title, String contents) {
    String s = "<!DOCTYPE html>\n<html>\n<head>\n";
    s += "<meta name='viewport' content='width=device-width,user-scalable=0'>\n";
    s += "<link rel='stylesheet' href='css/simple.css'>\n";
    s += "<link rel='stylesheet' href='css/basic.css'>\n";
    s += "<link rel='stylesheet' href='css/custom.css'>\n";
    s += "<title>";
    s += device_title + " | " + page_title;
    s += "</title>\n</head>\n<body>\n<header>\n";
    s += "<img src='img/logo.png' title='gallNFC' alt='gallNFC Logo' align='middle'>\n";
    s += "</header>\n<div class=\"content-body\">\n";
    s += contents;
    s += "</div>\n</body>\n</html>";
    return s;
}

// Decode URL
String urlDecode(String input) {
    String s = input;
    s.replace("%20", " ");
    s.replace("+", " ");
    s.replace("%21", "!");
    s.replace("%22", "\"");
    s.replace("%23", "#");
    s.replace("%24", "$");
    s.replace("%25", "%");
    s.replace("%26", "&");
    s.replace("%27", "\'");
    s.replace("%28", "(");
    s.replace("%29", ")");
    s.replace("%30", "*");
    s.replace("%31", "+");
    s.replace("%2C", ",");
    s.replace("%2E", ".");
    s.replace("%2F", "/");
    s.replace("%2C", ",");
    s.replace("%3A", ":");
    s.replace("%3A", ";");
    s.replace("%3C", "<");
    s.replace("%3D", "=");
    s.replace("%3E", ">");
    s.replace("%3F", "?");
    s.replace("%40", "@");
    s.replace("%5B", "[");
    s.replace("%5C", "\\");
    s.replace("%5D", "]");
    s.replace("%5E", "^");
    s.replace("%5F", "-");
    s.replace("%60", "`");
    return s;
}

//Load config from Json file in SPIFFS
boolean loadJsonParam(const char *service) {
    File configFile = SPIFFS.open("/config/config.json", "r");
    if (!configFile) {
        Serial.println("ERROR: Failed to open config file (loadJsonParam)");
        return (boolean) false;
    }
    size_t size = configFile.size();
    if (size > 1024) {
        Serial.println("ERROR: Config file size is too large (loadJsonParam)");
        return (boolean) false;
    }
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    DynamicJsonBuffer jsonBuffer;
    JsonObject &json = jsonBuffer.parseObject(buf.get());
    if (!json.success()) {
        Serial.println("ERROR: Failed to parse config file (loadJsonParam)");
        return (boolean) false;
    }
    boolean config = json[service]["enabled"];
    if (config) {
        return (boolean) true;
    }
    return (boolean) false;
}

const char *loadJsonParam(const char *service, const char *param) {
    File configFile = SPIFFS.open("/config/config.json", "r");
    if (!configFile) {
        Serial.println("ERROR: Failed to open config file (loadJsonParam)");
        return (boolean) false;
    }
    size_t size = configFile.size();
    if (size > 1024) {
        Serial.println("ERROR: Config file size is too large (loadJsonParam)");
        return (boolean) false;
    }
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    DynamicJsonBuffer jsonBuffer;
    JsonObject &json = jsonBuffer.parseObject(buf.get());
    if (!json.success()) {
        Serial.println("ERROR: Failed to parse config file (loadJsonParam)");
        return (boolean) false;
    }
    const char *config = json[service][param];
    return (char *) config;
}

//Write config in Json file in SPIFFS
boolean saveJsonConfig(const char *service, const char *param, const char *config) {
    File configFile = SPIFFS.open("/config/config.json", "r");
    if (!configFile) {
        Serial.println("ERROR: Failed to open config file (saveJsonConfig)");
        return (boolean) false;
    }
    size_t size = configFile.size();
    if (size > 1024) {
        Serial.println("ERROR: Config file size is too large (saveJsonConfig)");
        return (boolean) false;
    }
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    DynamicJsonBuffer jsonBuffer;
    JsonObject &json = jsonBuffer.parseObject(buf.get());
    if (!json.success()) {
        Serial.println("ERROR: Failed to parse config file (saveJsonConfig)");
        return (boolean) false;
    }
    configFile.close();
    JsonObject &nested = json[service];
    nested.set(param, config);
    configFile = SPIFFS.open("/config/config.json", "w+");
    json.prettyPrintTo(configFile);
    return (boolean) true;
}

boolean saveJsonConfig(const char *service, const char *param, boolean status) {
    File configFile = SPIFFS.open("/config/config.json", "r");
    if (!configFile) {
        Serial.println("ERROR: Failed to open config file (saveJsonConfig)");
        return (boolean) false;
    }
    size_t size = configFile.size();
    if (size > 1024) {
        Serial.println("ERROR: Config file size is too large (saveJsonConfig)");
        return (boolean) false;
    }
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    DynamicJsonBuffer jsonBuffer;
    JsonObject &json = jsonBuffer.parseObject(buf.get());
    if (!json.success()) {
        Serial.println("ERROR: Failed to parse config file (saveJsonConfig)");
        return (boolean) false;
    }
    configFile.close();
    JsonObject &nested = json[service];
    nested.set(param, status);
    configFile = SPIFFS.open("/config/config.json", "w+");
    json.prettyPrintTo(configFile);
    return (boolean) true;
}

//Debug function to print spiffs files tree
void debugSPIFFS() {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {
        String fileName = dir.fileName();
        Serial.printf("FS File: %s\n", fileName.c_str());
    }
}