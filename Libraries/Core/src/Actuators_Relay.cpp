#include "Actuators_Relay.hpp"
#include <Arduino.h>

ActuatorRelay::ActuatorRelay(const uint8_t pin)
    : _pin(pin)
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH); // pull up
}

ActuatorRelay::~ActuatorRelay()
{
}

void ActuatorRelay::SetState(const bool state)
{
    _state = state;
    digitalWrite(_pin, 1 ^ state);
}

bool ActuatorRelay::GetState()
{
    return (_state);
}
