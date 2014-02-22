#include "devfs.h"
#include "devfs_rule.h"
#include <pwd.h>

void devfs_ruleset_handler(char *buffer)
{
	static char* rulenum;
	if (buffer[0] == '#') return;   // comment line
 	char *line = trim(buffer);
 	if (buffer[0] == '[') 
 	{
 		sprintf(rulenum, "%s", &line[strlen(line) - 2]);
 	}
 	else if (rulenum != NULL) {
 		char *cmd[] = { "/sbin/devfs", "rule", "-s", rulenum, line };
 		devfs_rule(5, cmd);
 	}
}

int devfs_ruleset_from_file(char *path)
{
 	for_each_line(path, devfs_ruleset_handler);
	return 0;
}

int devfs_init_ruleset()
{
	char *devfs_rulesets = getvar("devfs_rulesets");
	if (devfs_rulesets != NULL)
	{
		char **devfs_rulesets_files = str_split(devfs_rulesets, ' ');
		while(*devfs_rulesets_files)
		{
			devfs_ruleset_from_file(*devfs_rulesets_files);
			devfs_rulesets_files++;
		}
	}
	return 0;
}

int devfs_set_ruleset(char *ruleset)
{
	char *cmd[] = { "/sbin/devfs", "/dev", "ruleset", ruleset  };
	return devfs_ruleset(4, cmd);
}

int devfs_apply_ruleset(char *ruleset)
{
	char *cmd[] = { "/sbin/devfs", "/dev", "rule", "-s", ruleset, "applyset" };
	return devfs_rule(6, cmd);
}

void devfs_conf_handle(char *buffer)
{
	char *line;
	char **rule;
	int i = 0;
	char *dev = NULL;
	char *target = NULL;
	if (buffer != NULL)
	{
		if (strlen(buffer) == 0) return;
		if (buffer[0] == '#') return;
		if (strncmp(buffer, "link ", 5) == 0)
		{
			//ln -sf 
			strncpy(line, buffer+5, strlen(buffer) - 5);
			rule = str_split(line, ' ');
			while(*rule)
			{
				if (i == 0) dev = *rule;
				else target = *rule;
				i++;
				rule++;
			}
		}
		else if (strncmp(buffer, "own ", 4) == 0)
		{
			//chown uid:gid
			strncpy(line, buffer+4, strlen(buffer) - 4);
			rule = str_split(line, ' ');
			while(*rule)
			{
				if (i == 0) dev = *rule;
				else target = *rule;
				i++;
				rule++;
			}
			if (dev != NULL && target != NULL)
			{
				char **id = str_split(target, ':');
				get
			}
		}
		else if (strncmp(buffer, "perm", 5) == 0)
		{
			//chmod mode
			strncpy(line, buffer+5, strlen(buffer) - 5);
			rule = str_split(line, ' ');
			while(*rule)
			{
				if (i == 0) dev = *rule;
				else target = *rule;
				i++;
				rule++;
			}
			if (dev != NULL && target != NULL)
			{
				mode_t *set;
				if ((set = setmode(target)) != NULL)
				{
					chmod(contact("/dev/", dev), set);
				}
			}
		}
	}
}

int devfs_apply_conf()
{
	if (file_readable(DEVFS_CONF))
	{
		for_each_line(DEVFS_CONF, devfs_conf_handle);
	}
}

int devfs_start()
{
	char *devfs_system_ruleset;
	char *devfs_set_rulesets;
	devfs_init_ruleset();
	devfs_system_ruleset = getvar("devfs_system_ruleset");
	devfs_set_rulesets = getvar("devfs_set_rulesets");
	if (devfs_system_ruleset != NULL)
	{
		devfs_set_ruleset(devfs_system_ruleset);
		devfs_apply_ruleset(devfs_system_ruleset);
	}
	if (devfs_set_rulesets != NULL)
	{
		char **devfs_set_items = str_split(devfs_set_rulesets, ' ');
		while (*devfs_set_items)
		{
			char **devfs_item = str_split(*devfs_set_items, '=');
			while (*devfs_item)
			{
				
				devfs_item++;
			}
			devfs_set_items++;
		}
	}
	return 0;
}

#include "../common.c"