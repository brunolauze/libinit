
#ifndef __DEVD_H__
#define __DEVD_H__
#include "../default.h"

#define	PROVIDE 	devd
#define REQUIRE 	{ NETIF }
#define BEFORE		{ NETWORKING, "mountcritremote" }
#define	KEYWORDS	{ NOJAIL, SHUTDOWN }

#define DEVD_CONF "/etc/devd.conf"
#define DEFAULT_PID_FILE "/var/run/devd.pid"

#include "../common.h"

#endif