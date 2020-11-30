#include "Sensors/Ultrasonic.hpp"

SensorUltrasonic::SensorUltrasonic(const uint8_t pin)
    : _analog_pin(pin)
{
    pinMode(pin, INPUT);
}

SensorUltrasonic::~SensorUltrasonic() { }

bool SensorUltrasonic::Update()
{
    _sensity_t = analogRead(_analog_pin);

    _dist_t = _sensity_t * SON_MAX_RANGE / ADC_RESOLUTION;

    /*
	**	No error handling implemented yet (if at all necessary).
	*** RE: definitely necessary: take average and store last average value
	*** to filter out wrong readings.
	*/

    return (true);
}

float SensorUltrasonic::GetDistance()
{
    return (_dist_t);
}
