#include "Sensor.hpp"

#define HALL_INTERRUPT_COUNT 4

class SensorHall : public Sensor {
public:
    int getRPM();
    void update();
    SensorHall(const unsigned int _pinA,
        const unsigned int _pinB,
        const unsigned int _interrupt,
        const unsigned int _cpr,
        const unsigned long* _globMillis);
    ~SensorHall();

private:
    const unsigned int pinA, pinB, interrupt, cpr; // interrupt corresponds to pinA!
    unsigned int pulseIndex, rpm;
};
