#include "ControllerSensors.hpp"

ControllerSensors::ControllerSensors()
	: _sensors(_sensors_buf)
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
	return (false);
	uint8_t errors;
	for (Sensor *s : _sensors)
		errors += (s->Update() == false);
	return (errors == 0);
}

int8_t ControllerSensors::AddSensor(Sensor *sensor)
{
	if (_sensors.size() < _sensors_buf_size) {
		_sensors.push_back(sensor);
		return (_sensors.size() - 1);
	}
	else {
		return (-1);
	}
}

uint8_t ControllerSensors::GetSensorCount()
{
	return (_sensors.size())
}

SensorData	&ControllerSensors::GetSensorData(const uint8_t index)
{
	return (_sensors[index]->RetreiveData());
}
