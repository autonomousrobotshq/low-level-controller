#include "Common/Deployment.hpp"
#include "Sandbox/Sandbox.hpp"
#include "Logic/Steering.hpp"
/*
** SAMPLE CODE
*/

using namespace sb;

Sandbox *sandbox;

void setup() //runs on startup
{
	sandbox = new Sandbox();
	sandbox->Setup();
}

void loop() // loops indefinitely
{
	// all your code here
	LogicSteering steer();
	// given by ROS dispatcher
	steer.driveLogic(100, 90);
	sandbox->SpinOnce();
}
