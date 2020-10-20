#ifndef SENSORIMU_HPP
#define SENSORIMU_HPP

#include <Vec3.hpp>
#include <MagneticSensorLsm303.h>

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
	Vec3 _accelerometerData, _magnetometerData;
};

#endif
