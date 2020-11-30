#ifndef SENSOR_IMU_HPP
#define SENSOR_IMU_HPP

#include <MagneticSensorLsm303.h>
#include "Common/Vec3.hpp"

class SensorIMU {
public:
    SensorIMU();
    ~SensorIMU();
    bool update();
    float getNavigationAngle();
    Vec3 getMagnetometerData();
    Vec3 getAccelerometerData();

private:
    MagneticSensorLsm303 _compass;
    float _navigationAngle;
};

#endif
