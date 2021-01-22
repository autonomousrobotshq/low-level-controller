#include <Arduino.h>
#include <ArduinoUnitTests.h>

#include <climits>
#include "Vec3.hpp"

unittest(Vec3)
{
	Vec3<int> v3(INT_MIN, 0 , INT_MAX);
	assertTrue(v3.x == INT_MIN && v3.y == 0 && v3.z == INT_MAX);
}

unittest_main()
