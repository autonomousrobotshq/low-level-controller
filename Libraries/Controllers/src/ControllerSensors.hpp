#ifndef CONTROLLER_SENSORS_HPP
#define CONTROLLER_SENSORS_HPP

#include "Vector.h"

#include "Controller.hpp"
#include "Sensor.hpp"

class ControllerSensors : public Controller {
public:
    ControllerSensors();
    ~ControllerSensors();
	bool Init();
    bool Update();
	bool AddSensor(Sensor *sensor);
	SensorData  *GetSensorData(const uint8_t index);
private:
	static const uint8_t _sensors_buf_size = 12;
	Sensor *_sensors_buf[_sensors_buf_size];
	Vector<Sensor*> _sensors;
};

#endif
