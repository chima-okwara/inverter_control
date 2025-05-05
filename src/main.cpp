////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       main.cpp
//*FILE DESC:       Main source file for inverfer_control.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Chimaroke Okwara (chima-okwara)
//*LAST MODIFIED:   Thursday, 19 December, 2024
//*LICENSE:         GNU LGPL v2.1
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <inverter.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

float voltage {}, current {}, temperature {}, power{}, val { }, actualVal { };
bool UVP {}, OVP {}, OLP {}, OCP {}, OTP {}, INV {}, BZ {},
      s1 {}, s2 {}, s3 {}, s4 {}, invt {},
      sleep {};


float average[AVG] { }, valueAverage { }, sum { }, avg { };
uint32_t value { };

long batPer { };


void setup()
{
    pinMode(iSense, INPUT_ANALOG);
    pinMode(vSense, INPUT_ANALOG);
    pinMode(tSense, INPUT_ANALOG);

    pinMode(sw1, INPUT_PULLUP);
    pinMode(sw2, INPUT_PULLUP);

    //OUTPUT PINS:
    pinMode(buzzerpin, OUTPUT);
    analogWrite(buzzerpin, buzOff);

    pinMode(invSw, OUTPUT);
    digitalWrite(invSw, invOff);

    pinMode(fan, OUTPUT);
    digitalWrite(fan, fanOff);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    attachInterrupt(digitalPinToInterrupt(sw1), sw1press, RISING);
    attachInterrupt(digitalPinToInterrupt(sw2), sw2press, FALLING);



    lcd.init();
    lcd.backlight();

    printWlc();
    delay(1500);

    current = 0.0;
    voltage = 0.0;
    temperature = 0.0;


    analogReadResolution(12);
    analogWriteResolution(8);

    //Turn OUTPUTS on
    digitalWrite(fan, fanOn);
    analogWrite(buzzerpin, buzOn);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1500);

    //Turn OUTPUTS off
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(invSw, invOff);
    digitalWrite(fan, fanOff);
    analogWrite(buzzerpin, buzOff);
    delay(1500);

    lcd.clear();
    lcd.home();
    lcd.print("------Press INV");
    lcd.setCursor(0, 1);
    lcd.print("to Start.------");
    delay(1000);
    while(!s1)
    {
        delay(100);
    }

    s1 = s2 = false;
}

void loop()
{
        fCheck();

        if(INV)
            invT();
        else
        {
            if(s2)
            {
                lcd.clear();
                lcd.home();
                lcd.print("Override Mode");
                delay(500);
                invT();
            }

            else
                invF();
        }

        delayMicroseconds(10);

    //    Serial.println("Voltage: %d | Current: %d | Temperature: %d |");

        digitalWrite(LED_BUILTIN, !(digitalRead(LED_BUILTIN)));
        delayMicroseconds(20);
}
