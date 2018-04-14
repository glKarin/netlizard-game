#include "spirit_reader.h"

#include "nl_util.h"

#include <string.h>
#include <stdlib.h>

static array * clone3d_class_g__function_M_void__read_spirit_map(const array *arr);

// clone 3d is cu.png.
// spirit texture file is u0.png, other 3D game like this, u\d.png file.
array * nlReadSpiritMap(const char *file)
{
	if(!file)
		return NULL;
	array *arr = nlReadFile(file);
	if(!arr)
		return NULL;
	array *rarr = NULL;
	array *qarr = clone3d_class_g__function_M_void__read_spirit_map(arr);
	if(qarr)
	{
		rarr = new_array(nl_user, qarr -> length, NULL, sizeof(NETLizard_Spirit));
		NETLizard_Spirit *spirit = (NETLizard_Spirit *)(rarr -> array);
		short **q = (short **)(qarr -> array);
		int i;
		for(i = 0; i < qarr -> length; i++)
		{
			spirit[i].x = q[i][0];
			spirit[i].y = q[i][1];
			spirit[i].width = q[i][2];
			spirit[i].height = q[i][3];
			spirit[i].private_4 = q[i][4];
			spirit[i].private_5 = q[i][5];
			free(q[i]);
		}
		delete_array(qarr);
		free(qarr);
	}
	delete_array(arr);
	free(arr);
	return rarr;
}

array * clone3d_class_g__function_M_void__read_spirit_map(const array *arr)
{
	if(!arr)
		return NULL;
	byte *arrayOfByte = (byte *)(arr -> array);
	int i1;
	int i5 = (short)(i1 = (arr -> length / 6));
	array *rarr = new_array(nl_pointer, i5, NULL, 0);
	short **q = (short **)(rarr -> array);
	int i2;
	for (i2 = 0; i2 < i1; i2++)
	{
		q[i2] = NEW_II(short, 6);
		int i4 = i2 * 6;
		int i3;
		for (i3 = 0; i3 < 6; i3++)
		{
			q[i2][i3] = ((short)arrayOfByte[(i4 + i3)]);
			if (q[i2][i3] < 0)
			{
				int tmp76_75 = i3;
				short *tmp76_74 = q[i2];
				tmp76_74[tmp76_75] = ((short)(tmp76_74[tmp76_75] + 256));
			}
		}
	}
	return rarr;
}

