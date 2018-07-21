#include "nl_util.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

array * nlReadFile(const char *name)
{
	if(!name)
		return NULL;
	FILE *file = fopen(name, "rb");
	if(!file)
		return NULL;
	fseek(file, 0, SEEK_END);
	unsigned long l = ftell(file);
	if(l == 0)
	{
		fclose(file);
		return NULL;
	}
	array *arr = new_array(nl_byte, l, NULL, 0);
	fseek(file, 0, SEEK_SET);
	fread(arr->array, sizeof(char), l, file);
	fclose(file);
	return arr;
}

int nlIsPNG(const array *arr)
{
	static const unsigned char PNG_Dec[] = {
		137, 80, 78, 71, 13, 10, 26, 10
	};
	/*
	static const unsigned char PNG_Hex[] = {
		0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A
	};
	*/

	int len = sizeof(PNG_Dec) / sizeof(unsigned char);
	if(!arr)
		return 0;
	int res = 1;
	if(arr->length < len)
		return 0;
	int i1;
	for(i1 = 0; i1 < len; i1++)
	{
		if(((byte *)(arr->array))[i1] != PNG_Dec[i1]) {
			res = 0;
			break;
		}
	}
	return res;
}

int nlIsPNGFile(const char *name)
{
	if(!name)
		return 0;
	array *arr = nlReadFile(name);
	if(!arr)
		return 0;
	int i = nlIsPNG(arr);
	delete_array(arr);
	free(arr);
	return i;
}

float nlIntBitsToFloat(int i)
{
	union bit
	{
		int i;
		float f;
	} u;
	memset(&u, 0, sizeof(union bit));
	u.i = i;
	return u.f;
}

long nlGetFileLength(const char *name)
{
	if(!name)
		return -1;
	FILE *file = fopen(name, "rb");
	if(!file)
		return -1;
	fseek(file, 0, SEEK_END);
	long l = ftell(file);
	fclose(file);
	return l;
}

char * nlParseString(array *arr)
{
	if(!arr)
		return NULL;
	int len = 0;
	char *str = NEW(char);
	ZERO(str, char);
	int i2;
	for(i2 = 0; i2 < arr->length; i2++)
	{
		long l1;
		char ch;
		char *tmp = NULL;
		if ((l1 = ((int *)(arr->array))[i2]) < 0L) {
			l1 += 4294967296LL;
		}
		ch = (char)(int)((l1 & 0xFF000000) >> 24);
		tmp = NEW_II(char, len + 1 + 1);
		memcpy(tmp, str, len * sizeof(char));
		tmp[len] = ch;
		free(str);
		str = tmp;
		len++;
		str[len] = '\0';
		int i1;
		if ((i1 = (char)(int)((l1 & 0xFF0000) >> 16)) == 0) {
			break;
		}
		ch = (char)i1;
		tmp = NEW_II(char, len + 1 + 1);
		memcpy(tmp, str, len * sizeof(char));
		tmp[len] = ch;
		free(str);
		str = tmp;
		len++;
		str[len] = '\0';
		if ((i1 = (char)(int)((l1 & 0xFF00) >> 8)) == 0) {
			break;
		}
		ch = (char)i1;
		tmp = NEW_II(char, len + 1 + 1);
		memcpy(tmp, str, len * sizeof(char));
		tmp[len] = ch;
		free(str);
		str = tmp;
		len++;
		str[len] = '\0';
		if ((i1 = (char)(int)(l1 & 0xFF)) == 0) {
			break;
		}
		ch = (char)i1;
		tmp = NEW_II(char, len + 1 + 1);
		memcpy(tmp, str, len * sizeof(char));
		tmp[len] = ch;
		free(str);
		str = tmp;
		len++;
		str[len] = '\0';
		//printf("%s\n", str);
	}
	return str;
}

char * nlParseStringC(array *arr)
{
	if(!arr)
		return NULL;
	int len = 0;
	char *str = NEW(char);
	ZERO(str, char);
	int i2;
	for(i2 = 0; i2 < arr->length; i2++)
	{
		int *iptr = &(((int *)(arr->array))[i2]);
		long l1 = *iptr;
		if (l1 < 0L) {
			*iptr += 4294967296LL;
		}
		char *ptr = (char *)iptr;
		int i;
		for(i = 0; i < 4; i++)
		{
			char ch = ptr[4 - i - 1];
			if((int)ch == 0)
				break;

			char *tmp = NEW_II(char, len + 1 + 1);
			memcpy(tmp, str, len * sizeof(char));
			tmp[len] = ch;
			free(str);
			str = tmp;
			len++;
			str[len] = '\0';
		}
	}
	//printf("%s\n", str);
	return str;
}

int nlIsNLPNG(const array *arr)
{
	static const unsigned char NL_PNG_Dec[] = {
		237, 53, 40, 32, 101, 99, 112, 97
	};

	int len = sizeof(NL_PNG_Dec) / sizeof(unsigned char);
	if(!arr)
		return 0;
	int res = 1;
	if(arr->length < len)
		return 0;
	int i1;
	for(i1 = 0; i1 < len; i1++)
	{
		if(((byte *)(arr->array))[i1] != NL_PNG_Dec[i1]) {
			res = 0;
			break;
		}
	}
	return res;
}

int nlIsNLPNGFile(const char *name)
{
	if(!name)
		return 0;
	array *arr = nlReadFile(name);
	if(!arr)
		return 0;
	int i = nlIsNLPNG(arr);
	delete_array(arr);
	free(arr);
	return i;
}

array * nlEncodeStringC(const char *str)
{
	if(!str)
		return NULL;
	const char *ptr = str;
	int len = 0;
	int *data = NULL;
	while(*ptr)
	{
		int j;
		char arr[4] = {0, 0, 0, 0};
		for(j = 0; j < 4; j++)
		{
			if(*ptr)
				arr[4 - j - 1] = *ptr;
			else
				break;
			ptr ++;
		}
		if(!data)
		{
			data = NEW(int);
			ZERO(data, int);
			int *iptr = (int *)arr;
			if(*iptr < 0)
				*iptr += 4294967296LL;
			*data = *iptr;
		}
		else
		{
			int *tmp = NEW_II(int, len + 1);
			memcpy(tmp, data, sizeof(int) * len);
			int *iptr = (int *)arr;
			if(*iptr < 0)
				*iptr += 4294967296LL;
			tmp[len] = *iptr;
			free(data);
			data = tmp;
		}
		len++;
	}
	return new_array(nl_int, len, data, 0);
}

// 3D map general function
// ct3d h.a(int, int)
// clone3d h.b(int, int)
// egypt3d f.a(int, int);
int nlMargeDigit(int paramInt1, int paramInt2)
{
	if (paramInt1 < 0) {
		paramInt1 += 256;
	}
	if (paramInt2 < 0) {
		paramInt2 += 256;
	}
	return paramInt1 + (paramInt2 << 8); // * 256
}

int nlSqrtBox(int x, int y, int z)
{
	int i2 = x * x + y * y + z * z;
	int i3 = 65536;
	int i5 = 0;
	while (i3 >>= 1 > 0) {
		if ((i5 + i3) * (i5 + i3) <= i2) {
			i5 += i3;
		}
	}
	return i5;
}

int nlIsNL3DV3Texture(const array *arr)
{
	if(!arr)
		return 0;
	const char *F = "BIP";
	if(arr->length < 3)
		return 0;
	const char *data = (char *)(arr->array);
	return(strncmp(data, F, 3) == 0);
}

int nlIsNL3DV3TextureFile(const char *name)
{
	if(!name)
		return 0;
	array *arr = nlReadFile(name);
	if(!arr)
		return 0;
	int i = nlIsNL3DV3Texture(arr);
	delete_array(arr);
	free(arr);
	return i;
}

int nlIsNL3DV2Texture(const array *arr)
{
	if(!arr)
		return 0;
	const char *F = "&&&";
	if(arr->length < 3)
		return 0;
	const char *data = (char *)(arr->array);
	return(strncmp(data, F, 3) == 0);
}

int nlIsNL3DV2TextureFile(const char *name)
{
	if(!name)
		return 0;
	array *arr = nlReadFile(name);
	if(!arr)
		return 0;
	int i = nlIsNL3DV2Texture(arr);
	delete_array(arr);
	free(arr);
	return i;
}

array * nlEncodeDecodeData(const array *arr)
{
	static const int n = 100;
	if(!arr)
		return NULL;
	array *data = new_array(nl_byte, arr->length, NULL, 0);
	int paramInt = n;
	int i2;
	for (i2 = 0; i2 < arr->length; i2++)
	{
		((byte *)(data->array))[i2] = ((byte)(((byte *)(arr->array))[i2] ^ paramInt));
		paramInt++;
		if (paramInt > 255) {
			paramInt = 0;
		}
	}
	return data;
}
