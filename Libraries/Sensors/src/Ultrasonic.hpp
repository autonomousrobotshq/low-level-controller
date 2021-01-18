#ifndef SENSOR_ULTRASONIC_HPP
#define SENSOR_ULTRASONIC_HPP

#include <Arduino.h>
#include "Sensor.hpp"
#include "MedianFilter.hpp"

class SensorUltrasonic : public Sensor {
public:
    SensorUltrasonic(const uint8_t pin, const uint16_t max_depth, const uint16_t sample_count, const unsigned long sampling_interval);
    ~SensorUltrasonic();
	bool Init();
    bool Update();
	
    /*!
	**	@brief Gets calculated distance from sensor.
	**	@return int16_t calculated distance in centimeters.
	*/
    uint16_t GetDistance();

private:
    const uint8_t _analog_pin;
	const uint16_t _max_depth;
	MedianFilter _filter;
	const uint16_t _sampling_count;
    uint16_t _distance;
};

#endif
