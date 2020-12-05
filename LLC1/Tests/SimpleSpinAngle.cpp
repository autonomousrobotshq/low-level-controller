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
	float angle = IMUGetNavigationAngle();
	const float target = 180;

	Serial.print("Angle : ");
	Serial.println(angle);

	if (abs(target - angle) > 10)
	{
		if (angle > target)
		{
			Serial.println("RIGHT");
			Driver(LEFT_SIDE, BACKWARD, 50);
			Driver(RIGHT_SIDE, FORWARD, 50);
		}
		else
		{
			Serial.println("LEFT");
			Driver(LEFT_SIDE, FORWARD, 50);
			Driver(RIGHT_SIDE, BACKWARD, 50);

		}
		sandbox->SpinOnce();
		delay(300);
	}
	else
	{
		Serial.println("HALTING");
		Driver(LEFT_SIDE, HALT);
		Driver(RIGHT_SIDE, HALT);
		sandbox->SpinOnce();
		delay(5000);
		//Driver(BOTH_SIDES, HALT);
	}

}

void post() // runs after break in loop()
{
	Serial.println("DIDDA");
}
