#include <Arduino.h>

#include <SPI.h>
#include "Ucglib.h"
//PIN definition
//Arduino Uno/Nano and Wemos D1 mini/pro
#define SCLK  /*13*/    14  /*D5*/
#define DATA  /*11*/    4   /*D2*/
#define CD    /*9*/     16  /*D0*/
#define CS    /*10*/    15  /*D8*/
#define RESET /*8*/     2   /*D4*/

Ucglib_ST7735_18x128x160_SWSPI ucg(SCLK,DATA,CD,CS,RESET);

void setup(void)
{
    delay(1000);
    //ucg.begin(UCG_FONT_MODE_TRANSPARENT);
    ucg.begin(UCG_FONT_MODE_SOLID);
    ucg.clearScreen();
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
