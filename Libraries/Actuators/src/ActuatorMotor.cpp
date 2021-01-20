#include <Arduino.h>
#include "ActuatorMotor.hpp"

ActuatorMotor::ActuatorMotor(const uint8_t pin_pwm, const uint8_t pin_a, const uint8_t pin_b)
    : _pin_pwm(pin_pwm)
    , _pin_a(pin_a)
    , _pin_b(pin_b)
{
}

ActuatorMotor::ActuatorMotor()
{
}

ActuatorMotor::~ActuatorMotor()
{
}

void ActuatorMotor::SetParameters(const uint8_t pin_pwm, const uint8_t pin_a, const uint8_t pin_b)
{
	_pin_pwm = pin_pwm;
	_pin_a = pin_a;
	_pin_b = pin_b;
}

bool ActuatorMotor::Init()
{
    pinMode(_pin_pwm, OUTPUT);
    pinMode(_pin_a, OUTPUT);
    pinMode(_pin_b, OUTPUT);
	return (true);
}

void ActuatorMotor::Forward(const uint8_t pulse_width)
{
    digitalWrite(this->_pin_a, HIGH);
    digitalWrite(this->_pin_b, LOW);
	SetThrottle(pulse_width);
}

void ActuatorMotor::Reverse(const uint8_t pulse_width)
{
    digitalWrite(this->_pin_a, LOW);
    digitalWrite(this->_pin_b, HIGH);
	SetThrottle(pulse_width);
}

void ActuatorMotor::Halt()
{
    digitalWrite(this->_pin_a, LOW);
    digitalWrite(this->_pin_b, LOW);
}

void ActuatorMotor::SetThrottle(const uint8_t pulse_width)
{
    analogWrite(this->_pin_pwm, pulse_width);
}
