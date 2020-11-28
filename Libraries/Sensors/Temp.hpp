#ifndef SENSOR_TEMP_HPP
#define SENSOR_TEMP_HPP

#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 8
// OneWire test(ONE_WIRE_BUS);
// DallasTemperature sensors(&test);

class SensorTemp {
private:
    OneWire _wire;
    DallasTemperature _sensors;
    int _celsius;

public:
    SensorTemp(const byte pin);
    ~SensorTemp();

    int getTemp();
    bool update();
};

#endif
