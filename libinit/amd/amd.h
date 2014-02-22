
#ifndef __AMD_H__
#define __AMD_H__
#include "../default.h"

#define PROVIDE		amd
#define REQUIRE 	{ FILESYSTEMS, "postrandom", "nfsclient", "nfs_client", "rpcbind" }
#define BEFORE 		{ NETIF }
#define KEYWORD 	{ NOJAIL }

#define AMD_COMMAND "/usr/sbin/" NAME
#define AMD_CONF	"/etc/" NAME ".conf"
#define PID_FILE	"/var/run/" NAME ".pid"
#define AMD_MAP_PROGRAM NAME "_map_program"

#include "../common.h"

#endif


