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
	if (t.IsTimeToExecute())
	{
		const unsigned int timeSinceLastExecution = t.GetTimeSinceLastExecution();
		t.Reset(); // set timer to current time so IsTimeToExecute() will not attempt to catch up with missed intervals

		// do something that only runs if the Timer instance has expired more than INTERVAL
	}

	delay(INTERVAL / 5);
}
