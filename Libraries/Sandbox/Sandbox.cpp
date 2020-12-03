#include "MemoryFree.h"

#include "Common/Deployment.hpp"
#include "Common/Platform.hpp"
#include "Sandbox/Sandbox.hpp"

namespace sb {

static Sandbox* g_sb;

Sandbox::Sandbox()
    : _sensor_imu(LLC::pins_imu)
    , _sensor_gps(LLC::pins_gps)
    , _sensor_temp(LLC::pins_temp[0])
{
    if (g_sb) {
        // crit: "Second initialisation of Sandbox!"
    } else {
        g_sb = this;
    }
}

Sandbox::~Sandbox()
{
}

void Sandbox::Setup()
{

}

void Sandbox::SpinOnce()
{
    // todo update all modules with timing (+ priority queued)
    // anything that could bring about delays must be timeregulated and executed
    // in this function
	_controller_motor.Update();
}

void Sandbox::Driver(const e_corner corner, const e_drive_action action, const uint8_t throttle)
{
#if VERBOSITY & DEBUG
    if (throttle >= MOTOR_THROTTLE_LOW && throttle <= MOTOR_THROTTLE_HIGH)
        _controller_motor.Driver(corner, action, throttle);
    else {
        // DEBUG: FALSE DRIVER CALL
        ;
    }
#endif
    _controller_motor.SetValues(corner, action, throttle);
}

// bool Sandbox::Driver(const e_corner corner, const e_drive_action action)
// {
//     return (_controller_motor.Driver(corner, action));
// }

int8_t Sandbox::GetRPM(const e_corner corner)
{
	return (_controller_motor.getRPM(corner));
}
int Sandbox::IMUGetNavigationAngle()
{
    return (this->_sensor_imu.getNavigationAngle());
}

Vec3 Sandbox::IMUGetMagnetoData()
{
    return (this->_sensor_imu.getMagnetometerData());
}

Vec3 Sandbox::IMUGetAcceleroData()
{
    return (this->_sensor_imu.getAccelerometerData());
}

int Sandbox::USGetDistance(e_corner corner)
{
    return (this->_controller_proximity.GetDistance(corner));
}

void Sandbox::GPSGetLocation(float* flat, float* flon)
{
    this->_sensor_gps.GetLocation(flat, flon);
}

void Sandbox::GPSGetTime(unsigned long* age, unsigned long* date, unsigned long* time)
{
    this->_sensor_gps.GetTime(age, date, time);
}

int Sandbox::GPSGetSpeed()
{
    return (this->_sensor_gps.GetSpeed());
}

int Sandbox::GPSGetCourse()
{
    return (this->_sensor_gps.GetCourse());
}

int8_t Sandbox::TEMPGetTemp()
{
    return (this->_sensor_temp.GetTemp());
}

int Sandbox::RAMGetFree()
{
    return (freeMemory());
}

bool Driver(const e_corner corner, const e_drive_action action) {
	return (g_sb->Driver(corner, action));
}

// bool Driver(const e_corner corner, const e_drive_action action, const uint8_t throttle) {
// 	return (g_sb->Driver(corner, action, throttle));

// }

int IMUGetNavigationAngle() {
	return (g_sb->IMUGetNavigationAngle());

}

Vec3 IMUGetMagnetoData() {
	return (g_sb->IMUGetMagnetoData());

}

Vec3 IMUGetAcceleroData() {
	return (g_sb->IMUGetAcceleroData());

}

int USGetDistance(e_corner corner) {
	return (g_sb->USGetDistance(corner));

}

void GPSGetLocation(float* flat, float* flon) {
	g_sb->GPSGetLocation(flat, flon);
}

void GPSGetTime(unsigned long* age, unsigned long* date, unsigned long* time) {
	g_sb->GPSGetTime(age, date, time);
}

int GPSGetSpeed() {
	return (g_sb->GPSGetSpeed());

}

int GPSGetCourse() {
	return (g_sb->GPSGetCourse());

}

int8_t TEMPGetTemp() {
	return (g_sb->TEMPGetTemp());

}

int RAMGetFree() {
	return (g_sb->RAMGetFree());

}

} // namespace sb
