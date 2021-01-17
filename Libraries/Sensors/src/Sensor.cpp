#include "Sensor.hpp"
#include <Arduino.h>

Sensor::Sensor(const uint16_t sampling_interval)
    : TimedUpdate(sampling_interval)
{
}

Sensor::~Sensor()
{
}
