#include "file_system.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int System_mkdir(const char *p)
{
	if(!p)
		return 0;
	struct stat buf;
	int r = stat(p, &buf);
	if(r == 0)
	{
		if(S_ISDIR(buf.st_mode))
			return 1;
		else
			return 0;
	}
	return(mkdir(p, 0755) == 0);
}

char * System_GetPathFromHome(const char *p)
{
	char *home = getenv("HOME");
	if(!home)
		return NULL;
	if(!p)
		return strdup(home);
	size_t len = strlen(home);
	char *r = calloc(len + strlen(p) + 2, sizeof(char));
	strcat(r, home);
	r[len] = '/';
	strcat(r + len + 1 , p);
	//printf("%s\n", r);
	return r;
}
