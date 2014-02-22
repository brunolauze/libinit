
#ifndef __BGFSCK_H__
#define __BGFSCK_H__
#include "../default.h"

#define PROVIDE		bgfsck
#define REQUIRE 	{ "cron", "devfs", "syslogd" }
#define KEYWORD 	{ NOJAIL }

#define START_VARIABLE "background_fsck"
#define DELAY_VARIABLE "background_fsck_delay"

#include "../common.h"

#endif

