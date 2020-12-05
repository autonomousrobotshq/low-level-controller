#ifndef SENSOR_IMU_HPP
#define SENSOR_IMU_HPP

#include <LSM303.h>

#include "Common/Datatypes.hpp"
#include "Common/SigFilter.hpp"
#include "Common/Vec3.hpp"

class SensorIMU {
public:
    SensorIMU(const t_pins_imu pins_imu, t_imu_calibration acc_cal, t_imu_calibration mag_cal);
    ~SensorIMU();
    bool Update();
    int16_t GetNavigationAngle();
    Vec3 GetMagnetometerData();
    Vec3 GetAccelerometerData();

private:
    const uint8_t _pin_sda, _pin_scl;
    LSM303 _compass;
    int16_t _navigation_angle;
    SigFilter _filter;
};

#endif
