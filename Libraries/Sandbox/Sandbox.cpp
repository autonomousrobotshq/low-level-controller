#include "MemoryFree.h"

#include "Common/State.hpp"
#include "Common/Deployment.hpp"
#include "Common/Platform.hpp"
#include "Sandbox/Sandbox.hpp"

namespace sb {

static Sandbox* g_sb;

Sandbox::Sandbox()
    : _controller_lifetime(LLC::pins_relay)
    , _controller_physical_feedback(LLC::pins_physicalfeedback)
    , _controller_anomaly(this, &_controller_lifetime)
    , _sensor_imu(LLC::pins_imu, LLC::imu_calibration_accelerometer, LLC::imu_calibration_magnetometer)
    , _sensor_gps(LLC::pins_gps)
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
    _controller_lifetime.Lifephase(S_STARTUP);
	_controller_physical_feedback.SignalState(S_STARTUP);
}

void Sandbox::Shutdown()
{
	_controller_physical_feedback.SignalState(S_SHUTDOWN);
    _controller_lifetime.Lifephase(S_SHUTDOWN);
}

void Sandbox::SetDriverLogicUpdate(bool (*f)(void))
{
    this->_DriverLogicUpdate = f;
}

void Sandbox::SpinOnce()
{
    // todo update all modules with timing (+ priority queued)
    // anything that could bring about delays must be timeregulated and executed
    // in this function
	while (!_controller_awareness.Update())
        _controller_anomaly.HandleError(g_state);
    while (!_sensor_imu.Update())
        _controller_anomaly.HandleError(g_state);
    while (!_sensor_gps.Update())
        _controller_anomaly.HandleError(g_state);

#if VERBOSITY & DEBUG
        // if (!this->_DriverLogicUpdate)
        // DEBUG: Hook _DriverLogicUpdate is not set
#endif

    while (!_DriverLogicUpdate())
        _controller_anomaly.HandleError(g_state);
    while (!_controller_motor.Update())
        _controller_anomaly.HandleError(g_state);
}

bool Sandbox::Driver(const e_side side, const e_drive_action action, const uint8_t throttle)
{
#if VERBOSITY & DEBUG
    if (throttle >= MOTOR_THROTTLE_LOW && throttle <= MOTOR_THROTTLE_HIGH)
        _controller_motor.Driver(side, action, throttle);
    else {
        // DEBUG: FALSE DRIVER CALL
        ;
    }
#endif
    _controller_motor.Driver(side, action, throttle);
    return (true); // NEEDS TO BE REWORKED
}

bool Sandbox::Driver(const e_side side, const e_drive_action action)
{
    return (_controller_motor.Driver(side, action));
}

int8_t Sandbox::GetRPM(const e_corner corner)
{
    return (_controller_motor.GetRPM(corner));
}

int8_t Sandbox::GetRevolutions(const e_corner corner)
{
    return (_controller_motor.GetRevolutions(corner));
}

int16_t Sandbox::IMUGetNavigationAngle()
{
    return (this->_sensor_imu.GetNavigationAngle());
}

Vec3 Sandbox::IMUGetMagnetoData()
{
    return (this->_sensor_imu.GetMagnetometerData());
}

Vec3 Sandbox::IMUGetAcceleroData()
{
    return (this->_sensor_imu.GetAccelerometerData());
}

int16_t Sandbox::USGetDistance(e_corner corner)
{
	return (this->_controller_awareness.GetDistance(corner));
}

void Sandbox::GPSGetLocation(float* flat, float* flon)
{
    this->_sensor_gps.GetLocation(flat, flon);
}

void Sandbox::GPSGetTime(unsigned long* age, unsigned long* date, unsigned long* time)
{
    this->_sensor_gps.GetTime(age, date, time);
}

int16_t Sandbox::GPSGetSpeed()
{
    return (this->_sensor_gps.GetSpeed());
}

int16_t Sandbox::GPSGetCourse()
{
    return (this->_sensor_gps.GetCourse());
}

int8_t Sandbox::TEMPGetTemperature()
{
    return (this->_controller_awareness.GetTemperature(0)); // IS JUST USING ZERO'TH INDEX FOR TEMP FOR NOW
}

void Sandbox::SIGBeep(const e_siglevel siglevel, const uint8_t count)
{
	_controller_physical_feedback.Beep(siglevel, count);
}

int16_t Sandbox::RAMGetFree()
{
    return (freeMemory());
}

bool Driver(const e_side side, const e_drive_action action) { return (g_sb->Driver(side, action)); }
bool Driver(const e_side side, const e_drive_action action, const uint8_t throttle) { return (g_sb->Driver(side, action, throttle)); }
int IMUGetNavigationAngle() { return (g_sb->IMUGetNavigationAngle()); }
Vec3 IMUGetMagnetoData() { return (g_sb->IMUGetMagnetoData()); }
Vec3 IMUGetAcceleroData() { return (g_sb->IMUGetAcceleroData()); }
int16_t USGetDistance(e_corner corner) { return (g_sb->USGetDistance(corner)); }
void GPSGetLocation(float* flat, float* flon) { g_sb->GPSGetLocation(flat, flon); }
void GPSGetTime(unsigned long* age, unsigned long* date, unsigned long* time) { g_sb->GPSGetTime(age, date, time); }
int16_t GPSGetSpeed() { return (g_sb->GPSGetSpeed()); }
int16_t GPSGetCourse() { return (g_sb->GPSGetCourse()); }
int8_t TEMPGetTemperature() { return (g_sb->TEMPGetTemperature()); }
void SIGBeep(const e_siglevel siglevel, const uint8_t count) { g_sb->SIGBeep(siglevel, count); }

int16_t RAMGetFree() { return (g_sb->RAMGetFree()); }

}
