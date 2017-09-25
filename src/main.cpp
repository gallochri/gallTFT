#include <Arduino.h>

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <FS.h>
#include "Ucglib.h"

#include "config.h"
#include "utils.h"

Ucglib_ST7735_18x128x160_SWSPI ucg(SCLK,DATA,CD,CS,RESET);

void setup(void)
{
    //Set WiFi to station mode
    WiFi.mode(WIFI_STA);
    //Init SPIFFS
    SPIFFS.begin();
    delay(1000);
    //ucg.begin(UCG_FONT_MODE_TRANSPARENT);
    ucg.begin(UCG_FONT_MODE_SOLID);
    ucg.clearScreen();
    ucg.setRotate90();
    ucg.setFont(ucg_font_ncenR08_tf);
    ucg.setColor(255, 255, 255);
    //Try to load saved wifi config and to connect to wifi
    if (!loadWiFiSavedConfig()) {
        ucg.setPrintPos(5, 15);
        ucg.print("OFF Line");
        isOnline = (boolean) false;
        delay(5000);
    } else if (!checkWiFiConnection()) {
        ucg.print("ON Line");
        isOnline = (boolean) false;
        delay(5000);
    }
}

void loop(void) {
    ucg.setRotate90();
    ucg.setFont(ucg_font_ncenR08_tf);
    ucg.setColor(255, 255, 255);

    ucg.setPrintPos(5, 15);
    ucg.print("Hello World!");
    ucg.setPrintPos(5,30);
    ucg.print("Second line");

    delay(500);
}
