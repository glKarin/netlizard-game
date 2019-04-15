#ifndef _KARIN_HLSDK_STUDIO_EXPORT_H
#define _KARIN_HLSDK_STUDIO_EXPORT_H

// export function

#include "studio_model.h"

bool BMP_ExportTexture(const StudioModel *mdl, const char *Texname, const char *Filename);
bool BMP_WriteTexture(const Byte *pBitData, const Byte *pColorData, const char *sFilename, const mstudiotexture_t *pTexture);
bool SMD_ExportSequence(const StudioModel *mdl, const char *Seqname, const char *filename);
void SMD_WriteFrame(const StudioModel *mdl, FILE *smdfile, int frame, const mstudioanim_t *panim, const mstudioseqdesc_t *pseqdesc);
void SMD_WriteNodes(const StudioModel *mdl, FILE *smd);
bool SMD_GenerateReferences(const StudioModel *mdl, int Bodyindex, const char *Refname, const char *Filename);
void SMD_WriteTriangle(const StudioModel *mdl, FILE *smdfile, const mstudiomodel_t *pmodel, const mstudiotexture_t *ptexture, const short *pA, const short *pB, const short *pC);

#endif
