#include "Controllers/Motor.hpp"
#include "Common/Platform.hpp"

ControllerMotor::ControllerMotor()
    : _acceleration_factor(50) // this should have it's own setter
{
    for (int i = 0; i < NUM_MOTOR_CONTROLLERS; i++) {
        _actuators_motor[i] = new ActuatorMotor(LLC::pins_motors[i]);
        _current_throttle[i] = 0;
        _starting_throttle[i] = 0;
        _desired_throttle[i] = 0;
        _action[i] = HALT;
        _motorstate[i] = READY;
    }
    for (int i = 0; i < NUM_MOTORS; i++) {
        _sensors_current[i] = new SensorCurrent(LLC::pins_current[i], LLC::exec_intervals.current);
        _sensors_hall[i] = new SensorHall(LLC::pins_hall[i], LLC::exec_intervals.hall);
    }
}

ControllerMotor::~ControllerMotor()
{
    for (int i = 0; i < NUM_MOTOR_CONTROLLERS; i++) {
        delete (_actuators_motor[i]);
    }
    for (int i = 0; i < NUM_MOTORS; i++) {
        delete (_sensors_current[i]);
        delete (_sensors_hall[i]);
    }
}

bool ControllerMotor::IsReady()
{
    return (_motorstate[LEFT] == READY && _motorstate[RIGHT] == READY);
}

bool ControllerMotor::IsMoving()
{
    return (_current_throttle[LEFT] > 0 || _current_throttle[RIGHT] > 0);
}

bool ControllerMotor::IsAccelerating()
{
    return (_motorstate[LEFT] == ACCELERATING || _motorstate[RIGHT] == ACCELERATING);
}

bool ControllerMotor::IsDecelerating()
{
    return (_motorstate[LEFT] == DECELERATING || _motorstate[RIGHT] == DECELERATING);
}

uint8_t ControllerMotor::GetThrottle(const e_side side)
{
    return (_current_throttle[side]);
}

void ControllerMotor::SetThrottle(const e_side side, const uint8_t throttle)
{
    this->SetAction(side, _action[side], throttle);
}

ControllerMotor::e_motorstate ControllerMotor::GetMotorstate(const e_side side, const uint8_t desired_throttle)
{
    if (desired_throttle > _current_throttle[side])
        return (ACCELERATING);
    else if (desired_throttle < _current_throttle[side])
        return (DECELERATING);
    else
        return (READY);
}

void ControllerMotor::SetActionParameters(const e_side side, const e_drive_action action, const uint8_t desired_throttle)
{
    if (_desired_throttle[side] != desired_throttle || _action[side] != action) {
        _motorstate[side] = GetMotorstate(side, desired_throttle);
        _action[side] = action;
        _starting_throttle[side] = _current_throttle[side];
        _desired_throttle[side] = desired_throttle;
        _acceleration_start_time[side] = millis();
    }
}

void ControllerMotor::SetAction(const e_side side, const e_drive_action action, const uint8_t desired_throttle)
{
    if (side == ALL_SIDES) {
        SetActionParameters(LEFT, action, desired_throttle);
        SetActionParameters(RIGHT, action, desired_throttle);
    } else {
        SetActionParameters(side, action, desired_throttle);
    }
}

void ControllerMotor::SetAction(const e_side side, const e_drive_action action)
{
    this->SetAction(side, action, (action == HALT || action == SLOWHALT) ? MOTOR_THROTTLE_LOW : MOTOR_THROTTLE_HIGH);
}

bool ControllerMotor::IsAtDesiredState(const e_side side)
{
    return (_current_throttle[side] == _desired_throttle[side]);
}

uint8_t ControllerMotor::NormalizeThrottle(int16_t throttle)
{
    if (throttle > MOTOR_THROTTLE_HIGH)
        throttle = MOTOR_THROTTLE_HIGH;
    else if (throttle < MOTOR_THROTTLE_LOW)
        throttle = MOTOR_THROTTLE_LOW;

    return (throttle);
}

void ControllerMotor::UpdateAcceleration(const e_side side, const int8_t acceleration)
{
    const unsigned long dev_millis = millis() - _acceleration_start_time[side];
    int16_t acceleration_coef = (dev_millis * acceleration) / 1000;
    int16_t throttle = (dev_millis * acceleration_coef) / 1000;

    if (_motorstate[side] == DECELERATING)
        throttle = _starting_throttle[side] - throttle;

    // overshoot
    if (_motorstate[side] == ACCELERATING && throttle > _desired_throttle[side])
        throttle = _desired_throttle[side];
    else if (_motorstate[side] == DECELERATING && throttle < _desired_throttle[side])
        throttle = _desired_throttle[side];

    _current_throttle[side] = NormalizeThrottle(throttle);
}

void ControllerMotor::UpdateMotorActuator(const e_side side)
{
    switch (_action[side]) {
    case FORWARD:
        _actuators_motor[side]->Forward(_current_throttle[side]);
        break;
    case BACKWARD:
        _actuators_motor[side]->Reverse(_current_throttle[side]);
        break;
    case HALT:
        _actuators_motor[side]->Halt();
        break;
    case SLOWHALT:
        _actuators_motor[side]->SetThrottle(_current_throttle[side]);
        break;
    default:
        // throw error ?
        break;
    }
}

void ControllerMotor::UpdateMotor(const e_side side)
{
    if (_action[side] == HALT) {
        _desired_throttle[side] = 0;
        _current_throttle[side] = 0;
    } else {
        this->UpdateAcceleration(side, _acceleration_factor);
    }

    this->UpdateMotorActuator(side);
}

bool ControllerMotor::Update()
{
    if (!this->IsAtDesiredState(LEFT))
        this->UpdateMotor(LEFT);
    else
        _motorstate[LEFT] = READY;

    if (!this->IsAtDesiredState(RIGHT))
        this->UpdateMotor(RIGHT);
    else
        _motorstate[RIGHT] = READY;

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
