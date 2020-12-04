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

bool DriverLogicUpdate(void) // is called just before update of motorcontroller in Sandbox::Spinonce
{
	return (true);
}

void setup() //runs on startup
{
	sandbox = new Sandbox();
	sandbox->Setup();
	sandbox->SetDriverLogicUpdate(DriverLogicUpdate);

	Serial.begin(115200);

	Serial.println("Test_MotorController.cpp");
}

void loop() // loops indefinitely
{
	Driver(RIGHT_SIDE, FORWARD);
	Driver(LEFT_SIDE, BACKWARD);

	//Driver(RIGHT_SIDE, BACKWARD);
	//Driver(LEFT_SIDE, FORWARD);

	//Driver(BOTH_SIDES, BACKWARD);
	//Driver(BOTH_SIDES, FORWARD);
	
	//Driver(BOTH_SIDES, HALT);
	//Driver(BOTH_SIDES, HALT);

	delay (20);
	sandbox->SpinOnce();
}

void post() // runs after break in loop()
{
	Serial.println("DIDDA");
}
