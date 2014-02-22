
#ifndef __DDB_H__
#define __DDB_H__
#include "../default.h"

#define	PROVIDE 	ddb
#define REQUIRE 	{ "dumpmon" }
#define BEFORE		{ "disks" }
#define	KEYWORDS	{ NOJAIL }

#define COMMAND	"/sbin/" NAME
#define PID_FILE "/var/run" NAME ".pid"
#define FLAGS_VARIABLE "ddb_config"

#include "../common.h"

#endif