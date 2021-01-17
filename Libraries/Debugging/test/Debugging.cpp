#include <Arduino.h>
#include <ArduinoUnitTests.h>

#include "Debugging.hpp"

unittest(Debugging)
{
	DBG::TimerSet();
	delay(500);
	assertTrue(DBG::TimerGetMillis() == 500);
}

unittest_main()
