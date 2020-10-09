#ifndef MOTORCONTROLLER_HPP
#define MOTORCONTROLLER_HPP
#include <Arduino.h>

class MotorController {
	private:
		const char	_encoder0pinA; //A pin -> the interrupt pin 0
		const char	_encoder0pinB; //B pin -> the digital pin 4
		char		_encoder0PinALast;
		int			_duration; //the number of the pulses
		bool		_direction; //the rotation direction

	public:
		MotorController();
		~MotorController();
		
		void	set_direction(bool new_direction);
		void 	wheelSpeed();
}

#endif
