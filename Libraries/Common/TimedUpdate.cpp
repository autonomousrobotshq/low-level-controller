#include "Common/TimedUpdate.hpp"
#include <Arduino.h>

uint16_t TimedUpdate::GetTimeSinceLastExecution()
{
    const unsigned long current_millis = millis();

    return (current_millis - _previous_millis);
}

bool TimedUpdate::IsTimeToExecute()
{
    const unsigned long current_millis = millis();

    if (current_millis - _previous_millis > _sampling_interval) {
        _previous_millis += _sampling_interval;
        return (true);
    }
    return (false);
}

TimedUpdate::TimedUpdate(const uint16_t sampling_interval)
    : _previous_millis(millis())
    , _sampling_interval(sampling_interval)
{
}

TimedUpdate::~TimedUpdate()
{
}
