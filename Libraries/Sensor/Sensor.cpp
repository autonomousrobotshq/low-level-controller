#include "Sensor.hpp"

unsigned long Sensor::getDuration()
{
    static unsigned long lastMillis;
    unsigned long lastMillisTmp = lastMillis;

    lastMillis = *this->globMillis;

    return (lastMillisTmp == 0 ? 0 : *this->globMillis - lastMillisTmp);
}

Sensor::Sensor(const unsigned long* _globMillis)
    : globMillis(_globMillis)
{
}

Sensor::Sensor()
    : globMillis(NULL)
{
}

Sensor::~Sensor()
{
}
