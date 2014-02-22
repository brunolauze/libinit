
#ifndef __DEVFS_H__
#define __DEVFS_H__
#include "../default.h"

#define	PROVIDE 	devfs
#define REQUIRE 	{ NETIF }
#define BEFORE		{ "mountcritremote" }
#define	KEYWORDS	{ NOJAIL }

#define ALWAYS_START 1

#define DEVFS_CONF "/etc/devfs.conf"

#include "../common.h"

#endif