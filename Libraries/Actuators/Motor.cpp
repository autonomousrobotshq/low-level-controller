#include "Actuators/Motor.hpp"
#include <Arduino.h>

void ActuatorMotor::forward(const uint8_t pulseWidth)
{
    digitalWrite(this->_pinA, LOW);
    digitalWrite(this->_pinB, HIGH);
    analogWrite(this->_pinPWM, pulseWidth);
}

void ActuatorMotor::reverse(const uint8_t pulseWidth)
{
    digitalWrite(this->_pinA, HIGH);
    digitalWrite(this->_pinB, LOW);
    analogWrite(this->_pinPWM, pulseWidth);
}

void ActuatorMotor::halt()
{
    digitalWrite(this->_pinA, LOW);
    digitalWrite(this->_pinB, LOW);
}

ActuatorMotor::ActuatorMotor(const t_pins_motor pins_motor)
    : _pinPWM(pins_motor.pin_pwm)
    , _pinA(pins_motor.pin_a)
    , _pinB(pins_motor.pin_b)
{
    pinMode(_pinPWM, OUTPUT);
    pinMode(_pinA, OUTPUT);
    pinMode(_pinB, OUTPUT);
}

ActuatorMotor::~ActuatorMotor()
{
}
