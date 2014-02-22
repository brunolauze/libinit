
#ifndef __ATM3_H__
#define __ATM3_H__
#include "../default.h"

#define PROVIDE		atm3
#define REQUIRE 	{ "atm2" }
#define BEFORE 		{ DAEMON }
#define KEYWORD 	{ NOJAIL }

#define START_VARIABLE "atm_enable"

#include "../common.h"

#endif

