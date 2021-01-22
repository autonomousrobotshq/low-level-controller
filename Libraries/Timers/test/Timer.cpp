#include <Arduino.h>
#include <ArduinoUnitTests.h>

#include "Timer.hpp"

bool TestForInterval(unsigned long interval)
{
	Timer timer(interval);
	int error = 0;

	delay(interval - interval / 2);
	error += !(timer.IsTimeToExecute() == (interval > 0) ? false : true);
	delay(interval / 2);
	error += !(timer.IsTimeToExecute() == true);
	timer.UpCycle();
	error += !(timer.IsTimeToExecute() == (interval > 0) ? false : true);

	// test if timer properly resets
	delay(interval - interval / 2);
	error += !(timer.IsTimeToExecute() == (interval > 0) ? false : true);
	delay(interval / 2);
	error += !(timer.IsTimeToExecute() == true);
	timer.UpCycle();
	error += !(timer.IsTimeToExecute() == (interval > 0) ? false : true);

	// test if timer returns proper time since last execution
	timer.Reset();
	delay(42);
	error += timer.GetTimeSinceLastExecution() != 42; 
	return (error == 0);
}

bool TestForInterval_Unlock(unsigned long interval)
{
	Timer timer(interval);
	int error = 0;

	delay(interval - interval / 2);
	error += !(timer.Unlock() == (interval > 0) ? false : true);
	delay(interval / 2);
	error += !(timer.Unlock() == true);
	error += !(timer.Unlock() == (interval > 0) ? false : true);

	// test if timer properly resets
	delay(interval - interval / 2);
	error += !(timer.Unlock() == (interval > 0) ? false : true);
	delay(interval / 2);
	error += !(timer.Unlock() == true);
	error += !(timer.Unlock() == (interval > 0) ? false : true);

	// test if timer returns proper time since last execution
	timer.Reset();
	delay(42);
	error += timer.GetTimeSinceLastExecution() != 42; 
	return (error == 0);
}

unittest(Timer)
{
	assertTrue(TestForInterval(0));
	assertTrue(TestForInterval(1 * 1000));
	assertTrue(TestForInterval(3 * 1000));
	assertTrue(TestForInterval(5 * 1000));
	assertTrue(TestForInterval(10 * 1000));
}

unittest(Timer_Unlock)
{
	assertTrue(TestForInterval_Unlock(0));
	assertTrue(TestForInterval_Unlock(1 * 1000));
	assertTrue(TestForInterval_Unlock(3 * 1000));
	assertTrue(TestForInterval_Unlock(5 * 1000));
	assertTrue(TestForInterval_Unlock(10 * 1000));
}

unittest_main()
