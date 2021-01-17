#ifndef TIMER_HPP
#define TIMER_HPP

class Timer {
public:
    Timer(const unsigned long _interval);
    ~Timer();
    unsigned long GetTimeSinceLastExecution();
    bool IsTimeToExecute();

private:
    unsigned long _previous_millis;
    const unsigned long _interval;
};

#endif
