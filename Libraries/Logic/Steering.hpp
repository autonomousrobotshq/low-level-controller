#ifndef LOGIC_STEERING_HPP
#define LOGIC_STEERING_HPP
#include "Sandbox/Sandbox.hpp"

using namespace sb;

class LogicSteering {
public:
    LogicSteering(Sandbox& sandbox);
    ~LogicSteering();
    void driveLogic(int distance, int angle);

private:
    void _turn(int angle);
    void _pivot(int angle, int rpmcount, int targetCount, int power);
    void _turnAngle(int angle, int targetCount, int power);
    void _driveDistance(int distance);

private: // data members
    Sandbox& _sandbox;
    const int _countsPerRev = 64;
    const int _wheelDiam = 120;
    const float _wheelCirc = 376.99;
    const float _pivotDiam = 203.763;
    const float _pivotCirc = 640.140;
};

#endif
