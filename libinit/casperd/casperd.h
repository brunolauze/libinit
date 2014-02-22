
#ifndef __CASPERD_H__
#define __CASPERD_H__
#include "../default.h"

#define PROVIDE		casperd
#define REQUIRE 	{ NETWORKING, "syslogd" }
#define BEFORE		{ DAEMON }
#define KEYWORD 	{ SHUTDOWN }

#define PID_FILE "/var/run/" NAME ".pid"
#define COMMAND "/sbin/" NAME

#include "../common.h"

#endif

