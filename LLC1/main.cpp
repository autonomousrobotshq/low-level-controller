#include "Common/Deployment.hpp"
#include "../Libraries/Sandbox/Sandbox.hpp"
#include "../Libraries/Sensors/IMU.hpp"
#include "../Libraries/Common/Platform.hpp"


/*
** SAMPLE CODE
*/

using namespace sb;

Sandbox sandbox;
SensorIMU imu(LLC1::pins_imu);

void setup() //runs on startup
{
	sandbox.Setup();
}

void loop() // loops indefinitely
{
	// all your code here
	sandbox.SpinOnce();
}
