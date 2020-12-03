#ifndef SANDBOX_HPP
#define SANDBOX_HPP

#include "Common/Datatypes.hpp"
#include "Common/Vec3.hpp"

#include "Controllers/Motor.hpp"
#include "Controllers/Anomaly.hpp"
#include "Controllers/Lifetime.hpp"

#include "Interfaces/ROS.hpp"

#include "Sensors/GPS.hpp"
#include "Sensors/IMU.hpp"
#include "Sensors/Temp.hpp"
#include "Sensors/Ultrasonic.hpp"

namespace sb {

class Sandbox {
public:
    void Setup();
    void SpinOnce();
    Sandbox();
    ~Sandbox();
    bool Driver(const e_corner corner, const e_drive_action action);
    bool Driver(const e_corner corner, const e_drive_action action, const uint8_t throttle);

    int IMUGetNavigationAngle();
    Vec3 IMUGetMagnetoData();
    Vec3 IMUGetAcceleroData();

    int USGetDistance(e_corner corner);

    void GPSGetLocation(float* flat, float* flon);
    void GPSGetTime(unsigned long* age, unsigned long* date, unsigned long* time); // overkill?
    int GPSGetSpeed();
    int GPSGetCourse();
    int8_t TEMPGetTemp();

    int RAMGetFree();
	int8_t	GetRPM(const e_corner corner);

    void check_anomalies();

private:
    unsigned long _glob_millis;
    ControllerMotor _controller_motor;
	ControllerLifetime _controller_lifetime;
    //ControllerProximity _controller_proximity;
    SensorIMU _sensor_imu;
    SensorGPS _sensor_gps;
    SensorTemp _sensor_temp;
    Anomaly _anomaly;
};

// public functions
bool Driver(const e_corner corner, const e_drive_action action);
bool Driver(const e_corner corner, const e_drive_action action, const uint8_t throttle);

int8_t GetRPM(const e_corner corner);

int IMUGetNavigationAngle();
Vec3 IMUGetMagnetoData();
Vec3 IMUGetAcceleroData();

int USGetDistance(e_corner corner);

void GPSGetLocation(float* flat, float* flon);
void GPSGetTime(unsigned long* age, unsigned long* date, unsigned long* time); // overkill?
int GPSGetSpeed();
int GPSGetCourse();

int8_t TEMPGetTemp();

int 	RAMGetFree();
} // namespace sb
#endif
