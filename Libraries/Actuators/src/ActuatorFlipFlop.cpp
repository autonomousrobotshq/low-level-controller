#include <Arduino.h>
#include "ActuatorFlipFlop.hpp"

ActuatorFlipFlop::ActuatorFlipFlop(const uint8_t pin, const bool inverted)
    : _pin(pin)
	, _inverted(inverted)
{
}

ActuatorFlipFlop::ActuatorFlipFlop()
{
}

ActuatorFlipFlop::~ActuatorFlipFlop()
{
}

void ActuatorFlipFlop::SetParameters(const uint8_t pin, const bool inverted)
{
	_pin = pin;
	_inverted = inverted;
}

bool ActuatorFlipFlop::Init(const bool default_state)
{
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, _inverted ^ default_state); //pull up/down
	return (true);
}

void ActuatorFlipFlop::SetState(const bool state)
{
    _state = state;
    digitalWrite(_pin, _inverted ^ _state);
}

bool ActuatorFlipFlop::Toggle()
{
    _state = 1 ^ _state;
    digitalWrite(_pin, _inverted ^ _state);
	return (_inverted ^ _state);
}

bool ActuatorFlipFlop::GetState()
{
    return (_inverted ^ _state);
}
