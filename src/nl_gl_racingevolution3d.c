#include "nl_gl.h"
#include "gl_util.h"
#include "netlizard/nl_util.h"
#include "netlizard/png_reader.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


GL_RE3D_Model * NETLizard_MakeGL2RE3DModel(const RE3D_Model *model)
{
	if(!model)
		return NULL;
	array *meshes = model->meshes;
	if(!meshes || !meshes->array)
		return NULL;
	GL_RE3D_Mesh *mesh = NEW_II(GL_RE3D_Mesh, meshes->length);
	int i;
	for(i = 0; i < meshes->length; i++)
	{
		GL_RE3D_Mesh *m = mesh + i;
		RE3D_Mesh *mesh = ((RE3D_Mesh *)(meshes->array)) + i;
		GLushort *index = NEW_II(GLushort, mesh->index->length);
		int j;
		for(j = 0; j < mesh->index->length; j++)
		{
			index[j] = ((unsigned int *)(mesh->index->array))[j];
		}
		m->buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, mesh->vertex->length * sizeof(float), (float *)(mesh->vertex->array), GL_STATIC_DRAW);
		m->buffers[texcoord_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, mesh->texcoord->length * sizeof(float), (float *)(mesh->texcoord->array), GL_STATIC_DRAW);
		m->buffers[index_buffer_type] = new_OpenGL_buffer_object(GL_ELEMENT_ARRAY_BUFFER, mesh->index->length * sizeof(GLushort), index, GL_STATIC_DRAW);
		free(index);
		memcpy(m->translations, mesh->translation, sizeof(float) * 3);
		m->strips = NEW_II(unsigned int, mesh->strip->length);
		memcpy(m->strips, mesh->strip->array, sizeof(unsigned int) * mesh->strip->length);
		m->primitive = mesh->primitive;
		m->tex_index = mesh->tex_index;
		vector3_t min = {0.0, 0.0, 0.0};
		vector3_t max = {0.0, 0.0, 0.0};
		Algo_ComputeAABBFromOriginalPointSet(mesh->vertex, &min, &max);
		//nlCastAABB(mesh->vertex, &min.x, &min.y, &min.z, &max.x, &max.y, &max.z);
		m->ortho[0] = max.x + m->translations[0];
		m->ortho[1] = max.y + m->translations[1];
		m->ortho[2] = max.z + m->translations[2];
		m->ortho[3] = min.x + m->translations[0];
		m->ortho[4] = min.y + m->translations[1];
		m->ortho[5] = min.z + m->translations[2];
	}

	array *texes = model->texes;
	texture **tex = NEW_II(texture *, texes->length);
	for(i = 0; i < texes->length; i++)
	{
		char *file = ((char **)(texes->array))[i];
		if(!file)
			continue;
		char *name = NULL;
		if(game_resource_path[nl_racing_evolution_3d])
		{
			name = NEW_II(char, strlen(file) + strlen(game_resource_path[nl_racing_evolution_3d]) + 1 + 1);
			memset(name, '\0', sizeof(char) * ((strlen(file) + strlen(game_resource_path[nl_racing_evolution_3d]) + 1 + 1)));
			sprintf(name, "%s/%s", game_resource_path[nl_racing_evolution_3d], file);
		}
		else
		{
			name = strdup(file);
		}
		tex[i] = new_texture_from_nl_file(name);
		free(name);
	}

	texture *sky = NULL;
	char *name = NULL;
	if(game_resource_path[nl_racing_evolution_3d])
	{
		name = NEW_II(char, strlen(RE3D_SKY_FILE) + strlen(game_resource_path[nl_racing_evolution_3d]) + 1 + 1);
		memset(name, '\0', sizeof(char) * ((strlen(RE3D_SKY_FILE) + strlen(game_resource_path[nl_racing_evolution_3d]) + 1 + 1)));
		sprintf(name, "%s/%s", game_resource_path[nl_racing_evolution_3d], RE3D_SKY_FILE);
	}
	else
		name = strdup(RE3D_SKY_FILE);
	sky = new_texture_from_nl_file(name);
	free(name);

	GL_RE3D_Model *glmodel = NEW(GL_RE3D_Model);
	ZERO(glmodel, GL_RE3D_Model);
	glmodel->meshes = mesh;
	glmodel->count = meshes->length;
	glmodel->texes = tex;
	glmodel->tex_count = texes->length;
	glmodel->bg_tex = sky;
	return glmodel;
}

GLvoid delete_GL_RE3D_Model(GL_RE3D_Model *model)
{
	if(!model)
		return;
	if(model->meshes)
	{
		unsigned int i;
		for(i = 0; i < model->count; i++)
			delete_GL_RE3D_Mesh(model->meshes + i);
		free(model->meshes);
	}
	if(model->texes)
	{
		unsigned int i;
		for(i = 0; i < model->tex_count; i++)
		{
			if(model->texes[i])
			{
				if(glIsTexture(model->texes[i]->texid))
					glDeleteTextures(1, &model->texes[i]->texid);
				free(model->texes[i]);
			}
		}
		free(model->texes);
	}
	if(model->bg_tex)
	{
		if(glIsTexture(model->bg_tex->texid))
			glDeleteTextures(1, &model->bg_tex->texid);
		free(model->bg_tex);
	}
}

GLvoid delete_GL_RE3D_Mesh(GL_RE3D_Mesh *mesh)
{
	if(!mesh)
		return;
	int i;
	for(i = 0; i < total_buffer_type; i++)
		if(glIsBuffer(mesh->buffers[i]))
			glDeleteBuffers(1, mesh->buffers + i);
	free(mesh->strips);
}

GLvoid NETLizard_RenderGLRE3DModel(const GL_RE3D_Model *model)
{
	if(!model)
		return;

	if(!model->meshes)
		return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	unsigned int i;
	for(i = 0; i < model->count; i++)
	{
		GL_RE3D_Mesh *m = model->meshes + i;
		if(m->tex_index != -1 && model->texes[m->tex_index])
			oglBindTexture(GL_TEXTURE_2D, model->texes[m->tex_index]->texid);
		glBindBuffer(GL_ARRAY_BUFFER, m->buffers[texcoord_buffer_type]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, m->buffers[vertex_buffer_type]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->buffers[index_buffer_type]);
		glPushMatrix();
		{
			glTranslatef(m->translations[0], m->translations[1], m->translations[2]);
			unsigned int k;
			int l = 0;
			for(k = 0; k < m->primitive; k++)
			{
				GLuint s = m->strips[k];
				oglDrawElements(GL_TRIANGLE_STRIP, s, GL_UNSIGNED_SHORT, (GLuint *)NULL + l);
				l += s;
			}

		}
		glPopMatrix();
		oglBindTexture(GL_TEXTURE_2D, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

GL_RE3D_Model * NETLizard_ReadGLRE3DModelFile(const char *name)
{
	if(!name)
		return NULL;
	RE3D_Model *m = nlReadRE3DMeshFile(name);
	if(!m)
		return NULL;
	GL_RE3D_Model *model = NETLizard_MakeGL2RE3DModel(m);
	delete_RE3D_Model(m);
	free(m);
	return model;
}

GL_RE3D_Model * NETLizard_ReadGLRE3DCarModelFile(const char *car_file, const char *tex_file)
{
	if(!car_file || !tex_file)
		return NULL;
	RE3D_Model *m = nlReadRE3DMeshFile(car_file);
	if(!m)
		return NULL;
	GL_RE3D_Model *model = NETLizard_MakeGL2RE3DModel(m);
	model->texes[0] = new_texture_from_nl_file(tex_file);
	delete_RE3D_Model(m);
	free(m);
	return model;
}

GLvoid nlCastAABB(array *vertex, GLfloat *min_x_r, GLfloat *min_y_r, GLfloat *min_z_r, GLfloat *max_x_r, GLfloat *max_y_r, GLfloat *max_z_r)
{
	if(!vertex)
		return;
	GLfloat min_x = 0.0f;
	GLfloat min_y = 0.0f;
	GLfloat min_z = 0.0f;
	GLfloat max_x = 0.0f;
	GLfloat max_y = 0.0f;
	GLfloat max_z = 0.0f;

	if(vertex->array)
	{
		int i;
		for(i = 0; i < vertex->length; i += 3)
		{
			GLfloat x = ((float *)(vertex->array))[i];
			GLfloat y = ((float *)(vertex->array))[i + 1];
			GLfloat z = ((float *)(vertex->array))[i + 2];
			if(i == 0)
			{
				min_x = x;
				min_y = y;
				min_z = z;
				max_x = x;
				max_y = y;
				max_z = z;
			}
			else
			{
				if(x < min_x) min_x = x;
				if(y < min_y) min_y = y;
				if(z < min_z) min_z = z;
				if(x > max_x) max_x = x;
				if(y > max_y) max_y = y;
				if(z > max_z) max_z = z;
			}
		}
	}
	if(min_x_r) *min_x_r = min_x;
	if(min_y_r) *min_y_r = min_y;
	if(min_z_r) *min_z_r = min_z;
	if(max_x_r) *max_x_r = max_x;
	if(max_y_r) *max_y_r = max_y;
	if(max_z_r) *max_z_r = max_z;
}

GLvoid NETLizard_RenderGLRE3DModelScene(const GL_RE3D_Model *model, GLint *scene, GLuint count)
{
	if(!model)
		return;
	if(!scene || count == 0)
	{
		NETLizard_RenderGLRE3DModel(model);
		return;
	}

	if(!model->meshes)
		return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	unsigned int i;
	for(i = 0; i < count; i++)
	{
		int c = model->count;
		if(scene[i] >= 0 && scene[i] < c)
		{
			GL_RE3D_Mesh *m = model->meshes + scene[i];
			if(m->tex_index != -1 && model->texes[m->tex_index])
				oglBindTexture(GL_TEXTURE_2D, model->texes[m->tex_index]->texid);
			glBindBuffer(GL_ARRAY_BUFFER, m->buffers[texcoord_buffer_type]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
			glBindBuffer(GL_ARRAY_BUFFER, m->buffers[vertex_buffer_type]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->buffers[index_buffer_type]);
			glPushMatrix();
			{
				glTranslatef(m->translations[0], m->translations[1], m->translations[2]);
				unsigned int k;
				int l = 0;
				for(k = 0; k < m->primitive; k++)
				{
					GLuint s = m->strips[k];
					oglDrawElements(GL_TRIANGLE_STRIP, s, GL_UNSIGNED_SHORT, (GLuint *)NULL + l);
					l += s;
				}

			}
			glPopMatrix();
			oglBindTexture(GL_TEXTURE_2D, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

