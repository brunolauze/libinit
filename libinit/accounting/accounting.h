
#ifndef __ACCOUNTING_H__
#define __ACCOUNTING_H__
#include "../default.h"

#define	PROVIDE		accounting
#define REQUIRE 	{ "mountcritremote" }
#define BEFORE		{ DAEMON }
#define KEYWORD 	{ NOJAIL }

#define ACCOUNTING_COMMAND "/usr/sbin/accton"
#define ACCOUNTING_FILE "/var/account/acct"

#define EXTRA_COMMANDS { "rotate_log" }
#define EXTRA_COMMANDS_DESC { "Rotates the accounting log" }

#include "../common.h"

int accounting_rotate_log(char *argv[]);

#endif

