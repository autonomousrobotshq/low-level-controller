#include "MotorController.hpp"

// HOW TO UNFLOAT THIS ?

void	MotorController::forward(const unsigned int throttle)
{
	digitalWrite(this->pinA, LOW);
	digitalWrite(this->pinB, HIGH);
	analogWrite(this->pinPWM, MOTORCONTROLLER_MAX_PWM * ((float)throttle / 100.0));
}

void	MotorController::reverse(const unsigned int throttle)
{
	digitalWrite(this->pinA, HIGH);
	digitalWrite(this->pinB, LOW);
	analogWrite(this->pinPWM, MOTORCONTROLLER_MAX_PWM * ((float)throttle / 100.0));
	
}

void	MotorController::halt()
{
	digitalWrite(this->pinA, LOW);
	digitalWrite(this->pinB, LOW);
	analogWrite(this->pinPWM, 0);
}

MotorController::MotorController(	const unsigned pinPWM,
									const unsigned pinA,
									const unsigned pinB)
									: _pinPWM(pinPWM)
									, _pinA(pinA)
									, _pinB(pinB)
{
	pinMode(pinPWM, OUTPUT);
	pinMode(pinA, OUTPUT);
	pinMode(pinB, OUTPUT);
}

MotorController::~MotorController()
{

}
