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

    Serial.println("Test_IMUWithAwarenessResponse.cpp");
}

void loop() // loops indefinitely
{
    int16_t angle = IMUGetNavigationAngle();
    const int16_t target = 175;
	static bool goForward;

    Serial.print("Angle : "); Serial.println(angle);
	if (!goForward)
	{
    	if (abs(target - angle) > 2) {
    	    if (angle > target) {
    	        Serial.println("RIGHT");
    	        Driver(LEFT_SIDE, BACKWARD, 50);
    	        Driver(RIGHT_SIDE, FORWARD, 50);
    	    } else {
    	        Serial.println("LEFT");
    	        Driver(LEFT_SIDE, FORWARD, 50);
    	        Driver(RIGHT_SIDE, BACKWARD, 50);
    	    }
    	} else {
			goForward = true;
    	    Serial.println("HALTING");
    	    Driver(LEFT_SIDE, HALT);
    	    Driver(RIGHT_SIDE, HALT);
    	}
	}
	else
	{
		// just go forward to test the ControllerAwareness response of the ultrasonics
		Driver(LEFT_SIDE, FORWARD);
		Driver(RIGHT_SIDE, FORWARD);
	}
	sandbox->SpinOnce();
}

void post() // runs after break in loop()
{
	sandbox->Shutdown();
}
