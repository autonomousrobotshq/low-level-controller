#include "Common/Deployment.hpp"
#include "../Libraries/Sandbox/Sandbox.hpp"
#include "../Libraries/Sensors/IMU.hpp"
#include "../Libraries/Common/Platform.hpp"
#include "../Libraries/SteerLogic/SteerLogic.hpp"

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
	sandbox->SpinOnce();
}
