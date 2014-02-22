
#ifndef __DEFAULTROUTE_H__
#define __DEFAULTROUTE_H__
#include "../default.h"

#define	PROVIDE 	defaultroute
#define REQUIRE 	{ "devd", "faith", NETIF, "stf" }
#define	KEYWORDS	{ NOJAIL }

#include "../common.h"

#endif