/*
 * Wiring the TFT panel
 * Arduino Uno/Nano
 * SCLK 13
 * DATA 11
 * CD    9
 * CS   10 not used
 * RESET 8
 *
 * Wemos D1 mini / pro
 * SCLK 14 D5
 * DATA  4 D2
 * CD   16 D0
 * CS   15 D8 not used
 * RESET 2 D4
 *
 * TFT panel pinout from left- GND-5V-RESET-CD-DATA-SCLK
 */
#ifndef GALLTFT_CONFIG_H
#define GALLTFT_CONFIG_H

//PIN definition
#define SCLK  14  /*D5*/
#define DATA  4   /*D2*/
#define CD    16  /*D0*/
#define CS    15  /*D8*/
#define RESET 2   /*D4*/

//Uncomment to enable serial print
#define DEBUGPRINT Serial

boolean isOnline = (boolean) true;                              //True if successful connection

#endif //GALLTFT_CONFIG_H
