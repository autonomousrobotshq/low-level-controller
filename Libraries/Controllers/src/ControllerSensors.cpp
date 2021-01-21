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
	return (true);
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

SensorData	*ControllerSensors::GetSensorData(const uint8_t index)
{
	return ((index >= 0 && index < _sensors.size()) ? &_sensors[index]->RetreiveData() : NULL);
}
