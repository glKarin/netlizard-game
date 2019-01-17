#include "mesh.h"

#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#ifndef __cplusplus
typedef enum
{
	false = 0,
	true
} bool;
#endif
#else
#include <stdbool.h>
#endif

void freemesh(mesh_s *mesh)
{
	int i;
	if(!mesh)
		return;
	for(i = 0; i < mesh->count; i++)
		freemat(mesh->materials + i);
	free(mesh->materials);
	mesh->count = 0;
}

void freemat(material_s *mat)
{
	if(!mat)
		return;
	free(mat->points);
	if(glIsTexture(mat->texture))
		glDeleteTextures(1, &mat->texture);
	mat->texture = 0;
	mat->count = 0;
}

void newmesh(mesh_s *mesh, int count)
{
	if(!mesh || count <= 0)
		return;
	mesh->count = count;
	mesh->materials = (material_s *)calloc(mesh->count, sizeof(material_s));
}

void newmat(material_s *mat, int count)
{
	if(!mat || count <= 0)
		return;
	mat->count = count;
	mat->points = (point_s *)calloc(mat->count, sizeof(point_s));
	mat->texture = 0;
	mat->color[0] = mat->color[1] = mat->color[2] = mat->color[3] = 1.0;
	mat->use_color = true;
}

void rendermesh(const mesh_s *mesh)
{
	int i;
	if(!mesh)
		return;
	for(i = 0; i < mesh->count; i++)
	{
		rendermat(mesh->materials + i);
	}
}

void rendermat(const material_s *mat)
{
	bool use_tex;
	bool use_color;

	if(!mat)
		return;

	use_tex = glIsTexture(mat->texture) && glIsEnabled(GL_TEXTURE_2D);
	use_color = !glIsEnabled(GL_COLOR_ARRAY) || mat->use_color;

	if(use_tex)
	{
		glBindTexture(GL_TEXTURE_2D, mat->texture);
	}
	if(!use_color)
	{
		glColorPointer(4, GL_FLOAT, sizeof(point_s), &(mat->points[0].color[0]));
	}
	else
		glColor4fv(mat->color);

	glNormalPointer(GL_FLOAT, sizeof(point_s), &(mat->points[0].normal[0]));
	glTexCoordPointer(2, GL_FLOAT, sizeof(point_s), &(mat->points[0].texcoord[0]));
	glVertexPointer(VERTEX_ELEMENT_COUNT, GL_FLOAT, sizeof(point_s), &(mat->points[0].vertex[0]));

	glDrawArrays(GL_TRIANGLES, 0, mat->count);

	if(use_tex)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

#define CPYELE(p) src->p = dst->p
void matcpy(material_s * RESTRICT src, const material_s * RESTRICT dst)
{
	if(!src || !dst || src == dst)
		return;

	newmat(src, dst->count);
	memcpy(src->points, dst->points, sizeof(point_s) * dst->count);

	memcpy(src->color, dst->color, sizeof(GLfloat) * 4);
	memcpy(src->position, dst->position, sizeof(GLfloat) * 3);
	memcpy(src->rotation, dst->rotation, sizeof(GLfloat) * 3);

	CPYELE(use_color);
	CPYELE(texture);
	CPYELE(face);
}

void meshcpy(mesh_s * RESTRICT src, const mesh_s * RESTRICT dst)
{
	int i;
	if(!src || !dst || src == dst)
		return;
	newmesh(src, dst->count);
	for(i = 0; i < dst->count; i++)
	{
		matcpy(src->materials + i, dst->materials + i);
	}
	memcpy(src->position, dst->position, sizeof(GLfloat) * 3);
	memcpy(src->rotation, dst->rotation, sizeof(GLfloat) * 3);
}
#undef CPYELE

