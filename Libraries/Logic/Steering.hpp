#ifndef LOGIC_STEERING_HPP
#define LOGIC_STEERING_HPP
#include "Sandbox/Sandbox.hpp"

using namespace sb;

#define PIVOT_RANGE 5

enum e_turn {
    LEFT,
    RIGHT
};

class LogicSteering {
public:
    LogicSteering(Sandbox& sandbox);
    ~LogicSteering();
    void Drive(float flat, float flon, uint8_t throttle);
    void Pivot();
    void Set_Pivot(e_turn turn, int degr);

private:
    Sandbox& _sandbox;
    e_turn _turn;
    int _nav_angle;
    bool _pivot;
};

#endif
