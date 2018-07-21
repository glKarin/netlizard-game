#include "texture_v2_reader.h"
#include "nl_util.h"
#include "SOIL/SOIL.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// ct 3d - class h
// specnaz 3d - class ?
// ct 3d ep2 - class ?

static array * class_h__function_b_1byte_array__color_map(const byte paramArrayOfByte[], png_texture_format *format);
static array * class_h__function_a_1byte_array_2bool_3int_4int_5int_6int__color_index(const array *data, int paramBoolean, int paramInt1, int paramInt2, int paramInt3, int paramInt4, int *width, int *height);
static void class_h__function_a_1byte_array__swap(byte paramArrayOfByte[]);

png_texture * nlReadTextureV2_File(const char *name)
{
	if(!name)
		return NULL;
	array *arr = nlReadFile(name);
	if(!arr)
		return NULL;
	png_texture *tex = nlReadTextureV2_Memory(arr);
	delete_array(arr);
	free(arr);
	return tex;
}

png_texture * nlReadTextureV2_Memory(const array *arr)
{
	if(!arr)
		return NULL;
	png_texture *tex = NEW(png_texture);
	ZERO(tex, png_texture);
	tex->color_map = class_h__function_b_1byte_array__color_map(arr->array, &tex->format);
	tex->color_index = class_h__function_a_1byte_array_2bool_3int_4int_5int_6int__color_index(arr, 0, 0, 0, 0, 0, &tex->width, &tex->height);
	//class_h__function_a_1byte_array__swap((byte *)(tex->color_index));
	return tex;
}

int nlSaveImage_V2File(const char *from, const char *to, int img_type)
{
	if(!from || !to)
		return 0;
	png_texture *tex = nlReadTextureV2_File(from);
	if(!tex)
		return 0;
	int res = nlSaveImage_V2Memory(tex, to, img_type);
	delete_png_texture(tex);
	free(tex);
	return res;
}

int nlSaveImage_V2Memory(const png_texture *tex, const char *to, int img_type)
{
	if(!tex || !to)
		return 0;
	unsigned char *data = nlMakeOpenGLTextureDataRGBA(tex);
	int channel = tex->format != nl_rgb ? SOIL_LOAD_RGBA : SOIL_LOAD_RGBA;
	if(data)
	{
		int res = SOIL_save_image(to, img_type, tex->width, tex->height, channel, data);
		free(data);
		return res;
	}
	return 0;
}

int nlSaveTextureV2_Memory(const unsigned char *data,  int width, int height, png_texture_format format, const char *to)
{
	if(!data || !to)
		return 0;
	FILE *file = fopen(to, "wb");
	if(!file)
		return 0;
	const int max_index_count = 255 * 255;
	const int max_map_count = 256;
	long index_len = width * height;
	if(index_len > max_index_count)
		index_len = max_index_count;
	byte *index = NEW_II(byte, index_len);
	unsigned int *map = NULL;
	int len = 0;
	int over = 0;
	int i;
	for(i = 0; i < index_len; i++)
	{
		unsigned color;
		if(format != nl_rgb)
			color = 0xff000000 + (((unsigned int)data[i * 4]) << 16) + (((unsigned int)data[i * 4 + 1]) << 8) + ((unsigned int)data[i * 4 + 2]);
		//color = (((unsigned int)data[i * 4 + 3]) << 24) + (((unsigned int)data[i * 4]) << 16) + (((unsigned int)data[i * 4 + 1]) << 8) + ((unsigned int)data[i * 4 + 2]);
		else
			color = (((unsigned int)data[i * 3]) << 16) + (((unsigned int)data[i * 3 + 1]) << 8) + ((unsigned int)data[i * 3 + 2]);
		if(!map)
		{
			map = NEW_II(unsigned int, len + 1);
			map[len] = color;
			len++;
		}
		else
		{
			int j;
			int cur = len;
			for(j = 0; j < len; j++)
			{
				if(map[j] == color)
				{
					cur = j;
					break;
				}
			}
			if(cur >= len)
			{
				if(len >= max_map_count)
				{
					over = 1;
					break;
				}
				unsigned int *tmp = NEW_II(unsigned int, len + 1);
				memcpy(tmp, map, sizeof(unsigned int) * len);
				tmp[len] = color;
				free(map);
				map = tmp;
				len++;
			}
		}
	}

	if(over)
		nlprintf("Color map'size is over 256. Need to compress.\n")
	else
		nlprintf("Color map'size is less 256. Don't need compress.\n")

	free(map);
	len = 0;
	map = NULL;

	for(i = 0; i < index_len; i++)
	{
		unsigned int color;
		if(format != nl_rgb)
			color = 0xff000000 + (((unsigned int)data[i * 4]) << 16) + (((unsigned int)data[i * 4 + 1]) << 8) + ((unsigned int)data[i * 4 + 2]);
		//color = (((unsigned int)data[i * 4 + 3]) << 24) + (((unsigned int)data[i * 4]) << 16) + (((unsigned int)data[i * 4 + 1]) << 8) + ((unsigned int)data[i * 4 + 2]);
		else
			color = (((unsigned int)data[i * 3]) << 16) + (((unsigned int)data[i * 3 + 1]) << 8) + ((unsigned int)data[i * 3 + 2]);

		color = nlColorRGB888ToRGB332(color);
		if(len == max_map_count)
		{
			index[i] = len - 1;
			continue;
		}
		if(!map)
		{
			map = NEW_II(unsigned int, len + 1);
			map[len] = color;
			index[i] = len;
			len++;
		}
		else
		{
			int j;
			int cur = len;
			if(over)
			{
				for(j = 0; j < len; j++)
				{
					if(map[j] == color)
					{
						cur = j;
						break;
					}
				}
			}
			else
			{
				for(j = 0; j < len; j++)
				{
					if(map[j] == color)
					{
						cur = j;
						break;
					}
				}
			}
			if(cur < len)
			{
				index[i] = cur;
			}
			else
			{
				unsigned int *tmp = NEW_II(unsigned int, len + 1);
				memcpy(tmp, map, sizeof(unsigned int) * len);
				tmp[len] = color;
				free(map);
				map = tmp;
				index[i] = len;
				len++;
			}
		}
	}

	//class_h__function_a_1byte_array__swap(index);

	nlprintf("Make v2 PNG Color map'size->%d\n", len);
	int i2 = 3; // 3
	int i3 = format != nl_rgb ? 1 : 0; // 4
	char c;
	char *magic = "&&&";
	for(i = 0; i < i2; i++)
		fwrite(magic + i, sizeof(char), 1, file);
	c = (char)i3;
	fwrite(&c, sizeof(char), 1, file);
	c = (char)len;
	fwrite(&c, sizeof(char), 1, file);

	// 1 color
	int i1 = len;
	if (i3 == 0)
	{
		int i4 = 0;
		while (i4 < i1)
		{
			//arrayOfInt[i4] = ((paramArrayOfByte[(++i2)] << 16) + (paramArrayOfByte[(++i2)] << 8) + paramArrayOfByte[(++i2)]);
			unsigned char r = (unsigned char)(map[i4] << 8 >> 24);
			unsigned char g = (unsigned char)(map[i4] << 16 >> 24);
			unsigned char b = (unsigned char)(map[i4] << 24 >> 24);
			fwrite(&r, sizeof(unsigned char), 1, file);
			fwrite(&g, sizeof(unsigned char), 1, file);
			fwrite(&b, sizeof(unsigned char), 1, file);
			i4++;
		}
	}
	else
	{
		int i5;
		for (i5 = 0; i5 < i1; i5++) {
			unsigned char a = (unsigned char)(map[i5] >> 24);
			if (a != 0)
			{
				//arrayOfInt[i5] = (-16777216 + (paramArrayOfByte[(++i2)] << 16) + (paramArrayOfByte[(++i2)] << 8) + paramArrayOfByte[(++i2)]);
				unsigned char r = (unsigned char)(map[i5] << 8 >> 24);
				unsigned char g = (unsigned char)(map[i5] << 16 >> 24);
				unsigned char b = (unsigned char)(map[i5] << 24 >> 24);
				fwrite(&a, sizeof(unsigned char), 1, file);
				fwrite(&r, sizeof(unsigned char), 1, file);
				fwrite(&g, sizeof(unsigned char), 1, file);
				fwrite(&b, sizeof(unsigned char), 1, file);
			}
			else
			{
				c = 0;
				fwrite(&c, sizeof(unsigned char), 1, file);
				fwrite(&c, sizeof(unsigned char), 1, file);
				fwrite(&c, sizeof(unsigned char), 1, file);
				fwrite(&c, sizeof(unsigned char), 1, file);
			}
		}
	}

	// 2 index
	unsigned int i5 = width;
	unsigned int i6 = height;
	nlprintf("Make v2 PNG->width: %d, height: %d\n", i5, i6);
	c = (unsigned char)(i5);
	fwrite(&c, sizeof(unsigned char), 1, file);
	c = (unsigned char)(i6);
	fwrite(&c, sizeof(unsigned char), 1, file);
	int i7;
	c = 0;
	fwrite(&c, sizeof(unsigned char), 1, file);
	i = i5 * i6;
	for (i7 = 0; i7 < i; i7++) {
		c = (unsigned char)index[i7];
		fwrite(&c, sizeof(unsigned char), 1, file);
	}
	fflush(file);
	fclose(file);
	free(index);
	free(map);
	return 1;
}

int nlSaveTextureV2_File(const char *from, const char *to)
{
	if(!from || !to)
		return 0;
	int channel;
	int width;
	int height;
	png_texture_format format;
	unsigned char *data = SOIL_load_image(from, &width, &height, &channel, SOIL_LOAD_AUTO);
	nlprintf("Read image->width: %d, height: %d\n", width, height);
	if(!data)
		return 0;
	if(channel == SOIL_LOAD_RGB)
		format = nl_rgb;
	else if(channel == SOIL_LOAD_RGBA)
		format = nl_rgba;
	else
	{
		free(data);
		return 0;
	}
	int res = nlSaveTextureV2_Memory(data, width, height, format, to);
	free(data);
	return res;
}



/* ******** static ******** */

array * class_h__function_b_1byte_array__color_map(const byte paramArrayOfByte[], png_texture_format *format)
{
	if(!paramArrayOfByte)
		return NULL;
	int i2 = 3;
	int i3 = 0;
	if (paramArrayOfByte[3] == 1) {
		i3 = 1;
	}
	int i1;
	i2++;
	if ((i1 = paramArrayOfByte[4]) < 0) {
		i1 += 256;
	}
	nlprintf("NETLizard 3D engine v2 texture color map'size->%d\n", i1);
	array *arr = new_array(nl_int, i1, NULL, 0);
	int *arrayOfInt = (int *)(arr->array);
	if (i3 == 0)
	{
		int i4 = 0;
		//tmpTernaryOp = paramArrayOfByte;
		while (i4 < i1)
		{
			arrayOfInt[i4] = ((paramArrayOfByte[(++i2)]) << 16 | (paramArrayOfByte[(++i2)]) << 8 | paramArrayOfByte[(++i2)]);
			i4++;
		}
	}
	else
	{
		int i5;
		for (i5 = 0; i5 < i1; i5++) {
			if (paramArrayOfByte[(++i2)] != 0)
			{
				arrayOfInt[i5] = (-16777216 + ((paramArrayOfByte[(++i2)]) << 16) + ((paramArrayOfByte[(++i2)]) << 8) + paramArrayOfByte[(++i2)]);
			}
			else
			{
				i2 += 3;
				arrayOfInt[i5] = 0;
			}
		}
	}
	if(format)
	{
		if(i3 != 0)
			*format = nl_rgba;
		else
			*format = nl_rgb;
	}
	return arr;
}

array * class_h__function_a_1byte_array_2bool_3int_4int_5int_6int__color_index(const array *data, int paramBoolean, int paramInt1, int paramInt2, int paramInt3, int paramInt4, int *width, int *height)
{
	if(!data)
		return NULL;
	int i2 = 0;
	int i3 = 0;
	byte *paramArrayOfByte = (byte *)(data->array);
	if (paramArrayOfByte[3] == 1) {
		i3 = 1;
	}
	int i4 = 0;
	if ((i4 = paramArrayOfByte[4]) < 0) {
		i4 += 256;
	}
	if (i3 != 0) {
		i2 = 4 + i4 * 4;
	} else {
		i2 = 4 + i4 * 3;
	}
	//printf("____%d,%d\n", i2, i4);
	byte *arrayOfByte = NULL;
	size_t length = 0;
	int w;
	int h;
	int i5;
	int i6;
	int i7;
	if (!paramBoolean)
	{
		i5 = paramArrayOfByte[(++i2)];
		i6 = paramArrayOfByte[(++i2)];
		if (i5 < 0) {
			i5 += 256;
		}
		if (i6 < 0) {
			i6 += 256;
		}
		if (i5 == 0) {
			i5 += 256;
		}
		if (i6 == 0) {
			i6 += 256;
		}
		int i1;
		arrayOfByte = NEW_II(byte, (i1 = i5 * i6));
		nlprintf("NETLizard 3D engine v2 texture->width: %d, height: %d\n", i5, i6);
		for (i7 = 0; i7 < i1; i7++) {
			arrayOfByte[i7] = paramArrayOfByte[(++i2)];
		}
		length = i1;
		w = i5;
		h = i6;
	}
	else
	{
		i5 = paramArrayOfByte[(++i2)];
		i2++;
		i6 = 0;
		if (i5 < 0) {
			i5 += 256;
		}
		i7 = 0;
		arrayOfByte = NEW_II(byte, paramInt3 * paramInt4);
		i2 += paramInt2 * i5 + paramInt1;
		i2++;
		int i9;
		for (i9 = 0; i9 < paramInt4; i9++)
		{
			int i8 = i9 * i5 + i2;
			int i10;
			for (i10 = 0; i10 < paramInt3; i10++)
			{
				arrayOfByte[i7] = paramArrayOfByte[(i8 + i10)];
				i7++;
			}
		}
		length = paramInt3 * paramInt4;
		w = paramInt4;
		h = paramInt3;
	}
	array *arr = new_array(nl_byte, length, arrayOfByte, 0);
	if(width)
		*width = w;
	if(height)
		*height = h;
	free(arrayOfByte);
	return arr;
}

void class_h__function_a_1byte_array__swap(byte paramArrayOfByte[])
{
	int i2;
	int i3;
	for (i2 = 63; i2 >= 0; i2--) {
		for (i3 = 31; i3 >= 0; i3--)
		{
			byte i1 = paramArrayOfByte[(i3 * 64 + i2)];
			paramArrayOfByte[(i3 * 64 + i2)] = paramArrayOfByte[((63 - i3) * 64 + i2)];
			paramArrayOfByte[((63 - i3) * 64 + i2)] = i1;
		}
	}
}
