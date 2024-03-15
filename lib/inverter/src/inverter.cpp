#include <Arduino.h>
#include <inverter.h>

HardwareTimer *timer = new HardwareTimer(TIM2);

void setTimer()
{
    //Configure timer:
//    timer->setPrescaleFactor(SYSCLOCK / ((1 / 5) - 1));
    timer->setOverflow(5 * 1000000, MICROSEC_FORMAT);

    // Attach the interrupt
    timer->attachInterrupt(timerInterrupt);

    // Start the timer
    timer->resume();
}


void timerInterrupt()
{
    digitalWrite(PC13, !(digitalRead(PC13)));
    Serial.println("Interrupt!");

}
