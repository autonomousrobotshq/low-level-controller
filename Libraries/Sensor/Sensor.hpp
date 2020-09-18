#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <stddef.h>

class Sensor {
public:
    unsigned long getDuration();
    Sensor(const unsigned long* globMillis);
    Sensor();
    ~Sensor();

private:
    const unsigned long* _globMillis;
    unsigned long lastMillis;
};

#endif
