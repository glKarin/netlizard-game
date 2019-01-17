#ifndef _KARIN_NL_SHADOW_H
#define _KARIN_NL_SHADOW_H

#include "nl_gl.h"
#include "vector.h"

void Shadow_RenderNETLizardModelScene(const GL_NETLizard_3D_Model *map_model, const int *scenes, unsigned int count, const vector3_t *lightpos);
void Shadow_RenderNETLizardModel(const GL_NETLizard_3D_Model *map_model, const vector3_t *lightpos);
void Shadow_RenderMask(void);

#endif
