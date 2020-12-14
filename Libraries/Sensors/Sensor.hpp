#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <stdint.h>

class Sensor {
public:
    Sensor(const uint16_t sampling_interval);
    ~Sensor();
	uint16_t GetTimeSinceLastExecution();
	bool IsTimeToExecute();
private:
	unsigned long _previous_millis;
	const uint16_t _sampling_interval;
};
#endif
