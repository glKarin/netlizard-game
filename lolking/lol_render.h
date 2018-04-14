#ifndef KARIN_LOL_RENDER_H
#define KARIN_LOL_RENDER_H

#include "lol_struct.h"
#include "opengl.h"

void LOL_RenderStaticModel(const LOL_Mesh *mesh, const GLuint *tex, int count);
void LOL_UpdateBone(LOL_Mesh_Bone *skl, const LOL_Animation *anm, int frame);
void LOL_RenderAnimationModel(const LOL_Mesh *mesh, const GLuint *tex, int count);

#endif
