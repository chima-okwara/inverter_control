#ifndef __NL_UPS_042__
#define __NL_UPS_042__
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <HardwareTimer.h>
#include <Buzzer.h>

#define SYSCLOCK 72000000

#define sw1 PA3
#define sw2 PA4
#define sw3 PA5
#define sw4 PA6

#define fan PA15
#define iSense PA0
#define vSense PA1
#define tSense PA2
#define buzzerpin PB1
#define invSw PB5

#define R1 100000.0
#define R2 33000.0

#define VTH 10.5
#define ITH 3
#define TTH 40

extern HardwareTimer *timer;
extern LiquidCrystal_I2C lcd;
extern Buzzer buzzer;
extern float voltage, current, temperature;
extern bool UVP, OCP, OTP, INV, BZ,
            s1, s2, s3, s4,
            over;
extern char volstr[3], curstr[3], temstr[3];

void setup();
void loop();

inline void setTimer();
inline void init();
inline void timerInterrupt();

inline void disp();

inline void measureVIT();
inline void displayVIT();
inline const float &readCurrent();
inline const float &readVoltage();
inline const float &readTemperature();

inline void sw1Pressed();
inline void sw2Pressed();
inline void sw3Pressed();
inline void sw4Pressed();



#endif
