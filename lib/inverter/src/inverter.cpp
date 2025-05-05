////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       inverter.cpp
//*FILE DESC:       Source file for inverfer_control library.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Chimaroke Okwara (chima-okwara)
//*LAST MODIFIED:   Thursday, 19 December, 2024
//*LICENSE:         GNU LGPL v2.1
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <inverter.h>


extern float average[AVG], valueAverage, sum, avg, val, actualVal;
extern uint32_t value;

extern float current, voltage, temperature, power;
extern LiquidCrystal_I2C lcd;

extern volatile bool sleep;

extern bool UVP , OVP, OLP, OCP , OTP , INV , BZ ,
      s1 , s2, s3, s4, invt;

extern long batPer;

void printWlc()
{
    lcd.clear();
    lcd.home();
    lcd.print("αϰ-Χιμα-Χυκυ");
    delay(2000);
    lcd.clear();
    lcd.home();
    lcd.print("****  xRis ****");
    delay(200);
    lcd.setCursor(0, 1);
    lcd.print("** Technology **");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(RATING);
    lcd.print(" W ------------");
    lcd.setCursor(0, 1);
    lcd.print("------- Inverter");
    delay(2000);

    printMsg();
    delay(2000);
}


void printMsg()
{
    lcd.clear();
    lcd.home();
    lcd.print("Povver _ Pakken");
    lcd.setCursor(0, 1);
    lcd.print("] / XRTC052   /  [");
    delay(200);
}

void printMsg2()
{
    lcd.clear();
    lcd.home();
    lcd.print("****  xRis ****");
    lcd.setCursor(0, 1);
    lcd.print("** Technology **");
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(RATING);
    lcd.print(" W ------------");
    lcd.setCursor(0, 1);
    lcd.print("------- Inverter");
    delay(200);
}


void disp()
{
    lcd.clear();
    lcd.home();
    lcd.print("Vo:     |Bt:    ");
    lcd.setCursor(0, 1);
    lcd.print("Te:    |Pw:     ");
}

void displayVIT()
{
    disp();

    lcd.setCursor(3, 0);
    lcd.print(voltage, 2);
    lcd.setCursor(12, 0);
    lcd.print(batPer);
    lcd.print('%');
    lcd.setCursor(3, 1);
    lcd.print(temperature, 2);
    lcd.setCursor(11, 1);
    lcd.print(power, 2);
}




void readCurrent()
{
    //Using shunt resistor:
    val = 0.0;
    actualVal = 0.0;
    current = 0.0;



    float maxVoltage = (IMAX * RSHUNT) * 1000;

    val = readVoltage(iSense, 0, 3300);
    convToBase(&val);
    current = val / (GAIN * RSHUNT);


    //Using current sensor:
//    actualVal = readVoltage(iSense, 0, 3349);
//    current = ((float (3349 / 2)) - actualVal) / 66;
//    current = abs(current);
//    convToBase(&current);
}


void readTemperature()
{
    val = 0.0;
    actualVal = 0.0;
    temperature = 0.0;
    val = readVoltage(tSense, 0, 3300);

    actualVal = constrain(val, 303.0, 1500.0);

    temperature = ( actualVal / 10.0) - 27.29;      //Where 10 is the sensor gain.
}


void toggleSleep()
{
        delayMicroseconds(900);
        analogWrite(buzzerpin, buzOff);
        digitalWrite(invSw, invOff);
        analogWrite(fan, fan);
        lcd.noBacklight();
        lcd.off();
}

void wkUpFn()
{

}


void fCheck()
{
      val = 0.0;
      actualVal = 0.0;
      voltage = 0.0;
      current = 0.0;
      power = 0.0;
      temperature = 0.0;

      val = readVoltage(vSense, 0, 3300);
      voltage = map(val, 0, 3300, 0, VDIVMAX);

      convToBase(&voltage);
      batPer = getBatPer(voltage, MinBatVoltage, MaxBatVoltage);



      readCurrent();
//
      power = voltage * current;

      readTemperature();
//
        UVP = (voltage <= VTH) ? true : false ;
        OCP = (current >= ITH) ? true : false ;
        OVP = (voltage >= MaxBatVoltage + 2.0) ? true : false;
        OLP = (power >= PMAX) ? true : false;
//        OTP = (temperature >= TTH) ? true : false ;
//        INV = (UVP || OCP || OTP) ? false : true ;
        INV = (UVP || OCP || OVP || OLP || !s1) ? false : true ;
}



void invF()
{
    digitalWrite(invSw, invOff);
    digitalWrite(fan, fanOff);

    lcd.clear();
    lcd.home();
    lcd.print("AC OFF.");
    delay(1000);

    if(!s1)
    {
        lcd.setCursor(0, 1);
        lcd.print("INV Switch off.");
        delay(1000);
        return;
    }




    analogWrite(buzzerpin, buzOn);
    delay(1000);
    analogWrite(buzzerpin, buzOff);
    delay(10);


    if(UVP)
    {
        analogWrite(buzzerpin, buzOn);
        delay(1000);

        lcd.clear();
        lcd.home();
        lcd.print("BAT LOW.");
        lcd.setCursor(0, 1);
        lcd.print("Vo: ");
        lcd.print(voltage, 2);
        delay(1300);
        analogWrite(buzzerpin, buzOff);
        delay(1000);
    }

    else if(OCP || OLP)
    {
        analogWrite(buzzerpin, buzOn);
        delay(1000);

        lcd.clear();
        lcd.home();
        lcd.print("OverLoad");

        if(OCP)
        {
            lcd.setCursor(0, 1);
            lcd.print("Cu: ");
            lcd.print(current, 2);
            delay(1300);
            analogWrite(buzzerpin, buzOff);
            delay(1000);
        }

        if(OLP)
        {
            lcd.setCursor(8, 1);
            lcd.print("Pw: ");
            lcd.print(power, 2);
            delay(1300);
            analogWrite(buzzerpin, buzOff);
            delay(1000);
        }

    }

    else if(OTP)
    {
        analogWrite(buzzerpin, buzOn);
        delay(1000);
        lcd.clear();
        lcd.home();
        lcd.print("Temperature err.");
        lcd.setCursor(0, 1);
        lcd.print("Te: ");
        lcd.print(temperature, 2);
        delay(1300);
        analogWrite(buzzerpin, buzOff);
        delay(1000);
    }
}

void invT()
{
    digitalWrite(fan, fanOn);
    digitalWrite(invSw, invOn);
    analogWrite(buzzerpin, buzOff);
    displayVIT();
    delay(2300);

    printMsg2();
    delay(700);
}

void sw1press()
{
    s1 = !s1;
}

void sw2press()
{
    s2 = !s2;
}
