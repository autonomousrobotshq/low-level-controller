#include <math.h>
#include "Common/Deployment.hpp"
#include "Sandbox/Sandbox.hpp"
#include "Logic/Steering.hpp"

using namespace sb;

LogicSteering::LogicSteering(Sandbox &sandbox) :
	_sandbox(sandbox)
{
	
}

LogicSteering::~LogicSteering()
{

}

void LogicSteering::_turn(int angle)
{
	int power = 10; // need to do this differently
	if (angle < 0)
		power *= -1;
	float correction = -5.0;
	if (angle > 0)
		angle += correction;
	else if (angle < 0)
		angle -= correction;
	
	int rpmcount = 0;

	float distance = abs(angle) / 360.0 * _pivotCirc;

	int numRev = distance / _wheelCirc;

	int targetCount = numRev * _countsPerRev;
	_pivot(angle, rpmcount, targetCount, power); // we can test this type of turning
	_turnAngle(	angle, targetCount,power); // or we can use this one;
}

void	LogicSteering::_pivot(int angle, int rpmcount, int targetCount, int power)
{
	
	if(angle < 0)
	{
		_sandbox.Driver(FRONT_LEFT, FORWARD, power);
		_sandbox.Driver(BACK_LEFT, FORWARD, power);
		_sandbox.Driver(FRONT_RIGHT, BACKWARD, power);
		_sandbox.Driver(BACK_RIGHT, BACKWARD, power);
		while(abs(rpmcount < targetCount))
		{
			if (_sandbox.GetRPM(FRONT_LEFT) != _sandbox.GetRPM(BACK_RIGHT))
			{
				_sandbox.Driver(FRONT_LEFT, HALT, power);
				_sandbox.Driver(BACK_LEFT, HALT, power);
				_sandbox.Driver(FRONT_RIGHT, HALT, power);
				_sandbox.Driver(BACK_RIGHT, HALT, power);
				// should be changed why do we need power if we are halting? 
			}
			rpmcount += _sandbox.GetRPM(FRONT_LEFT); // I added this so someone has to check if this works
		}
		_sandbox.Driver(FRONT_LEFT, HALT, power);
		_sandbox.Driver(BACK_LEFT, HALT, power);
		_sandbox.Driver(FRONT_RIGHT, HALT, power);
		_sandbox.Driver(BACK_RIGHT, HALT, power);
	}
	if(angle > 0)
	{
		_sandbox.Driver(FRONT_LEFT, BACKWARD, power);
		_sandbox.Driver(BACK_LEFT, BACKWARD, power);
		_sandbox.Driver(FRONT_RIGHT, FORWARD, power);
		_sandbox.Driver(BACK_RIGHT, FORWARD, power);
		while(abs(rpmcount < targetCount))
		{
			if (_sandbox.GetRPM(FRONT_LEFT) != _sandbox.GetRPM(BACK_RIGHT))
			{
				_sandbox.Driver(FRONT_LEFT, HALT, power);
				_sandbox.Driver(BACK_LEFT, HALT, power);
				_sandbox.Driver(FRONT_RIGHT, HALT, power);
				_sandbox.Driver(BACK_RIGHT, HALT, power);
				// should be changed why do we need power if we are halting? 
			}
			rpmcount += _sandbox.GetRPM(FRONT_LEFT); // I added this so someone has to check if this works
		}
		_sandbox.Driver(FRONT_LEFT, HALT, power);
		_sandbox.Driver(BACK_LEFT, HALT, power);
		_sandbox.Driver(FRONT_RIGHT, HALT, power);
		_sandbox.Driver(BACK_RIGHT, HALT, power);
	}
}

void	LogicSteering::_turnAngle(int angle, int targetCount, int power)
{
	if (angle > 0)
	{
		_sandbox.Driver(FRONT_RIGHT, HALT, power);
		_sandbox.Driver(BACK_RIGHT, HALT, power);
		_sandbox.Driver(FRONT_LEFT, FORWARD, power);
		_sandbox.Driver(BACK_LEFT, FORWARD, power);
		long leftcount = 0;
		while(leftcount < targetCount)
		{
			leftcount += _sandbox.GetRPM(FRONT_LEFT);
		}
	}
	else
	{
		_sandbox.Driver(FRONT_RIGHT, FORWARD, power);
		_sandbox.Driver(BACK_RIGHT, FORWARD, power);
		_sandbox.Driver(FRONT_LEFT, HALT, power);
		_sandbox.Driver(BACK_LEFT, HALT, power);
		long rightcount = 0;
		while(rightcount < targetCount)
		{
			rightcount += _sandbox.GetRPM(BACK_RIGHT);
		}
	}
	_sandbox.Driver(FRONT_RIGHT, HALT, power);
	_sandbox.Driver(BACK_RIGHT, HALT, power);
	_sandbox.Driver(FRONT_LEFT, HALT, power);
	_sandbox.Driver(BACK_LEFT, HALT, power);
}

void	LogicSteering::_driveDistance(int distance)
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

	while(abs(rightcount) < abs(targetCount))
	{
		leftCount = _sandbox.GetRPM(FRONT_LEFT);
		rightcount = _sandbox.GetRPM(BACK_RIGHT);

		leftDiff = abs(leftCount - prevLeftCount);
		rightDiff = abs(rightcount - prevRightCount);

		prevLeftCount = leftCount;
		prevRightCount = rightcount;

		if (leftDiff > rightDiff)
		{
			leftpower = leftpower - offset;
			rightpower = rightpower + offset;
		}
		else if ( leftDiff < rightDiff)
		{
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

void	LogicSteering::driveLogic(int distance, int angle)
{
	if(angle != 0)
		_turn(angle);
	// drive straight the distance given by the ROS node
	_driveDistance(distance);
}
