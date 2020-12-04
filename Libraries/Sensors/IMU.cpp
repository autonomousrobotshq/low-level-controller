#include "Sensors/IMU.hpp"

SensorIMU::SensorIMU(const t_pins_imu pins_imu)
    : _pin_sda(pins_imu.pin_sda)
    , _pin_scl(pins_imu.pin_scl)
{
    _compass.init();
    _compass.enable();
}
SensorIMU::~SensorIMU() { }

bool SensorIMU::Update()
{
    _compass.read();
    _navigationAngle = _compass.getNavigationAngle();

    /* No error handling as of yet.
	** This might be implemented here,
	** but can also be implemented when dissecting the MageticSensorLsm303 code.
	*/

    return (true);
}

Vec3 SensorIMU::GetNormalizedAccelerometerData() {
	Vec3 ret;
	ret.x = 100 * ((_compass.accelerometer.x - ACC_MIN_X) / (ACC_MAX_X - ACC_MIN_X));
	ret.y = 100 * ((_compass.accelerometer.y - ACC_MIN_Y) / (ACC_MAX_Y - ACC_MIN_Y));
	ret.z = 100 * ((_compass.accelerometer.z - ACC_MIN_Z) / (ACC_MAX_Z - ACC_MIN_Z));
	return (ret);
}

Vec3 SensorIMU::GetNormalizedMagnetometerData() {
	Vec3 ret;
	ret.x = 100 * ((_compass.magnetometer.x - MAG_MIN_X) / (MAG_MAX_X - MAG_MIN_X));
	ret.y = 100 * ((_compass.magnetometer.y - MAG_MIN_Y) / (MAG_MAX_Y - MAG_MIN_Y));
	ret.z = 100 * ((_compass.magnetometer.z - MAG_MIN_Z) / (MAG_MAX_Z - MAG_MIN_Z));
	return (ret);
}

float SensorIMU::GetNavigationAngle()
{
    return (this->_navigationAngle);
}

Vec3 SensorIMU::GetAccelerometerData()
{
    return (Vec3(_compass.accelerometer.x, _compass.accelerometer.y, _compass.accelerometer.z));
}

Vec3 SensorIMU::GetMagnetometerData()
{
    return (Vec3(_compass.magnetometer.x, _compass.magnetometer.y, _compass.magnetometer.z));
}
