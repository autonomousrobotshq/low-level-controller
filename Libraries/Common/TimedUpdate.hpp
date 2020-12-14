#ifndef COMMON_TIMED_UPDATE_HPP
#define COMMON_TIMED_UPDATE_HPP

#include <stdint.h>

class TimedUpdate {
public:
    TimedUpdate(const uint16_t sampling_interval);
    ~TimedUpdate();
	uint16_t GetTimeSinceLastExecution();
	bool IsTimeToExecute();
private:
	unsigned long _previous_millis;
	const uint16_t _sampling_interval;
};
#endif
