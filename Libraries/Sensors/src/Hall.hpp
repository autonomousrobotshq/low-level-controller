#ifndef SENSOR_HALL_HPP
#define SENSOR_HALL_HPP

#include "Sensor.hpp"

#define HALL_INTERRUPT_COUNT 4
#define HALL_CPR 100 // needs to be discovered in testing!

class SensorHall : public Sensor {
public:
    SensorHall( const uint8_t pin_interrupt,
				const uint8_t index_interrupt,
				const uint16_t exec_interval,
				const uint16_t exec_interval);
    ~SensorHall();
    int GetRPM();
    int GetRevolutions();
    bool Update();

private:
    const uint8_t _interrupt_index, _interrupt_pin;
    unsigned int _rpm;
    unsigned int _revolutions;
};

#endif
