#ifndef SENSORULTRASONIC_HPP
#define SENSORULTRASONIC_HPP

#include <Arduino.h>

/*!
**	@brief The max measurement value of the module is 520cm.
*/
#define	MAX_RANGE		(520)

/*!
**	@brief ADC accuracy of Arduino (set default for Arduino UNO -> 10 bit).
*/
#define ADC_SOLUTION	(1023.0)

class SensorUltrasonic {
public:
	SensorUltrasonic(const int pin);
	~SensorUltrasonic();

	bool update();

	/*!
	**	@brief Gets calculated distance from sensor.
	**	@return Floating point calculated distance in centimeters.
	*/
	float getDistance();

private:
	int _analogPin;
	float _dist_t;
	float _sensity_t;
};

#endif
