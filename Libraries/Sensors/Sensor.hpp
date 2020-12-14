#ifndef SENSOR_SENSOR_HPP
#define SENSOR_SENSOR_HPP

#include <stdint.h>
#include "Common/TimedUpdate.hpp"

class Sensor : public TimedUpdate {
public:
    Sensor(const uint16_t sampling_interval);
    ~Sensor();
private:
};
#endif
