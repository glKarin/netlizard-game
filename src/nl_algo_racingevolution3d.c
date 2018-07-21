#include "nl_algo.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int * Algo_GetRE3DMapRenderScenes(const GL_RE3D_Model *netlizard_3d_model, unsigned int *c, GLfloat frustum[][4])
{
	if(!netlizard_3d_model)
		return NULL;
	int *scenes = NULL;
	unsigned int i;
	unsigned int count = 0;
	for(i = 0; i < netlizard_3d_model->count; i++)
	{
		const GL_RE3D_Mesh *mesh = netlizard_3d_model->meshes + i;
		int r = Algo_AABBInFrustum(frustum, mesh->ortho[3], mesh->ortho[4], mesh->ortho[5], mesh->ortho[0], mesh->ortho[1], mesh->ortho[2]);
		if(r)
		{
			if(!scenes)
			{
				scenes = NEW_II(unsigned int, netlizard_3d_model->count);
			}
			scenes[count] = i;
			count++;
		}
	}
	if(c)
		*c = count;
	int *s = NEW_II(int, count);
	memcpy(s, scenes, sizeof(int) * count);
	free(scenes);
	return s;
}

