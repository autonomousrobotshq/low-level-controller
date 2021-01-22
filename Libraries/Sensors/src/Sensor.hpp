#ifndef SENSOR_SENSOR_HPP
#define SENSOR_SENSOR_HPP

#include <stdint.h>
#include "Timer.hpp"
#include "SensorData.hpp"

class Sensor {
public:
	Sensor();
    Sensor(const unsigned long sampling_interval);
    virtual ~Sensor();
	virtual bool Init();
	virtual bool Update();
	virtual SensorData &RetreiveData();
	Timer _timer;
private:
	SensorData _data;
};
#endif
