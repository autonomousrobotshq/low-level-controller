#include <Arduino.h>
#include <ArduinoUnitTests.h>

#include "SensorCurrent.hpp"

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
	assertEqual(0, sensor.RetreiveData().GetCurrentMilliAmps());
	assertEqual(0, sensor.RetreiveData().GetCurrentAmps());
}

unittest(Current_max)
{
	GodmodeState* state = GODMODE();   // get access to the state

	const int pin = 10;
	const int sample_count = 10;
	const int sampling_interval = 0;
	const int adc_resolution = 1023;

	SensorCurrent sensor(pin, sample_count, sampling_interval);
	assertTrue(sensor.Init());

	analogWrite(pin, adc_resolution);
	assertTrue(sensor.Update());
	assertMore(sensor.RetreiveData().GetCurrentMilliAmps(), 0);
	assertMore(sensor.RetreiveData().GetCurrentAmps(), 0);
}

unittest_main()
