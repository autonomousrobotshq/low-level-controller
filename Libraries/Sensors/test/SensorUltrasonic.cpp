#include <Arduino.h>
#include <ArduinoUnitTests.h>

#include "SensorUltrasonic.hpp"

unittest(Ultrasonic_min)
{
	GodmodeState* state = GODMODE();   // get access to the state

	const int pin = 10;
	const int max_depth = 520;
	const int sample_count = 10;
	const int sampling_interval = 0;

	SensorUltrasonic sensor(pin, max_depth, sample_count, sampling_interval);
	assertTrue(sensor.Init());

	analogWrite(pin, 0);
	assertTrue(sensor.Update());
	assertEqual(0, sensor.GetDistance());
}

unittest(Ultrasonic_max)
{
	GodmodeState* state = GODMODE();   // get access to the state

	const int pin = 10;
	const int max_depth = 520;
	const int sample_count = 10;
	const int sampling_interval = 0;
	const int adc_resolution = 1023;

	SensorUltrasonic sensor(pin, max_depth, sample_count, sampling_interval);
	assertTrue(sensor.Init());

	analogWrite(pin, adc_resolution);
	assertTrue(sensor.Update());
	assertEqual(max_depth, sensor.GetDistance());
}

unittest_main()
