
#ifndef __BTHIDD_H__
#define __BTHIDD_H__
#include "../default.h"

#define PROVIDE		bthidd
#define REQUIRE 	{ DAEMON, "hcsecd" }
#define BEFORE		{ LOGIN }
#define KEYWORD 	{ NOJAIL, SHUTDOWN }

#define DEFAULT_BTHIDD_CONF "/etc/bluetooth/" NAME ".conf"
#define REQUIRED_FILES { DEFAULT_BTHIDD_CONF }
#define DEFAULT_HIDS_FILE "/var/db/" NAME ".hids"
#define PID_FILE  "/var/run/" NAME ".pid"
#define BTHIDD_COMMAND_ARGS_FORMAT "-c %s -H %s -p " PID_FILE

#include "../common.h"

#endif

