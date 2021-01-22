#include "Timer.hpp"

class Test : public Timer
{
	public:
		Test(const unsigned long interval)
			: Timer(interval)
		{
		}
};

#define INTERVAL 1000

Test t(INTERVAL);

void setup() {
}

void loop() {
	if (t.IsTimeToExecute()) // will return true if timer has expired
	{
		const unsigned int timeSinceLastExecution = t.GetTimeSinceLastExecution();
		t.UpCycle(); // increase timer by INTERVAL

		// do something that only runs if the Timer instance has expired more than INTERVAL
	}

	delay(INTERVAL / 5);
}
