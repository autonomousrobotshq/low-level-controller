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

    Serial.println("Test_MotorController.cpp");
}

void loop() // loops indefinitely
{
    int16_t angle = IMUGetNavigationAngle();
    const int16_t target = 175;

    Serial.print("Angle : ");
    Serial.println(angle);

    if (abs(target - angle) > 1) {
        if (angle > target) {
            Serial.println("RIGHT");
            Driver(LEFT_SIDE, BACKWARD, 50);
            Driver(RIGHT_SIDE, FORWARD, 50);
        } else {
            Serial.println("LEFT");
            Driver(LEFT_SIDE, FORWARD, 50);
            Driver(RIGHT_SIDE, BACKWARD, 50);
        }
        sandbox->SpinOnce();
    } else {
        Serial.println("HALTING");
        Driver(LEFT_SIDE, HALT);
        Driver(RIGHT_SIDE, HALT);
        sandbox->SpinOnce();
        //Driver(BOTH_SIDES, HALT);
		delay(50);
    }
}

void post() // runs after break in loop()
{
    Serial.println("DIDDA");
}
