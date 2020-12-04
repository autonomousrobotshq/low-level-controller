#include "Logic/Steering.hpp"
#include "Common/Deployment.hpp"
#include "Sandbox/Sandbox.hpp"
#include <math.h>
#define  PRECISION 5
using namespace sb;

LogicSteering::LogicSteering(Sandbox& sandbox)
    : _sandbox(sandbox)
{
	state = DONE;
}

LogicSteering::~LogicSteering()
{
}

void LogicSteering::driveLogic(int distance, int angle)
{
	Serial.println("distance received");
	Serial.println(distance);
	_starting_angle = _sandbox.GPSGetCourse();
    _target_angle = angle;
	_target_distance = distance;
	_leftcount = 0;
	_rightcount = 0;
	_prev_left_count = 0;
	_prev_right_count = 0;
	_left_diff = 0;
	_right_diff = 0;
	_right_power = 20;
	_left_power = 20;
	_left_power = 50;
    _right_power = 50; // needs to be set
    _offset = 5; // pid controller controls this
	_numRev_distance = _target_distance / _wheelCirc;
	_target_count_distance = _numRev_distance * _countsPerRev;
	Serial.println("target count distance");
	Serial.println(_target_count_distance);
	delay(20000);
	if (angle != 0)
	{
		state = TURNING;
		_pivot(angle);
		// _turnAngle(angle);
	}
}

void LogicSteering::_pivot(int angle)
{
    if (angle < 0) {
        _sandbox.Driver(LEFT_SIDE, FORWARD, _power);
        _sandbox.Driver(RIGHT_SIDE, BACKWARD, _power);
	}
    if (angle > 0) {
		_sandbox.Driver(LEFT_SIDE, BACKWARD, _power);
        _sandbox.Driver(RIGHT_SIDE, FORWARD, _power);
	}
}

void LogicSteering::_turnAngle(int angle)
{
	
    if (angle > 0)
	{
        _sandbox.Driver(RIGHT_SIDE, HALT, _power);
        _sandbox.Driver(LEFT_SIDE, FORWARD, _power);
    }
	else 
	{
        _sandbox.Driver(RIGHT_SIDE, FORWARD, _power);
        _sandbox.Driver(LEFT_SIDE, HALT, _power);
    }
	
}

void LogicSteering::_driveDistance()
{
	_sandbox.Driver(RIGHT_SIDE, FORWARD, _right_power);
	_sandbox.Driver(LEFT_SIDE, FORWARD, _left_power);

	Serial.println("RIGHT_SIDE _power");
	Serial.println(_right_power);
	Serial.println("LEFT_SIDE _power");
	Serial.println(_left_power);
	delay(10000);
}

void LogicSteering::_stop()
{
	_sandbox.Driver(LEFT_SIDE, HALT, _power);
	_sandbox.Driver(RIGHT_SIDE, HALT, _power);
}

void LogicSteering::_update_turn()
{
	int current_angle = _sandbox.IMUGetNavigationAngle();
	if (current_angle < _target_angle + PRECISION && current_angle > _target_angle - PRECISION)
	{
		_stop();
		Serial.println("Done with turning");
		delay(10000);
		state = DRIVING;
		_driveDistance();
	}
}

void LogicSteering::_update_distance()
{
	if (abs(_rightcount) < abs(_target_count_distance) || abs(_leftcount) < abs(_target_count_distance))
	{
		_left_diff = abs(_leftcount - _prev_left_count);
		_right_diff = abs(_rightcount - _prev_right_count);

		_prev_left_count = _leftcount;
		_prev_right_count = _rightcount;

		if (_left_diff > _right_diff) {
			_left_power = _left_power - _offset;
			_right_power = _right_power + _offset;
		} 
		else if (_left_diff < _right_diff) {
			_left_power = _left_power + _offset;
			_right_power = _right_power - _offset;
		}
		Serial.println("new powers per side");
		Serial.println(_right_power);
		Serial.println(_left_power);
		delay(1000);
		_sandbox.Driver(RIGHT_SIDE, FORWARD, _right_power);
		_sandbox.Driver(LEFT_SIDE, FORWARD, _left_power);
		_leftcount += _sandbox.GetRevelation(FRONT_LEFT);
		_rightcount += _sandbox.GetRevelation(BACK_RIGHT);
	}
	else
		_stop();
}

void LogicSteering::drive()
{
	Serial.println("LogicSteering::drive() called");
	if (state == DONE)
		driveLogic(10000, 20);
	if (state == TURNING)
	{
		Serial.print("LogicSteering::drive() -> ANGLE : ");
		Serial.println(_sandbox.IMUGetNavigationAngle());

		_update_turn(); // Stan komt hiervoor terug met een betere oplossing
	}
	if (state == DRIVING)
	{
		Serial.println("update distance");
		delay(1000);
		_update_distance();
	}
	
}
