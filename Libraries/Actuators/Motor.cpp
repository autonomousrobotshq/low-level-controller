#include "Actuators/Motor.hpp"
#include <Arduino.h>

void ActuatorMotor::forward(const byte pulseWidth)
{
    digitalWrite(this->_pinA, LOW);
    digitalWrite(this->_pinB, HIGH);
    analogWrite(this->_pinPWM, pulseWidth);
}

void ActuatorMotor::reverse(const byte pulseWidth)
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

ActuatorMotor::ActuatorMotor(const byte pinPWM,
    const byte pinA,
    const byte pinB)
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
