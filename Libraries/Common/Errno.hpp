/*
*	Global errno
*/

#ifndef COMMON_ERRNO_HPP
#define COMMON_ERRNO_HPP

#include <stdint.h>

enum e_errno {
	OK_ERRNO,
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

extern e_errno *__geterrno(void);

#define g_errno (*__geterrno())

#endif
