#ifndef SENSOR_SENSOR_HPP
#define SENSOR_SENSOR_HPP

#include <stdint.h>
#include "Timer.hpp"

class Sensor : public Timer {
public:
    Sensor(const unsigned long sampling_interval);
    virtual ~Sensor();
	virtual bool Init();
	virtual bool Update();

private:
};
#endif
