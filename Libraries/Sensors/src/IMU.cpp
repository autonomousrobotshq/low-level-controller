#include <Wire.h>
#include "IMU.hpp"

SensorIMU::SensorIMU(const uint8_t pid_sda,
					const uint8_t pin_scl,
					const IMU::cal_t acc_cal,
					const IMU::cal_t mag_cal,
					const uint16_t sample_count,
					const uint16_t exec_interval)
    : Sensor(exec_interval)
    , _pin_sda(pin_sda)
    , _pin_scl(pin_scl)
    , _filter(sample_count)
	, _sample_count(sample_count)
{
    Wire.begin(); // should never be called from constructor ? .begin kills clock
    if (!_compass.init()) {
        // handle ungraceful init
    }
    _compass.enableDefault();

    _compass.m_min = (LSM303::vector<int16_t>) { mag_cal.x_min, mag_cal.y_min, mag_cal.z_min };
    _compass.m_max = (LSM303::vector<int16_t>) { mag_cal.x_max, mag_cal.y_max, mag_cal.z_max };

    (void)acc_cal;
    (void)mag_cal;
}

SensorIMU::~SensorIMU() { }

bool SensorIMU::Update()
{
    if (!this->IsTimeToExecute())
        return (true);
    _filter.Reset();
    for (uint8_t i = 0; i < _sample_count; i++) {
        _compass.read();
        _filter.NewReading(_compass.heading());
    }
    _navigation_angle = _filter.GetFilteredAverage();
    /* No error handling as of yet.
	** This might be implemented here,
	** but can also be implemented when dissecting the MageticSensorLsm303 code.
	*/

    return (true);
}

int16_t SensorIMU::GetNavigationAngle()
{
    return (this->_navigation_angle);
}

Vec3 SensorIMU::GetAccelerometerData()
{
    return (Vec3(_compass.a.x, _compass.a.y, _compass.a.z));
}

void SensorIMU::GetAccelerometerData(int16_t* x, int16_t* y, int16_t* z)
{
    *x = _compass.a.x;
    *y = _compass.a.y;
    *z = _compass.a.z;
}

Vec3 SensorIMU::GetMagnetometerData()
{
    return (Vec3(_compass.m.x, _compass.m.y, _compass.m.z));
}

void SensorIMU::GetMagnetometerData(int16_t* x, int16_t* y, int16_t* z)
{
    *x = _compass.m.x;
    *y = _compass.m.y;
    *z = _compass.m.z;
}
