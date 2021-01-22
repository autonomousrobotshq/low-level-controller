#ifndef CONTROLLER_SENSORS_HPP
#define CONTROLLER_SENSORS_HPP

#include <stdint.h>
#include "Vector.h"
#include "Controller.hpp"
#include "Sensor.hpp"

class ControllerSensors : public Controller {
	public:
	    ControllerSensors();
	    ~ControllerSensors();
		bool Init();
	    bool Update();
		int8_t AddSensor(Sensor *sensor);
		uint8_t GetSensorCount();
		SensorData  &GetSensorData(const uint8_t index);
	private:
		static const uint8_t _sensors_buf_size = 12;
		Sensor *_sensors_buf[_sensors_buf_size];
		Vector<Sensor*> _sensors;
};

#endif
