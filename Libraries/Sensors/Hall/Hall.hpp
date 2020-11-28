#ifndef SENSOR_HALL_HPP
# define SENSOR_HALL_HPP

# include "Sensor.hpp"

# define HALL_INTERRUPT_COUNT 4

class SensorHall : public Sensor {
public:
    int getRPM();
    bool update();
    SensorHall(const unsigned int pinA,
        const unsigned int pinB,
        const unsigned int interrupt,
        const unsigned int cpr,
        const unsigned long* globMillis);
    ~SensorHall();

private:
    const unsigned int _pinA,
        _pinB,
        _interrupt, // interrupt corresponds to pinA!
        _cpr;
    unsigned int _pulseIndex,
        _rpm;
};

#endif
