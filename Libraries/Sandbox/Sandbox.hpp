

#ifndef SANDBOX_HPP
# define SANDBOX_HPP

#include "Controllers/Motor.hpp"
#include "Sensors/IMU.hpp"
#include "Sensors/GPS.hpp"
#include "Sensors/Temp.hpp"
#include "Sensors/Ultrasonic.hpp"

namespace sandbox {

class Sandbox
{
	public:
		void	Setup();
		void	SpinOnce();
		Sandbox();
		~Sandbox();
	private:
		unsigned int		_glob_millis;
		ControllerMotor 	_controller_motor;
		SensorIMU			_sensor_imu;
		SensorGPS			_sensor_gps;
		SensorUltrasonic	_sensor_ultrasonic;
		SensorTemp			_sensor_temp;
};

static Sandbox *sb;

// public functions
void	Driver(e_corner corner, e_drive_action action);

int		IMUGetNavigationAngle();
Vec3	IMUGetMagnetoData();
Vec3	IMUGetAcceleroData();

int		USGetDistance(e_corner corner;

void	GPSGetLocation(float *flat, float *flon);
void	GPSGetTime(unsigned long *age, unsigned long *date, unsigned long *time); // overkill?
int		GPSGetSpeed();
int		GPSGetCourse();

int		TEMPGetTemp();

} // namespace sandbox
#endif
