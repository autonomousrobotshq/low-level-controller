/*
*	All deployment related configurations
*	EXAMPLE : Everything is up for discussion
*	--
*/

#ifndef COMMON_DEPLOYMENT_HPP
#define COMMON_DEPLOYMENT_HPP

#define LLC LLC1

enum e_runtime { LAUNCH,
    UNSAFE,
    NOINIT };
/*
* RUNTIME defined as # will assert the following modes of operation:
*	0. LAUNCH		:	Autonomous. Bus access restriced. Flashing restricted.
*	1. UNSAFE		:	Requests from bus are accepted unconditionally.
*	2. NOINIT		:	No initialisation sequence. Waits for bus commands.
*/
#define RUNTIME NOINIT

enum e_verbosity {
    PRODUCTION = 0,
    DEBUG = 1,
    SERIAL_DEBUG = 2
};
/*
* VERBOSITY defined as:
*	PRODUCTION		:	Log only output marked critical.
*	ROS_DEBUG		:	Log permanent debugging statements to ROS
*	SERIAL_DEBUG	:	Log permanent debugging statements to serial console and disable ros output
*
*	Always set to PRODUCTION when deploying autonomous.
*/

#define VERBOSITY (DEBUG | SERIAL_DEBUG) // for SERIAL_DEBUGGING
//#define VERBOSITY DEBUG // for ROS DEBUGGING
//#define VERBOSITY PRODUCTION // when performance is key

#endif
