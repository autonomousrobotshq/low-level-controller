#include "SensorIMU.hpp"

SensorIMU::SensorIMU() {
	_compass.init();
	_compass.enable();
}
SensorIMU::~SensorIMU() {}

bool SensorIMU::update() {
	_compass.read();
	_navigationAngle = _compass.getNavigationAngle();
	_accelerometerData.x = _compass.accelerometer.x;
	_accelerometerData.y = _compass.accelerometer.y;
	_accelerometerData.z = _compass.accelerometer.z;
	_magnetometerData.x = _compass.magnetometer.x;
	_magnetometerData.y = _compass.magnetometer.y;
	_magnetometerData.z = _compass.magnetometer.z;
	
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
	return (this->_accelerometerData);
}

Vec3 SensorIMU::getMagnetometerData() {
	return (this->_magnetometerData);
}
