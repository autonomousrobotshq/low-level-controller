#include "Actuators/Motor.hpp"
#include <Arduino.h>

void ActuatorMotor::Forward(const uint8_t pulse_width)
{
    digitalWrite(this->_pin_a, HIGH);
    digitalWrite(this->_pin_b, LOW);
    analogWrite(this->_pin_pwm, pulse_width);
}

void ActuatorMotor::Reverse(const uint8_t pulse_width)
{
    digitalWrite(this->_pin_a, LOW);
    digitalWrite(this->_pin_b, HIGH);
    analogWrite(this->_pin_pwm, pulse_width);
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

ActuatorMotor::ActuatorMotor(const t_pins_motor pins_motor)
    : _pin_pwm(pins_motor.pin_pwm)
    , _pin_a(pins_motor.pin_a)
    , _pin_b(pins_motor.pin_b)
{
    pinMode(_pin_pwm, OUTPUT);
    pinMode(_pin_a, OUTPUT);
    pinMode(_pin_b, OUTPUT);
}

ActuatorMotor::~ActuatorMotor()
{
}
