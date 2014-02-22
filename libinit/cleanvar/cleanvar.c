#include "cleanvar.h"

int cleanvar_start()
{ 	
	char *exceptions[] = { "log", "logpriv" };
	rm_subdir("/var/run"); /* clean pid files */
	rm_subdir_except("/var/spool/lock", exceptions);
	rm_subdir("/var/spool/uucp/.Temp/");
	return 0;
}

#include "../common.c"
