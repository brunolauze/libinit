#include "bgfsck.h"

void runfsck()
{
	char *cmd[] = { "nice", "-4", "fsck", "-B", "-p" };
	run_async(cmd);
}

int bgfsck_start()
{
	rundelayed(runfsck, 5);
	return 0;
}

#include "../common.c"