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

void setup() //runs on startup
{
	sandbox = new Sandbox();
	sandbox->Setup();

	Serial.begin(115200);

	Serial.println("Test_MotorController.cpp");
}

void loop() // loops indefinitely
{

	Driver(LEFT_SIDE, FORWARD);
	Driver(RIGHT_SIDE, BACKWARD);

	delay (20);
	sandbox->SpinOnce();
}

void post() // runs after break in loop()
{
	Serial.println("DIDDA");
}
