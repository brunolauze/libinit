
#ifndef __BRIDGE_H__
#define __BRIDGE_H__
#include "../default.h"

#define PROVIDE		bridge
#define REQUIRE 	{ NETIF, "faith", "ppp", "stf" }
#define BEFORE		{ LOGIN }
#define KEYWORD 	{ NOJAIL }

#define ADDM_COMMAND "addm"
#define DELETEM_COMMAND "deletem"

#include "../common.h"

#endif

