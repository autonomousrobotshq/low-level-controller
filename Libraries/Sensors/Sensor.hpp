#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <stddef.h>

class Sensor {
public:
    unsigned long GetDuration();
    bool IsWaiting();
    void SetWaitTime(const unsigned long wait_millis);
    Sensor(const unsigned long glob_millis);
    Sensor();
    ~Sensor();

private:
    const unsigned long _glob_millis;
    unsigned long _last_millis;
    unsigned long _end_millis;
};
#endif
