#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <stddef.h>
#include "arduino.h"

class Sensor {
public:
    unsigned long getDuration();
    bool isWaiting();
    void setWaitTime(const unsigned long wait_millis);
    Sensor(const unsigned long glob_millis);
    Sensor();
    ~Sensor();
private:
    const unsigned long _glob_millis;
    unsigned long _last_millis;
    unsigned long _end_millis;
};
#endif
