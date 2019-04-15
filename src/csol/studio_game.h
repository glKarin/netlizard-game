#ifndef _KARIN_HLSDK_STUDIO_GAME_H
#define _KARIN_HLSDK_STUDIO_GAME_H

#include "csol/studio_render.h"
#include "csol/hlsdk.h"

#define HL_MDL_Z_TRANSLATE 36

#define LEG_PART 1
#define BODY_PART 2
#define ALL_PART 0

enum
{
	Leg_Part_Index,
	Body_Part_Index,
	All_Part_Count
};

typedef struct {
	StudioModel mdl;
	unsigned has_init;
	unsigned int sequences[All_Part_Count];
	float frames[All_Part_Count];
	float fps[All_Part_Count];
	unsigned part;
} GameStudioModel;

int CSOL_FindBone(const StudioModel *mdl, const char *name);
int CSOL_GetPartBones(StudioModel *mdl, unsigned int ret[], unsigned int count, unsigned part);
void CSOL_SetUpBones ( GameStudioModel *gmdl );
void CSOL_DrawModel(GameStudioModel *gmdl);
unsigned CSOL_LoadMDL(GameStudioModel *gmdl, const char *mdlfile);
void CSOL_FreeMDL(GameStudioModel *gmdl);
void CSOL_SetSequence( GameStudioModel *gmdl, unsigned part, int iSequence );
mstudioseqdesc_t * CSOL_GetSequence( GameStudioModel *gmdl, const char *name, int *index );
float CSOL_SetFrame(GameStudioModel *gmdl, unsigned part, float frame);
float CSOL_AdvanceFrame( GameStudioModel *gmdl, unsigned part, float dt );
void CSOL_CalcRotations ( StudioModel *mdl, vec3_t *pos, vec4_t *q, mstudioseqdesc_t *pseqdesc, mstudioanim_t *panim, float f, mstudioseqdesc_t *pseqdesc2, mstudioanim_t *panim2, float f2 );

#endif
