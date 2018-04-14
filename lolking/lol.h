#ifndef KARKN_LOL_H
#define KARKN_LOL_H

#include "lol_struct.h"
#include "opengl.h"

typedef enum _LOL_Animation_Type
{
	LOL_Idle1_Type = 0,
	LOL_Idle2_Type,
	LOL_Idle3_Type,
	LOL_Idle4_Type,
	LOL_Run1_Type,
	LOL_Run2_Type,
	LOL_Run3_Type,
	LOL_Run4_Type,
	LOL_Spell1_Type,
	LOL_Spell2_Type,
	LOL_Spell3_Type,
	LOL_Spell4_Type,
	LOL_Attack1_Type,
	LOL_Attack2_Type,
	LOL_Attack3_Type,
	LOL_Attack4_Type,
	LOL_Crit_Type,
	LOL_Recall_Type,
	LOL_Joke_Type,
	LOL_Taunt_Type,
	LOL_Dance_Type,
	LOL_Laugh_Type,
	LOL_Death_Type,
	LOL_Channel_Type,
	LOL_Total_Type,
	LOL_Other_Type
} LOL_Animation_Type;

typedef struct _LOL_Model
{
	LOL_Mesh *mesh;
	LOL_Anim *anim;
	GLuint *tex;
	unsigned int tex_count;
} LOL_Model;

LOL_Model * new_LOL_Model(const char *meshf, const char *animf, const char *texf[], int texc);
void LOL_RenderModel(const LOL_Model *model, int animation, int animi, int framei);
void delete_LOL_Model(LOL_Model *model);
int LOL_GetAnimationRangeByName(const LOL_Model *model, const char *name, int *anim, int *count);
const char * LOL_GetAnimationRangeByType(const LOL_Model *model, LOL_Animation_Type type, int *anim, int *count);

#endif
