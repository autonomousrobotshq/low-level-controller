#include "ControllerMotor.hpp"

#define MOTOR_THROTTLE_LOW 0
#define MOTOR_THROTTLE_HIGH 255

ControllerMotor::ControllerMotor(const uint8_t motor_count, const t_motor_pins pins[], const uint8_t acceleration_coef)
	: _motor_count(motor_count)
    , _acceleration_coef(acceleration_coef)
{
	_motors = new Motor[motor_count];
    for (int i = 0; i < motor_count; i++) {
        _motors[i].Clear();
		_motors[i].SetParameters(pins[i]);
    }
}

ControllerMotor::ControllerMotor()
	: _motor_count(0)
	, _acceleration_coef(0)
{
}

ControllerMotor::~ControllerMotor()
{
	delete[] _motors;
}

void ControllerMotor::SetParameters(const uint8_t motor_count, const t_motor_pins pins[], const uint8_t acceleration_coef)
{
	if (!_motors)
		_motors = new Motor[motor_count];
    for (int i = 0; i < motor_count; i++) {
        _motors[i].Clear();
		_motors[i].SetParameters(pins[i]);
    }
	_motor_count = motor_count;
	_acceleration_coef = acceleration_coef;
}

bool ControllerMotor::Init()
{
	uint8_t errors = 0;
    for (uint8_t i = 0; i < _motor_count; i++) {
        errors += !_motors[i]._actuators_motor.Init();
	return (errors);
}

void ControllerMotor::Motor::Clear()
{
	_motorstate = READY;
	_action = HALT;
	_current_throttle = 0;
	_starting_throttle = 0;
	_desired_throttle = 0;
	_acceleration_start_time = 0;
	_acceleration_start_throttle = 0;
}

void ControllerMotor::Motor::SetParameters(const t_motor_pins &pins)
{
	_actuators_motor.SetParameters(pins.pin_pwm, pins.pin_a, pins.pin_b);
}

bool ControllerMotor::IsReady()
{
	for (uint8_t i = 0; i < _motor_count; i++)
		if (_motors[i]._motorstate != READY)
				return (false);
	return (true);
}

bool ControllerMotor::IsMoving()
{
	for (uint8_t i = 0; i < _motor_count; i++)
		if (_motors[i]._current_throttle > 0)
				return (true);
	return (false);
}

bool ControllerMotor::IsAccelerating()
{
	for (uint8_t i = 0; i < _motor_count; i++)
		if (_motors[i]._motorstate == ACCELERATING)
				return (true);
	return (false);
}

bool ControllerMotor::IsDecelerating()
{
	for (uint8_t i = 0; i < _motor_count; i++)
		if (_motors[i]._motorstate == DECELERATING)
				return (true);
	return (false);
}

uint8_t ControllerMotor::GetThrottle(const uint8_t i)
{
    return (_motors[i]._current_throttle);
}

void ControllerMotor::SetThrottle(const uint8_t i, const uint8_t throttle)
{
    this->SetAction(i, _motors[i]._action, throttle);
}

ControllerMotor::e_motorstate ControllerMotor::GetMotorstate(const uint8_t i, const uint8_t desired_throttle)
{
    if (desired_throttle > _motors[i]._current_throttle)		return (ACCELERATING);
    else if (desired_throttle < _motors[i]._current_throttle)	return (DECELERATING);
    else																return (READY);
}

void ControllerMotor::SetActionParameters(const uint8_t i, const e_drive_action action, const uint8_t desired_throttle)
{
    if (_motors[i]._desired_throttle != desired_throttle || _motors[i]._action != action) {
        _motors[i]._motorstate = GetMotorstate(i, desired_throttle);
        _motors[i]._action = action;
        _motors[i]._starting_throttle = _motors[i]._current_throttle;
        _motors[i]._desired_throttle = desired_throttle;
        _motors[i]._acceleration_start_time = millis();
    }
}

void ControllerMotor::SetAction(const uint8_t i, const e_drive_action action, const uint8_t desired_throttle)
{
    if (i == ALL) {
		for (uint8_t i = 0; i < _motor_count; i++)
        	SetActionParameters(i, action, desired_throttle);
    } else {
        SetActionParameters(i, action, desired_throttle);
    }
}

void ControllerMotor::SetAction(const uint8_t i, const e_drive_action action)
{
    this->SetAction(i, action, (action == HALT || action == SLOWHALT) ? MOTOR_THROTTLE_LOW : MOTOR_THROTTLE_HIGH);
}

bool ControllerMotor::IsAtDesiredState(const uint8_t i)
{
    return (_motors[i]._current_throttle == _motors[i]._desired_throttle);
}

uint8_t ControllerMotor::NormalizeThrottle(int16_t throttle)
{
    if (throttle > MOTOR_THROTTLE_HIGH)		throttle = MOTOR_THROTTLE_HIGH;
    else if (throttle < MOTOR_THROTTLE_LOW)	throttle = MOTOR_THROTTLE_LOW;
    return (throttle);
}

void ControllerMotor::UpdateAcceleration(const uint8_t i, const int8_t acceleration)
{
    const unsigned long dev_millis = millis() - _motors[i]._acceleration_start_time;
    int16_t acceleration_coef = (dev_millis * acceleration) / 1000;
    int16_t throttle = (dev_millis * acceleration_coef) / 1000;

    if (_motors[i]._motorstate == DECELERATING)
        throttle = _motors[i]._starting_throttle - throttle;

    // overshoot
    if (_motors[i]._motorstate == ACCELERATING && throttle > _motors[i]._desired_throttle)
        throttle = _motors[i]._desired_throttle;
    else if (_motors[i]._motorstate == DECELERATING && throttle < _motors[i]._desired_throttle)
        throttle = _motors[i]._desired_throttle;

    _motors[i]._current_throttle = NormalizeThrottle(throttle);
}

void ControllerMotor::UpdateMotorActuator(const uint8_t i)
{
    switch (_motors[i]._action) {
    case FORWARD:
        _motors[i]._actuators_motor.Forward(_motors[i]._current_throttle);
        break;
    case BACKWARD:
        _motors[i]._actuators_motor.Reverse(_motors[i]._current_throttle);
        break;
    case HALT:
        _motors[i]._actuators_motor.Halt();
        break;
    case SLOWHALT:
        _motors[i]._actuators_motor.SetThrottle(_motors[i]._current_throttle);
        break;
    default:
        // throw error ?
        break;
    }
}

void ControllerMotor::UpdateMotor(const uint8_t i)
{
    if (_motors[i]._action == HALT) {
        _motors[i]._desired_throttle = 0;
        _motors[i]._current_throttle = 0;
    } else {
        this->UpdateAcceleration(i, _acceleration_coef);
    }
    this->UpdateMotorActuator(i);
}

bool ControllerMotor::Update()
{
	for (uint8_t i = 0; i < _motor_count; i++)
	{
    	if (!this->IsAtDesiredState(i))	this->UpdateMotor(i);
    	else							_motors[i]._motorstate = READY;
	}
    return (true);
}
