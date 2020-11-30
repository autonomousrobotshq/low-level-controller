#include "MemoryFree.h"

#include "Common/Deployment.hpp"
#include "Common/Platform.hpp"
#include "Sandbox/Sandbox.hpp"

namespace sb {

static Sandbox *g_sb;

Sandbox::Sandbox() :
		_sensor_imu(LLC::pins_imu),
		_sensor_gps(LLC::pins_gps),
		_sensor_temp(LLC::pins_temp[0])
{
	if (g_sb)
	{
		// crit: "Second initialisation of Sandbox!"
	}
	else
	{
		g_sb = this;
	}
}

Sandbox::~Sandbox()
{

}

void	Sandbox::Setup()
{

}

void	Sandbox::SpinOnce()
{

}

void	Driver(e_corner corner, e_drive_action action)
{

}

int		IMUGetNavigationAngle()
{

}

Vec3	IMUGetMagnetoData()
{

}

Vec3	IMUGetAcceleroData()
{

}

int		USGetDistance(e_corner corner)
{

}

void	GPSGetLocation(float *flat, float *flon)
{

}

void	GPSGetTime(unsigned long *age, unsigned long *date, unsigned long *time)
{

}

int		GPSGetSpeed()
{

}

int		GPSGetCourse()
{

}

int8_t		TEMPGetTemp()
{
	//return (g_sb->_sensor_temp.GetTemp());
}

int RAMGetFree()
{
	return (freeMemory());	
}

} // namespace sb
