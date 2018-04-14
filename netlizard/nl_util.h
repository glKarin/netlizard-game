#ifndef KARIN_NL_UTIL_H
#define KARIN_NL_UTIL_H

#include "netlizard.h"

array * nlReadFile(const char *name);
char * nlParseString(array *arr);
char * nlParseStringC(array *arr);
array * nlEncodeStringC(const char *str);
int nlIsPNGFile(const char *name);
int nlIsPNG(const array *arr);
int nlIsNLPNGFile(const char *name);
int nlIsNLPNG(const array *arr);
float nlIntBitsToFloat(int i);
long nlGetFileLength(const char *name);
int nlMargeDigit(int paramInt1, int paramInt2);
int nlSqrtBox(int x, int y, int z);
int nlIsNL3DV2TextureFile(const char *name);
int nlIsNL3DV2Texture(const array *arr);
int nlIsNL3DV3TextureFile(const char *name);
int nlIsNL3DV3Texture(const array *arr);
array *nlEncodeDecodeData(const array *arr);

#endif
