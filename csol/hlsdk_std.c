#include "hlsdk_std.h"
#include "mathlib.h"

char * strset(char *str, char ch)
{
	if(!str || strlen(str) == 0)
		return str;
	char *ptr = str;
	while(*ptr)
		*ptr++ = ch;
	return str;
}
