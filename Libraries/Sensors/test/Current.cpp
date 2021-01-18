#include <Arduino.h>
#include <ArduinoUnitTests.h>

#include "Current.hpp"

unittest(Current_min)
{
	GodmodeState* state = GODMODE();   // get access to the state

	const int pin = 10;
	const int sample_count = 10;
	const int sampling_interval = 0;

	SensorCurrent sensor(pin, sample_count, sampling_interval);
	assertTrue(sensor.Init());

	analogWrite(pin, 0);
	assertTrue(sensor.Update());
	assertEqual(0, sensor.GetCurrentMilliAmps());
	assertEqual(0, sensor.GetCurrentAmps());
}

unittest(Current_max)
{
	GodmodeState* state = GODMODE();   // get access to the state

	const int pin = 10;
	const int sample_count = 10;
	const int sampling_interval = 0;

	SensorCurrent sensor(pin, sample_count, sampling_interval);
	assertTrue(sensor.Init());

	analogWrite(pin, 200);
	assertTrue(sensor.Update());
	assertMore(sensor.GetCurrentMilliAmps(), 0);
	assertMore(sensor.GetCurrentAmps(), 0);
}

unittest_main()
