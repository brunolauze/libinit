#include "abi.h"

int sysvipc_start()
{
	if (load_kld("sysvmsg")) 
		if (load_kld("sysvsem")) 
			return load_kld("sysvshm");
	return -1;
}

int linux_start()
{
	return load_kld("linux");
}

int srv4_start()
{
	if (load_kld("svr4elf") == 0)
		return load_kld("svr4");
	return (-1);
}

#define __canstart
int abi_canstart()
{
	return is_enabled("sysvipc") || is_enabled("linux") || is_enabled("srv4");
}

int abi_start()
{
	int err1 = 0, err2 = 0, err3 = 0;
	if (is_enabled("sysvipc")) err1 = sysvipc_start();
	if (is_enabled("linux")) err2 = linux_start();
	if (is_enabled("srv4")) err3 = srv4_start();
	return err1 && err2 && err3;
}

#include "../common.c"