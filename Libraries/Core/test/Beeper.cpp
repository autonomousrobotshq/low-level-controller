#include <Arduino.h>
#include <ArduinoUnitTests.h>
#include "Actuators_Beeper.hpp"

#define PIN 10

ActuatorBeeper beeper(PIN);

void setup() {
}

void loop() {
	GodmodeState* state = GODMODE();
	beeper.SetState(true);
	assertTrue(state->digitalPin[LED_BUILTIN] == HIGH);
}
