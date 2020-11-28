#ifndef SENSOR_HALL_HPP
#define SENSOR_HALL_HPP

#include "Sensor.hpp"

#define HALL_INTERRUPT_COUNT 4
#define HALL_CPR 100 // needs to be discover in testing!

class SensorHall : public Sensor {
public:
    int getRPM();
    bool update();
    SensorHall(const byte pinA,
        const byte pinB,
        const byte interruptPin,
        const unsigned long* globMillis);
    ~SensorHall();

private:
    const byte _pinA, _pinB, _interrupt; // interrupt corresponds to pinA!
    unsigned int _pulseIndex,
        _rpm;
};

#endif
