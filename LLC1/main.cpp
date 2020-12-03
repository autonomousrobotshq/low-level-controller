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
//SensorIMU imu(LLC1::pins_imu);

void setup() //runs on startup
{
	sandbox = new Sandbox();
	sandbox->Setup();
	Serial.begin(115200);
	Serial.println("INIT");
}

void loop() // loops indefinitely
{
	SteerLogic steer(*sandbox);
	// all your code here
	sandbox->SpinOnce();
	
	int distance = 150; // sample code this will be received by ROS
	int angle = 90; // sample code this will be received by ROS
	steer.driveLogic(distance, angle);
	Serial.println("LOOP");
}
