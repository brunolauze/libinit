#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/linker.h>
#include <sys/sysctl.h>
#include <sys/stat.h>
#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

/* common functions */
char * 			getoutput(char *cmd);
int 			rundaemon(char *argv[], char *pidpath);
int 			writepid(int pid, const char *path);
int 			run_async(char *argv[]);
int 			is_enabled(const char *svc);
char * 			getflags(const char *svc);
char * 			getvar(const char *name);
char**			getvarlist(const char *name);
int 			load_kld(const char *kldname);
int				file_readable(char *fname);
int				file_executable(char *fname);
char *			getsysctlbyname(const char *sysctlname);
int				getsysctlflagbyname(const char *sysctlname);
int 			setsysctlflagbyname(char *sysctlname, long flag);
char *			path_basename(const char *path);
char** 			str_split(char* a_str, const char a_delim);
char *			concat(char *one, char *two);
char *			ltrim(char *s);
char *			rtrim(char *s);
char *			trim(char *s);
int 			ifup(char *ifname);
int 			ifdown(char *ifname);
char**			getiflist();
void 			rundelayed(void *func, int delay);
int				clearpid_file(char *path);
int 			rm_dir(const char *path);
int 			rm_subdir(const char *path);
int 			rm_subdir_except(const char *path, char **exceptions);
char* 			read_file(char *filename);
char * 			find_in_file(char *file, char *token, int skipbefore, int skipafter);
int 			for_each_line(char *path, void (*iterator)(char *buffer));