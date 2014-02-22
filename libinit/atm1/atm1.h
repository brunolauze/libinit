
#ifndef __ATM1_H__
#define __ATM1_H__
#include "../default.h"

#define PROVIDE		atm1
#define REQUIRE 	{ "root" }
#define BEFORE 		{ NETIF }
#define KEYWORD 	{ NOJAIL }

#define START_VARIABLE "atm_enable"

#include "../common.h"

#endif

