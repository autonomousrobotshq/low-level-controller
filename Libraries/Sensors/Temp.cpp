#include "Sensors/Temp.hpp"

SensorTemp::SensorTemp(const byte pin)
    : _wire(pin)
    , _celsius(0)
    , _sensors(&_wire)
{
    this->_sensors.begin();
    this->update();
}

SensorTemp::~SensorTemp()
{
}

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
