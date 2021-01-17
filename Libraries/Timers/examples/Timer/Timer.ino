#include "Timer.hpp"

class Test : public Timer
{
	public:
		Test(const unsigned long interval)
			: Timer(interval)
		{
		}
};

#define INTERVAL 5

Test t(5);

void setup() {
}

void loop() {
	if (t.IsTimeToExecute())
	{
		// do something that only runs if the Timer instance has expired more than INTERVAL
		// if IsTimeToExecute returns true, it will again return falls until it again has expired more than INTERVAL.
	}

	const unsigned int timeSinceLastExecution = t.GetTimeSinceLastExecution();
}
