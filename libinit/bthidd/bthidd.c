#include "bthidd.h"

#define __prestart
int bthidd_prestart()
{
	if (load_kld("kbdmux") == -1) return (-1);
	if (load_kld("vkbd") == -1) return (-1);
	if (load_kld("ng_btsocket") == -1) return (-1);
	return 0;
}

int bthidd_start()
{
	return 0;
}

#include "../common.c"