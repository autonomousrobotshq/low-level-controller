#include "Current.hpp"

#define PIN 10
#define SAMPLE_COUNT 10 // get ten samples before taking the median value
#define SAMPLING_INTERVAL 1000 // update every 1 second

SensorCurrent sensor(PIN, SAMPLE_COUNT, SAMPLING_INTERVAL);

void setup() {
	sensor.Init();
}

void loop() {
	sensor.Update();
	int16_t amps = sensor.GetCurrentAmps();
	int16_t milli_amps = sensor.GetCurrentMilliAmps();

	Serial.print("Current -> milliamps { ");
	Serial.print(milli_amps);
	Serial.print(" }, amps {");
	Serial.print(amps);
	Serial.println(" }.");

	delay(200);
}
