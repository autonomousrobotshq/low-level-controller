#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <stddef.h>
#include "arduino.h"

class Sensor {
public:
    unsigned long getDuration();
    bool isWaiting();
    void setWaitTime(const unsigned long waitMillis);
    Sensor(const unsigned long globMillis);
    Sensor();
    ~Sensor();
private:
    const unsigned long* _globMillis;
    unsigned long _lastMillis;
    unsigned long _endMillis;
};
#endif
