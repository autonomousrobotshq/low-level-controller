#include "Controllers/Lifetime.hpp"
#include <Arduino.h>

void ControllerLifetime::Lifephase(const e_state state)
{
    switch (state) {
    case S_STARTUP:
        for (uint8_t i = 0; i < NUM_RELAYS; i++) {
            _relays[i]->SetState(true);
            delay(200); // tiny wait to avoid current spike
        }
        break;
    case S_SHUTDOWN:
        for (int8_t i = NUM_RELAYS - 1; i > 0; i--) {
            _relays[i]->SetState(false);
            delay(200); // tiny wait to avoid current spike
        }
        break;
    case S_COOLDOWN:
        _relays[LLC::REL_MOTORS]->SetState(false); // Switch everything off except fans
        break;
    }
};

ControllerLifetime::ControllerLifetime(const uint8_t pins_relays[NUM_RELAYS])
{
    for (uint8_t i = 0; i < NUM_RELAYS; i++)
        _relays[i] = new ActuatorRelay(pins_relays[i]);
}

ControllerLifetime::~ControllerLifetime()
{
    for (uint8_t i = 0; i < NUM_RELAYS; i++)
        delete _relays[i];
}
