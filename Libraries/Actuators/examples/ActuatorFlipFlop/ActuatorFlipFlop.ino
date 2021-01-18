#include <ActuatorFlipFlop.hpp>

#define PIN 10
#define DEFAULT_STATE LOW // state which flipflop will be set to when Init() is called
#define INVERTED false // so relays turn on when pulled to ground

ActuatorFlipFlop flipflop(PIN, INVERTED);

void setup() {
	flipflop.Init(DEFAULT_STATE);
}

void loop() {
	flipflop.SetState(true);
}
