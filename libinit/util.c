#include  "util.h"
#include <assert.h>
#include <sys/socket.h>
#include <sys/sockio.h>
#include <net/if.h>
#include <pthread.h>

int writepid(int pid, const char* path)
{
	/* Write pid in that file */
	FILE *pipe;
	pipe = fopen(path, "wb");
	fprintf(pipe, "%d", pid);
	fclose(pipe);
	return 0;
}

int run_async(char *argv[])
{
	int pid = vfork();
	if (pid == 0)
	{
		pid = vfork();
		if (pid != 0)
		{
			execvp(argv[0], argv);
		}
		exit(0);
	}
	return pid;
}

int rundaemon(char *argv[], char *pidpath)
{
	return writepid(run_async(argv), pidpath);
}

int is_enabled(const char *svc)
{
        char name[256];
        sprintf(name, "%s_enable", svc);
        if (strcasecmp(getenv(name), "YES") == 0)
                return 1;
        return 0;
}

char * getflags(const char *svc)
{
        char name[256];
        sprintf(name, "%s_flags", svc);
        return getenv(name);
}

char * getvar(const char *name)
{
        return getenv(name);
}

char **getvarlist(const char *name)
{
	char *var_str = getvar(name);

	if (var_str != NULL && strlen(var_str) > 0)
	{
		return str_split(var_str, ' ');
	}
	return NULL;
}

#define PATHCTL "kern.module_path"

static int path_check(const char *);

/*
 * Check to see if the requested module is specified as a filename with no
 * path.  If so and if a file by the same name exists in the module path,
 * warn the user that the module in the path will be used in preference.
 */
static int
path_check(const char *kldname)
{
	int	mib[5], found;
	size_t	miblen, pathlen;
	char	kldpath[MAXPATHLEN];
	char	*path, *tmppath, *element;
	struct	stat sb;
	dev_t	dev;
	ino_t	ino;

	if (strchr(kldname, '/') != NULL) {
		return (0);
	}
	if (strstr(kldname, ".ko") == NULL) {
		return (0);
	}
	if (stat(kldname, &sb) != 0) {
		return (0);
	}

	found = 0;
	dev = sb.st_dev;
	ino = sb.st_ino;

	miblen = sizeof(mib) / sizeof(mib[0]);
	if (sysctlnametomib(PATHCTL, mib, &miblen) != 0) {
		err(1, "sysctlnametomib(%s)", PATHCTL);
	}
	if (sysctl(mib, miblen, NULL, &pathlen, NULL, 0) == -1) {
		err(1, "getting path: sysctl(%s) - size only", PATHCTL);
	}
	path = malloc(pathlen + 1);
	if (path == NULL) {
		err(1, "allocating %lu bytes for the path",
		    (unsigned long)pathlen + 1);
	}
	if (sysctl(mib, miblen, path, &pathlen, NULL, 0) == -1) {
		err(1, "getting path: sysctl(%s)", PATHCTL);
	}
	tmppath = path;

	while ((element = strsep(&tmppath, ";")) != NULL) {
		strlcpy(kldpath, element, MAXPATHLEN);
		if (kldpath[strlen(kldpath) - 1] != '/') {
			strlcat(kldpath, "/", MAXPATHLEN);
		}
		strlcat(kldpath, kldname, MAXPATHLEN);
				
		if (stat(kldpath, &sb) == -1) {
			continue;
		}	

		found = 1;

		if (sb.st_dev != dev || sb.st_ino != ino) {
			/*
			if (!quiet) {
				warnx("%s will be loaded from %s, not the "
				    "current directory", kldname, element);
			}
			*/
			break;
		} else if (sb.st_dev == dev && sb.st_ino == ino) {
			break;
		}
	}

	free(path);
	
	if (!found) {
		/*
		if (!quiet) {
			warnx("%s is not in the module path", kldname);
		}
		*/
		return (-1);
	}
	
	return (0);
}

int load_kld(const char *kldname)
{
	if (path_check(kldname) == 0) {
		return kldload(kldname);
	}
	return (-1);
}

/* Quick check to see if a file is readable */
int
file_readable(char *fname)
{
    if (access(fname, F_OK))
		return 0;
    return (-1);
}

/* Quick check to see if a file is executable */
int
file_executable(char *fname)
{
    if (access(fname, X_OK))
		return 0;
    return (-1);
}

/* Concatenate two strings into static storage */
char *
concat(char *one, char *two)
{
    static char tmp[FILENAME_MAX];

    /* Yes, we're deliberately cavalier about not checking for overflow */
    strcpy(tmp, one);
    strcat(tmp, two);
    return tmp;
}

/* sane strncpy() function */
char *
sstrncpy(char *dst, const char *src, int size)
{
    dst[size] = '\0';
    return strncpy(dst, src, size);
}

/* Concatenate three strings into static storage */
char *
string_concat3(char *one, char *two, char *three)
{
    static char tmp[FILENAME_MAX];

    /* Yes, we're deliberately cavalier about not checking for overflow */
    strcpy(tmp, one);
    strcat(tmp, two);
    strcat(tmp, three);
    return tmp;
}

/* Clip the whitespace off the end of a string */
char *
string_prune(char *str)
{
    int len = str ? strlen(str) : 0;

    while (len && isspace(str[len - 1]))
	str[--len] = '\0';
    return str;
}

char* getoutput(char *cmd)
{
   char *buffer = NULL;
   char *result;
   int len = 0;
   FILE *pipe = popen(cmd,"r");
   result = malloc(sizeof(char) * 4);
   strcpy(result, "");
   if (pipe)
   {
   		while(!feof(pipe)) {
	    	if (fgets(buffer, 128, pipe) != NULL)
	    	{
	    		len += 128;
	    		realloc(result, sizeof(char) * len);
	    		strcat(result, buffer);
	    	}
    	}
   		pclose(pipe);
   }

   return result;
}

/* run the whitespace off the front of a string */
char *
string_skipwhite(char *str)
{
    while (*str && isspace(*str))
	++str;
    return str;
}

/* copy optionally and allow second arg to be null */
char *
string_copy(char *s1, char *s2)
{
    if (!s1)
	return NULL;
    if (!s2)
	s1[0] = '\0';
    else
	strcpy(s1, s2);
    return s1;
}

/* convert an integer to a string, using a static buffer */
char *
itoa(int value)
{
    static char buf[13];

    snprintf(buf, 12, "%d", value);
    return buf;
}

int
directory_exists(const char *dirname)
{
    DIR *tptr;

    if (!dirname)
	return (-1);
    if (!strlen(dirname))
	return (-1);

    tptr = opendir(dirname);
    if (!tptr)
	return (-1);

    closedir(tptr);
    return 0;
}


/* A free guaranteed to take NULL ptrs */
void
safe_free(void *ptr)
{
    if (ptr)
	free(ptr);
}

/* A malloc that checks errors */
void *
safe_malloc(size_t size)
{
    void *ptr;

    if (size <= 0)
		return NULL;
    ptr = malloc(size);
    if (!ptr)
	 	return NULL;
    bzero(ptr, size);
    return ptr;
}

/* A realloc that checks errors */
void *
safe_realloc(void *orig, size_t size)
{
    void *ptr;

    if (size <= 0)
		return orig;
    ptr = reallocf(orig, size);
    if (!ptr)
		return orig;
    return ptr;
}


/*
 * Get a sysctl variable as a string or "<unknown>" if sysctl fails.
 * Caller must free returned string.
 */
char *
getsysctlbyname(const char *sysctlname)
{
    char *buf;
    size_t sz, buf_sz = 0;
    const char unk_str[] = "<unknown>";

    sysctlbyname(sysctlname, NULL, &buf_sz, NULL, 0);
    buf_sz = MAX(sizeof(unk_str), buf_sz) + 1;
    sz = buf_sz - 1;
    buf = (char *)safe_malloc(buf_sz);

    if (sysctlbyname(sysctlname, buf, &sz, NULL, 0) != -1)
	buf[sz] = '\0';
    else
	strlcpy(buf, unk_str, buf_sz);

    return buf;
}

int
getsysctlflagbyname(const char *sysctlname)
{
    size_t len;
    int val;
    if (sysctlbyname(sysctlname, &val, &len, NULL, 0) == 0)
    	return val;
    return (-1);
}

static int
name2oid(char *name, int *oidp)
{
        int oid[2];
        int i;
        size_t j;

        oid[0] = 0;
        oid[1] = 3;

        j = CTL_MAXNAME * sizeof(int);
        i = sysctl(oid, 2, oidp, &j, name, strlen(name));
        if (i < 0)
                return (i);
        j /= sizeof(int);
        return (j);
}

int setsysctlflagbyname(char *sysctlname, long flag)
{
    int mib[CTL_MAXNAME];
    int len = name2oid(sysctlname, mib);
    return sysctl(mib, len, 0, 0, &flag, sizeof(flag));
}

char *
path_basename(const char *path)
{
    char *pt;
    char *ret = (char *)path;

    pt = strrchr(path,(int)'/');

    if (pt != 0)			/* if there is a slash */
    {
	ret = ++pt;			/* start the file after it */
    }
    
    return(ret);
}


char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        //assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

char *ltrim(char *s)
{
    while(*s == ' ' || *s == '#') s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while((*--back) == ' ' || (*--back) == '#');
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}

int setifflags(char * ifname, int flag, int add)
{
    int sockfd;
	struct ifreq ifr;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	    return (-1);
	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, ifname, IFNAMSIZ);
	if (add == 1)
		ifr.ifr_flags |= flag;
	else
		ifr.ifr_flags = ifr.ifr_flags & ~flag;
	ioctl(sockfd, SIOCSIFFLAGS, &ifr);
	return 0;
}

int ifup(char *ifname)
{
	return setifflags(ifname, IFF_UP, 1);
}

int ifdown(char *ifname)
{
	return setifflags(ifname, IFF_UP, 0);
}

char **getiflist()
{
	return NULL;
}

typedef struct run_delayed_args
{
	void *func;
	int delay;
} run_delayed_t;

void *__rundelayed(void *arg)
{
	run_delayed_t *params = (run_delayed_t*)arg;
	sleep(params->delay);
	void (*foo)();
	foo = params->func;
	foo();
	pthread_exit(NULL);
}

void rundelayed(void *func, int delay)
{
	pthread_t thr;
	run_delayed_t arg;
	arg.func = func;
	arg.delay = delay;
	pthread_create(&thr, NULL, __rundelayed, &arg);
}

int clearpid_file(char *path)
{
	if (file_readable(path))
	{
		unlink(path);
		return 0;
	}
	return (-1);
}

int __rm_subdir(const char *path, char **exceptions, int current)
{
   DIR *d = opendir(path);
   size_t path_len = strlen(path);
   int r = -1;

   if (d)
   {
      struct dirent *p;

      r = 0;

      while (!r && (p=readdir(d)))
      {
          int r2 = -1;
          char *buf;
          size_t len;

          /* Skip the names "." and ".." as we don't want to recurse on them. */
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
          {
             continue;
          }
		  if (exceptions != NULL)
		  {
	          char **except = exceptions;
	          int except_found = 0;
	          while(*except)
	          {
	          	if (strcmp(p->d_name, *except) == 0) {
	          		except_found = 1;
	          		break;
	          	}
	          }
	          if (except_found == 1) continue;
	      }

          len = path_len + strlen(p->d_name) + 2; 
          buf = malloc(len);

          if (buf)
          {
             struct stat statbuf;

             snprintf(buf, len, "%s/%s", path, p->d_name);

             if (!stat(buf, &statbuf))
             {
                if (S_ISDIR(statbuf.st_mode))
                {
                   r2 = __rm_subdir(buf, exceptions, 1);
                }
                else
                {
                   r2 = unlink(buf);
                }
             }

             free(buf);
          }

          r = r2;
      }

      closedir(d);
   }
   if (current == 1 && !r)
   {
      r = rmdir(path);
   }
   return r;
}

int rm_subdir_except(const char *path, char **exceptions)
{
	return __rm_subdir(path, exceptions, 0);
}

int rm_subdir(const char *path)
{
	return __rm_subdir(path, NULL, 0);
}

int rm_dir(const char *path)
{
   return __rm_subdir(path, NULL, 1);
}

char *find_in_file(char *file, char *token, int skipbefore, int skipafter)
{
   	char *result;
   	result = (char*)malloc(sizeof(char) * 512);
	FILE *pipe = popen(file, "r");
	if (!pipe) { sprintf(result, "%s", ""); }
	char buffer[512];
    while(!feof(pipe)) {
    	if (fgets(buffer, 128, pipe) != NULL)
    	{
    		if (!strlen(buffer))   continue;    // blank line

         	if (buffer[0] == '#')  continue;   // comment line
         	if (strncmp(buffer, "/*", 4) == 0) break; // Were at some comments...

         	char *buf = trim(buffer);

         	if (strncmp(buf, token, strlen(token)) == 0)
         	{
         		strncpy(result, buf+strlen(token)+skipbefore, strlen(buf) - strlen(token) - skipafter);
         		break;
         	}
         }
    }
	return result;
}

char* read_file(char *filename)
{
   char *buffer = NULL;
   int string_size,read_size;
   FILE *pipe = fopen(filename,"r");

   if (pipe)
   {
       //seek the last byte of the file
       fseek(pipe,0,SEEK_END);
       //offset from the first to the last byte, or in other words, filesize
       string_size = ftell (pipe);
       //go back to the start of the file
       rewind(pipe);

       //allocate a string that can hold it all
       buffer = (char*) malloc (sizeof(char) * (string_size + 1) );
       //read it all in one operation
       read_size = fread(buffer,sizeof(char),string_size,pipe);
       //fread doesnt set it so put a \0 in the last position
       //and buffer is now officialy a string
       buffer[string_size+1] = '\0';

       if (string_size != read_size) {
           //something went wrong, throw away the memory and set
           //the buffer to NULL
           free(buffer);
           buffer = NULL;
        }
    }

    fclose(pipe);

    return buffer;
}


int for_each_line(char *path, void (*iterator)(char *buffer))
{
    FILE *pipe = fopen(path, "r");
	if (!pipe) { return (-1); }
	char buffer[512];
    while(!feof(pipe)) {
    	if (fgets(buffer, 128, pipe) != NULL)
    	{
    		if (!strlen(buffer))   continue;    // blank line
    		iterator(buffer);
     	}
	}
	pclose(pipe);
	return 0;
}