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
	if (t.Unlock()) // Unlock() returns true if timer has expired and up cycles by 1
	{
		// execute code that should run for every INTERVAL
	}

	delay(INTERVAL / 5);
}
