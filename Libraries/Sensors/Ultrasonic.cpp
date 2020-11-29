#include "Sensors/Ultrasonic.hpp"

SensorUltrasonic::SensorUltrasonic(const uint8_t pin)
    : _analogPin(pin)
{
    pinMode(pin, INPUT);
}

SensorUltrasonic::~SensorUltrasonic() { }

bool SensorUltrasonic::update()
{
    _sensity_t = analogRead(_analogPin);

    _dist_t = _sensity_t * SON_MAX_RANGE / ADC_RESOLUTION;

    /*
	**	No error handling implemented yet (if at all necessary).
	*** RE: definitely necessary: take average and store last average value
	*** to filter out wrong readings.
	*/

    return (true);
}

float SensorUltrasonic::getDistance()
{
    return (_dist_t);
}
