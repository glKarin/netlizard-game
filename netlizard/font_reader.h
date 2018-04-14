#ifndef KARIN_FONT_READER_H
#define KARIN_FONT_READER_H

#include "netlizard.h"
#define NETLIZARD_FONT_FILE "fnt.png"

typedef struct _NETLizard_Font_Char_Raster
{
	short x;
	short y;
	short width;
	short height;
	short x_strip;
	short y_strip;
} NETLizard_Font_Char_Raster;

typedef struct _NETLizard_Font
{
  array* char_raster_map;
  array* offset;
  int char_count;

	byte private_e;
  byte private_l;
  byte private_m;

	char fnt_file[8];
} NETLizard_Font;

NETLizard_Font * nlReadNETLizardFont(const char *map_file);
void delete_NETLizard_Font(NETLizard_Font *fnt);

#endif
