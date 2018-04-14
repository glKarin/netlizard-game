#include "nl_struct_info.h"
#include "netlizard/nl_util.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STRUCT_DIR _KARIN_RESOURCE_DIR"resource/struct"
#define STRUCT_SUBFIX "struct"

static char *name = NULL;
static int show_comment = 0;

int Info_ShowNETLizardStruct(const char *type, int comment)
{
	if(!type)
		return 0;
	if(name)
	{
		free(name);
		name = NULL;
	}
	char t[4];
	memset(t, '\0', 4);
	if(strcasecmp(type, "ct3d") == 0)
	{
		strcpy(t, "lvl");
		name = strdup(type);
	}
	else if(strcasecmp(type, "specnaz3d") == 0)
	{
		strcpy(t, "lvl");
		name = strdup(type);
	}
	else if(strcasecmp(type, "ct3dep2") == 0)
	{
		strcpy(t, "lvl");
		name = strdup(type);
	}
	else if(strcasecmp(type, "egypt3d") == 0)
	{
		strcpy(t, "lvl");
		name = strdup(type);
	}
	else if(strcasecmp(type, "clone3d") == 0)
	{
		strcpy(t, "lvl");
		name = strdup(type);
	}
	else if(strcasecmp(type, "ct3dep2") == 0)
	{
		strcpy(t, "lvl");
		name = strdup(type);
	}
	else if(strcasecmp(type, "tex_v2") == 0)
	{
		strcpy(t, "tex");
		name = strdup("3D_engine_v2");
	}
	else if(strcasecmp(type, "tex_v3") == 0)
	{
		strcpy(t, "tex");
		name = strdup("3D_engine_v3");
	}
	else if(strcasecmp(type, "tex_v3z") == 0)
	{
		strcpy(t, "tex");
		name = strdup("3D_engine_v3_compress");
	}
	else
		return 0;
	show_comment = comment;
	char *file = NEW_II(char, strlen(STRUCT_DIR) + 1 + strlen(name) + 1 + strlen(t) + 1 + strlen(STRUCT_SUBFIX) + 1);
	sprintf(file, "%s/%s.%s.%s", STRUCT_DIR, name, t, STRUCT_SUBFIX);
	printfs(file);
	array *arr = nlReadFile(file);
	if(!arr)
		return 0;
	char *data = (char *)(arr -> array);
	char *title = NULL;
	int i = 0;
	char ch;
	while(i < arr -> length)
	{
		while((ch = data[i]) == '\n') i++;
		if(title == NULL && ch == '[')
		{
			i += 1;
			int j = 0;
			while(data[i + j] != ']' && i + j < arr -> length)
				j++;
			title = NEW_II(char, j + 1);
			memcpy(title, data + i, sizeof(char) * (j + 1));
			title[j] = '\0';
			printf("[%s]\n", title);
			j++;
			i += j;
			while((ch = data[i]) != '\n') i++;
		}
		else if(title && ch == '#')
		{
			i += 1;
			while(isspace((ch = data[i]))) i++;
			int j = 0;
			while(data[i + j] != '\n' && i + j < arr -> length)
				j++;
			if(show_comment)
			{
				char *str = NEW_II(char, j + 1);
				memcpy(str, data + i, sizeof(char) * (j + 1));
				str[j] = '\0';
				printf("# %s\n", str);
				free(str);
			}
			j++;
			i += j;
		}
		else if(title && ch == '<')
		{
			i += 1;
			int j = 0;
			while(data[i + j] != '>' && i + j < arr -> length)
				j++;
			char *str = NEW_II(char, j + 1);
			memcpy(str, data + i, sizeof(char) * (j + 1));
			str[j] = '\0';
			printf("<%s>\n", str);
			free(str);
			j++;
			i += j;
			while((ch = data[i]) != '\n') i++;
		}
		else if(title)
		{
			int j = 0;
			while(data[i + j] != '\n' && i + j < arr -> length)
				j++;
			char *str = NEW_II(char, j + 1);
			memcpy(str, data + i, sizeof(char) * (j + 1));
			str[j] = '\0';
			printf("%s\n", str);
			free(str);
			j++;
			i += j;
		}
		else
		{
			int j = 0;
			while(data[i + j] != '\n' && i + j < arr -> length)
				j++;
			j++;
			i += j;
		}
	}
	free(title);
	free(file);
	delete_array(arr);
	free(arr);
	free(name);
	name = NULL;
	show_comment = 0;
	return 1;
}
