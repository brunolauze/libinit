#include "amd.h"

int amd_start()
{
	char *baseflags = getflags(NAME);
	char *map_cmd = getvar(AMD_MAP_PROGRAM);
	char *cmd[] = { AMD_COMMAND, concat(baseflags, getoutput(map_cmd)) };
	return rundaemon(cmd, PID_FILE);
}

#include "../common.c"
