#ifndef SENSOR_SENSOR_HPP
#define SENSOR_SENSOR_HPP

#include "Common_TimedUpdate.hpp"
#include <stdint.h>

class Sensor : public TimedUpdate {
public:
    Sensor(const uint16_t sampling_interval);
    ~Sensor();

private:
};
#endif
