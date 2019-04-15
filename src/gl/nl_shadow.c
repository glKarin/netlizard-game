#include "nl_shadow.h"
#include "nl_std.h"
#include "netlizard/netlizard.h"

#include <string.h>
#include <stdio.h>

#define SHADOW_BEGIN \
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

void Shadow_RenderNETLizardModelScene(const GL_NETLizard_3D_Model *map_model, const int *scenes, unsigned int count, const Light_Source_s *light, int method)
{
	GLuint i;
	GLint c;
	GLuint j;
	GL_NETLizard_3D_Mesh *m;
	GL_NETLizard_3D_Item_Mesh *im;

	if(!map_model || !light)
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
		//Shadow_RenderShadow(m, light);
		for(j = m->item_index_range[0]; j < m->item_index_range[1]; j++) 
		{
			im = map_model->item_meshes + j;
			if(!im->item_mesh.materials) // REDO
				continue;
			if(im->item_type == Item_Box_Type)
				continue;
			Shadow_RenderItemShadow(im, light, method);
		}
	}

	SHADOW_END
}

void Shadow_RenderNETLizardModel(const GL_NETLizard_3D_Model *map_model, const Light_Source_s *light, int method)
{
	GLuint i;
	GLuint j;
	GL_NETLizard_3D_Mesh *m;
	GL_NETLizard_3D_Item_Mesh *im;

	if(!map_model || !light)
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
				Shadow_RenderItemShadow(im, light, method);
			}
		}

	SHADOW_END
}

#define SHADOW_MASK_Z 10
#define SHADOW_MASK_W 5000
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
		-SHADOW_MASK_W, -SHADOW_MASK_W, -SHADOW_MASK_Z,
		SHADOW_MASK_W, -SHADOW_MASK_W, -SHADOW_MASK_Z,
		-SHADOW_MASK_W, SHADOW_MASK_W, -SHADOW_MASK_Z,
		SHADOW_MASK_W, SHADOW_MASK_W, -SHADOW_MASK_Z
	};

	//glDisable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glDepthMask(GL_FALSE);
#if SHADOW_MASK_LIGHT
	glStencilFunc(GL_EQUAL, 0, ~0U);
#else
	glStencilFunc(GL_NOTEQUAL, 0, ~0U);
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
	glStencilFunc(GL_ALWAYS, 0, ~0U);
	glDepthMask(GL_TRUE);
	//glEnable(GL_DEPTH_TEST);
}

void Shadow_RenderNETLizard3DAnimationModel(const GL_NETLizard_3D_Animation_Model *m, int a, int f, const float pos[3], float xangle, float yangle, const Light_Source_s *light, int method)
{
	GL_NETLizard_3D_Item_Mesh item_mesh;
	NETLizard_3D_Role_Animation *animation;
	GL_NETLizard_3D_Mesh *mesh;
	unsigned int anim;
	unsigned int frame;

	if(!m || !light)
		return;

	SHADOW_BEGIN

	anim = a;
	frame = f;
	ZERO(&item_mesh, GL_NETLizard_3D_Item_Mesh);

	if(anim >= m->anim_count)
		anim = 0;
	animation = m->animations + anim;
	if(frame > animation->end - animation->begin)
		frame = 0;
	mesh = m->meshes + animation->begin + frame;

	if(pos)
	{
		item_mesh.pos[0] = pos[0];
		item_mesh.pos[1] = pos[1];
		item_mesh.pos[2] = pos[2];
	}
	item_mesh.angle[0] = xangle;
	item_mesh.angle[1] = yangle;

	item_mesh.item_mesh = *mesh;

	Shadow_RenderItemShadow(&item_mesh, light, method);

	SHADOW_END
}

void Shadow_RenderNETLizard3DItemMesh(const GL_NETLizard_3D_Item_Mesh *m, const Light_Source_s *light, int method)
{
	if(!m || !light)
		return;

	SHADOW_BEGIN

	Shadow_RenderItemShadow(m, light, method);

	SHADOW_END
}

void Shadow_RenderNETLizard3DMesh(const GL_NETLizard_3D_Mesh *m, const float pos[3], float xangle, float yangle, const Light_Source_s *light, int method)
{
	GL_NETLizard_3D_Item_Mesh item_mesh;

	if(!m || !light)
		return;

	SHADOW_BEGIN

	ZERO(&item_mesh, GL_NETLizard_3D_Item_Mesh);

	if(pos)
	{
		item_mesh.pos[0] = pos[0];
		item_mesh.pos[1] = pos[1];
		item_mesh.pos[2] = pos[2];
	}
	item_mesh.angle[0] = xangle;
	item_mesh.angle[1] = yangle;

	item_mesh.item_mesh = *m;

	Shadow_RenderShadow(m, light, method);

	SHADOW_END
}
