#ifndef _KARIN_HLSDK_STUDIO_GL_H
#define _KARIN_HLSDK_STUDIO_GL_H

#include "studio_model.h"

extern int g_texnum;
extern int textures[MAXSTUDIOSKINS];

void UploadTexture(mstudiotexture_t *ptexture, const Byte *data, const Byte *pal, int texnum, bool import );


#endif
