#include "SensorCurrent.hpp"
#include "ControllerSensors.hpp"

ControllerSensors cs;

#define PIN 10
#define SAMPLE_COUNT 10
#define SAMPLING_INTERVAL 0

SensorCurrent sensor(PIN, SAMPLE_COUNT, SAMPLING_INTERVAL);

void setup() {
	cs.Init();
	cs.AddSensor(&sensor);
}

void loop() {
	cs.Update();
}
