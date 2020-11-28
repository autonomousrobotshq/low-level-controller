#ifndef CONTROLLER_MOTOR_HPP
# define CONTROLLER_MOTOR_HPP

#include "Controller/Controller.hpp"

namespace motorcontroller {

enum {FRONT_LEFT, FRONT_RIGHT, BACK_LEFT, BACK_RIGHT, ALL} e_corner;
enum {FORWARD, BACKWARD, HALT} e_drive_action;

class ControllerMotor : public Controller
{
	public:
		bool			Driver(e_corner corner, e_drive_action action);
		ControllerMotor();
		~ControllerMotor();
	private:
		ActuatorMotor	_actuator_motor;
		SensorCurrent	_sensor_current;
		SensorHall		_sensor_hall;
};

} // namespace motorcontroller
#endif
