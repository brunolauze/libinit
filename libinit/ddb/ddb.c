#include "ddb.h"

#define __prestart
int ddb_prestart()
{
	if (getsysctlbyname("debug.ddb.scripting.scripts") == NULL)
	{
		return (-1);
	}
	return 0;
}


#include "../common.c"