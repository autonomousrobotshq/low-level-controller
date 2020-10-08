#ifndef SENSORTEMP_HPP
#define SENSORTEMP_HPP

#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 8
// OneWire test(ONE_WIRE_BUS);
// DallasTemperature sensors(&test);

class SensorTemp {
public:
    float getTemp();
    bool update();
    SensorTemp(const int pin);
    ~SensorTemp();

private:
    OneWire _wire;
    DallasTemperature _sensors;
    float _celsius;
};
#endif
