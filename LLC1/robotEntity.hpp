#ifndef ROBOTENTITY_HPP
# define ROBOTENTITY_HPP
# include "Vector.h"
# include "llc1.hpp"

class robotEntity
{
public:
	robotEntity();
	~robotEntity();
	void				updateRobot();
	Vector	<float> 	getcurrentPosition();
	float				getcurrentSpeed();
	float				getcurrentDirection();
	SensorHall*			getSensorhallLeftFront();
	SensorHall*			getSensorhallLeftBack();
	SensorHall*			getSensorhallRightFront();
	SensorHall*			getSensorhallRightBack();
	MotorController*	getMotorControllerLeft();
	MotorController*	getMotorControllerRight();
	SensorIMU*			getKompass();
private:
	void			setcurrentPosition(Vector	<float> &newPosition);
	void			setcurrentDirection(const int &newDirection);
	void			setcurrentSpeed(const float &newSpeed);
private:
	Vector 	<float> m_currentPosition;
	float			m_currentSpeed;
	int				m_currentDirection;
	MotorController *m_rightSide;
	MotorController *m_leftSide;
	SensorHall		*m_leftFront;
	SensorHall		*m_leftBack;
	SensorHall		*m_rightFront;
	SensorHall		*m_rightBack;
	SensorGPS		*m_sensorGps;
	SensorIMU		*m_sensorKompass;

	
	// hier zometeen de composition classes plaatsen
};

#endif
