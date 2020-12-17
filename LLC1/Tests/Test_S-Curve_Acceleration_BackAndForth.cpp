#include "Common/Deployment.hpp"
#include "Common/Platform.hpp"
#include "Logic/Steering.hpp"
#include "Sandbox/Sandbox.hpp"
#include "Sensors/IMU.hpp"

/*
** SAMPLE CODE
*/

using namespace sb;

Sandbox* sandbox;

bool LogicDriverUpdate(void) // is called just before update of motorcontroller in Sandbox::Spinonce
{
    return (true);
}

void setup() //runs on startup
{
    sandbox = new Sandbox();
    sandbox->Setup();
    sandbox->SetLogicDriverUpdate(LogicDriverUpdate);

    Serial.begin(115200);

    Serial.println("Test_S-Curve_Acceleration_BackAndForth.cpp");
}

#define _SPEED 200
void loop() // loops indefinitely
{
	static bool first;
	if (!first && DriverIsReady())
	{
    	Driver(ALL_SIDES, FORWARD, _SPEED);
		first = true;
	}

	static bool second;
	if (!second & DriverIsReady())
	{
    	Driver(ALL_SIDES, SLOWHALT);
		second = true;
	}

	static bool third;
	if (!third & DriverIsReady())
	{
    	Driver(ALL_SIDES, BACKWARD, _SPEED);
		third = true;
	}
	// WTF 4 static bools and STK Timeout???
	static int fourth;
	if (!fourth & DriverIsReady())
	{
    	Driver(ALL_SIDES, SLOWHALT);
		fourth = true;
	}

	if (first && second && third && fourth && DriverIsReady())
	{
		first = false;
		second = false;
		third = false;
		fourth = false;
	}

    sandbox->SpinOnce();
}

void post() // runs after break in loop()
{
}
