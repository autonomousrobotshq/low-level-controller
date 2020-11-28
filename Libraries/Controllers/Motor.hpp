#ifndef CONTROLLER_MOTOR_HPP
# define CONTROLLER_MOTOR_HPP

#include "Controllers/Controller.hpp"
#include "Actuators/Motor.hpp"
#include "Sensors/Current.hpp"
#include "Sensors/Hall.hpp"

enum e_drive_action {FORWARD, BACKWARD, HALT};

class ControllerMotor : public Controller
{
	public:
		bool			Driver(e_corner corner, e_drive_action action);
		ControllerMotor();
		~ControllerMotor();
	private:
		ActuatorMotor	_actuator_motor[4];
		SensorCurrent	_sensor_current;
		SensorHall		_sensor_hall;
};

#endif
