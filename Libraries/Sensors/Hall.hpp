#ifndef SENSOR_HALL_HPP
#define SENSOR_HALL_HPP

#include "Common/Datatypes.hpp"
#include "Sensors/Sensor.hpp"

#define HALL_INTERRUPT_COUNT 4
#define HALL_CPR 100 // needs to be discover in testing!

class SensorHall : public Sensor {
public:
    int GetRPM();
	int	GetRevelations();
    bool Update();
    SensorHall(const t_pins_hall pins_hall);
    ~SensorHall();

private:
    const uint8_t _interrupt_index, _interrupt_pin;
    unsigned int _rpm;
	unsigned int _revelations;
};

#endif
