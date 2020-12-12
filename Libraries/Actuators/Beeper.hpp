#ifndef ACTUATOR_BEEPER_HPP
#define ACTUATOR_BEEPER_HPP

#include "stdint.h"

#include "Actuators/Actuator.hpp"

class ActuatorBeeper : public Actuator {
public:
    ActuatorBeeper(const uint8_t pin);
    ~ActuatorBeeper();
    void SetState(const bool state);
    bool GetState();

private:
    bool _state;
    const uint8_t _pin;
};

#endif
