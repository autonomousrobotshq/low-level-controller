#include <Arduino.h>
#include "Sensors/Sensor.hpp"

Sensor::Sensor(const uint16_t sampling_interval)
	: TimedUpdate(sampling_interval)
{
}

Sensor::~Sensor()
{
}
