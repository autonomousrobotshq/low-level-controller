#include <Arduino.h>
#include "Timer.hpp"

Timer::Timer(const unsigned long _interval)
    : _previous_millis(millis())
    , _interval(_interval)
{
}

Timer::~Timer()
{
}

bool Timer::IsTimeToExecute()
{
    return (millis() - _previous_millis >= _interval);
}

unsigned long Timer::GetTimeSinceLastExecution()
{
    return (millis() - _previous_millis);
}

bool Timer::Unlock()
{
    if (IsTimeToExecute()) {
		UpCycle(1);
		return (true);
	}
	return (false);
}

void Timer::UpCycle(int count)
{
	_previous_millis += _interval * count;
}

void Timer::DownCycle(int count)
{
	_previous_millis -= _interval * count;
}

void Timer::Reset()
{
	_previous_millis = millis();
}
