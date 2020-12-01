#include "Controllers/Motor.hpp"
#include "Common/Platform.hpp"

ControllerMotor::ControllerMotor()
{
    for (int i = 0; i < NUM_MOTORS; i++) {
        _actuators_motor[i] = new ActuatorMotor(LLC::pins_motors[i]);
        _sensors_current[i] = new SensorCurrent(LLC::pins_current[i]);
        _sensors_hall[i] = new SensorHall(LLC::pins_hall[i]); // use glob millis?
    }
}

ControllerMotor::~ControllerMotor()
{
    for (int i = 0; i < NUM_MOTORS; i++) {
        delete _actuators_motor[i];
        delete _sensors_current[i];
        delete _sensors_hall[i];
    }
}

bool ControllerMotor::Driver(const e_corner corner, const e_drive_action action)
{
    // motor logic here
    // if (_sensors_current[corner]->getCurrent()) // is overcurrent
    // 	return false; // error: overcurrent
    // if (corner == ALL) {
    // 	_actuators_motor[FRONT_LEFT]->drive_commands[action]();
    // 	_actuators_motor[FRONT_RIGHT]->drive_commands[action];
    // 	_actuators_motor[BACK_LEFT]->drive_commands[action];
    // 	_actuators_motor[BACK_RIGHT]->drive_commands[action];
    // }
    // else
    // 	_actuators_motor[corner]->drive_commands[action];
    (void)corner;
    (void)action;
    return (false);
}

bool ControllerMotor::Driver(const e_corner corner, const e_drive_action action, const uint8_t throttle)
{
	Sensor	t;
	uint8_t start_throttle = 0;

	t.setWaitTime(50);
    // motor logic here
    if (_sensors_current[corner]->getCurrent()) // is overcurrent
        return false; // error: overcurrent
    if (corner == ALL) {
        switch (action) {
        case FORWARD:
			while (start_throttle <= throttle) {
				if (t.isWaiting() == false) {
					_actuators_motor[FRONT_LEFT]->forward(start_throttle);
					_actuators_motor[FRONT_RIGHT]->forward(start_throttle);
					_actuators_motor[BACK_LEFT]->forward(start_throttle);
					_actuators_motor[BACK_RIGHT]->forward(start_throttle);
					start_throttle += 1;
					t.setWaitTime(50);
				}
			}
            break;
        case BACKWARD:
            while (start_throttle <= throttle) {
				if (t.isWaiting() == false) {
					_actuators_motor[FRONT_LEFT]->reverse(start_throttle);
					_actuators_motor[FRONT_RIGHT]->reverse(start_throttle);
					_actuators_motor[BACK_LEFT]->reverse(start_throttle);
					_actuators_motor[BACK_RIGHT]->reverse(start_throttle);
					start_throttle += 1;
					t.setWaitTime(50);
				}
			}
            break;
        case HALT:
            _actuators_motor[FRONT_LEFT]->halt();
            _actuators_motor[FRONT_RIGHT]->halt();
            _actuators_motor[BACK_LEFT]->halt();
            _actuators_motor[BACK_RIGHT]->halt();
            break;
        default:
            break;
        }
    } else {
        switch (action) {
        case FORWARD:
			while (start_throttle <= throttle) {
				if (t.isWaiting() == false) {
            		_actuators_motor[corner]->forward(throttle);
					start_throttle += 1;
					t.setWaitTime(50);
				}
			}
            break;
        case BACKWARD:
            while (start_throttle <= throttle) {
				if (t.isWaiting() == false) {
            		_actuators_motor[corner]->reverse(throttle);
					start_throttle += 1;
					t.setWaitTime(50);
				}
			}
            break;
        case HALT:
            _actuators_motor[corner]->halt();
            break;
        default:
            break;
        }
    }
    return (false);
}
