
#ifndef __AUDITDISTD_H__
#define __AUDITDISTD_H__
#include "../default.h"

#define PROVIDE		auditdistd
#define REQUIRE 	{ "auditd" }
#define BEFORE 		{ DAEMON }
#define KEYWORD 	{ NOJAIL, SHUTDOWN }

#define AUDITDISTD_COMMAND "/usr/sbin/" NAME
#define PID_FILE	"/var/run/" NAME ".pid"
#define COMMAND AUDITDISTD_COMMAND
#define REQUIRE_FILES { "/etc/security/auditdistd.conf" }

#include "../common.h"

#endif

