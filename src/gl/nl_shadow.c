#include "nl_shadow.h"
#include "shadow.h"

#define SHADOW_BEGIN \
	glClear(GL_STENCIL_BUFFER_BIT); \
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); \
	glDepthMask(GL_FALSE); \
	glEnable(GL_STENCIL_TEST); \
	glStencilFunc(GL_ALWAYS, 0, ~0);


#define SHADOW_END \
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); \
	glDepthMask(GL_TRUE); \
	glDisable(GL_STENCIL_TEST); \
	glCullFace(GL_BACK); \
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

void Shadow_RenderNETLizardModelScene(const GL_NETLizard_3D_Model *map_model, const int *scenes, unsigned int count, const vector3_t *lightpos)
{
	GLuint i;
	GLint c;
	GLuint j;
	GL_NETLizard_3D_Mesh *m;
	GL_NETLizard_3D_Item_Mesh *im;

	if(!map_model || !lightpos)
		return;
	if(!map_model->item_meshes)
		return;

	SHADOW_BEGIN

		c = map_model->count;
	for(i = 0; i < count; i++)
	{
		if(scenes[i] < 0 && scenes[i] >= c)
			continue;
		m = map_model->meshes + scenes[i];
		for(j = m->item_index_range[0]; j < m->item_index_range[1]; j++) 
		{
			im = map_model->item_meshes + j;
			if(!im->item_mesh.materials) // REDO
				continue;
			if(im->item_type == Item_Box_Type)
				continue;
			Shadow_RenderShadow(im, lightpos);
		}
	}

	SHADOW_END
}

void Shadow_RenderNETLizardModel(const GL_NETLizard_3D_Model *map_model, const vector3_t *lightpos)
{
	GLuint i;
	GLuint j;
	GL_NETLizard_3D_Mesh *m;
	GL_NETLizard_3D_Item_Mesh *im;

	if(!map_model || !lightpos)
		return;
	if(!map_model->item_meshes)
		return;

	SHADOW_BEGIN

		for(i = 0; i < map_model->count; i++)
		{
			m = map_model->meshes + i;
			for(j = m->item_index_range[0]; j < m->item_index_range[1]; j++) 
			{
				im = map_model->item_meshes + j;
				if(!im->item_mesh.materials) // REDO
					continue;
				if(im->item_type == Item_Box_Type)
					continue;
				Shadow_RenderShadow(im, lightpos);
			}
		}

	SHADOW_END
}

void Shadow_RenderMask(void)
{
	const GLfloat mask_color[] = {
#if SHADOW_MASK_LIGHT
		1.0, 1.0, 1.0, 0.1
#else
			0.0, 0.0, 0.0, 1 - 0.618
	};
#endif
	GLfloat mask[] = {
		-5000, -5000, -10,
		5000, -5000, -10,
		-5000, 5000, -10,
		5000, 5000, -10
	};

	//glDisable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	//glStencilFunc(GL_ALWAYS, 0, ~0);
#if SHADOW_MASK_LIGHT
	glStencilFunc(GL_EQUAL, 0, ~0);
#else
	glStencilFunc(GL_NOTEQUAL, 0, ~0);
#endif


	glPushMatrix();
	glLoadIdentity();
	glColor4fv(mask_color);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, mask);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glColor4f(1, 1, 1, 1);

	glPopMatrix();
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_DEPTH_TEST);
}
