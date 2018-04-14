#ifndef KARIN_TEXTURE_V2_READER_H
#define KARIN_TEXTURE_V2_READER_H

#include "texture_reader.h"

png_texture * nlReadTextureV2_File(const char *name);
png_texture * nlReadTextureV2_Memory(const array *data);
int nlSaveImage_V2File(const char *from, const char *to, int img_type);
int nlSaveImage_V2Memory(const png_texture *tex, const char *to, int img_type);
int nlSaveTextureV2_File(const char *from, const char *to);
int nlSaveTextureV2_Memory(const unsigned char *data, int width, int height, png_texture_format formay, const char *to);

#endif
