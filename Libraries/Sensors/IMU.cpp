#include "Sensors/IMU.hpp"
#include "Common/Platform.hpp"
#include <Wire.h>

SensorIMU::SensorIMU(const t_pins_imu pins_imu, const t_imu_calibration acc_cal, const t_imu_calibration mag_cal, const uint16_t exec_interval)
	: Sensor(exec_interval)
    , _pin_sda(pins_imu.pin_sda)
    , _pin_scl(pins_imu.pin_scl)
    , _filter(IMU_SAMPLE_COUNT)
{
    Wire.begin();
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
    _filter.Reset();
    for (uint8_t i = 0; i < IMU_SAMPLE_COUNT; i++) {
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

Vec3 SensorIMU::GetMagnetometerData()
{
    return (Vec3(_compass.m.x, _compass.m.y, _compass.m.z));
}
