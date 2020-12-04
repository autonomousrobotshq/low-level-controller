#include "Controllers/Motor.hpp"
#include "Common/Platform.hpp"

ControllerMotor::ControllerMotor()
{
    _current_throttle = 0;
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

bool ControllerMotor::IsReady()
{
    return _current_throttle == _desired_throttle;
}

bool ControllerMotor::Driver(const e_corner corner, const e_drive_action action, const uint8_t throttle)
{
    _corner = corner;
    _action = action;
    _desired_throttle = throttle;
    return (true);
}

bool ControllerMotor::Driver(const e_corner corner, const e_drive_action action)
{
    _corner = corner;
    _action = action;
    _desired_throttle = 255;
    return (true);
}

bool ControllerMotor::Update()
{
    // motor logic here
    //if (_sensors_current[_corner]->getCurrent()) // is overcurrent
    //    return false; // error: overcurrent

    if (_corner == ALL) {
        switch (_action) {
        case FORWARD:
            if (_current_throttle < _desired_throttle)
                _current_throttle += 1;
            _actuators_motor[FRONT_LEFT]->forward(_current_throttle);
            _actuators_motor[FRONT_RIGHT]->forward(_current_throttle);
            _actuators_motor[BACK_LEFT]->forward(_current_throttle);
            _actuators_motor[BACK_RIGHT]->forward(_current_throttle);
            break;
        case BACKWARD:
            if (_current_throttle < _desired_throttle)
                _current_throttle += 1;
            _actuators_motor[FRONT_LEFT]->reverse(_current_throttle);
            _actuators_motor[FRONT_RIGHT]->reverse(_current_throttle);
            _actuators_motor[BACK_LEFT]->reverse(_current_throttle);
            _actuators_motor[BACK_RIGHT]->reverse(_current_throttle);
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
        switch (_action) {
        case FORWARD:
            if (_current_throttle < _desired_throttle)
                _current_throttle += 1;
            _actuators_motor[_corner]->forward(_current_throttle);
            break;
        case BACKWARD:
            if (_current_throttle > _desired_throttle)
                _current_throttle -= 1;
            _actuators_motor[_corner]->reverse(_current_throttle);
            break;
        case HALT:
            _actuators_motor[_corner]->halt();
            break;
        default:
            break;
        }
    }
    return (true);
}

int8_t ControllerMotor::GetRPM(const e_corner corner)
{
    return (_sensors_hall[corner]->GetRPM());
}

int8_t ControllerMotor::GetRevelation(const e_corner corner)
{
	return (_sensors_hall[corner]->GetRevelations());
}
