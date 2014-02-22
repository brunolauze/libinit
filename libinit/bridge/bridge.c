#include "bridge.h"

int do_bridge(char *ifcmd, char *bridge, char *iface)
{
	/* Do it the real way */
	char *cmd[] = { "ifconfig", bridge, ifcmd, iface };
	run_async(cmd);
	return 0;
}

int do_autobridge(char *ifcmd)
{
	char **autobridge_interfaces = getvarlist("autobridge_interfaces");
	if (autobridge_interfaces != NULL)
	{
		char **ifnames_ = getiflist();
		while (*autobridge_interfaces)
		{
			/* get all interfaces */
			char **ifnames = ifnames_;
			while (*ifnames)
			{
				if (strcmp(*ifnames, *autobridge_interfaces) == 0)
				{
					do_bridge(ifcmd, *autobridge_interfaces, *ifnames);
				}
				ifnames++;
			}
			autobridge_interfaces++;
		}
	}
	return 0;
}

int bridge_start()
{
	return do_autobridge(ADDM_COMMAND);
}

#define __stop
int bridge_stop()
{
	return do_autobridge(DELETEM_COMMAND);
}

#include "../common.c"