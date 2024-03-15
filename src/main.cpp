////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       main.cpp
//*FILE DESC:       Main source file for inverfer_control.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Chimaroke Okwara (chima-okwara)
//*LAST MODIFIED:   Friday, 15 March, 2024
//*LICENSE:         GNU LGPL v2.1
////////////////////////////////////////////////////////////////////////////////////////////////////#include <Arduino.h>
#include <inverter.h>


char volstr[3] { }, curstr[3] { }, temstr[3] { };
bool over;

void setup()
{
    //Set pin modes:
    init();
    Serial.begin(115200);
    Serial.println("HELLO.");
    digitalWrite(PC13, HIGH);

    over = false;
}


void loop()
{
    if(UVP)
    {
        lcd.clear();
        do
        {
            lcd.home();
            lcd.print("BATTERY LOW!");
            lcd.setCursor(0, 1);
            char msg [] = "Inverter off. Press S1 to override.";
            lcd.print(msg);
            int len = sizeof(msg);
            for(int i = 0; i < len; ++i)
            {
                lcd.scrollDisplayLeft();
                delay(500);
            }
            delay(100);
        } while(!s1 && !s2 && UVP);
        if(s1)
        {
            s1 = false;
            over = true;
        }
    }

    if(OCP)
    {
        lcd.clear();
        do
        {
            lcd.home();
            lcd.print("TOO MUCH CURRENT!");
            lcd.setCursor(0, 1);
            char msg [] = "Inverter off. Remove load!";
            lcd.print(msg);
            int len = sizeof(msg);
            for(int i = 0; i < len; ++i)
            {
                lcd.scrollDisplayLeft();
                delay(500);
            }
            delay(100);
        } while(!s1 && !s2 && OCP);
        if(s1 || s2)
        {
            s1 = false;
            s2 = false;
        }
    }

    if(OTP)
    {
        analogWriteResolution(12);
        uint32_t fanspeed = map((long) temperature, 44, 99, 0, 4095);
        fanspeed = constrain(fanspeed, 500, 4095);
        analogWrite(fan, fanspeed);

        if(temperature >= 99)
            do
            {
                lcd.clear();
                lcd.home();
                lcd.print("SYSTEM TOO HOT");
                lcd.setCursor(0, 1);
                char msg [] = "Inverter off. Reduce load!";
                lcd.print(msg);
                int len = sizeof(msg);
                for(int i = 0; i < len; ++i)
                {
                    lcd.scrollDisplayLeft();
                    delay(500);
                }
                delay(100);
            } while(temperature >= 99);
        }

}


