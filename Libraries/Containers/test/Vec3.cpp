#include <Arduino.h>
#include <ArduinoUnitTests.h>

#include "Vec3.hpp"

unittest(Vec3)
{
	Vec3 v3(1, 2 , 3);
	assertTrue(v3.x == 1 && v3.y == 2 && v3.z == 3);
}

unittest_main()
