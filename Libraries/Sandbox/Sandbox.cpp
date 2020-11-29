#include "Sandbox/Sandbox.hpp"

static Sandbox *sb;

Sandbox::Sandbox() :
		_sensor_imu(IMU_SDA, IMU_SCL),
		_sensor_gps(GPS_TX, GPS_RX),
		_sensor_temp(0)
{
	if (sb)
	{
		// crit: "Second initialisation of Sandbox!"
	}
	else
	{
		sb = this;
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

int		TEMPGetTemp()
{

}

unsigned int RAMGetFree()
{

}
