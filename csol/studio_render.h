/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
****/
#ifndef _KARIN_HLSDK_STUDIO_RENDER_H
#define _KARIN_HLSDK_STUDIO_RENDER_H

#include "studio_model.h"

typedef void (* HLSDK_Render_Function)(unsigned, unsigned int, float *, unsigned int, float *, unsigned int, float *, unsigned int, float *, unsigned int);
typedef void (* HLSDK_Color3f)(float, float, float);
typedef void (* HLSDK_Color4f)(float, float, float, float);
typedef void (* HLSDK_Texture2D)(int, unsigned int);

extern HLSDK_Render_Function karinDrawArrays;
extern HLSDK_Color3f karinColor3f;
extern HLSDK_Color4f karinColor4f;
extern HLSDK_Texture2D karinTexture2D;

void CalcBoneAdj( StudioModel *mdl );
void CalcBoneQuaternion( const StudioModel *mdl, int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *q );
void CalcBonePosition( const StudioModel *mdl, int frame, float s, mstudiobone_t *pbone, mstudioanim_t *panim, float *pos );
void CalcRotations ( StudioModel *mdl, vec3_t *pos, vec4_t *q, mstudioseqdesc_t *pseqdesc, mstudioanim_t *panim, float f );
mstudioanim_t * GetAnim( StudioModel *mdl, mstudioseqdesc_t *pseqdesc );
void SlerpBones( const StudioModel *mdl, vec4_t q1[], vec3_t pos1[], vec4_t q2[], vec3_t pos2[], float s );
float AdvanceFrame( StudioModel *mdl, float dt );
void SetUpBones ( StudioModel *mdl );
void Lighting (StudioModel *mdl, float *lv, int bone, int flags, vec3_t normal);
void Chrome (StudioModel *mdl, int *pchrome, int bone, vec3_t normal);
void SetupLighting (const StudioModel *mdl);
void SetupModel ( StudioModel *mdl, int bodypart );
void DrawModel(StudioModel *mdl);
void DrawHitboxes (const StudioModel *mdl);
void DrawMaterial( StudioModel *mdl, int skin, int nWidth, int nHeight );
void DrawUVMap(const StudioModel *mdl, int skin, int nWidth, int nHeight );
void DrawAtachments (const StudioModel *mdl);
void DrawPoints (StudioModel *mdl);
mstudiotexture_t * GetMaterial(StudioModel *mdl, const char *name );

void drawBox (const vec3_t *v);
void drawBoxFill (const vec3_t *v);
void DrawIcosahedron(float x,float y,float z,float size);
void DrawBones (const StudioModel *mdl);


float SetFrame( StudioModel *mdl, float frame);

#endif

