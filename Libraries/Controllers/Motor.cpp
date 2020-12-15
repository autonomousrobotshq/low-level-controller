#include "Controllers/Motor.hpp"
#include "Common/Platform.hpp"

ControllerMotor::ControllerMotor()
{
    for (int i = 0; i < 3; i++) {
        _current_throttle[i] = 0;
        _desired_throttle[i] = 0;
        _action[i] = HALT;
        _is_side[i] = false;
    }
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

bool ControllerMotor::DriverIsReady()
{
    return (_current_throttle[BOTH_SIDES] == _desired_throttle[BOTH_SIDES]);
}

bool ControllerMotor::DriverIsMoving()
{
    return (_current_throttle[BOTH_SIDES] > 0);
}

bool ControllerMotor::DriverIsAccelerating()
{
    return (_current_throttle[BOTH_SIDES] < _desired_throttle[BOTH_SIDES]);
}

bool ControllerMotor::DriverIsDecelerating()
{
    return (_current_throttle[BOTH_SIDES] > _desired_throttle[BOTH_SIDES]);
}

uint8_t ControllerMotor::DriverGetThrottle() {
	return (_current_throttle[BOTH_SIDES]);
}

bool ControllerMotor::SlowHalt() {
	if (_current_throttle[BOTH_SIDES] > 20)
		SetThrottle(BOTH_SIDES, true);
	else
	{
		_actuators_motor[FRONT_LEFT]->halt();
		_actuators_motor[FRONT_RIGHT]->halt();
		_actuators_motor[BACK_LEFT]->halt();
		_actuators_motor[BACK_RIGHT]->halt();
	}
	return (true);
}

bool ControllerMotor::Driver(const e_side side, const e_drive_action action, const uint8_t throttle)
{
    _is_side[side] = true;
    _action[side] = action;
    _desired_throttle[side] = throttle;
    return (true);
}

bool ControllerMotor::Driver(const e_side side, const e_drive_action action)
{
    _is_side[side] = true;
    _action[side] = action;
    _desired_throttle[side] = 255;
    return (true);
}

void ControllerMotor::DriverSetThrottle(const e_side side, const uint8_t throttle)
{
    _is_side[side] = true;
    _desired_throttle[side] = throttle;
}

// current time / desired time * 255
bool ControllerMotor::SetThrottle(const e_side side, bool halt)
{
	uint8_t throttle_increase = 0;
	int16_t curr_throttle = _current_throttle[side];

	throttle_increase = (millis() / TIME_TO_ACCELERATE) * 255;
    if (curr_throttle < _desired_throttle[side]) {
        curr_throttle += throttle_increase;
	}
    else if (curr_throttle > _desired_throttle[side] || halt == true) {
        curr_throttle -= throttle_increase;
	}

	if (curr_throttle > 255)
		curr_throttle = 255;
	else if (curr_throttle < 0)
		curr_throttle = 0;
	_current_throttle[side] = curr_throttle;
    return (true);
}

bool ControllerMotor::Update()
{
    // motor logic here
    //if (_sensors_current[_corner]->getCurrent()) // is overcurrent
    //    return false; // error: overcurrent

    if (_is_side[BOTH_SIDES] == true) {
        switch (_action[BOTH_SIDES]) {
			case FORWARD:
				if (_current_throttle[BOTH_SIDES] != _desired_throttle[BOTH_SIDES])
					SetThrottle(BOTH_SIDES);
				_actuators_motor[FRONT_LEFT]->forward(_current_throttle[BOTH_SIDES]);
				_actuators_motor[FRONT_RIGHT]->forward(_current_throttle[BOTH_SIDES]);
				_actuators_motor[BACK_LEFT]->forward(_current_throttle[BOTH_SIDES]);
				_actuators_motor[BACK_RIGHT]->forward(_current_throttle[BOTH_SIDES]);
				break;
			case BACKWARD:
				if (_current_throttle[BOTH_SIDES] != _desired_throttle[BOTH_SIDES])
					SetThrottle(BOTH_SIDES);
				_actuators_motor[FRONT_LEFT]->reverse(_current_throttle[BOTH_SIDES]);
				_actuators_motor[FRONT_RIGHT]->reverse(_current_throttle[BOTH_SIDES]);
				_actuators_motor[BACK_LEFT]->reverse(_current_throttle[BOTH_SIDES]);
				_actuators_motor[BACK_RIGHT]->reverse(_current_throttle[BOTH_SIDES]);
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
        if (_is_side[LEFT_SIDE] == true) {
            switch (_action[LEFT_SIDE]) {
				case FORWARD:
					if (_current_throttle[LEFT_SIDE] != _desired_throttle[LEFT_SIDE])
						SetThrottle(LEFT_SIDE);
					_actuators_motor[FRONT_LEFT]->forward(_current_throttle[LEFT_SIDE]);
					_actuators_motor[BACK_LEFT]->forward(_current_throttle[LEFT_SIDE]);
					break;
				case BACKWARD:
					if (_current_throttle[LEFT_SIDE] != _desired_throttle[LEFT_SIDE])
						SetThrottle(LEFT_SIDE);
					_actuators_motor[FRONT_LEFT]->reverse(_current_throttle[LEFT_SIDE]);
					_actuators_motor[BACK_LEFT]->reverse(_current_throttle[LEFT_SIDE]);
					break;
				case HALT:
					_actuators_motor[FRONT_LEFT]->halt();
					_actuators_motor[BACK_LEFT]->halt();
					break;
				default:
					break;
            }
		}
        if (_is_side[RIGHT_SIDE] == true) {
            switch (_action[RIGHT_SIDE]) {
				case FORWARD:
					if (_current_throttle[RIGHT_SIDE] != _desired_throttle[RIGHT_SIDE])
						SetThrottle(RIGHT_SIDE);
					_actuators_motor[FRONT_RIGHT]->forward(_current_throttle[RIGHT_SIDE]);
					_actuators_motor[BACK_RIGHT]->forward(_current_throttle[RIGHT_SIDE]);
					break;
				case BACKWARD:
					if (_current_throttle[RIGHT_SIDE] != _desired_throttle[RIGHT_SIDE])
						SetThrottle(RIGHT_SIDE);
					_actuators_motor[FRONT_RIGHT]->reverse(_current_throttle[RIGHT_SIDE]);
					_actuators_motor[BACK_RIGHT]->reverse(_current_throttle[RIGHT_SIDE]);
					break;
				case HALT:
					_actuators_motor[FRONT_RIGHT]->halt();
					_actuators_motor[BACK_RIGHT]->halt();
					break;
				default:
					break;
            }
        }
    }
	for (uint8_t i = 0; i < 3; i++)
		_is_side[i] = false;
    return (true);
}

int8_t ControllerMotor::GetRPM(const e_corner corner)
{
    return (_sensors_hall[corner]->GetRPM());
}

int8_t ControllerMotor::GetRevolutions(const e_corner corner)
{
    return (_sensors_hall[corner]->GetRevolutions());
}
