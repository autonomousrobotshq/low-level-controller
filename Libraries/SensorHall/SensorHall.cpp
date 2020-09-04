#include <Arduino.h>

#include "SensorHall.hpp"

// i am not proud of this

// attach interrupt doesnt allow arguments, so hardcoded globs are required
static unsigned int pulses[HALL_INTERRUPT_COUNT];

void SensorHall::update()
{
    unsigned long millisDev = this->getDuration();
    rpm = millisDev == 0 ? 0 : (pulses[pulseIndex] / cpr) / (millisDev / 60000);
    pulses[pulseIndex] = 0;
}

int SensorHall::getRPM()
{
    return (this->rpm);
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

SensorHall::SensorHall(const unsigned int _pinA,
    const unsigned int _pinB,
    const unsigned int _interrupt,
    const unsigned int _cpr,
    const unsigned long* _globMillis)
    : Sensor(_globMillis)
    , pinA(_pinA)
    , pinB(_pinB)
    , interrupt(_interrupt)
    , cpr(_cpr)
{
    static unsigned int cc;

    pinMode(_pinB, INPUT);
    switch (cc) {
    case 0:
        attachInterrupt(_interrupt, interruptCallA, CHANGE);
        pulseIndex = 0;
        break;
        ;
        ;
    case 1:
        attachInterrupt(_interrupt, interruptCallB, CHANGE);
        pulseIndex = 1;
        break;
        ;
        ;
    case 2:
        attachInterrupt(_interrupt, interruptCallB, CHANGE);
        pulseIndex = 2;
        break;
        ;
        ;
    case 3:
        attachInterrupt(_interrupt, interruptCallB, CHANGE);
        pulseIndex = 3;
        break;
        ;
        ;
    }
    cc++;
}

SensorHall::~SensorHall()
{
}
