#ifndef SENSOR_TEMPERATURE_HPP
#define SENSOR_TEMPERATURE_HPP

#ifndef ARDUINO_CI
# include <DallasTemperature.h>
# include <OneWire.h>
#endif

#include "Sensor.hpp"

class SensorTemp : public Sensor {
public:
    SensorTemp(const uint8_t pin, const unsigned long sampling_interval);
    ~SensorTemp();
	bool Init();
    bool Update();
    int8_t GetTemp();

private:
#ifndef ARDUINO_CI
    OneWire _wire;
    DallasTemperature _dallas;
#endif
    int8_t _celsius;
};

#endif
