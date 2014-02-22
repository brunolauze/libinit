#include "bootparams.h"

int bootparams_start()
{
	char *cmd[] = { BOOTPARAMS_COMMAND };
	return run_async(cmd);
}

#include "../common.c"
