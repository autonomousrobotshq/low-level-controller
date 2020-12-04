#include "Common/Deployment.hpp"
#include "Sandbox/Sandbox.hpp"
#include "Sensors/IMU.hpp"
#include "Common/Platform.hpp"
#include "Logic/Steering.hpp"

/*
** SAMPLE CODE
*/

using namespace sb;

Sandbox *sandbox;
LogicSteering *steering;

void setup() //runs on startup
{
	sandbox = new Sandbox();
	sandbox->Setup();

	steering = new LogicSteering(*sandbox);

	Serial.begin(115200);

	Serial.println("Test_SteeringLogic.cpp");
}

void loop() // loops indefinitely
{
	int distance = 150; // sample code this will be received by ROS
	int angle = 90; // sample code this will be received by ROS

	steering->driveLogic(distance, angle);

	sandbox->SpinOnce();
}

void post() // runs after break in loop()
{
	Serial.println("DIDDA");
}
