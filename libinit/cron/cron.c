#include "cron.h"

#define __start
int cron_start()
{
	char *dst_flag = NULL;
	if (strcasecmp(getvar("cron_dst"), YES) == 0)
	{
		dst_flag = "-p";
	}
	char *cmd[] = { COMMAND, getflags(NAME), dst_flag };
	return rundaemon(cmd, PID_FILE);
}

#include "../common.h"
