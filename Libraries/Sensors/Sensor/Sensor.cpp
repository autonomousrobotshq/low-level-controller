#include "Sensor.hpp"

unsigned long Sensor::getDuration()
{
    if (this->_globMillis) {
        unsigned long lastMillisTmp = this->lastMillis;

        this->lastMillis = *this->_globMillis;

        return (lastMillisTmp == 0 ? 0 : *this->_globMillis - lastMillisTmp);
    } else
        return (0);
}

Sensor::Sensor(const unsigned long* globMillis)
    : _globMillis(globMillis)
    , lastMillis(0)
{
}

Sensor::Sensor()
    : _globMillis(NULL)
{
}

Sensor::~Sensor()
{
}
