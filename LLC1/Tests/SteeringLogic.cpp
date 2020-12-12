#include "Common/Deployment.hpp"
#include "Logic/Steering.hpp"
#include "Sandbox/Sandbox.hpp"

/*
** SAMPLE CODE
*/

using namespace sb;

Sandbox* sandbox;
LogicSteering* steering;

bool LogicDriverUpdate(void) // is called just before update of motorcontroller in Sandbox::Spinonce
{
    steering->drive();
    return (true);
}

void setup() //runs on startup
{
    sandbox = new Sandbox();
    sandbox->Setup();
    sandbox->SetLogicDriverUpdate(LogicDriverUpdate);

    steering = new LogicSteering(*sandbox);

    Serial.begin(115200);

    Serial.println("Test_SteeringLogic.cpp");
}

void loop() // loops indefinitely
{

    sandbox->SpinOnce();
}

void post()
{
}
