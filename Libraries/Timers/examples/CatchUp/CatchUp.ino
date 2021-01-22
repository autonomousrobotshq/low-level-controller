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
		t.UpCycle(); // increase timer by INTERVAL so that it is guaranteed that for every interval X it will run exactly X times 

		// do something that only runs if the Timer instance has expired more than INTERVAL
	}

	//decrease timer by 5 * INTERVAL so that IsTimeToExecute will return true until 5 t.UpCycle() are called within one interval (to catch up)
	t.DownCycle(5);

	delay(INTERVAL / 5);
}
