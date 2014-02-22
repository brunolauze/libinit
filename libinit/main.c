#include "main.h"
#include <stdlib.h>
#include <string.h>

char **provide()
{
	char *items[] = GLOBAL_DEFINE;
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