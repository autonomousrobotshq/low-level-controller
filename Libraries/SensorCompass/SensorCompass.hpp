#ifndef SENSORCOMPASS_HPP
#define SENSORCOMPASS_HPP

#include <MagneticSensorLsm303.h>

class SensorCompass {
public:
    SensorCompass(const int analogPin);
    ~SensorCompass();

    bool update();

	/*!
	**	@brief Passes through the navigation angle from MagneticSensorLsm303 object.
	**	@return Angle value.
	*/
	float getNavigationAngle();

	/*!
	**	@brief Fetches magnetometer readings from MagneticSensorLsm303 object.
	**	@return Vector object containing magnetometer readings.
	*/
    vector<int16_t> getMagnetometerReadings();
	/*!
	**	@brief Fetches accelerometer readings from MagneticSensorLsm303 object.
	**	@return Vector object containing accelerometer readings.
	*/
	vector<int16_t> getAccelerometerReadings();

private:
	MagneticSensorLsm303 _compass;
};

#endif
