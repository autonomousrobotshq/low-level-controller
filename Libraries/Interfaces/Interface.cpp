#include "Interfaces/Interface.hpp"
#include <Arduino.h>

Interface::Interface(const uint16_t sampling_interval)
	: TimedUpdate(sampling_interval)
{
}

Interface::~Interface()
{
}
