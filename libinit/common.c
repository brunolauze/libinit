
const char * PROVIDE_FUNC()
{
	return NAME;
}

char **REQUIRE_FUNC()
{
	char *items[] = REQUIRE;
	char **arr = items;
	char **results = (char**)malloc(sizeof(char*) * sizeof(items));
	int i = 0;
	while (*arr)
	{
		results[i] = (char*)malloc(sizeof(char) * strlen(*arr));
		strcpy(results[i++], *arr);
		arr++;
	}
	return results;
}

char **BEFORE_FUNC()
{
	char *items[] = BEFORE;
	char **arr = items;
	char **results = (char**)malloc(sizeof(char*) * sizeof(items));
	int i = 0;
	while (*arr)
	{
		results[i] = (char*)malloc(sizeof(char) * strlen(*arr));
		strcpy(results[i++], *arr);
		arr++;
	}
	return results;
}

char **KEYWORD_FUNC()
{
	char *items[] = KEYWORD;
	char **arr = items;
	char **results = (char**)malloc(sizeof(char*) * sizeof(items));
	int i = 0;
	while (*arr)
	{
		results[i] = (char*)malloc(sizeof(char) * strlen(*arr));
		strcpy(results[i++], *arr);
		arr++;
	}
	return results;
}

#ifndef __canstart
int CANSTART_FUNC()
{
#if ALWAYS_START
	return 0;
#else
#ifndef START_VARIABLE
#define START_VARIABLE NAME "_enable"
#endif
	return is_enabled(START_VARIABLE);
#endif
}
#endif

#ifndef __prestart
int PRESTART_FUNC()
{
	return 0;
}
#endif

#if !defined(__stop)
int STOP_FUNC()
{
	return 0;
}
#endif

#ifndef __status
int STATUS_FUNC()
{
	printf("No status to report");
	return 0;
}
#endif

#ifndef __sanity
int SANITY_FUNC()
{
#ifdef REQUIRED_FILES
	char *files_[] = REQUIRED_FILES;
	char **files = files_;
	while(*files)
	{
		if (file_readable(*files) == -1) return (-1);
		files++;
	}
#endif
	return 0;
}
#endif

#ifndef __listcmd
int LISTCMD_FUNC()
{
#if defined(EXTRA_COMMANDS) && defined(EXTERA_COMMANDS_DESC)
	printf("\n\tsanity: Reports sanity of the service\n");
	printf("\tstart: Starts the service\n");
	printf("\tstop: Stop the service\n");
	printf("\tstatus: Reports the current service status\n");
	char *extra_cmds_ = EXTRA_COMMANDS;
	char *extra_cmds_desc_ = EXTRA_COMMANDS;
	char **extra_cmds = extra_cmds_;
	char **extra_cmds_desc = extra_cmds_desc_;
	while (*extra_cmds)
	{
		printf("\t%s: %s\n", *extra_cmds, *extra_cmds_desc);
		extra_cmds++; 
		extra_cmds_desc++;
	}
#endif
	return 0;
}

#ifndef FLAGS_VARIABLE
#define FLAGS_VARIABLE NAME "_flags"
#endif


#if defined(PID_FILE) && defined(COMMAND)
#ifndef __start
int START_FUNC()
{
	char *cmd[] = { COMMAND, getvar(FLAGS_VARIABLE) };
	return rundaemon(cmd, PID_FILE);
}
#endif
#endif
#endif