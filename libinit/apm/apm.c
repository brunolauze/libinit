#include "apm.h"
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <machine/apm_bios.h>
#include <x86/apm_bios.h>

static int
apm_getinfo(int fd, apm_info_t aip)
{
	if (ioctl(fd, APMIO_GETINFO, aip) == -1)
		return (-1);
	return 0;
}

static void
apm_enable(int fd, int enable)
{
        if (enable == 1) {
                if (ioctl(fd, APMIO_ENABLE) == -1)
                        err(1, "ioctl(APMIO_ENABLE)");
        } else {
                if (ioctl(fd, APMIO_DISABLE) == -1)
                        err(1, "ioctl(APMIO_DISABLE)");
        }
}



#define __prestart
int apm_prestart()
{
	char *arch = getsysctlbyname("hw.machine_arch");
	if (strcasecmp(arch, "i386") == 0)
	{
		return 0;
	}
	return (-1);
}

int apm_start()
{
	int fd = 0;
	fd = open(APMDEV, O_RDWR);
	apm_enable(fd, 1);
	return 0;
}

#define __stop
int apm_stop()
{
	int fd = 0;
	fd = open(APMDEV, O_RDWR);
	apm_enable(fd, 0);
	return 0;
}


#define __status
int status()
{
	int fd = 0;
	struct apm_info aip;
	fd = open(APMDEV, O_RDONLY);
	if (apm_getinfo(fd, &aip) == 0)
	{
		if (aip.ai_status == 0) {
			printf("APM is disabled\n");
		}
		else {
			printf("APM is enabled\n");
		}
		return 0;
	}
	return (-1);
}

#include "../common.c"
