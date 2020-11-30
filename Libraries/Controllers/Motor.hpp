#ifndef CONTROLLER_MOTOR_HPP
# define CONTROLLER_MOTOR_HPP

#include "Common/Datatypes.hpp"
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
		SensorCurrent	_sensor_current[4];
		SensorHall		_sensor_hall[4];
		// this could be put into an array, for scalability
		//ActuatorMotor	_actuator_motor_front_left;
		//ActuatorMotor	_actuator_motor_front_right;
		//ActuatorMotor	_actuator_motor_back_left;
		//ActuatorMotor	_actuator_motor_back_right;

		//SensorCurrent	_sensor_current_front_left;
		//SensorCurrent	_sensor_current_front_right;
		//SensorCurrent	_sensor_current_back_left;
		//SensorCurrent	_sensor_current_back_right;

		//SensorHall		_sensor_hall_front_left;
		//SensorHall		_sensor_hall_front_right;
		//SensorHall		_sensor_hall_back_left;
		//SensorHall		_sensor_hall_back_right;
};

#endif
