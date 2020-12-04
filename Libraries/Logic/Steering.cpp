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


void LogicSteering::Drive(uint8_t distance, uint8_t throttle)
{

}
void LogicSteering::Pivot(e_turn turn)
{
    
}