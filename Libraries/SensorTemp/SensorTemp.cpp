#include "SensorTemp.hpp"

float SensorTemp::getTemp()
{
    return (this->Celsius);
}

float SensorTemp::readTempC()
{
    float _Celcius;
    sensors.requestTemperatures();
    _Celcius = sensors.getTempCByIndex(0);
    return (_Celcius);
}

bool SensorTemp::update()
{
    this->Celsius = readTempC();
    // error handling inbouwen
    return (true);
}

SensorTemp::SensorTemp(const int wire)
{
    this->Wire = wire;
    sensors.begin();
    this->update();
}

SensorTemp::~SensorTemp()
{
}