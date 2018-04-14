#ifndef KARIN_TEXTURE_V3_READER_H
#define KARIN_TEXTURE_V3_READER_H

#include "texture_reader.h"

png_texture * nlReadTextureV3_File(const char *name, int i);
png_texture * nlReadTextureV3_Memory(const array *data, int i);
int nlSaveImage_V3File(const char *from, int i, const char *to, int img_type);
int nlSaveImage_V3Memory(const png_texture *tex, const char *to, int img_type);
int nlSaveTextureV3_File(const char *from, int _i, const char *to);
int nlSaveTextureV3_Memory(const unsigned char *data, int _i, int width, int height, png_texture_format formay, const char *to);

png_texture * nlReadCompressTextureV3_File(const char *name);
png_texture * nlReadCompressTextureV3_Memory(const array *data);
int nlSaveCompressImage_V3File(const char *from, const char *to, int img_type);
int nlSaveCompressImage_V3Memory(const png_texture *tex, const char *to, int img_type);

#endif
