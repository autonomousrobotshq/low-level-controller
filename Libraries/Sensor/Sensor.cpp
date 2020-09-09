#include "Sensor.hpp"

unsigned long Sensor::getDuration()
{
    static unsigned long		lastMillis;
    unsigned long 				lastMillisTmp = lastMillis;

    lastMillis = *this->_globMillis;

    return (lastMillisTmp == 0 ? 0 : *this->_globMillis - lastMillisTmp);
}

Sensor::Sensor(const unsigned long* globMillis)
    : _globMillis(globMillis)
{
}

Sensor::Sensor()
    : _globMillis(0)
{
}

Sensor::~Sensor()
{
}
