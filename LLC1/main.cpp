#include "Common/Deployment.hpp"
#include "Sandbox/Sandbox.hpp"
#include "math.h"
#include "SteerLogic/SteerLogic.hpp"
/*
** SAMPLE CODE
*/

using namespace sb;

Sandbox sandbox;

void setup() //runs on startup
{
	sandbox.Setup();
}

void loop() // loops indefinitely
{
	SteerLogic steer(sandbox);
	// all your code here
	sandbox.SpinOnce();
	
	int distance = 150; // sample code this will be received by ROS
	int angle = 90; // sample code this will be received by ROS
	steer.driveLogic(distance, angle);
}