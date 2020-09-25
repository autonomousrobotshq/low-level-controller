#include "SensorUltrasonic.hpp"

SensorUltrasonic::SensorUltrasonic(const int pin)
    : _analogPin(pin)
{
    this->update();
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
