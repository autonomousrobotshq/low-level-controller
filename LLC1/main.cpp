#include "Common/Deployment.hpp"
#include "Sandbox/Sandbox.hpp"
#include "../Libraries/Sensors/IMU.hpp"
#include "../Libraries/Common/Platform.hpp"


/*
** SAMPLE CODE
*/

using namespace sb;

Sandbox sandbox;
SensorIMU imu(LLC1::pins_imu);

void setup() {
	Serial.begin(9600);
}

void loop() {
	Vec3 ret = imu.getAccelerometerData();
	Serial.println(ret.x);
	Serial.println(ret.y);
	Serial.println(ret.z);
	ret = imu.getMagnetometerData();
	Serial.println(ret.x);
	Serial.println(ret.y);
	Serial.println(ret.z);
	imu.update();
	Serial.println(imu.getNavigationAngle());
}
