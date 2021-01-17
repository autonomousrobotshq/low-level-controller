#ifndef ACTUATOR_RELAY_HPP
#define ACTUATOR_RELAY_HPP

#include "stdint.h"
#include "Actuator.hpp"

class ActuatorRelay : public Actuator {
public:
    ActuatorRelay(const uint8_t pin);
    ~ActuatorRelay();
    void SetState(const bool state);
    bool GetState();

private:
    bool _state;
    const uint8_t _pin;
};

#endif
