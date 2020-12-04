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
	MOTOR_FAILURE_ERRNO,
#if VERBOSITY & DEBUG
	LOW_RAM
#endif
};

#endif