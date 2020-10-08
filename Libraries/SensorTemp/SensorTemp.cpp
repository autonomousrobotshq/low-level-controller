#include "SensorTemp.hpp"

float SensorTemp::getTemp()
{
    return (this->_celsius);
}

bool SensorTemp::update()
{
    this->_sensors.requestTemperatures();
    this->_celsius = _sensors.getTempCByIndex(0);
    // flash out illegal values, reset the old if value was invalid
    return (true);
}

SensorTemp::SensorTemp(const int pin)
    : _wire(pin), _celsius(0), _sensors(&_wire)
{
    this->_sensors.begin();
    this->update();
}

SensorTemp::~SensorTemp()
{
}
