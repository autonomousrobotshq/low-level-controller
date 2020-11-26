#include "steeringLogic.hpp"
#include <math.h>

steeringLogic::steeringLogic(float &angle, float &distance)
{
	m_power = 50;
	m_rightcount = 0;
	m_wheelCirc = M_PI * m_wheelDiam;
	m_pivotCirc = M_PI * m_pivotDiam;
	m_distance = abs(angle) / 360.0 * m_pivotCirc;
	m_numRev = m_distance / m_wheelCirc;
	m_targetCount = m_numRev * m_countsperRev;
	m_distance = distance;
	m_angle = angle;
}

steeringLogic::~steeringLogic()
{
}

void	steeringLogic::pivot()
{
	if (m_angle < 0)
		m_power *= -1;
	float correction = -5.0;
	if (m_angle > 0)
		m_angle += correction;
	else if (m_angle < 0)
		m_angle -= correction;
	
	long rpmcount = 0;

	float distance = abs(m_angle) / 360.0 * m_pivotCirc;
	float numRev = distance / m_wheelCirc;

	float targetCount = m_numRev * m_countsperRev;

	MotorController *left = m_robot->getMotorControllerLeft();
	MotorController *right = m_robot->getMotorControllerRight();
	SensorHall *leftfront = m_robot->getSensorhallLeftFront();
	SensorHall *rightfront = m_robot->getSensorhallRightFront();
	// this part is to turn left
	if (m_angle < 0)
	{
		left->reverse(20); // hardcoded we need to test this.
		right->forward(20); // hardcoded motor amounts need to test this.
		while(abs(rpmcount < abs(m_targetCount)))
			rpmcount += leftfront->getRPM();
		left->halt();
		right->halt();
	}
	// this part is to turn right
	else if (m_angle > 0)
	{
		left->forward(20); // hardcoded we need to test this
		right->reverse(20); // hardcoded motor amounts need to test this
		while(abs(rpmcount < abs(m_targetCount)))
			rpmcount += rightfront->getRPM();
		left->halt();
		right->halt();
	}
}

void	steeringLogic::driveStraightForward()
{
	long	rightcount;
	long	leftcount;
	long	prevLeftCount = 0;
	long	prevRightCount = 0;
	int		offset = 5; // might need to tweek this one
	SensorHall *leftfront = m_robot->getSensorhallLeftFront();
	SensorHall *rightfront = m_robot->getSensorhallRightFront();
	MotorController *left = m_robot->getMotorControllerLeft();
	MotorController *right = m_robot->getMotorControllerRight();
	leftcount = leftfront->getRPM();
	rightcount = rightfront->getRPM();

	long leftdiff = leftcount - prevLeftCount;
	long rigthdiff = rightcount - prevRightCount;

	prevLeftCount = leftcount;
	prevRightCount = rightcount;

	int	powerLeft = 50;
	int powerRight = 50;
	if (leftdiff > rigthdiff)
	{
		powerLeft = powerLeft - offset;
		powerRight = powerRight + offset;
	}
	else if (leftdiff < rigthdiff)
	{
		powerLeft = powerLeft + offset;
		powerRight = powerRight - offset;
	}
	left->forward(powerLeft);
	right->forward(powerRight);
}

void	steeringLogic::driveStraightBackward()
{
	long	rightcount;
	long	leftcount;
	long	prevLeftCount = 0;
	long	prevRightCount = 0;
	int		offset = 5; // might need to tweek this one
	SensorHall *leftfront = m_robot->getSensorhallLeftFront();
	SensorHall *rightfront = m_robot->getSensorhallRightFront();
	MotorController *left = m_robot->getMotorControllerLeft();
	MotorController *right = m_robot->getMotorControllerRight();
	leftcount = leftfront->getRPM();
	rightcount = rightfront->getRPM();

	long leftdiff = leftcount - prevLeftCount;
	long rigthdiff = rightcount - prevRightCount;

	prevLeftCount = leftcount;
	prevRightCount = rightcount;

	int	powerLeft = 50; // I dont like hardcoded stuff
	int powerRight = 50; // I dont like hardcoded stuff
	if (leftdiff > rigthdiff)
	{
		powerLeft = powerLeft - offset;
		powerRight = powerRight + offset;
	}
	else if (leftdiff < rigthdiff)
	{
		powerLeft = powerLeft + offset;
		powerRight = powerRight - offset;
	}
	powerleft = 15000;
	left->reverse(powerLeft);
	right->reverse(powerRight);
}

void	steeringLogic::driveDistanceForward()
{
	int leftPower = 50;
	int rightPower = 50;

	int offset = 5;
	long leftCount = 0;
	long rightcount = 0;
	long prevLeftCount = 0;
	long prevRightCount = 0;
	long leftdiff;
	long rigthdiff;

	m_numRev = m_distance / m_wheelCirc;

	m_targetCount = m_numRev * m_countsperRev;
	MotorController *left = m_robot->getMotorControllerLeft();
	MotorController *right = m_robot->getMotorControllerRight();
	
	left->forward(leftPower);
	right->forward(rightPower);

	SensorHall *leftfront = m_robot->getSensorhallLeftFront();
	SensorHall *rightfront = m_robot->getSensorhallRightFront();

	while(abs(rightcount) < abs(m_targetCount))
	{
		leftCount = leftfront->getRPM();
		rightcount = rightfront->getRPM();

		leftdiff = abs(leftCount - prevLeftCount);
		rigthdiff = abs(rightcount - prevRightCount);

		prevLeftCount = leftCount;
		prevRightCount = rightcount;

		if (leftdiff > rigthdiff)
		{
			leftPower = leftPower + offset;
			rightPower = rightPower - offset;
		}
		left->forward(leftPower);
		right->forward(rightPower);
	}
	left->halt();
	right->halt();
}

void	steeringLogic::driveStraightForward()
{
	long	rightcount;
	long	leftcount;
	long	prevLeftCount = 0;
	long	prevRightCount = 0;
	int		offset = 5; // might need to tweek this one
	SensorHall *leftfront = m_robot->getSensorhallLeftFront();
	SensorHall *rightfront = m_robot->getSensorhallRightFront();
	MotorController *left = m_robot->getMotorControllerLeft();
	MotorController *right = m_robot->getMotorControllerRight();
	leftcount = leftfront->getRPM();
	rightcount = rightfront->getRPM();

	long leftdiff = leftcount - prevLeftCount;
	long rigthdiff = rightcount - prevRightCount;

	prevLeftCount = leftcount;
	prevRightCount = rightcount;

	int	powerLeft = 50;
	int powerRight = 50;
	if (leftdiff > rigthdiff)
	{
		powerLeft = powerLeft - offset;
		powerRight = powerRight + offset;
	}
	else if (leftdiff < rigthdiff)
	{
		powerLeft = powerLeft + offset;
		powerRight = powerRight - offset;
	}
	left->forward(powerLeft);
	right->forward(powerRight);
}

void	steeringLogic::driveStraightBackward()
{
	long	rightcount;
	long	leftcount;
	long	prevLeftCount = 0;
	long	prevRightCount = 0;
	int		offset = 5; // might need to tweek this one
	SensorHall *leftfront = m_robot->getSensorhallLeftFront();
	SensorHall *rightfront = m_robot->getSensorhallRightFront();
	MotorController *left = m_robot->getMotorControllerLeft();
	MotorController *right = m_robot->getMotorControllerRight();
	leftcount = leftfront->getRPM();
	rightcount = rightfront->getRPM();

	long leftdiff = leftcount - prevLeftCount;
	long rigthdiff = rightcount - prevRightCount;

	prevLeftCount = leftcount;
	prevRightCount = rightcount;

	int	powerLeft = 50; // I dont like hardcoded stuff
	int powerRight = 50; // I dont like hardcoded stuff
	if (leftdiff > rigthdiff)
	{
		powerLeft = powerLeft - offset;
		powerRight = powerRight + offset;
	}
	else if (leftdiff < rigthdiff)
	{
		powerLeft = powerLeft + offset;
		powerRight = powerRight - offset;
	}
	left->reverse(powerLeft);
	right->reverse(powerRight);
}

void	steeringLogic::driveDistanceBackward()
{
	int leftPower = 50;
	int rightPower = 50;

	int offset = 5;
	long leftCount = 0;
	long rightcount = 0;
	long prevLeftCount = 0;
	long prevRightCount = 0;
	long leftdiff;
	long rigthdiff;

	m_numRev = m_distance / m_wheelCirc;

	m_targetCount = m_numRev * m_countsperRev;
	MotorController *left = m_robot->getMotorControllerLeft();
	MotorController *right = m_robot->getMotorControllerRight();
	
	left->reverse(leftPower);
	right->reverse(rightPower);

	SensorHall *leftfront = m_robot->getSensorhallLeftFront();
	SensorHall *rightfront = m_robot->getSensorhallRightFront();

	while(abs(rightcount) < abs(m_targetCount))
	{
		leftCount = leftfront->getRPM();
		rightcount = rightfront->getRPM();

		leftdiff = abs(leftCount - prevLeftCount);
		rigthdiff = abs(rightcount - prevRightCount);

		prevLeftCount = leftCount;
		prevRightCount = rightcount;

		if (leftdiff > rigthdiff)
		{
			leftPower = leftPower + offset;
			rightPower = rightPower - offset;
		}
		left->reverse(leftPower);
		right->reverse(rightPower);
	}
	left->halt();
	right->halt();
}