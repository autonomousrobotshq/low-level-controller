#include "llc1.hpp"
#include "driveLogic.hpp"
/* This code makes our robot drive. it gets as input the distance and direction of the new position
* it checks if the robot is currently facing the right direction if its not facing the right direction
* it turns the robot around until its linned up towards the right direction. after that it start driving
* towards the new position and checks the direction and distance the entire time. if its drifting of course
* the robot will change the direction so its linned up again. After the location has been reached the robot halts
*/

driveLogic::driveLogic(coordinates &coordinates, int &targetDirection, float &targetDistance, robotEntity *robot) :
	m_targetcoordinates(coordinates),
	m_targetDirection(targetDirection),
	m_targetDistance(targetDistance),
	m_robot(robot)
{
}

driveLogic::~driveLogic()
{
}

coordinates	driveLogic::gettargetcoordinates()
{
	return (m_targetcoordinates);
}

int				driveLogic::gettargetDirection()
{
	return (m_targetDirection);
}

float			driveLogic::gettargetDistance()
{
	return (m_targetDistance);
}

void			driveLogic::settargetDistance(float distancetoTarget)
{
	this->m_targetDistance = distancetoTarget;
}

void			driveLogic::Drive()
{
	// check if robot is facing right direction at that moment
	SensorIMU *kompass = m_robot->getKompass();

	float currentDirection = kompass->getNavigationAngle();
	
	float turn_angle = currentDirection - m_targetDirection;
	steeringLogic steer(turn_angle, m_targetDistance);
	steer.pivot();
	steer.driveDistanceForward();
}
// drive towards destination

// check if robot is drifting

// redirect robot into right direction

// check if the location has been reached

