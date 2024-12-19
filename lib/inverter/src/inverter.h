////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       inverter.cpp
//*FILE DESC:       Header file for inverfer_control library.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Chimaroke Okwara (chima-okwara)
//*LAST MODIFIED:   Thursday, 19 December, 2024
//*LICENSE:         GNU LGPL v2.1
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __NL_UPS_042__
#define __NL_UPS_042__
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <eichen_lib.h>


#define RATING 400

#define sw1 PA3
#define sw2 PA4
#define sw3 PA5
#define sw4 PA6

#define iSense PA0
#define vSense PA1
#define tSense PA2

#define fan PA15
#define buzzerpin PB1
#define invSw PB5

#define invOn   HIGH
#define invOff  LOW
#define fanOn   HIGH
#define fanOff  LOW
#define buzOn   255
#define buzOff  0

#define R1 100000.0
#define R2 319453.924
#define RSHUNT 0.02

#define VTH 9.55
#define ITH IMAX
#define TTH 40

#define VMAX 15.5
#define VDIVMAX 16000
#define IMAX 35
#define MAXCURRENT (IMAX*1000)
#define MAXVOLTAGE (VMAX*1000)
#define PMAX (VMAX*IMAX)
#define ISENSE_FACTOR  66


void readCurrent();
void readTemperature();


void disp();
void displayVIT();
void printMsg();
void printMsg2();
void printWlc();

void toggleSleep();
void wkUpFn();

void mapFanValue();
void fCheck();


void invF();
void invT();

void sw1press();
void sw2press();
/**
TODO: Add mapFanValue to map temperature to value between 255 to 20 and then write this to fan.
**/


#endif
