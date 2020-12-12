#ifndef CONTROLLER_LIFETIME_HPP
#define CONTROLLER_LIFETIME_HPP

#include "Common/State.hpp"
#include "Common/Datatypes.hpp"
#include "Common/Platform.hpp"
#include "Controllers/Controller.hpp"
#include "Actuators/Relay.hpp"

class ControllerLifetime : public Controller {
public:
    ControllerLifetime(const uint8_t pins_relays[NUM_RELAYS]);
    ~ControllerLifetime();
    void Lifephase(const e_state state);

private:
    ActuatorRelay* _relays[NUM_RELAYS];
};

#endif
