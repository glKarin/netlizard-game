#include "netlizard.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int nl_debug_mode = 0;

void delete_array(array *arr)
{
	if(!arr)
		return;
	free(arr->array);
}

array * new_array(datatype type, size_t length, void *data, size_t s)
{
	if(length == 0)
		return NULL;
	void *ptr = NULL;
	size_t size = 0;
	if(type == nl_byte || type == nl_unsigned_byte)
	{
		ptr = NEW_II(byte, length);
		size = sizeof(byte);
	}
	else if(type == nl_short || type == nl_unsigned_short)
	{
		ptr = NEW_II(short, length);
		size = sizeof(short);
	}
	else if(type == nl_int || type == nl_unsigned_int)
	{
		ptr = NEW_II(int, length);
		size = sizeof(int);
	}
	else if(type == nl_long || type == nl_unsigned_long)
	{
		ptr = NEW_II(long, length);
		size = sizeof(long);
	}
	else if(type == nl_float)
	{
		ptr = NEW_II(float, length);
		size = sizeof(float);
	}
	else if(type == nl_pointer)
	{
		ptr = NEW_II(void *, length);
		size = sizeof(void *);
	}
	else
	{
		ptr = calloc(length, s);
		size = s;
	}
	array *arr = NEW(array);
	ZERO(arr, array);
	arr->type = type;
	arr->array = ptr;
	arr->length = length;
	if(data)
		memcpy(arr->array, data, size * length);
	return arr;
}

