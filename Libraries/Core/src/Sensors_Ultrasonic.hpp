#ifndef SENSOR_ULTRASONIC_HPP
#define SENSOR_ULTRASONIC_HPP

#include "Sensors_Sensor.hpp"
#include <Arduino.h>

/*!
**	@brief The max measurement value of the module is 520cm.
*/
#define SON_MAX_RANGE (520)

/*!
**	@brief ADC accuracy of Arduino (set default for Arduino UNO -> 10 bit).
*** RE: if this is a global characteristic of an Arduino, this should be in a global file.
*/
#define ADC_RESOLUTION (1023.0)

class SensorUltrasonic : public Sensor {
public:
    SensorUltrasonic(const uint8_t pin, const uint16_t exec_interval);
    ~SensorUltrasonic();

    bool Update();

    /*!
	**	@brief Gets calculated distance from sensor.
	**	@return Floating point calculated distance in centimeters.
	*/
    float GetDistance();

private:
    const uint8_t _analog_pin;
    float _dist_t;
    float _sensity_t;
};

#endif
