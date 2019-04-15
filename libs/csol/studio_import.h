#ifndef _KARIN_HLSDK_STUDIO_IMPORT_H
#define _KARIN_HLSDK_STUDIO_IMPORT_H

#include "studio_model.h"

bool BMP_ImportTexture(const StudioModel *mdl, const char *Texname, const char *Filename);
bool BMP_ReadTexture(Byte *pBitData, Byte *pColorData, const char *sFilename, const mstudiotexture_t *pTexture);


#endif
