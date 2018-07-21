#include "netlizard_converter.h"
#include "netlizard/text_reader.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *dst_text_file = NULL;
char *decode_text = NULL;
char *src_text_file = NULL;

int Converter_DecodeTextFile(const char *name, const char *to, int save)
{
	if(!name)
		return 0;
	src_text_file = strdup(name);
	array *data = nlHandleText_File2Memory(name);
	if(!data || data->length == 0)
		return 0;

	decode_text = NEW_II(char, data->length);
	memcpy(decode_text, data->array, sizeof(char) * data->length);

	printfs(src_text_file);
	int res = 1;
	if(save)
	{
		if(to)
		{
			dst_text_file = strdup(to);
		}
		else
		{
			char txt[] = ".txt";
			char *subfix = strstr(src_text_file, txt);
			if(subfix != src_text_file + strlen(src_text_file) - strlen(txt))
			{
				size_t len = strlen(src_text_file) + strlen(txt) + 1;
				dst_text_file = NEW_II(char, len);
				sprintf(dst_text_file, "%s%s", src_text_file, txt);
			}
			else
			{
				const char *end = "_nlp_dec_";
				size_t len = strlen(src_text_file) + strlen(end) + 1;
				dst_text_file = NEW_II(char, len);
				strncat(dst_text_file, src_text_file, subfix - src_text_file);
				strcat(dst_text_file, end);
				strcat(dst_text_file, txt);
			}
		}
		printfs(dst_text_file);
		FILE *file = fopen(dst_text_file, "w");
		if(!file)
			res = 0;
		else
		{
			res = (fprintf(file, "%s", ((byte *)(data->array))) == data->length - 1) ? 1 : 0;
			fflush(file);
			fclose(file);
		}
	}
	delete_array(data);
	free(data);
	return res;
}

void Converter_FreeText(void)
{
	if(dst_text_file)
	{
		free(dst_text_file);
		dst_text_file = NULL;
	}
	if(src_text_file)
	{
		free(src_text_file);
		src_text_file = NULL;
	}
	if(decode_text)
	{
		free(decode_text);
		decode_text = NULL;
	}
}
