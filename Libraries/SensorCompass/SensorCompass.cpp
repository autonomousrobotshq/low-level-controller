#include "SensorCompass.hpp"

SensorCompass::SensorCompass() {
	_compass.init();
	_compass.enable();
}
SensorCompass::~SensorCompass() {}

bool SensorCompass::update() {
	_compass.read();
	
	/* No error handling as of yet.
	** This might be implemented here,
	** but can also be implemented when dissecting the MageticSensorLsm303 code.
	*/

    return (true);
}

float SensorCompass::getNavigationAngle() {
	return (_compass.getNavigationAngle());
}

vector<int16_t> getMagnetometerReadings() {	
	return (_compass.magnetometer);
}
vector<int16_t> getAccelerometerReadings() {
	return (_compass.accelerometer);
}
