#include "atm1.h"

int atm1_start()
{
	char **natm_interfaces = getvarlist("natm_interfaces");
	if (natm_interfaces != NULL)
	{
		if (load_kld("if_harp") == -1) return (-1);
		while(*natm_interfaces)
		{
			char* ifname = *(natm_interfaces);
			/* Bring ifname up */
			if (ifup(ifname) == -1)
			{
				/* Report ifup error */
			}
			natm_interfaces++;
		}
	}

	/* Load loadable HARP drivers */
	char **atm_load = getvarlist("atm_load");
	if (atm_load != NULL)
	{
		while(*atm_load)
		{
			char *dev = *(atm_load);
			load_kld(dev);
			atm_load++;
		}
	}

	/* Locate all probed ATM adapters */
	// cmd: atm sh stat int 

	return 0;
}

#include "../common.c"