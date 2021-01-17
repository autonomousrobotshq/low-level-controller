#include <Arduino.h>
#include <ArduinoUnitTests.h>

#include "PeakFilter.hpp"

bool	TestForArray(int nums[], int samplecount, int expected)
{
	PeakFilter filter(samplecount);
	
	filter.Reset();
	
	for (int i = 0; i < samplecount; i++) {
	    filter.NewReading(nums[i]);
	}
	const int16_t f_avg = filter.GetFilteredSignal();

	return (f_avg == expected);
}

unittest(PeakFilter)
{
	int nums[] = {1, 1, 1, 5};
	assertTrue(TestForArray(nums, 4, 1));
}

unittest_main()
