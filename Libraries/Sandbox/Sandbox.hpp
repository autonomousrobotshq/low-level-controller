#ifndef SANDBOX_HPP
#define SANDBOX_HPP

#include "Common/Datatypes.hpp"
#include "Common/Vec3.hpp"

#include "Controllers/Anomaly.hpp"
#include "Controllers/PhysicalFeedback.hpp"
#include "Controllers/Lifetime.hpp"
#include "Controllers/Motor.hpp"
#include "Controllers/Awareness.hpp"

#include "Interfaces/ROS.hpp"

#include "Sensors/GPS.hpp"
#include "Sensors/IMU.hpp"
#include "Sensors/Temp.hpp"
#include "Sensors/Ultrasonic.hpp"

namespace sb {

class Sandbox {
public:
    void Setup();
    void Shutdown();
    void SpinOnce();
    Sandbox();
    ~Sandbox();
    bool Driver(const e_side side, const e_drive_action action);
    bool Driver(const e_side side, const e_drive_action action, const uint8_t throttle);
	bool DriverIsReady();
	uint8_t DriverGetThrottle();
	void DriverSetThrottle(const e_side side, const uint8_t throttle);

    int16_t IMUGetNavigationAngle();
    Vec3 IMUGetMagnetoData();
    Vec3 IMUGetAcceleroData();

    int16_t USGetDistance(e_corner corner);

    void GPSGetLocation(float* flat, float* flon);
    void GPSGetTime(unsigned long* age, unsigned long* date, unsigned long* time); // overkill?
    int16_t GPSGetSpeed();
    int16_t GPSGetCourse();
    int8_t TEMPGetTemperature();

	void SIGBeep(const e_siglevel siglevel, const uint8_t count);

    int16_t RAMGetFree();

    int8_t GetRPM(const e_corner corner);
    int8_t GetRevolutions(const e_corner corner);

    void SetDriverLogicUpdate(bool (*f)(void));

private:
    unsigned long _glob_millis;
    ControllerMotor _controller_motor;
    ControllerLifetime _controller_lifetime;
	ControllerPhysicalFeedback _controller_physical_feedback;
    ControllerAnomaly _controller_anomaly;
	ControllerAwareness _controller_awareness;
    SensorIMU _sensor_imu;
    SensorGPS _sensor_gps;

    bool (*_DriverLogicUpdate)(void);
};

// public functions
bool Driver(const e_side side, const e_drive_action action);
bool Driver(const e_side side, const e_drive_action action, const uint8_t throttle);
bool DriverIsReady();
uint8_t DriverGetThrottle();
void DriverSetThrottle(const e_side side, const uint8_t throttle);

int8_t GetRPM(const e_corner corner);

int16_t IMUGetNavigationAngle();
Vec3 IMUGetMagnetoData();
Vec3 IMUGetAcceleroData();

int16_t USGetDistance(e_corner corner);

void GPSGetLocation(float* flat, float* flon);
void GPSGetTime(unsigned long* age, unsigned long* date, unsigned long* time); // overkill?
int16_t GPSGetSpeed();
int16_t GPSGetCourse();

int8_t TEMPGetTemperature();

void SIGBeep(const e_siglevel siglevel, const uint8_t count);

int16_t RAMGetFree();
} // namespace sb
#endif
