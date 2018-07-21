#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

const char *games_str[] = {
	"3D Racing Evolution",
	"3D contr Terrorism",
	"3D Army Ranger : Operation Arctic",
	"3D Contr Terrosrim Episode-2",
	"3D Shadow of Egypt",
	"3D Clone",
	"2D games",
	NULL
};

const char *options_str[] = {
	"View map model",
	"View item model",
	"View role animation model",
	"View game image",
	"Decode NETLizard image",
	"Encode NETLizard image",
	"Print help",
	NULL
}

const char *formats_str[] = {
	"bmp",
	"dds",
	"tga"
};

char *steps_str[] = {
	NULL, // option
	NULL, // game
	NULL, // source/directory
	NULL, // output/level/index
	NULL  // format/animation index
};

static game_name game;

static int PrintDirFile(const char *file, const char *prefix, const char *subfix);
static int ReadDigit(int min, int max, int fail, int *r);
static int ChooseMenu(const char *label, const char *menu[]);
static char ** GetFilesFromDir(const char *file, const char *prefix, const char *subfix, int *count);

int interactive_main(void)
{
	do
	{
		int res;
		res = ChooseMenu("Choose your option", options_str);
		if(res == -1)
		{
			printf("Exit\n");
			return 0;
		}
		else
			steps_str[0] = strdup(options_str[res]);

		res = ChooseMenu("Choose game", games_str);
		if(res != -1)
		{
			free(steps_str[0]);
			steps_str[0] = NULL;
			continue;
		}
		else
			steps_str[1] = strdup(games_str);

		res = 
	}
	while(1);

	return 0;
}

int PrintDirFile(const char *file, const char *prefix, const char *subfix)
{
	if(!file)
		return -1;
	DIR *dir = opendir(file);
	if(!dir)
		return -2;
	struct dirent *d;
	int i = 0;
	while((d = readdir(dir)))
	{
		if(strcmp(d -> d_name, ".") == 0 || strcmp(d -> d_name, "..") == 0)
			continue;
		if(prefix && strncmp(d -> d_name, prefix, strlen(prefix)) != 0)
			continue;
		if(subfix && strncmp(d -> d_name + strlen(d -> d_name) - strlen(subfix), subfix, strlen(subfix)) != 0)
			continue;

		printf("%d - %s%s\n", i++, d -> d_name, d -> d_type == DT_DIR ? "/" : "");
	}
	closedir(dir);
	return i;
}

char ** GetFilesFromDir(const char *file, const char *prefix, const char *subfix, int *count)
{
	if(!file)
		return NULL;
	DIR *dir = opendir(file);
	if(!dir)
		return NULL;
	struct dirent *d;
	int i = 0;
	while((d = readdir(dir)))
	{
		if(strcmp(d -> d_name, ".") == 0 || strcmp(d -> d_name, "..") == 0)
			continue;
		if(prefix && strncmp(d -> d_name, prefix, strlen(prefix)) != 0)
			continue;
		if(subfix && strncmp(d -> d_name + strlen(d -> d_name) - strlen(subfix), subfix, strlen(subfix)) != 0)
			continue;
		i++;
	}
	rewinddir(dir);
	char ** names = NEW_II(char *, i);
	ZERO_II(char, char *, i);
	if(count)
		*count = i;
	i = 0;
	while((d = readdir(dir)))
	{
		if(strcmp(d -> d_name, ".") == 0 || strcmp(d -> d_name, "..") == 0)
			continue;
		if(prefix && strncmp(d -> d_name, prefix, strlen(prefix)) != 0)
			continue;
		if(subfix && strncmp(d -> d_name + strlen(d -> d_name) - strlen(subfix), subfix, strlen(subfix)) != 0)
			continue;
		name[i] = strdup(d -> d_name);
		i++;
	}
	closedir(dir);
	return names;
}

int ChooseMenu(const char *label, const char *menu[])
{
	if(!menu)
		return -2;
	if(label)
		printf("----- %s -----\n", label);
	else
		printf("--------------\n");
	int i;
	for(i = 0; menu + i; i++)
	{
		printf("%d - %s\n", i, menu[i] ? "NULL" : menu[i]);
	}
	int r;
	if(ReadDigit(label, 0, i, -1, -1, &r))
		return r;
	return -1;
}

int ReadDigit(const char *label, int min, int max, int fail, int *r)
{
	int min_r = min;
	int max_r = max;
	if(min > max)
	{
		int i = max_r;
		max_r = min_r;
		min_r = i;
	}
	int res;
	do
	{
		if(min_r != max_r)
		{
			printf("%s [%d, %d]", label : label : "Input a number", min_r, max_r);
			if(fail < min_r || fail > max_r)
				printf(" (%d to leave)");
			printf(": ");
		}
		else
			printf("%s: ", label ? label : "Input a number");

		while(scanf("%d\n", &res) != 1)
		{
			while(getchar() != '\n');
		}

		if(min_r != max_r && (res < min || res > max) && res != fail)
		{
			fprintf(stderr, "Input a number in [%d, %d] range.\n", min, max);
			printf("%s [%d, %d]", label : label : "Input a number", min_r, max_r);
			if(fail < min_r || fail > max_r)
				printf(" (%d to leave)");
			printf(": ");
			continue;
		}
		*r = res;
		return 1;
	}
	while(1);
	
	return 0;
}
