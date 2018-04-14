#include "font_reader.h"

#include "nl_util.h"

#include <stdlib.h>
#include <string.h>

typedef struct _class__o__font
{
	int a;
	int d;
	boolean bool__e;
  array* short_2_array_6x__f__map;
  array* byte_array__h__offset;
  int int__i__char_count;
  boolean bool__l;
  boolean bool__m;
} class__o__font;

static class__o__font * nlMakeFontClass(void);
static class__o__font * clone3d_class_o__function_a_void_return_class_o(const array *arr);
static int clone3d_class_o__function_a_1int_return_int__get_char_map_index(const class__o__font *o, int paramInt);

NETLizard_Font * nlReadNETLizardFont(const char *map_file)
{
	if(!map_file)
		return NULL;
	array *arr = nlReadFile(map_file);
	if(!arr)
		return NULL;
	class__o__font *o = clone3d_class_o__function_a_void_return_class_o(arr);
	if(o)
	{
		NETLizard_Font *fnt = NEW(NETLizard_Font);
		ZERO(fnt, NETLizard_Font);
		fnt -> private_m = o -> bool__m;
		fnt -> private_e = o -> bool__e;
		fnt -> private_l = o -> bool__l;
		fnt -> char_count = o -> int__i__char_count;
		strcpy(fnt -> fnt_file, NETLIZARD_FONT_FILE);
		fnt -> offset = new_array(nl_byte, o -> byte_array__h__offset -> length, o -> byte_array__h__offset -> array, 0);
		fnt -> char_raster_map = new_array(nl_user, o -> short_2_array_6x__f__map -> length, NULL, sizeof(NETLizard_Font_Char_Raster));
		int i;
		short **f = (short **)(o -> short_2_array_6x__f__map -> array);
		for(i = 0; i < o -> short_2_array_6x__f__map -> length; i++)
		{
			NETLizard_Font_Char_Raster *c = (NETLizard_Font_Char_Raster *)(fnt -> char_raster_map -> array) + i;
			c -> x = f[i][0];
			c -> y = f[i][1];
			c -> width = f[i][2];
			c -> height = f[i][3];
			c -> x_strip = f[i][4];
			c -> y_strip = f[i][5];
		}

		for(i = 0; i < o -> short_2_array_6x__f__map -> length; i++)
			free(f[i]);
		delete_array(o -> short_2_array_6x__f__map);
		free(o -> short_2_array_6x__f__map);
		delete_array(o -> byte_array__h__offset);
		free(o -> byte_array__h__offset);
		free(o);
		return fnt;
	}
	delete_array(arr);
	free(arr);
	return NULL;
}

void delete_NETLizard_Font(NETLizard_Font *fnt)
{
	if(!fnt)
		return;
	delete_array(fnt -> char_raster_map);
	free(fnt -> char_raster_map);
	delete_array(fnt -> offset);
	free(fnt -> offset);
}

class__o__font * nlMakeFontClass(void)
{
	class__o__font *fnt = NEW(class__o__font);
	ZERO(fnt, class__o__font);
  fnt -> bool__e = _true;
  fnt -> short_2_array_6x__f__map = NULL;
  signed char h[] = { 0, 4, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 10, 0, 0, 0, 0, 0, 12, 0, 0, 2, 0, 0, 0, 16, 0, 3, 17, 0, 1, 0, -4, 0, 0, 0, 0, 0, 0, 0, -8, 0, 0, 0, -10, 0, 0, 0, 0, 0, -12, 0, 0, -2, 0, 0, 0, -16, 0, -3, -17, -1, 0, 0, 0, 5, -5, 19, -19, 20, -20, 0, 0, 0, 0, 6, -6, 7, -7, 0, 0, 0, 0, 0, 0, 0, 0, 21, -21, 9, -9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, -22, 23, -23, 0, 0, 11, -11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, -13, 24, -24, 0, 0, 0, 0, 14, -14, 0, 0, 15, -15, 0, 0, 0, 0, 0, 0, 0, 0, 27, -27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25, -25, 26, -26, 18, -18, 0, 0, 0 };
	fnt -> byte_array__h__offset = new_array(nl_byte, sizeof(h) / sizeof(signed char), h, 0);
  fnt -> int__i__char_count = 127;
  fnt -> bool__l = _true;
  fnt -> bool__m = _true;
	return fnt;
}

// cf.png
class__o__font * clone3d_class_o__function_a_void_return_class_o(const array *arr)
{
	if(!arr)
		return NULL;
	class__o__font *o = nlMakeFontClass();
	byte *arrayOfByte = (byte *)(arr -> array);
	int i4 = arr -> length / 6;
	if (o -> int__i__char_count < i4) {
		o -> int__i__char_count = i4;
	}
	o -> short_2_array_6x__f__map = new_array(nl_pointer, o -> int__i__char_count + 2, NULL, 0);
	short **f = (short **)(o -> short_2_array_6x__f__map -> array);
	f[o -> int__i__char_count] = NEW_II(short, 6);
	f[o -> int__i__char_count + 1] = NEW_II(short, 6);
	int i2 = 0;
	int i1;
	for (i1 = 0; i1 < o -> int__i__char_count; i1++)
	{
		f[i1] = NEW_II(short, 6);
		int n;
		for (n = 0; n < 6; n++)
		{
			f[i1][n] = ((short)(signed char)arrayOfByte[i2]);
			i2++;
		}
		if (f[i1][0] < 0)
		{
			int tmp141_140 = 0;
			short *tmp141_139 = f[i1];
			tmp141_139[tmp141_140] = ((short)(tmp141_139[tmp141_140] + 256));
		}
		if (f[i1][1] < 0)
		{
			int tmp167_166 = 1;
			short *tmp167_165 = f[i1];
			tmp167_165[tmp167_166] = ((short)(tmp167_165[tmp167_166] + 256));
		}
		if (i2 >= arr -> length) {
			break;
		}
	}
	if (f[0][2] == 0) {
		f[0][2] = f[16][2];
	}
	if (f[0][2] == 0) {
		f[0][2] = f[33][2];
	}
	f[0][3] = 0;
	if (i4 < 146)
	{
		o -> bool__l = _false;
		o -> bool__m = _false;
		o -> bool__e = _false;
	}
	else
	{
		o -> bool__l = _true;
		o -> bool__m = _true;
		o -> bool__e = _true;
	}
	o -> d = f[clone3d_class_o__function_a_1int_return_int__get_char_map_index(o, 1062)][3];
	int n = 0;
	long l1 = 0L;
	for (i1 = 65; i1 <= 90; i1++)
	{
		l1 += f[clone3d_class_o__function_a_1int_return_int__get_char_map_index(o, i1)][3];
		if (n < f[clone3d_class_o__function_a_1int_return_int__get_char_map_index(o, i1)][3]) {
			n = f[clone3d_class_o__function_a_1int_return_int__get_char_map_index(o, i1)][3];
		}
	}
	o -> d = ((int)(l1 / 26L));
	o -> d = n;
	n = 100;
	i1 = -100;
	for (i2 = 0; i2 < o -> short_2_array_6x__f__map -> length; i2++)
	{
		int i3 = -f[i2][5];
		i4 = -(f[i2][3] + f[i2][5]);
		if (i1 < i3) {
			i1 = i3;
		}
		if (n > i4) {
			n = i4;
		}
	}
	int i3 = i1 - n;
	if (o -> d > i3) {
		o -> d = i3;
	}
	if ((n = (i4 = i3 - o -> d >> 1) - i1) != 0) {
		for (i1 = 0; i1 < o -> short_2_array_6x__f__map -> length; i1++)
		{
			int tmp529_528 = 5;
			short *tmp529_527 = f[i1];
			tmp529_527[tmp529_528] = ((short)(tmp529_527[tmp529_528] - n));
		}
	}
	n = 100;
	i1 = -100;
	for (i2 = 65; i2 <= 90; i2++)
	{
		i3 = clone3d_class_o__function_a_1int_return_int__get_char_map_index(o, i2);
		i4 = -f[i3][5];
		i3 = -(f[i3][3] + f[i3][5]);
		if (i1 < i4) {
			i1 = i4;
		}
		if (n > i3) {
			n = i3;
		}
	}
	i3 = i1 - n;
	if ((n = (i4 = o -> d - i3 >> 1) - i1) != 0) {
		for (i3 = 0; i3 < o -> short_2_array_6x__f__map -> length; i3++)
		{
			int tmp668_667 = 5;
			short *tmp668_666 = f[i3];
			tmp668_666[tmp668_667] = ((short)(tmp668_666[tmp668_667] - n));
		}
	}
	o -> a = o -> d;
	//localo1.g = null;
	return o;
}

int clone3d_class_o__function_a_1int_return_int__get_char_map_index(const class__o__font *o, int paramInt)
{
	if(!o)
		return 0;
	int n = paramInt;
	if (paramInt == 946) {
		n = 223;
	}
	signed char *h = (signed char *)(o -> byte_array__h__offset -> array);
	if ((n >= 192) && (n - 192 < o -> byte_array__h__offset -> length))
	{
		if ((paramInt = h[(n - 192)]) < 0)
		{
			paramInt = -paramInt;
			n = 100;
			if (o -> bool__e) {
				n = 201;
			}
			return n + paramInt;
		}
		n = 100;
		if (o -> bool__e) {
			n = 165;
		}
		return n + paramInt;
	}
	if (n > 848) {
		n = paramInt - 848;
	}
	if ((n >= 97) && (n <= 122))
	{
		if (o -> bool__l) {
			n += 35;
		} else {
			n -= 32;
		}
	}
	else if ((n >= 192) && (n <= 223)) {
		n -= 96;
	} else if ((n >= 224) && (n <= 255))
	{
		if (o -> bool__m) {
			n -= 61;
		} else {
			n -= 128;
		}
	}
	else if ((n >= 154) && (n <= 191)) {
		n -= 26;
	}
	n -= 32;
	if ((n < 0) || (n >= o -> int__i__char_count)) {
		n = 0;
	}
	return n;
}

