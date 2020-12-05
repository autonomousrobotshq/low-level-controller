#ifndef SENSOR_IMU_HPP
#define SENSOR_IMU_HPP

#include <MagneticSensorLsm303.h>

#include "Common/Datatypes.hpp"
#include "Common/Vec3.hpp"
#include "Common/SigFilter.hpp"

class SensorIMU {
public:
    SensorIMU(const t_pins_imu pins_imu);
    ~SensorIMU();
    bool Update();
    uint16_t GetNavigationAngle();
    Vec3 GetMagnetometerData();
    Vec3 GetAccelerometerData();

private:
    const uint8_t _pin_sda, _pin_scl;
    MagneticSensorLsm303 _compass;
    uint16_t _navigation_angle;
	SigFilter _filter;
};

#endif
