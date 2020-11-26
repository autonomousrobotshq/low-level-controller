#include "robotEntity.hpp"
#include "Vector.h"
#include "llc1.hpp"
#include "driveLogic.hpp"

// this is the global time variable which every class instance may use to
// perform time based logic.
static unsigned long globMillis;

robotEntity::robotEntity()
{
	MotorController *m_rightSide = new MotorController(1,2,3); // have to set this all properly before hand
	MotorController *m_leftSide = new MotorController(4,5,6);
	SensorHall 		*m_leftFront = new SensorHall(7,8,9, 10, &globMillis); 
	SensorHall 		*m_leftBack = new SensorHall(7,8,9,10, &globMillis);
	SensorHall 		*m_rightFront  = new SensorHall(7,8,9,10, &globMillis);
	SensorHall 		*m_rightBack  = new SensorHall(7,8,9,10, &globMillis);
	SensorGPS 		*m_sensorGps = new SensorGPS(11,11);
	SensorIMU		*m_sensorKompass = new SensorIMU();

	// underneeth here all the sensors for near hit checks etc.
}

robotEntity::~robotEntity()
{
	delete m_rightSide;
	delete m_leftSide;
	delete m_leftFront;
	delete m_leftBack;
	delete m_rightFront;
	delete m_rightBack;
	delete m_sensorGps;

}

/*
* this function checks all the hardware components and updates the robotEntity
*/
void			robotEntity::updateRobot()
{
	float 			longtitude;
	float 			latitude;
	Vector <float>	position;
	// get current position
	m_sensorGps->getLocation(&latitude, &longtitude);
	// assign these values to the vector;
	position.assign(latitude, longtitude);
	setcurrentPosition(position);
	// assign current Speed
	setcurrentSpeed(m_sensorGps->getSpeed());
	// assign current Direction
	setcurrentDirection(m_sensorGps->getCourse());
}

Vector <float> robotEntity::getcurrentPosition()
{
	return (m_currentPosition);
}

float			robotEntity::getcurrentSpeed()
{
	return (m_currentSpeed);
}

float			robotEntity::getcurrentDirection()
{
	return (m_currentDirection);
}


void			robotEntity::setcurrentPosition(Vector <float> &newPosition)
{
	this->m_currentPosition = newPosition;
}

void			robotEntity::setcurrentDirection(const int &newDirection)
{
	this->m_currentDirection = newDirection;
}

void			robotEntity::setcurrentSpeed(const float &newSpeed)
{
	this->m_currentSpeed = newSpeed;
}

SensorHall*			robotEntity::getSensorhallLeftFront()
{
	return (m_leftFront);
}

SensorHall*			robotEntity::getSensorhallLeftBack()
{
	return (m_leftBack);
}

SensorHall*			robotEntity::getSensorhallRightFront()
{
	return (m_rightFront);
}

SensorHall*			robotEntity::getSensorhallRightBack()
{
	return (m_rightBack);
}

MotorController*		robotEntity::getMotorControllerLeft()
{
	return (m_leftSide);
}

MotorController*		robotEntity::getMotorControllerRight()
{
	return (m_rightSide);
}

SensorIMU*				robotEntity::getKompass()
{
	return (m_sensorKompass);
}

void					robotEntity::setmotorleftfrontforward(int speed)
{
	if (speed < 150)
		//

}
