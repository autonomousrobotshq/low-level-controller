#include <Arduino.h>

#include "Sensors/Hall.hpp"

// attach interrupt doesnt allow arguments(like a 'this' argument), so hardcoded globs are required
static unsigned int pulses[HALL_INTERRUPT_COUNT];

bool SensorHall::update()
{
    unsigned long millisDev = this->getDuration();
    this->_rpm = millisDev == 0 ? 0 : (pulses[this->_pulseIndex] / HALL_CPR) / (millisDev / 60000);
    pulses[this->_pulseIndex] = 0;
    // error handling here
    return (true);
}

int SensorHall::getRPM()
{
    return (this->_rpm);
}

void interruptCallA()
{
    pulses[0]++;
}

void interruptCallB()
{
    pulses[1]++;
}

void interruptCallC()
{
    pulses[2]++;
}
void interruptCallD()
{
    pulses[3]++;
}

SensorHall::SensorHall(const unsigned int pinA,
    const unsigned int pinB,
    const unsigned int pinInterrupt,
    const unsigned long* globMillis)
    : Sensor(globMillis)
    , _pinA(pinA)
    , _pinB(pinB)
    , _pinInterrupt(pinInterrupt)
{
    static unsigned int cc;

    pinMode(_pinB, INPUT);

    // this is not pretty indeed, unfortunately 'attachInterrupt' is an archaic C function ; it works as follows:
    // every time the SensorHall constructor is called the static int cc increases and a separate interupt function is 'attached' to the pin that reads pulses from the
    // hall sensor. This is because as of now 'attachInterrupt' cannot differentiate between difference instances of a class and therefore a universal interrupt function
    // is not possible.
    switch (cc) {
    case 0:
        attachInterrupt(_pinInterrupt, interruptCallA, CHANGE);
        this->_pulseIndex = 0;
        break;
    case 1:
        attachInterrupt(_pinInterrupt, interruptCallB, CHANGE);
        this->_pulseIndex = 1;
        break;
    case 2:
        attachInterrupt(_pinInterrupt, interruptCallB, CHANGE);
        this->_pulseIndex = 2;
        break;
    case 3:
        attachInterrupt(_pinInterrupt, interruptCallB, CHANGE);
        this->_pulseIndex = 3;
        break;
    }
    cc++;
}

SensorHall::~SensorHall()
{
}
