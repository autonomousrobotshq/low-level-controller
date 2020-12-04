/*
*	Global errno
*/

#ifndef COMMON_ERRNO_HPP
#define COMMON_ERRNO_HPP

#include <stdint.h>

static uint8_t g_errno;

enum e_errno {
	OVERHEATING_ERRNO,
	HEATWARNING_ERRNO,
	US_PROXIMITY_ERRNO,
	LOW_BATTERY_ERRNO,
	OVER_CURRENT_ERRNO,
	MOTOR_FAILURE_ERRNO, // No current going to motor?
#if VERBOSITY & DEBUG
	LOW_RAM
#endif
};

#endif