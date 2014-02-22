#include "daemon.h"

int daemon_start()
{
	/* Rub DAEMON Script */
	system("sh /etc/rc.d/DAEMON");
	return 0;
}

#include "../common.c"
