#include "devd.h"

#define __prestart
int devd_prestart()
{
	if (!is_enabled(DEFAULT_START_VARIABLE))
		setsysctlflagbyname("hw.bus.devctl_disable", 1);
	return 0;
}

int devd_start()
{
	if (file_readable(DEVD_CONF))
	{
		char *pid_file = find_in_file("/etc/devd.conf", "pid_file", 2, 2);
		if (pid_file == NULL)
		{
			pid_file = DEFAULT_PID_FILE;
		}
	}
	else {
		//Report missing /etc/devd.conf
	}
	return 0;
}

#include "../common.c"