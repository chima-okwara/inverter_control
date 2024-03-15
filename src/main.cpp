#include <Arduino.h>
#include <inverter.h>


//LiquidCrystal_I2C lcd (0x27);

void setup()
{
    //Set pin modes:
    setTimer();
    Serial.begin(115200);
    Serial.println("HELLO.");
    digitalWrite(PC13, HIGH);

    pinMode(PC13, OUTPUT);

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


}


void loop()
{

}


