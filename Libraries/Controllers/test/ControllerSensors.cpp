#include <Arduino.h>
#include <ArduinoUnitTests.h>

#include "Sensor.hpp"
#include "ControllerSensors.hpp"

unittest(ControllersSensors)
{
	GodmodeState* state = GODMODE();   // get access to the state
	ControllerSensors cm;
	assertTrue(cm.Init());

	Sensor s;
	int8_t s_i = cm.AddSensor(&s);
	assertEqual(0, (int)s_i);

	assertTrue(cm.Update());
	SensorData s2 = cm.GetSensorData(s_i);
}

unittest_main()
