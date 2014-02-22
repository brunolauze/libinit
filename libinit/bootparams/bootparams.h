
#ifndef __BOOTPARAMS_H__
#define __BOOTPARAMS_H__
#include "../default.h"

#define PROVIDE		bootparams
#define REQUIRE 	{ "rpcbind", DAEMON }
#define BEFORE		{ LOGIN }
#define KEYWORD 	{ NOJAIL }

#define START_VARIABLE "bootparamd_enable"
#define BOOTPARAMS_CONF "/etc/" NAME
#define BOOTPARAMS_COMMAND "/usr/sbin/" NAME
#define REQUIRED_FILES { BOOTPARAMS_CONF }

#include "../common.h"

#endif

