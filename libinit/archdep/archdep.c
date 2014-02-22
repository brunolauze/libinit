#include "archdep.h"

int archdep_start()
{
	char *arch = getsysctlbyname("hw.machine_arch");
	if (strcasecmp(arch, "i386") == 0)
	{
		if (is_enabled("ibcs2"))
		{
			load_kld("ibcs2");
			const char* ibcs2_load = getvar("ibcs2_loaders");
			if (strcasecmp("ibcs2_load", "NO") != 0)
			{
				char ibcs2_kld[32];
				sprintf(ibcs2_kld,"ibcs2_%s", ibcs2_load);
				load_kld(ibcs2_kld);
			}
		}
	}
	return 0;
}