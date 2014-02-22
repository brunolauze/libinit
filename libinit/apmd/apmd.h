
#ifndef __APMD_H__
#define __APMD_H__
#include "../default.h"

#define PROVIDE		apmd
#define REQUIRE 	{ DAEMON }
#define BEFORE 		{ LOGIN }
#define KEYWORD 	{ NOJAIL }

#include "../common.h"

#endif

