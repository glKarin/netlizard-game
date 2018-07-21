#include "png_reader.h"
#include "nl_util.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

array * nlHandlePNG_File2Memory(const char *name)
{
	if(!name)
		return NULL;
	array *arr = nlReadFile(name);
	if(!arr)
		return NULL;
	array *data = nlHandlePNG_Memory2Memory(arr);
	delete_array(arr);
	free(arr);
	return data;
}

array * nlHandlePNG_Memory2Memory(const array *arr)
{
	if(!arr)
		return NULL;
	if(nlIsPNG(arr))
		nlprintf("Encode NETLizard 2D image PNG\n")
	else if(nlIsNLPNG(arr))
		nlprintf("Decode NETLizard 2D image PNG\n")
	else
	{
		nlprintf("Unsupported PNG\n");
		return NULL;
	}
	return nlEncodeDecodeData(arr);
}

int nlHandlePNG_File2File(const char *from, const char *to)
{
	if(!from || !to)
		return 0;
	array *data = nlHandlePNG_File2Memory(from);
	int res = 0;
	if(data)
	{
		FILE *file = fopen(to, "wb");
		if(!file)
			res = 0;
		else
		{
			size_t i = fwrite(data->array, sizeof(byte), data->length, file);
			size_t l = data->length;
			res = (i == l) ? 1 : 0;
			fflush(file);
			fclose(file);
		}
		delete_array(data);
		free(data);
		return res;
	}
	return 0;
}

int nlHandlePNG_Memory2File(const array *arr, const char *to)
{
	if(!arr || !to)
		return 0;
	array *data = nlHandlePNG_Memory2Memory(arr);
	int res = 0;
	if(data)
	{
		FILE *file = fopen(to, "wb");
		if(!file)
			res = 0;
		else
		{
			size_t i = fwrite(data->array, sizeof(byte), data->length, file);
			size_t l = data->length;
			res = (i == l) ? 1 : 0;
			fflush(file);
			fclose(file);
		}
		delete_array(data);
		free(data);
		return res;
	}
	return 0;
}

