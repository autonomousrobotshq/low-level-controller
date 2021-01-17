#include <Beeper.hpp>

#define PIN 10

ActuatorBeeper beeper(PIN);

void setup() {
}

void loop() {
	beeper.SetState(true);
}
