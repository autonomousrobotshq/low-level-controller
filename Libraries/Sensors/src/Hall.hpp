#ifndef SENSOR_HALL_HPP
#define SENSOR_HALL_HPP

#include "Sensor.hpp"

class SensorHall {
public:
    SensorHall( const uint8_t pin_interrupt,
				const uint8_t index_interrupt,
				const uint16_t counts_per_revolution,
				const uint16_t distance_per_revolution);
    ~SensorHall();
	bool Init();
	void CounterReset();
	uint16_t CounterGetDistance();

private:
    const uint8_t _interrupt_index, _interrupt_pin;
	const uint16_t _counts_per_revolution, _distance_per_revolution;
};

#endif
