#include "Common/Platform.hpp"
#include "Controllers/Motor.hpp"

ControllerMotor::ControllerMotor()
{
	for (int i = 0; i < NUM_MOTORS; i++)
	{
		_actuators_motor[i] = new ActuatorMotor(LLC::pins_motors[i]);
		_sensors_current[i] = new SensorCurrent(LLC::pins_current[i]);
		_sensors_hall[i] = new SensorHall(LLC::pins_hall[i]); // use glob millis?
	}
}

ControllerMotor::~ControllerMotor()
{
	for (int i = 0; i < NUM_MOTORS; i++)
	{
		delete _actuators_motor[i];
		delete _sensors_current[i];
		delete _sensors_hall[i];
	}
}

bool	ControllerMotor::Driver(e_corner corner, e_drive_action action)
{
	// motor logic here
	(void)corner;
	(void)action;
	return (false);
}
