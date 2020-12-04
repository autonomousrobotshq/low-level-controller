#ifndef LOGIC_STEERING_HPP
#define LOGIC_STEERING_HPP
#include "Sandbox/Sandbox.hpp"

using namespace sb;

enum e_turn {
    LEFT,
    RIGHT
};

class LogicSteering {
public:
    LogicSteering(Sandbox& sandbox);
    ~LogicSteering();
    Drive(uint8_t distance, uint8_t throttle);
    Pivot(e_turn turn);

private:
    Sandbox& _sandbox;
};

#endif
