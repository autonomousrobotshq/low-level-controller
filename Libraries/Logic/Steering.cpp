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
    int power = 10; // need to do this differently
    int revelationcount = 0;

    float distance = abs(angle) / 360.0 * _pivotCirc;

    int numRev = distance / _wheelCirc;

    int targetCount = numRev * _countsPerRev;
    _pivot(angle, revelationcount, targetCount, power); // we can test this type of turning
    _turnAngle(angle, targetCount, power); // or we can use this one;
}

void LogicSteering::_VerifyDirection(int expected_angle)
{
	int current_angle;
	int adjusted_angle;
	current_angle = _sandbox.GPSGetCourse();
	if (current_angle + PRECISION < expected_angle || current_angle - PRECISION > expected_angle)
	{
		// debugging message is needed here because we did not turn as much as we needed
		adjusted_angle = expected_angle - current_angle;
		_retryCount += 1;
		if (_retryCount < 10)
		{
			_pivot(adjusted_angle); // choose one of these
			_turnAngle(adjusted_angle); // choose one of these
			// protection against infinite loop
		}
		else
			;// error message not reached target angle within 10 tries.
	}
}

void LogicSteering::_pivot(int angle, int revelationcount, int targetCount, int power)
{
    if (angle < 0) {
        _sandbox.Driver(FRONT_LEFT, FORWARD, power);
        _sandbox.Driver(BACK_LEFT, FORWARD, power);
        _sandbox.Driver(FRONT_RIGHT, BACKWARD, power);
        _sandbox.Driver(BACK_RIGHT, BACKWARD, power);
        while (abs(revelationcount < targetCount)) {
            if (_sandbox.GetRevelation(FRONT_LEFT) != _sandbox.GetRevelation(BACK_RIGHT)) {
                _sandbox.Driver(FRONT_LEFT, HALT, power);
                _sandbox.Driver(BACK_LEFT, HALT, power);
                _sandbox.Driver(FRONT_RIGHT, HALT, power);
                _sandbox.Driver(BACK_RIGHT, HALT, power);
                // should be changed why do we need power if we are halting?
            }
            revelationcount += _sandbox.GetRevelation(FRONT_LEFT); // I added this so someone has to check if this works
        }
        _sandbox.Driver(FRONT_LEFT, HALT, power);
        _sandbox.Driver(BACK_LEFT, HALT, power);
        _sandbox.Driver(FRONT_RIGHT, HALT, power);
        _sandbox.Driver(BACK_RIGHT, HALT, power);
    }
    if (angle > 0) {
        _sandbox.Driver(FRONT_LEFT, BACKWARD, power);
        _sandbox.Driver(BACK_LEFT, BACKWARD, power);
        _sandbox.Driver(FRONT_RIGHT, FORWARD, power);
        _sandbox.Driver(BACK_RIGHT, FORWARD, power);
        while (abs(revelationcount < targetCount)) {
            if (_sandbox.GetRevelation(FRONT_LEFT) != _sandbox.GetRevelation(BACK_RIGHT)) {
                _sandbox.Driver(FRONT_LEFT, HALT, power);
                _sandbox.Driver(BACK_LEFT, HALT, power);
                _sandbox.Driver(FRONT_RIGHT, HALT, power);
                _sandbox.Driver(BACK_RIGHT, HALT, power);
                // should be changed why do we need power if we are halting?
            }
            revelationcount += _sandbox.GetRevelation(FRONT_LEFT); // I added this so someone has to check if this works
        }
        _sandbox.Driver(FRONT_LEFT, HALT, power);
        _sandbox.Driver(BACK_LEFT, HALT, power);
        _sandbox.Driver(FRONT_RIGHT, HALT, power);
        _sandbox.Driver(BACK_RIGHT, HALT, power);
    }
	_VerifyDirection(angle, PRECISION);
}

void LogicSteering::_turnAngle(int angle, int targetCount, int power)
{
    if (angle > 0) {
        _sandbox.Driver(FRONT_RIGHT, HALT, power);
        _sandbox.Driver(BACK_RIGHT, HALT, power);
        _sandbox.Driver(FRONT_LEFT, FORWARD, power);
        _sandbox.Driver(BACK_LEFT, FORWARD, power);
        long leftcount = 0;
        while (leftcount < targetCount) {
            leftcount += _sandbox.GetRevelation(FRONT_LEFT);
        }
    } else {
        _sandbox.Driver(FRONT_RIGHT, FORWARD, power);
        _sandbox.Driver(BACK_RIGHT, FORWARD, power);
        _sandbox.Driver(FRONT_LEFT, HALT, power);
        _sandbox.Driver(BACK_LEFT, HALT, power);
        long rightcount = 0;
        while (rightcount < targetCount) {
            rightcount += _sandbox.GetRevelation(BACK_RIGHT);
        }
    }
    _sandbox.Driver(FRONT_RIGHT, HALT, power);
    _sandbox.Driver(BACK_RIGHT, HALT, power);
    _sandbox.Driver(FRONT_LEFT, HALT, power);
    _sandbox.Driver(BACK_LEFT, HALT, power);
	_VerifyDirection(angle);
}

void LogicSteering::_driveDistance(int distance)
{
    int leftpower = 50;
    int rightpower = 50;
    int offset = 5;
    int prevLeftCount = 0;
    int prevRightCount = 0;

    float numRev = distance / _wheelCirc;

    float targetCount = numRev * _countsPerRev;

    while (abs(rightcount) < abs(targetCount)) {
        int leftCount = _sandbox.GetRevelation(FRONT_LEFT);
        int rightcount = _sandbox.GetRevelation(BACK_RIGHT);

        int leftDiff = abs(leftCount - prevLeftCount);
        int rightDiff = abs(rightcount - prevRightCount);

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
        // Add some sort of delay ?
    }
    _sandbox.Driver(FRONT_RIGHT, HALT, rightpower);
    _sandbox.Driver(BACK_RIGHT, HALT, rightpower);
    _sandbox.Driver(FRONT_LEFT, HALT, leftpower);
    _sandbox.Driver(BACK_LEFT, HALT, leftpower);
}

void LogicSteering::driveLogic(int distance, int angle)
{
	_starting_angle = _sandbox.GPSGetCourse();
    if (angle != 0)
        _turn(angle);
    // drive straight the distance given by the ROS node
    _driveDistance(distance);
}
