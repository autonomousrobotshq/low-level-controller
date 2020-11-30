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
    int8_t _celsius;

public:
    SensorTemp(const uint8_t pin);
    ~SensorTemp();

    int8_t GetTemp();
    bool update();
};

#endif
