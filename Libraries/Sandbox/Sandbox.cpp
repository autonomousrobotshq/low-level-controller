#include "Common/Deployment.hpp"
#include "Common/Platform.hpp"
#include "Common/Debugging.hpp"
#include "Common/State.hpp"
#include "Sandbox/Sandbox.hpp"

namespace sb {

static Sandbox* g_sb;

Sandbox::Sandbox()
	: _interface_ros(LLC::exec_intervals.interface_ros)
    , _controller_lifetime(LLC::pins_relay)
    , _controller_physical_feedback(LLC::pins_physicalfeedback)
    , _controller_anomaly(this, &_controller_lifetime)
	, _controller_awareness(&_interface_ros)
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

void Sandbox::SetLogicDriverUpdate(bool (*f)(void))
{
    this->_LogicDriverUpdate = f;
}

void Sandbox::SpinOnce()
{
	if (!_interface_ros.Update())
		_controller_anomaly.HandleError(g_state);
    if (!_controller_awareness.Update())
        _controller_anomaly.HandleError(g_state);
    if (!_LogicDriverUpdate())
        _controller_anomaly.HandleError(g_state);
    if (!_controller_motor.Update())
		_controller_anomaly.HandleError(g_state);
}

void Sandbox::ROSAddSubscriber(ros::Subscriber_ &s)
{
	_interface_ros.AddSubscriber(s);
}

void Sandbox::ROSAddPublisher(ros::Publisher &p)
{
	_interface_ros.AddPublisher(p);
}

bool Sandbox::Driver(const e_side side, const e_drive_action action, const uint8_t throttle)
{
    _controller_motor.SetAction(side, action, throttle);
    return (true);
}

bool Sandbox::Driver(const e_side side, const e_drive_action action)
{
    _controller_motor.SetAction(side, action);
	return (true);
}

bool Sandbox::DriverIsReady()
{
    return (_controller_motor.IsReady());
}

bool Sandbox::DriverIsMoving()
{
    return (_controller_motor.IsMoving());
}

bool Sandbox::DriverIsAccelerating()
{
    return (_controller_motor.IsAccelerating());
}

bool Sandbox::DriverIsDecelerating()
{
    return (_controller_motor.IsDecelerating());
}

uint8_t Sandbox::DriverGetThrottle(const e_side side)
{
    return (_controller_motor.GetThrottle(side));
}

void Sandbox::DriverHalt()
{
    Driver(LEFT, HALT);
    Driver(RIGHT, HALT);
    _controller_motor.Update();
}

void Sandbox::DriverSlowHalt(const e_side side)
{
    Driver(side, SLOWHALT);
}

void Sandbox::DriverSlowHalt()
{
    Driver(LEFT, SLOWHALT);
    Driver(RIGHT, SLOWHALT);
}

void Sandbox::DriverSetThrottle(const e_side side, const uint8_t throttle)
{
	_controller_motor.SetThrottle(side, throttle);
}

int8_t Sandbox::GetRPM(const e_corner corner) // -> DOESNT FOLLOW NAMING STYLE
{
    return (_controller_motor.GetRPM(corner));
}

int8_t Sandbox::GetRevolutions(const e_corner corner) // -> DOESNT FOLLOW NAMING STYLE
{
    return (_controller_motor.GetRevolutions(corner));
}

int16_t Sandbox::IMUGetNavigationAngle()
{
    return (this->_controller_awareness._sensor_imu.GetNavigationAngle());
}

Vec3 Sandbox::IMUGetMagnetoData()
{
    return (this->_controller_awareness._sensor_imu.GetMagnetometerData());
}

Vec3 Sandbox::IMUGetAcceleroData()
{
    return (this->_controller_awareness._sensor_imu.GetAccelerometerData());
}

int16_t Sandbox::USGetDistance(e_corner corner)
{
    return (this->_controller_awareness.GetDistance(corner));
}

void Sandbox::GPSGetLocation(float* flat, float* flon)
{
    this->_controller_awareness._sensor_gps.GetLocation(flat, flon);
}

void Sandbox::GPSGetTime(unsigned long* age, unsigned long* date, unsigned long* time)
{
    this->_controller_awareness._sensor_gps.GetTime(age, date, time);
}

int16_t Sandbox::GPSGetSpeed()
{
    return (this->_controller_awareness._sensor_gps.GetSpeed());
}

int16_t Sandbox::GPSGetCourse()
{
    return (this->_controller_awareness._sensor_gps.GetCourse());
}

int8_t Sandbox::TEMPGetTemperature()
{
    return (this->_controller_awareness.GetTemperature(0)); // IS JUST USING ZERO'TH INDEX FOR TEMP FOR NOW
}

void Sandbox::SIGBeep(const e_siglevel siglevel, const uint8_t count)
{
    _controller_physical_feedback.Beep(siglevel, count);
}
void ROSAddSubscriber(ros::Subscriber_ &s) { g_sb->ROSAddSubscriber(s); }
void ROSAddPublisher(ros::Publisher &p) {g_sb->ROSAddPublisher(p); }

bool Driver(const e_side side, const e_drive_action action) { return (g_sb->Driver(side, action)); }
bool Driver(const e_side side, const e_drive_action action, const uint8_t throttle) { return (g_sb->Driver(side, action, throttle)); }
bool DriverIsReady() { return g_sb->DriverIsReady(); }
bool DriverIsMoving() { return g_sb->DriverIsMoving(); }
bool DriverIsAccelerating() { return g_sb->DriverIsAccelerating(); }
bool DriverIsDecelerating() { return g_sb->DriverIsDecelerating(); }
uint8_t DriverGetThrottle(const e_side side) { return g_sb->DriverGetThrottle(side); }
void DriverSetThrottle(const e_side side, const uint8_t throttle) { g_sb->DriverSetThrottle(side, throttle); }
void DriverHalt() { g_sb->DriverHalt(); }
void DriverSlowHalt() { g_sb->DriverSlowHalt(); }
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
}
