#include "accounting.h"

int accounting_start()
{
	char *cmd[] = { ACCOUNTING_COMMAND, ACCOUNTING_FILE };
	run_async(cmd);
	return 0;
}

#define __stop
int accounting_stop()
{
	printf("Turning off accouting...\n");
	char *cmd[] = { ACCOUNTING_COMMAND };
	run_async(cmd);
	return 0;
}

int accounting_rotate_log(char __unused *argv[])
{
	if (accounting_canstart())
	{
		/* Rotate logs */
		return 0;
	}
	return (-1);
}

#include "../common.c"