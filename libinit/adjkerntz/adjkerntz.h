
#ifndef __ADJKERNTZ_H__
#define __ADJKERNTZ_H__
#include "../default.h"

#define PROVIDE 	adjkerntz
#define REQUIRE 	{ FILESYSTEMS, "postrandom" }
#define BEFORE 		{ NETIF }
#define KEYWORD 	{ NOJAIL }

#define ALWAYS_START 1

#define ADJKERNTZ_COMMAND NAME
#define ADJKERNTZ_DEFAULT_FLAGS "-i"

#include "../common.h"

#endif


