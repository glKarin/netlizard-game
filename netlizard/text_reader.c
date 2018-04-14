#include "text_reader.h"
#include "nl_util.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>

// clone 3d
static array * class_p__function_a_1string_2char__text(const array *arr, wchar_t paramChar);

array * nlHandleText_File2Memory(const char *name)
{
	if(!name)
		return NULL;
	array *arr = nlReadFile(name);
	if(!arr)
		return NULL;
	array *data = nlHandleText_Memory2Memory(arr);
	delete_array(arr);
	free(arr);
	return data;
}

array * nlHandleText_Memory2Memory(const array *arr)
{
	if(!arr)
		return NULL;
	//return nlEncodeDecodeData(arr);
	return class_p__function_a_1string_2char__text(arr, (wchar_t)' ');
}

int nlHandleText_File2File(const char *from, const char *to)
{
	if(!from || !to)
		return 0;
	array *data = nlHandleText_File2Memory(from);
	int res = 0;
	if(data)
	{
		FILE *file = fopen(to, "w");
		if(!file)
			res = 0;
		else
		{
			res = (fprintf(file, "%s", ((byte *)(data -> array))) == data -> length - 1) ? 1 : 0;
			fflush(file);
			fclose(file);
		}
		delete_array(data);
		free(data);
		return res;
	}
	return 0;
}

int nlHandleText_Memory2File(const array *arr, const char *to)
{
	if(!arr || !to)
		return 0;
	array *data = nlHandleText_Memory2Memory(arr);
	int res = 0;
	if(data)
	{
		FILE *file = fopen(to, "w");
		if(!file)
			res = 0;
		else
		{
			res = (fprintf(file, "%s", ((byte *)(data -> array))) == data -> length - 1) ? 1 : 0;
			fflush(file);
			fclose(file);
		}
		delete_array(data);
		free(data);
		return res;
	}
	return 0;
}

// clone 3d
array * class_p__function_a_1string_2char__text(const array *arr, wchar_t paramChar)
{
	if(!arr)
		return NULL;
	if(arr -> length == 0)
		return NULL;
	int length = arr -> length;
	signed char *o = (signed char *)(arr -> array);
	array *data = NULL;
	signed char *paramString = NULL;
	if ((length > 1) && (o[0] == 59) && (o[1] == 67)) {
		data = nlEncodeDecodeData(arr);
		length = data -> length;
		paramString = (signed char *)(data -> array);
	}
	else if ((length > 1) && (o[0] == -101) && (o[1] == -101)) {
		data = nlEncodeDecodeData(arr);
		length = data -> length;
		paramString = (signed char *)(data -> array);
	}
	else
	{
		length = arr -> length;
		paramString = (signed char *)(arr -> array);
	}
	wchar_t c1 = '\000';
	if ((length > 0) && (paramString[0] == 95)) {
		c1 = '\002';
	}
	/*
	if ((paramString.length >= 2) && (paramString[0] == -1) && (paramString[1] == -2)) {
		return a(paramString);
	}*/
	wchar_t c2 = c1;
	int k;
	paramChar = length;
	int j = (k = length - c1) + c1;
	wchar_t c3;
	for (c3 = c1; c3 < (unsigned int)j; c3++) {
		if (paramString[c3] == 0)
		{
			k = c3 - c1;
			paramChar = c3;
			break;
		}
	}
	wchar_t *arrayOfChar = NEW_II(wchar_t, k);
	int m;
	for (m = 0; m < k; m++)
	{
		if ((j = paramString[(m + c1)]) < 0) {
			j += 256;
		}
		arrayOfChar[m] = ((wchar_t)j);
	}
	while (c2 < paramChar)
	{
		if ((j = paramString[c2]) < 0) {
			j += 256;
		}
		if (j == 0) {
			break;
		}
		if (j == 32) {
			arrayOfChar[(c2 - c1)] = ' ';
		}
		if (j < 10) {
			arrayOfChar[(c2 - c1)] = ' ';
		}
		if ((j >= 192) && (j <= 255))
		{
			j += 848;
			arrayOfChar[(c2 - c1)] = ((wchar_t)j);
		}
		c2++;
	}
	size_t s = sizeof(wchar_t) / sizeof(char);
	setlocale(LC_CTYPE, "ru");
	char *str = NEW_II(char, k * s + 1);

	int l = -1;
	int count = 1;
	char *p = str;
	int i = 0;
	int ii = 0;
	wchar_t *wp = arrayOfChar;
	while(1)
	{
		if(i >= k)
			break;
		l = wcstombs(p, wp, count);
		if(l <= 0)
		{
			count++;
			continue;
		}
		p += count;
		ii += count;
		count = 1;
		wp++;
		i++;
	}
	array *res = new_array(nl_byte, ii + 1, str, 0);
	((char *)(res -> array))[ii] = '\0';
	setlocale(LC_CTYPE, NULL);
	delete_array(data);
	free(data);
	free(arrayOfChar);
	free(str);
	return res;
}

