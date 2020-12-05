#include "Common/Platform.hpp"
#include "Sensors/IMU.hpp"

SensorIMU::SensorIMU(const t_pins_imu pins_imu)
    : _pin_sda(pins_imu.pin_sda)
    , _pin_scl(pins_imu.pin_scl)
	, _filter(IMU_SAMPLE_COUNT)
{
    _compass.init();
    _compass.enable();
}
SensorIMU::~SensorIMU() { }

bool SensorIMU::Update()
{
	_filter.Reset();
	for (uint8_t i = 0; i < IMU_SAMPLE_COUNT; i++)
	{
    	_compass.read();
    	_filter.NewReading(_compass.getNavigationAngle());
	}
	_navigation_angle = _filter.GetFilteredAverage();
    /* No error handling as of yet.
	** This might be implemented here,
	** but can also be implemented when dissecting the MageticSensorLsm303 code.
	*/

    return (true);
}

uint16_t SensorIMU::GetNavigationAngle()
{
    return (this->_navigation_angle);
}

Vec3 SensorIMU::GetAccelerometerData()
{
    return (Vec3(_compass.accelerometer.x, _compass.accelerometer.y, _compass.accelerometer.z));
}

Vec3 SensorIMU::GetMagnetometerData()
{
    return (Vec3(_compass.magnetometer.x, _compass.magnetometer.y, _compass.magnetometer.z));
}
