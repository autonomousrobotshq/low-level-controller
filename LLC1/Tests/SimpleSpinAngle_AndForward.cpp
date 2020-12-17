#include "Common/Deployment.hpp"
#include "Common/Platform.hpp"
#include "Logic/Steering.hpp"
#include "Sandbox/Sandbox.hpp"
#include "Sensors/IMU.hpp"

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

    Serial.println("Test_SimpleSpinAngle_AndForward.cpp");
}

#define _TARGET 175
#define _SPEED 50
void loop() // loops indefinitely
{
    int16_t angle = IMUGetNavigationAngle();

    Serial.print("Angle : "); Serial.println(angle);

	static bool drive_forward;
	if (!drive_forward)
	{
    if (abs(_TARGET - angle) > 2) {
        if (angle > _TARGET) {
            Serial.println("RIGHT");
            Driver(RIGHT, BACKWARD, _SPEED);
            Driver(LEFT, FORWARD, _SPEED);
        } else {
            Serial.println("LEFT");
            Driver(RIGHT, FORWARD, _SPEED);
            Driver(LEFT, BACKWARD, _SPEED);
        }
    } else {
        Serial.println("HALTING");
        Driver(ALL_SIDES, HALT);
		drive_forward = true;
    }
	}
	else
	{
        Serial.println("FORWARD");
        Driver(ALL_SIDES, FORWARD);
	}
	sandbox->SpinOnce();
}

void post() // runs after break in loop()
{
	sandbox->Shutdown();
}
