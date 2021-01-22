#ifndef TIMER_HPP
#define TIMER_HPP

class Timer {
public:
    Timer(const unsigned long _interval);
    ~Timer();
    unsigned long GetTimeSinceLastExecution();
    bool IsTimeToExecute();
	bool Unlock();
	void UpCycle(int count = 1);
	void DownCycle(int count = 1);
	void Reset();

private:
    unsigned long _previous_millis;
    const unsigned long _interval;
};

#endif
