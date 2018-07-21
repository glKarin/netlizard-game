#include "netlizard_converter.h"
#include "netlizard/nl_util.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *dst_string = NULL;
int *dst_digit_array = NULL;
int dst_digit_size = 0;

int Converter_DecodeIntArrayToString(const char *arr)
{
	Converter_FreeString();
	if(!arr)
		return 0;
	const char *Sp = ",";
	char *cp = strdup(arr);
	const char *p = cp;
	size_t len = 0;
	while((p = strchr(p, Sp[0])) != NULL)
	{
		p++;
		len++;
	}
	len += 1;
	//printfi(len);
	array *a = new_array(nl_int, len, NULL, 0);
	int *dec = (int *)(a->array);
	char *s = strtok(cp, Sp);
	int i = 0;
	do
	{
		dec[i] = atoi(s);
		i++;
	}while((s = strtok(NULL, Sp)) != NULL);

	dst_string = nlParseString(a);
	dst_digit_array = NEW_II(int, a->length);
	memcpy(dst_digit_array, a->array, sizeof(int) * a->length);
	dst_digit_size = a->length;

	delete_array(a);
	free(a);
	free(cp);
	return 1;
}

int Converter_EncodeStringToIntArray(const char *text)
{
	Converter_FreeString();
	if(!text)
		return 0;
	array *arr = nlEncodeStringC(text);
	if(!arr)
		return 0;
	dst_string = strdup(text);
	dst_digit_array = NEW_II(int, arr->length);
	memcpy(dst_digit_array, arr->array, arr->length * sizeof(int));
	dst_digit_size = arr->length;
	printf("Text->%s\n", text);
	delete_array(arr);
	free(arr);
	return 1;
}

void Converter_FreeString(void)
{
	if(dst_digit_array)
	{
		free(dst_digit_array);
		dst_digit_array = NULL;
		dst_digit_size = 0;
	}

	if(dst_string)
	{
		free(dst_string);
		dst_string = NULL;
	}
}
