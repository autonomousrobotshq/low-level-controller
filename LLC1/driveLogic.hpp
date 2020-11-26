#ifndef DRIVELOGIC_HPP
# define DRIVELOGIC_HPP
# include "Vector.h"
# include "robotEntity.hpp"
# include "steeringLogic.hpp"

class driveLogic
{
public:
	driveLogic(coordinates &coordinates, int &targetDirection, float &targetDistance, robotEntity *robot);
	~driveLogic();
	coordinates		gettargetcoordinates();
	int				gettargetDirection();
	float			gettargetDistance();
	void			settargetDistance(float distancetoTarget);
	void			Drive();
protected:
	int 			m_targetDirection;
	float			m_targetDistance;
	coordinates		m_targetcoordinates;
	robotEntity		*m_robot;
};
#endif