#ifndef SANDBOX_HPP
# define SANDBOX_HPP

#include "Common/Vec3.hpp"
#include "Common/Datatypes.hpp"

#include "Controllers/Motor.hpp"
#include "Controllers/Proximity.hpp"

#include "Interfaces/ROS.hpp"

#include "Sensors/IMU.hpp"
#include "Sensors/GPS.hpp"
#include "Sensors/Temp.hpp"
#include "Sensors/Ultrasonic.hpp"

namespace sb {

class Sandbox
{
	public:
		void	Setup();
		void	SpinOnce();
		Sandbox();
		~Sandbox();
	private:
		unsigned long		_glob_millis;
		ControllerMotor 	_controller_motor;
		ControllerProximity	_controller_proximity;
		InterfaceROS		_interface_ros;
		SensorIMU			_sensor_imu;
		SensorGPS			_sensor_gps;
		SensorTemp			_sensor_temp;
};

// public functions
void	Driver(e_corner corner, e_drive_action action);

int		IMUGetNavigationAngle();
Vec3	IMUGetMagnetoData();
Vec3	IMUGetAcceleroData();

int		USGetDistance(e_corner corner);

void	GPSGetLocation(float *flat, float *flon);
void	GPSGetTime(unsigned long *age, unsigned long *date, unsigned long *time); // overkill?
int		GPSGetSpeed();
int		GPSGetCourse();

int8_t	TEMPGetTemp();

int		RAMGetFree();

} // namespace sb
#endif
