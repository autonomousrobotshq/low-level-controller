#include <Arduino.h>
#include "Sensor.hpp"

Sensor::Sensor()
	: _timer(0)
{
}

Sensor::Sensor(const unsigned long sampling_interval)
    : _timer(sampling_interval)
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
