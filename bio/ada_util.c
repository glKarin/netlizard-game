#include "ada_util.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

static char * Ada_SkipSpace(char *str, int *count);

char * Ada_ReadLine(FILE *is)
{
	if(!is)
		return NULL;
	if(feof(is))
		return NULL;
	if(ferror(is))
		return NULL;
	long start = ftell(is);
	int c = 0;
	int rn = 0;
	char ch;
	do
	{
		fread(&ch, sizeof(char), 1, is);
		c++;
		if(ch == '\r')
		{
			fread(&ch, sizeof(char), 1, is);
			if(ch == '\n')
			{
				rn = 1;
				break;
			}
			else
				c++;
		}
		else if(ch == '\n')
		{
			break;
		}
	}while(feof(is) == 0 && ferror(is) == 0);
	fseek(is, start, SEEK_SET);
	char *str = calloc(c, sizeof(char));
	fread(str, sizeof(char), c, is);
	str[c - 1] = '\0';
	if(rn)
		fseek(is, 1, SEEK_CUR);
	//printf("|%s|\n", str);
	return str;
}

int Ada_ReadString(char *str, char **r, int *count)
{
	if(!str)
		return 0;
	int c = 0;
	char *p = Ada_SkipSpace(str, &c);
	if(!p)
		return 0;
	if(*p == '\0')
		return 0;
	if(*p != '"')
	{
		fprintf(stderr, "next data is not a string.\n");
		return 0;
	}
	int i = 1;
	while(p[i] != '"')
	{
		if(p[i] == '\0')
			break;
		i++;
	}
	if(p[i] != '"')
	{
		fprintf(stderr, "string miss a second quato.\n");
		return 0;
	}
	c += i;
	if(r)
	{
		if(i == 1)
			*r = NULL;
		else
		{
			*r = calloc(i, sizeof(char));
			memset(*r, '\0', sizeof(char) * i);
			strncpy(*r, p + 1, i - 1);
		}
		if(count)
			*count = c + 1;
	}
	return 1;
}

int Ada_ReadInt(char *str, int *r, int *count)
{
	if(!str)
		return 0;
	int c = 0;
	char *p = Ada_SkipSpace(str, &c);
	if(!p)
		return 0;
	if(*p == '\0')
		return 0;
	if(!isdigit(*p) && *p != '-')
	{
		fprintf(stderr, "next data is not a digit.\n");
		return 0;
	}
	int i = 1;
	while(!isspace(p[i]))
	{
		if(p[i] == '\0')
			break;
		i++;
	}
	c += i;
	if(r)
	{
		char *s = calloc(i + 1, sizeof(char));
		memset(s, '\0', sizeof(char) * (i + 1));
		strncpy(s, p, i);
		*r = atoi(s);
		free(s);
		if(count)
			*count = c;
	}
	return 1;
}

int Ada_ReadFloat(char *str, float *r, int *count)
{
	if(!str)
		return 0;
	int c = 0;
	char *p = Ada_SkipSpace(str, &c);
	if(!p)
		return 0;
	if(*p == '\0')
		return 0;
	if(!isdigit(*p) && *p != '-')
	{
		fprintf(stderr, "next data is not a float.\n");
		return 0;
	}
	int i = 1;
	while(!isspace(p[i]))
	{
		if(p[i] == '\0')
			break;
		i++;
	}
	c += i;
	if(r)
	{
		char *s = calloc(i + 1, sizeof(char));
		memset(s, '\0', sizeof(char) * (i + 1));
		strncpy(s, p, i);
		*r = atof(s);
		free(s);
		if(count)
			*count = c;
	}
	return 1;
}

char * Ada_SkipSpace(char *str, int *count)
{
	if(!str)
	{
		if(count)
			*count = 0;
		return NULL;
	}
	int i = 0;
	while(isspace(str[i]))
	{
		if(str[i] == '\0')
			break;
		i++;
	}
	//printf("|%s\n||%s\n\n", str, str+i);
	if(count)
		*count = i;
	return str + i;
}

void Ada_SkipLine(FILE *is)
{
	if(!is)
		return;
	if(feof(is))
		return;
	if(ferror(is))
		return;
	char ch;
	do
	{
		fread(&ch, sizeof(char), 1, is);
		if(ch == '\r')
		{
			fread(&ch, sizeof(char), 1, is);
			if(ch == '\n')
				break;
		}
		else if(ch == '\n')
		{
			break;
		}
	}while(feof(is) == 0 && ferror(is) == 0);
}
