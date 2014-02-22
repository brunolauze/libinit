
#ifndef __ATM2_H__
#define __ATM2_H__
#include "../default.h"

#define PROVIDE		atm2
#define REQUIRE 	{ "atm1", NETIF }
#define BEFORE 		{ "routing" }
#define KEYWORD 	{ NOJAIL }

#define START_VARIABLE "atm_enable"

#include "../common.h"

#endif

