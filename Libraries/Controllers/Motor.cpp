#include "Controllers/Motor.hpp"
#include "Common/Platform.hpp"

ControllerMotor::ControllerMotor()
{
    for (int i = 0; i < 3; i++) {
        _current_throttle[i] = 0;
        _desired_throttle[i] = 0;
        _action[i] = HALT;
		_acceleration_step[i] = 0;
		_acceleration_time[i] = 0;
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
		_current_throttle[BOTH_SIDES] -= 1;
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
	_acceleration_time[side] = millis() + TIME_TO_ACCELERATE;
	_acceleration_step[side] = TIME_TO_ACCELERATE / 100;
    _is_side[side] = true;
    _action[side] = action;
    _desired_throttle[side] = throttle;
    return (true);
}

bool ControllerMotor::Driver(const e_side side, const e_drive_action action)
{
	_acceleration_time[side] = millis();
	_acceleration_step[side] = TIME_TO_ACCELERATE / 255;
    _is_side[side] = true;
    _action[side] = action;
    _desired_throttle[side] = 255;
    return (true);
}

void ControllerMotor::DriverSetThrottle(const e_side side, const uint8_t throttle)
{
	(void) side;
	(void) throttle;
}

bool ControllerMotor::SetThrottle(const e_side side)
{
	uint8_t throttle_increase = 0;
	uint16_t curr_throttle = _current_throttle[side];
	Serial.println("_acceleration_time[side]: ");
	Serial.println(_acceleration_time[side]);
	Serial.println("_acceleration_step[side]: ");
	Serial.println(_acceleration_step[side]);
	Serial.println("millis(): ");
	Serial.println(millis());
	if (_acceleration_time[side] + _acceleration_step[side] > millis())
		throttle_increase = ((_acceleration_time[side] - millis()) / (_acceleration_step[side]));
	else
		throttle_increase = 1;
	Serial.println("throttle_increase: ");
	Serial.println(throttle_increase);
    if (_current_throttle[side] < _desired_throttle[side]) {
        curr_throttle += throttle_increase;
	}
    else if (_current_throttle[side] > _desired_throttle[side]) {
        curr_throttle -= throttle_increase;
	}

	if (curr_throttle > 255)
		_current_throttle[side] = 255;
	else
		_current_throttle[side] += 1;
	Serial.println("_current_throttle[side]: ");
	Serial.println(_current_throttle[side]);
	//_acceleration_time[side] = millis();
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
				SetThrottle(BOTH_SIDES);
				_actuators_motor[FRONT_LEFT]->forward(_current_throttle[BOTH_SIDES]);
				_actuators_motor[FRONT_RIGHT]->forward(_current_throttle[BOTH_SIDES]);
				_actuators_motor[BACK_LEFT]->forward(_current_throttle[BOTH_SIDES]);
				_actuators_motor[BACK_RIGHT]->forward(_current_throttle[BOTH_SIDES]);
				break;
			case BACKWARD:
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
					SetThrottle(LEFT_SIDE);
					_actuators_motor[FRONT_LEFT]->forward(_current_throttle[LEFT_SIDE]);
					_actuators_motor[BACK_LEFT]->forward(_current_throttle[LEFT_SIDE]);
					break;
				case BACKWARD:
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
					SetThrottle(RIGHT_SIDE);
					_actuators_motor[FRONT_RIGHT]->forward(_current_throttle[RIGHT_SIDE]);
					_actuators_motor[BACK_RIGHT]->forward(_current_throttle[RIGHT_SIDE]);
					break;
				case BACKWARD:
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
