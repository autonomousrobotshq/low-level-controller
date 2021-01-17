#ifndef CONTROLLER_LIFETIME_HPP
#define CONTROLLER_LIFETIME_HPP

#include "Actuators_Relay.hpp"
#include "Common_Datatypes.hpp"
#include "Common_Platform.hpp"
#include "Common_State.hpp"
#include "Controllers_Controller.hpp"

class ControllerLifetime : public Controller {
public:
    ControllerLifetime(const uint8_t pins_relays[NUM_RELAYS]);
    ~ControllerLifetime();
    void Lifephase(const e_state state);

private:
    ActuatorRelay* _relays[NUM_RELAYS];
};

#endif
