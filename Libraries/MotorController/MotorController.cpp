#include "MotorController.hpp"

//The sample code for driving one way motor encoder

MotorController::MotorController() : _encoder0pinA(2), _encoder0pinB(4), _duration(0)
{
	// EncoderInit();//Initialize the module
}

void 	MotorController::wheelSpeed()
{
	int Lstate = digitalRead(_encoder0pinA);
	if (this->_encoder0PinALast == LOW && Lstate == HIGH)
	{
		int val = digitalRead(_encoder0pinB);
		if (val == LOW && this->_direction)
		{
			this->_direction = false; //Reverse
		}
		else if (val == HIGH && !this->_direction)
		{
			this->_direction = true;  //Forward
		}
	}
	this->_encoder0PinALast = Lstate;

	if (!this->_direction)
		this->_duration++;
	else
		this->_duration--;
}

void	MotorController::set_direction(bool new_direction)
{
	this->_direction = new_direction;
}

void EncoderInit()
{
	this->_direction = true;//default -> Forward
	pinMode(_encoder0pinB, INPUT);
	attachInterrupt(0, wheelSpeed, CHANGE);
}

