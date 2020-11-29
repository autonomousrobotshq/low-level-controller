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

ActuatorMotor::ActuatorMotor(const uint8_t pinPWM,
    const uint8_t pinA,
    const uint8_t pinB)
    : _pinPWM(pinPWM)
    , _pinA(pinA)
    , _pinB(pinB)
{
    pinMode(_pinPWM, OUTPUT);
    pinMode(_pinA, OUTPUT);
    pinMode(_pinB, OUTPUT);
}

ActuatorMotor::~ActuatorMotor()
{
}
