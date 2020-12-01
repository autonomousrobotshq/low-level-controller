#include "Actuators/Motor.hpp"
#include <Arduino.h>

<<<<<<< HEAD
void ActuatorMotor::forward(const uint8_t &pulseWidth)
=======
void ActuatorMotor::forward(const uint8_t pulse_width)
>>>>>>> 5c31d08fce932d8e7198b1f97dc90c1448dddf38
{
    digitalWrite(this->_pin_a, LOW);
    digitalWrite(this->_pin_b, HIGH);
    analogWrite(this->_pin_pwm, pulse_width);
}

<<<<<<< HEAD
void ActuatorMotor::reverse(const uint8_t &pulseWidth)
=======
void ActuatorMotor::reverse(const uint8_t pulse_width)
>>>>>>> 5c31d08fce932d8e7198b1f97dc90c1448dddf38
{
    digitalWrite(this->_pin_a, HIGH);
    digitalWrite(this->_pin_b, LOW);
    analogWrite(this->_pin_pwm, pulse_width);
}

void ActuatorMotor::halt()
{
    digitalWrite(this->_pin_a, LOW);
    digitalWrite(this->_pin_b, LOW);
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
