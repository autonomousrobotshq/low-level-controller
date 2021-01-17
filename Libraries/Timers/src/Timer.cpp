#include <Arduino.h>
#include "Timer.hpp"

unsigned long Timer::GetTimeSinceLastExecution()
{
    return (millis() - _previous_millis);
}

bool Timer::IsTimeToExecute()
{
    if (millis() - _previous_millis >= _interval) {
        _previous_millis += _interval;
        return (true);
    }
    return (false);
}

Timer::Timer(const unsigned long _interval)
    : _previous_millis(millis())
    , _interval(_interval)
{
}

Timer::~Timer()
{
}
