
#ifndef __CTLD_H__
#define __CTLD_H__
#include "../default.h"

#define	PROVIDE 	ctld
#define REQUIRE 	{ FILESYSTEMS }
#define BEFORE		{ DAEMON }
#define KEYWORD		{ NOJAIL }

#define COMMAND	"/usr/sbin/" NAME
#define PID_FILE "/var/run/" NAME

#define CTLD_CONF "/etc/" NAME ".conf"
#define REQUIRED_FILES { CTLD_CONF }
#define REQUIRED_MODULES { "ctl" }

#include "../common.h"

#endif