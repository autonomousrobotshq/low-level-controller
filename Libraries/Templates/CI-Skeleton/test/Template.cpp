#include <Arduino.h>
#include <ArduinoUnitTests.h>

#include "Beeper.hpp"

// example 

#define PIN 10

unittest(NAME)
{
	GodmodeState* state = GODMODE();   // get access to the state
	ActuatorBeeper beeper(PIN);
	beeper.SetState(true);
	assertTrue(state->digitalPin[PIN] == HIGH);
}

unittest_main()
