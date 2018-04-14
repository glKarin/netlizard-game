#ifndef KARIN_TEXTURE_READER_H
#define KARIN_TEXTURE_READER_H

#include "netlizard.h"

typedef enum _png_texture_format
{
	nl_rgb = 0,
	nl_rgba
} png_texture_format;

typedef struct _texture_png
{
	png_texture_format format;
	int width;
	int height;
	int depth;
	array *color_map;
	array *color_index;
} png_texture;

unsigned char * nlMakeOpenGLTextureDataRGB(const png_texture *tex);
unsigned char * nlMakeOpenGLTextureDataRGBA(const png_texture *tex);
unsigned char * nlMakeOpenGLTextureDataRGBACompress(const png_texture *tex);
unsigned int nlColorRGB888ToRGB332(unsigned int a);
void delete_png_texture(png_texture *tex);

#endif
