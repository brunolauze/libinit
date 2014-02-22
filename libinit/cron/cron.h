
#ifndef __CRON_H__
#define __CRON_H__
#include "../default.h"

#define	PROVIDE 	cron
#define REQUIRE 	{ LOGIN, FILESYSTEMS }
#define BEFORE		{ SECURELEVEL }
#define KEYWORD		{ SHUTDOWN }

#define COMMAND	"/usr/sbin/" NAME
#define PID_FILE "/var/run/" NAME



#include "../common.h"

#endif


