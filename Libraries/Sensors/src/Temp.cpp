#include "Temp.hpp"

SensorTemp::SensorTemp(const uint8_t pin, const uint16_t exec_interval)
    : Sensor(exec_interval)
    , _wire(pin)
    , _sensors(&_wire)
{
    this->_sensors.begin();
}

SensorTemp::~SensorTemp()
{
}

int8_t SensorTemp::GetTemp()
{
    return (this->_celsius);
}

bool SensorTemp::Update()
{
    if (!this->IsTimeToExecute())
        return (true);
    this->_sensors.requestTemperatures();
    this->_celsius = (int)_sensors.getTempCByIndex(0);
    // flash out illegal values, reset the old if value was invalid
    return (true);
}
