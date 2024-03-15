#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

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


LiquidCrystal_I2C lcd (0x27);
void setup();
void loop();


void setup()
{
    pinMode(sw1, INPUT);
    pinMode(sw2, INPUT);
    pinMode(sw3, INPUT);
    pinMode(sw4, INPUT);

    pinMode(iSense, INPUT_ANALOG);
    pinMode(vSense, INPUT_ANALOG);
    pinMode(tSense, INPUT_ANALOG);

    pinMode(buzzer, OUTPUT);
    pinMode(fan, OUTPUT);

    digitalWrite(buzzer, 0);


    lcd.begin(16, 2);

}


void loop()
{

}
