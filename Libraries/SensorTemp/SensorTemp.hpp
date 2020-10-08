#ifndef SENSORTEMP_HPP
#define SENSORTEMP_HPP

#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 8
// OneWire test(ONE_WIRE_BUS);
// DallasTemperature sensors(&test);

class SensorTemp {
private:
    OneWire				_wire;
    DallasTemperature	_sensors;
    float				_celsius;

public:
    SensorTemp(const int pin);
    ~SensorTemp();

    float	getTemp();
    bool	update();
};

#endif
