#include "ControllerSensors.hpp"

ControllerSensors::ControllerSensors()
	: _sensors(_sensors_buf, _sensors_buf_size)
{
}

ControllerSensors::~ControllerSensors()
{
}

bool ControllerSensors::Init()
{
}

bool ControllerSensors::Update()
{
	uint8_t errors;
	for (Sensor *s : _sensors)
		errors += !s->Update();
	return (errors == 0);
}

bool ControllerSensors::AddSensor(Sensor *sensor)
{
	if (_sensors.size() < _sensors_buf_size) {
		_sensors.push_back(sensor);
		return (true);
	}
	else {
		return (false);
	}
}
