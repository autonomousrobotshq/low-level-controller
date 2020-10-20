#include <Arduino.h>
#include "MotorController.hpp"

// HOW TO UNFLOAT THIS ?

void	MotorController::forward(const unsigned int throttle)
{
	digitalWrite(this->_pinA, LOW);
	digitalWrite(this->_pinB, HIGH);
	analogWrite(this->_pinPWM, MOTORCONTROLLER_MAX_PWM * ((float)throttle / 100.0));
}

void	MotorController::reverse(const unsigned int throttle)
{
	digitalWrite(this->_pinA, HIGH);
	digitalWrite(this->_pinB, LOW);
	analogWrite(this->_pinPWM, MOTORCONTROLLER_MAX_PWM * ((float)throttle / 100.0));
	
}

void	MotorController::halt()
{
	digitalWrite(this->_pinA, LOW);
	digitalWrite(this->_pinB, LOW);
	analogWrite(this->_pinPWM, 0);
}

MotorController::MotorController(	const unsigned pinPWM,
									const unsigned pinA,
									const unsigned pinB)
									: _pinPWM(pinPWM)
									, _pinA(pinA)
									, _pinB(pinB)
{
	pinMode(_pinPWM, OUTPUT);
	pinMode(_pinA, OUTPUT);
	pinMode(_pinB, OUTPUT);
}

MotorController::~MotorController()
{

}
