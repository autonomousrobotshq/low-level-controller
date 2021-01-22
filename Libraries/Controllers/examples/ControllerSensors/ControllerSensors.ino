#include "SensorCurrent.hpp"
#include "ControllerSensors.hpp"

ControllerSensors cs;
Sensor s;

int sensor_index = 0;

void setup() {
	sensor_index = cs.AddSensor(&s);
	cs.Init();
}

void loop() {
	if (cs.Update()) {
		SensorData sd = cs.GetSensorData(sensor_index);

		// do something with data
	} else {
		int error = cs.GetSensorData(sensor_index).GetError();

		// handle error
	}
}
