#include "SensorIMU.hpp"

SensorIMU::SensorIMU() {
	_compass.init();
	_compass.enable();
}
SensorIMU::~SensorIMU() {}

bool SensorIMU::update() {
	_compass.read();
	_navigationAngle = _compass.getNavigationAngle();
	
	/* No error handling as of yet.
	** This might be implemented here,
	** but can also be implemented when dissecting the MageticSensorLsm303 code.
	*/

    return (true);
}

float SensorIMU::getNavigationAngle() {
	return (this->_navigationAngle);
}

Vec3 SensorIMU::getAccelerometerData() {
	return (Vec3(_compass.accelerometer.x, _compass.accelerometer.y, _compass.accelerometer.z));
}

Vec3 SensorIMU::getMagnetometerData() {
	return (Vec3(_compass.magnetometer.x, _compass.magnetometer.y, _compass.magnetometer.z));
}
