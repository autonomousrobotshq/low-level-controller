#ifndef ACTUATOR_FLIPFLOP_HPP
#define ACTUATOR_FLIPFLOP_HPP

#include "stdint.h"
#include "Actuator.hpp"

class ActuatorFlipFlop : public Actuator {
public:
    ActuatorFlipFlop(const uint8_t pin, const bool inverted);
    ActuatorFlipFlop();
    ~ActuatorFlipFlop();
	void SetParameters(const uint8_t pin, const bool inverted);
	bool Init(const bool default_state);
    void SetState(const bool state);
	bool Toggle();
    bool GetState();
private:
    bool _state;
	bool _inverted;
    uint8_t _pin;
};

#endif
