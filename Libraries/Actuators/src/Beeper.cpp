#include "Beeper.hpp"
#include <Arduino.h>

ActuatorBeeper::ActuatorBeeper(const uint8_t pin)
    : _pin(pin)
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW); // pull down
}

ActuatorBeeper::~ActuatorBeeper()
{
}

void ActuatorBeeper::SetState(const bool state)
{
    _state = state;
    digitalWrite(_pin, state);
}

bool ActuatorBeeper::GetState()
{
    return (_state);
}
