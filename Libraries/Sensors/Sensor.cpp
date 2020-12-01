#include "Sensor.hpp"
#include <Arduino.h>

unsigned long Sensor::getDuration()
{
    if (this->_glob_millis) {
        unsigned long last_millis_tmp = this->_last_millis;
        this->_last_millis = this->_glob_millis;
        return (last_millis_tmp == 0 ? 0 : this->_glob_millis - last_millis_tmp);
    } else
        return (0);
}

bool Sensor::isWaiting()
{
    return this->_end_millis > millis();
}

void Sensor::setWaitTime(const unsigned long wait_millis)
{
    this->_end_millis = millis() + wait_millis;
}

Sensor::Sensor(const unsigned long glob_millis)
    : _glob_millis(globMillis)
    , _last_millis(0)
    , _endMillis(0)
{
}

Sensor::Sensor()
    : _glob_millis(NULL)
    , _endMillis(0)
{
}

Sensor::~Sensor()
{
}
