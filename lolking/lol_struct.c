#include "lol_struct.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char * LOL_ReadLowerStringData(FILE *data, unsigned short len)
{
	if(!data)
		return NULL;
	char *str = LOL_ReadStringData(data, len);
	size_t l = strlen(str);
	unsigned int i;
	for(i = 0; i < l; i++)
		if(isupper(str[i]))
			str[i] = tolower(str[i]);
	return str;
}

char * LOL_ReadStringData(FILE *data, unsigned short l)
{
	if(!data)
		return NULL;
	unsigned short len = l;
	if(len == 0)
		fread(&len, 2, 1, data);
	//printf("len %d", len);
	char *str = calloc(len + 1, 1);
	fread(str, 1, len, data);
	str[len] = '\0';
	//printf(" %s\n", str);
	return str;
}
