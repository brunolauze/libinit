#include "adjkerntz.h"

int adjkerntz_start()
{
	char *cmd[] = { ADJKERNTZ_COMMAND, ADJKERNTZ_DEFAULT_FLAGS };
	run_async(cmd);
	return 0;
}

#include "../common.c"

