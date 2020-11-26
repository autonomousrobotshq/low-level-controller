#ifndef STEERINGLOGIC_HPP
# define STEERINGLOGIC_HPP
# include "llc1.hpp"
# include "robotEntity.hpp"
# include "driveLogic.hpp"
class steeringLogic
{
public:
	steeringLogic(float &angle, float &distance);
	~steeringLogic();
	void	pivot();
	// turn angle
	void	driveStraightForward();
	void	driveStraightBackward();
	void	driveDistanceForward();
	void	driveDistanceBackward();
	void	increaseSpeed();
protected:
	int			m_power;
	long		m_rightcount;	
	const float m_countsperRev = 64;
	const float m_wheelDiam = 120;
	float 		m_wheelCirc;
	const float m_pivotDiam = 203.763; // change after info from Max
	float 		m_pivotCirc;
	float 		m_distance;
	float 		m_numRev;
	float 		m_targetCount;
	float		m_angle;
	robotEntity	*m_robot;
};

#endif