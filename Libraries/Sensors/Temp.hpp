#ifndef SENSOR_TEMP_HPP
#define SENSOR_TEMP_HPP

#include <DallasTemperature.h>
#include <OneWire.h>

#include "Sensors/Sensor.hpp"

#define ONE_WIRE_BUS 8
// OneWire test(ONE_WIRE_BUS);
// DallasTemperature sensors(&test);

class SensorTemp : public Sensor {
public:
    SensorTemp(const uint8_t pin, const uint16_t exec_interval);
    ~SensorTemp();
    int8_t GetTemp();
    bool Update();
private:
    OneWire _wire;
    DallasTemperature _sensors;
    int8_t _celsius;
};

#endif
