#include <Arduino.h>
#include <ArduinoUnitTests.h>

#include "ActuatorFlipFlop.hpp"

// example 

#define PIN 10

unittest(ActuatorFlipFlop_Normal)
{
	GodmodeState* state = GODMODE();   // get access to the state

	bool default_state = false;
	bool inverted = false;
	ActuatorFlipFlop relay(PIN, inverted);
	relay.Init(default_state);
	assertTrue(state->digitalPin[PIN] == LOW);
	relay.SetState(true);
	assertTrue(state->digitalPin[PIN] == HIGH);
}

unittest(ActuatorFlipFlop_Inverted)
{
	GodmodeState* state = GODMODE();   // get access to the state

	bool default_state = false;
	bool inverted = true;
	ActuatorFlipFlop relay(PIN, inverted);
	relay.Init(default_state);
	assertTrue(state->digitalPin[PIN] == HIGH);
	relay.SetState(true);
	assertTrue(state->digitalPin[PIN] == LOW);
}

unittest(ActuatorFlipFlop_SetParameters)
{
	GodmodeState* state = GODMODE();   // get access to the state

	bool default_state = false;
	bool inverted = true;
	ActuatorFlipFlop relay;
	relay.SetParameters(PIN, inverted);
	relay.Init(default_state);
	assertTrue(state->digitalPin[PIN] == HIGH);
	relay.SetState(true);
	assertTrue(state->digitalPin[PIN] == LOW);
}

unittest_main()
