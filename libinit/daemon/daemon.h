
#ifndef __DAEMON_H__
#define __DAEMON_H__
#include "../default.h"

#undef DAEMON
#define	PROVIDE 	DAEMON
#define REQUIRE 	{ NETWORKING, SERVERS }

#include "../common.h"

#endif