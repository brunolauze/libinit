#include "auditd.h"

#define __stop
int auditd_stop()
{
	char *cmd[] = { AUDITD_COMMAND, AUDITD_STOP_FLAGS };
	if (run_async(cmd) != -1) clearpid_file(PID_FILE);
	return 0;
}

#include "../common.c"