/*
*	Global state
*/

#ifndef COMMON_STATE_HPP
#define COMMON_STATE_HPP

#include <stdint.h>

enum e_state {
    S_OK,
    S_STARTUP,
    S_SHUTDOWN,
    S_TEMP_WARN,
    S_TEMP_CRIT,
    S_TEMP_ERROR,
    S_COOLDOWN,
    S_PROXIMITY_WARN,
    S_PROXIMITY_CRIT,
    S_PROXIMITY_ERROR,
    S_BATTERY_WARN,
    S_BATTERY_CRIT,
    S_CURRENT_CRIT,
    S_CURRENT_ERROR,
	S_GPS_ERROR,
	S_IMU_ERROR,
	S_ROS_DISCONNECTED
};

extern e_state* __getstate(void);

#define g_state (*__getstate())

#endif
