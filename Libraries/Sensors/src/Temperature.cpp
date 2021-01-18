#include "Temperature.hpp"

SensorTemp::SensorTemp(const uint8_t pin, const unsigned long  sampling_interval)
    : Sensor(sampling_interval)
#ifndef ARDUINO_CI
    , _wire(pin)
    , _dallas(&_wire)
	, _celsius(0)
#endif
{
}

SensorTemp::~SensorTemp()
{
}

bool SensorTemp::Init()
{
#ifndef ARDUINO_CI
    _dallas.begin();
#endif
	return (true);
}

int8_t SensorTemp::GetTemp()
{
    return (_celsius);
}

bool SensorTemp::Update()
{
    if (!IsTimeToExecute())
        return (true);
#ifndef ARDUINO_CI
    _dallas.requestTemperatures();
    _celsius = (int)_dallas.getTempCByIndex(0);
#endif

	// filter values ?
    return (true);
}
