
#ifndef __APM_H__
#define __APM_H__
#include "../default.h"

#define	PROVIDE		apm
#define REQUIRE 	{ DAEMON }
#define BEFORE 		{ LOGIN }
#define KEYWORD 	{ NOJAIL }

#define APMDEV "/dev/" NAME

#include "../common.h"

#endif


