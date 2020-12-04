#include "Logic/Steering.hpp"
#include "Common/Deployment.hpp"
#include "Sandbox/Sandbox.hpp"
#include <math.h>
#define  PRECISION 5
using namespace sb;

LogicSteering::LogicSteering(Sandbox& sandbox)
    : _sandbox(sandbox)
{
}

LogicSteering::~LogicSteering()
{
}

void LogicSteering::_turn(int angle)
{
    
    int revelationcount = 0;

    float distance = abs(angle) / 360.0 * _pivotCirc;

    int numRev = distance / _wheelCirc;

    _target_count = numRev * _countsPerRev;
    _pivot(angle, revelationcount); // we can test this type of turning
    // _turnAngle(angle); // or we can use this one;
}

void LogicSteering::_VerifyDirection()
{
	int current_angle;
	int adjusted_angle;
	current_angle = _sandbox.GPSGetCourse();
	if (current_angle + PRECISION < _target_angle || current_angle - PRECISION > expected_angle)
	{
		// debugging message is needed here because we did not turn as much as we needed
		adjusted_angle = _target_angle - current_angle;
		_retryCount += 1;
		if (_retryCount < 10)
		{
			_turn(adjusted_angle);
		}
		else
			;// error message not reached target angle within 10 tries.
	}
}

void LogicSteering::_pivot(int angle, int revelationcount)
{
    if (angle < 0) {
        _sandbox.Driver(FRONT_LEFT, FORWARD, _power);
        _sandbox.Driver(BACK_LEFT, FORWARD, _power);
        _sandbox.Driver(FRONT_RIGHT, BACKWARD, _power);
        _sandbox.Driver(BACK_RIGHT, BACKWARD, _power);
	}
    if (angle > 0) {
		_sandbox.Driver(FRONT_LEFT, BACKWARD, _power);
        _sandbox.Driver(BACK_LEFT, BACKWARD, _power);
        _sandbox.Driver(FRONT_RIGHT, FORWARD, _power);
        _sandbox.Driver(BACK_RIGHT, FORWARD, _power);
	}
}

void LogicSteering::_turnAngle(int angle)
{
	
    if (angle > 0)
	{
        _sandbox.Driver(FRONT_RIGHT, HALT, _power);
        _sandbox.Driver(BACK_RIGHT, HALT, _power);
        _sandbox.Driver(FRONT_LEFT, FORWARD, _power);
        _sandbox.Driver(BACK_LEFT, FORWARD, _power);
    }
	else 
	{
        _sandbox.Driver(FRONT_RIGHT, FORWARD, _power);
        _sandbox.Driver(BACK_RIGHT, FORWARD, _power);
        _sandbox.Driver(FRONT_LEFT, HALT, _power);
        _sandbox.Driver(BACK_LEFT, HALT, _power);
    }
	
}

void LogicSteering::_driveDistance(int distance)
{
    int leftpower = 50;
    int rightpower = 50;
    int offset = 5;
    int leftCount = 0;
    int rightcount = 0;
    int prevLeftCount = 0;
    int prevRightCount = 0;
    int leftDiff;
    int rightDiff;

    float numRev = distance / _wheelCirc;

    float targetCount = numRev * _countsPerRev;

    while (abs(rightcount) < abs(targetCount)) {
        leftCount = _sandbox.GetRevelation(FRONT_LEFT);
        rightcount = _sandbox.GetRevelation(BACK_RIGHT);

        leftDiff = abs(leftCount - prevLeftCount);
        rightDiff = abs(rightcount - prevRightCount);

        prevLeftCount = leftCount;
        prevRightCount = rightcount;

        if (leftDiff > rightDiff) {
            leftpower = leftpower - offset;
            rightpower = rightpower + offset;
        } else if (leftDiff < rightDiff) {
            leftpower = leftpower + offset;
            rightpower = rightpower - offset;
        }
        _sandbox.Driver(FRONT_RIGHT, FORWARD, rightpower);
        _sandbox.Driver(BACK_RIGHT, FORWARD, rightpower);
        _sandbox.Driver(FRONT_LEFT, FORWARD, leftpower);
        _sandbox.Driver(BACK_LEFT, FORWARD, leftpower);
    }
    _sandbox.Driver(FRONT_RIGHT, HALT, rightpower);
    _sandbox.Driver(BACK_RIGHT, HALT, rightpower);
    _sandbox.Driver(FRONT_LEFT, HALT, leftpower);
    _sandbox.Driver(BACK_LEFT, HALT, leftpower);
}

void LogicSteering::driveLogic(int distance, int angle)
{
	// start turning
	_starting_angle = _sandbox.GPSGetCourse();
    _start_turning(angle);
	_target_angle = angle;
	// start driving distance
	// update distance
	// stop driving distance
}

void LogicSteering::_start_turning(int angle)
{
	if (angle != 0)
        _turn(angle);
}

void LogicSteering::_stopturning()
{
		_sandbox.Driver(FRONT_LEFT, HALT, _power);
		_sandbox.Driver(BACK_LEFT, HALT, _power);
		_sandbox.Driver(FRONT_RIGHT, HALT, _power);
		_sandbox.Driver(BACK_RIGHT, HALT, _power);
}

void LogicSteering::update_turn()
{
	_revelation_count += _sandbox.GetRevelation(FRONT_LEFT);
	// _leftcount += _sandbox.GetRevelation(FRONT_LEFT);
	// _rightcount += _sandbox.GetRevelation(BACK_RIGHT); being activated when we start testing the other steering form
	if (_revelation_count == _target_count)
	{
		_stopturning();
		_VerifyDirection()
	}
}
