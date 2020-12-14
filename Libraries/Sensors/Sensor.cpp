#include "Sensor.hpp"
#include <Arduino.h>

uint16_t Sensor::GetTimeSinceLastExecution()
{
	unsigned long current_millis = millis();

	return (current_millis - _previous_millis);
}

bool Sensor::IsTimeToExecute()
{
	unsigned long current_millis = millis();

	if (current_millis - _previous_millis > _sampling_interval)
	{
		_previous_millis += _sampling_interval;
		return (true);
	}
	return (false);
}

Sensor::Sensor(const uint16_t sampling_interval)
	: _previous_millis(millis())
	, _sampling_interval(sampling_interval)
{
}

Sensor::~Sensor()
{
}
