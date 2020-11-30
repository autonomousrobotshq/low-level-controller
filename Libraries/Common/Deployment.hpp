/*
*	All deployment related configurations
*	EXAMPLE : Everything is up for discussion
*	--
*/

#ifndef COMMON_DEPLOYMENT_HPP
# define COMMON_DEPLOYMENT_HPP

#define LLC LLC1

enum e_runtime { LAUNCH, UNSAFE, NOINIT };
/*
* RUNTIME defined as # will assert the following modes of operation:
*	0. LAUNCH		:	Autonomous. Bus access restriced. Flashing restricted.
*	1. UNSAFE		:	Requests from bus are accepted unconditionally.
*	2. NOINIT		:	No initialisation sequence. Waits for bus commands.
*/
# define RUNTIME		NOINIT

enum e_verbosity { CRITICAL = 0, VERBOSE = 1, TARGETED = 2, DEBUG = 4 };
/*
* VERBOSITY defined as:
*	CRITICAL		:	Log only output marked critical.	:	crit_f()
*	VERBOSE			:	Log permanent info statements		:	info_f()
*	TARGETED		:	Log targeted debugging statements	:	tmp_f()
*	DEBUG			:	Log permanent debugging statements:	debug_f()
*
*	Always set to CRITICAL when deploying autonomous.
*/
# define VERBOSITY		DEBUG|TARGETED|VERBOSE

#endif
