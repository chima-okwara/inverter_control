#ifndef __NL_UPS_042__
#define __NL_UPS_042__
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <HardwareTimer.h>

#define SYSCLOCK 72000000

#define sw1 PA3
#define sw2 PA4
#define sw3 PA5
#define sw4 PA6

#define fan PA15
#define iSense PA0
#define vSense PA1
#define tSense PA2
#define buzzer PB1
#define invSw PB5

extern HardwareTimer *timer;

void setup();
void loop();

void setTimer();
void timerInterrupt();


#endif
