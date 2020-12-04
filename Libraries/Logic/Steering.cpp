#include "Logic/Steering.hpp"
#include "Common/Deployment.hpp"
#include "Sandbox/Sandbox.hpp"
#include <math.h>

using namespace sb;

LogicSteering::LogicSteering(Sandbox& sandbox)
    : _sandbox(sandbox)
{
}

LogicSteering::~LogicSteering()
{
}

void LogicSteering::Drive(float flat, float flon, uint8_t throttle)
{
    (void)flat;
    (void)flon;
    (void)throttle;
}

// Pivot robot towards navigation angle
void LogicSteering::Set_Pivot(e_turn turn, int nav_angle)
{
    this->_turn = turn;
    this->_nav_angle = nav_angle;
    this->_pivot = true;
}

void LogicSteering::Pivot()
{
    if (!this->_pivot)
        return ;
    int current_angle = this->_sandbox.IMUGetNavigationAngle();
    if (current_angle >= this->_nav_angle - PIVOT_RANGE or current_angle <= this->_nav_angle + PIVOT_RANGE) {
        this->_sandbox.Driver(ALL, HALT);
        this->_pivot = false;
        return ;
    }
    switch (this->_turn) {
        case LEFT:
            this->_sandbox.Driver(FRONT_LEFT, BACKWARD, 50);
            this->_sandbox.Driver(BACK_LEFT, BACKWARD, 50);
            this->_sandbox.Driver(FRONT_RIGHT, FORWARD, 50);
            this->_sandbox.Driver(BACK_RIGHT, FORWARD, 50);
            break ;
        case RIGHT:
            this->_sandbox.Driver(FRONT_LEFT, FORWARD, 50);
            this->_sandbox.Driver(BACK_LEFT, FORWARD, 50);
            this->_sandbox.Driver(FRONT_RIGHT, BACKWARD, 50);
            this->_sandbox.Driver(BACK_RIGHT, BACKWARD, 50);
            break ;
        default:
            break ;
    }
}