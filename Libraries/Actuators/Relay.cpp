#include "Actuators/Relay.hpp"
#include <Arduino.h>

ActuatorRelay::ActuatorRelay(const byte pinCooling)
    : _pinCooling(pinCooling)
{
    pinMode(pinCooling, OUTPUT);
    digitalWrite(pinCooling, LOW);
}

ActuatorRelay::~ActuatorRelay()
{
}

void ActuatorRelay::setState(const bool state)
{
    _state = state;
    digitalWrite(_pinCooling, state);
}

bool ActuatorRelay::getState()
{
    return (_state);
}
