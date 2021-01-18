#include "Sensor.hpp"
#include <Arduino.h>

Sensor::Sensor(const unsigned long sampling_interval)
    : Timer(sampling_interval)
{
}

Sensor::~Sensor()
{
}

bool Sensor::Init()
{
	return (true);
}

bool Sensor::Update()
{
	return (true);
}
