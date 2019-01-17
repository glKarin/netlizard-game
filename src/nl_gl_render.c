#include "nl_gl.h"
#include "nl_algo.h"

#include <stdlib.h>

#ifdef GL_VERSION_3_0_____
#include <GL/glext.h>
static void OpenGL_ConditionalDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
{
#define OPENGL_QUICK_RENDER  \
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); \
	glDepthMask(GL_FALSE); \
	oglDisable(GL_TEXTURE_2D); \
	oglDisable(GL_BLEND); \
	oglDisable(GL_LIGHTING); \
	oglDisable(GL_ALPHA_TEST); \
	oglDisable(GL_FOG); \
	oglDisable(GL_STENCIL_TEST); \
	glShadeModel(GL_FLAT); \
	oglDisable(GL_LINE_SMOOTH); \
	oglDisable(GL_POLYGON_SMOOTH);
	int query;
	glGenQueries(1, &query);
	glBeginQuery(GL_SAMPLES_PASSED, query);
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT);
	{
		OPENGL_QUICK_RENDER
			oglDrawElements(mode, count, type, indices);
	}
	glPopAttrib();
	glEndQuery(GL_SAMPLES_PASSED);
#if 0
	GLuint available = GL_FALSE;

	glGetQueryObjectuiv(query[i], GL_QUERY_RESULT_AVAILABLE, &available);
	if(available)
	{
		GLint samples = 0;
		glGetQueryObjectiv(query[i], GL_QUERY_RESULT, &samples);
		if(samples != 0)
			return;
	}
#endif
	glBeginConditionalRender(query, GL_QUERY_WAIT);
	{
		oglDrawElements(mode, count, type, indices);
	}
	glEndConditionalRender();
	glDeleteQueries(1, &query);
}

#define DrawElements OpenGL_ConditionalDrawElements
#else
#define DrawElements oglDrawElements
#endif

void NETLizard_RenderGL3DModel(const GL_NETLizard_3D_Model *model)
{
	if(!model)
		return;

	if(model->meshes)
	{
		GLuint i;
		for(i = 0; i < model->count; i++)
		{
			GL_NETLizard_3D_Mesh *m = model->meshes + i;
			NETLizard_RenderGL3DMesh(m, model->texes);
			if(model->item_meshes)
			{
				GLuint j;
				for(j = m->item_index_range[0]; j < m->item_index_range[1]; j++) 
				{
					GL_NETLizard_3D_Item_Mesh *im = model->item_meshes + j;
					if(!im->item_mesh.materials) // REDO
						continue;
					glPushMatrix();
					{
						glTranslatef(im->pos[0], im->pos[1], im->pos[2]);
						glRotatef(im->angle[0], 1.0f, 0.0f, 0.0f);
						glRotatef(im->angle[1], 0.0f, 0.0f, 1.0f);
						NETLizard_RenderGL3DMesh(&(im->item_mesh), model->texes);
					}
					glPopMatrix();
				}
			}
		}
	}

	if(model->item_meshes)
	{
		GLuint i;
		for(i = 0; i < model->item_count; i++)
		{
			GL_NETLizard_3D_Item_Mesh *m = model->item_meshes + i;
			if(!m->item_mesh.materials) // REDO
				continue;
			if(m->item_type == Item_Box_Type)
				continue;
			glPushMatrix();
			{
				glTranslatef(m->pos[0], m->pos[1], m->pos[2]);
				glRotatef(m->angle[0], 1.0f, 0.0f, 0.0f);
				glRotatef(m->angle[1], 0.0f, 0.0f, 1.0f);
				NETLizard_RenderGL3DMesh(&(m->item_mesh), model->texes);
			}
			glPopMatrix();
		}
	}
}

GLvoid NETLizard_RenderGL3DItemModel(const GL_NETLizard_3D_Item_Model *m)
{
	if(!m)
		return;
	NETLizard_RenderGL3DItemMesh(&(m->item_mesh), m->tex);
}

GLvoid NETLizard_RenderGL3DAnimationModel(const GL_NETLizard_3D_Animation_Model *m, GLuint anim, GLuint frame)
{
	if(!m)
		return;
	if(anim >= m->anim_count)
		anim = 0;
	NETLizard_3D_Role_Animation *animation = m->animations + anim;
	if(frame > animation->end - animation->begin)
		frame = 0;
	GL_NETLizard_3D_Mesh *mesh = m->meshes + animation->begin + frame;
	NETLizard_RenderGL3DItemMesh(mesh, m->tex);
}

GLvoid NETLizard_RenderGL3DMesh(const GL_NETLizard_3D_Mesh *m, texture **const texes)
{
	if(!m || !texes)
		return;

	if(m->vertex_array.gl & OPENGL_RENDER_VERTEX_BUFFER)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, m->vertex_array.vertex_buffer.vertex_buffer);
		glNormalPointer(GL_FLOAT, sizeof(GL_NETLizard_3D_Vertex), (GLubyte *)NULL + sizeof(GLfloat) * 3);
		glTexCoordPointer(2, GL_FLOAT, sizeof(GL_NETLizard_3D_Vertex), (GLubyte *)NULL + sizeof(GLfloat) * 6);
		glVertexPointer(3, GL_FLOAT, sizeof(GL_NETLizard_3D_Vertex), NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->vertex_array.vertex_buffer.index_buffer);
		GLuint j;
		for(j = 0; j < m->count; j++)
		{
			if(texes[m->materials[j].tex_index])
				oglBindTexture(GL_TEXTURE_2D, texes[m->materials[j].tex_index]->texid);
			DrawElements(GL_TRIANGLES, m->materials[j].index_count, GL_UNSIGNED_SHORT, (GLubyte *)NULL + sizeof(GLushort) * m->materials[j].index_start);
			oglBindTexture(GL_TEXTURE_2D, 0);
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	else if(m->vertex_array.gl & OPENGL_RENDER_VERTEX_DATA)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glNormalPointer(GL_FLOAT, sizeof(GL_NETLizard_3D_Vertex), m->vertex_array.vertex_data.vertex[0].normal);
		glTexCoordPointer(2, GL_FLOAT, sizeof(GL_NETLizard_3D_Vertex), m->vertex_array.vertex_data.vertex[0].texcoord);
		glVertexPointer(3, GL_FLOAT, sizeof(GL_NETLizard_3D_Vertex), m->vertex_array.vertex_data.vertex[0].position);
		GLuint j;
		for(j = 0; j < m->count; j++)
		{
			if(texes[m->materials[j].tex_index])
				oglBindTexture(GL_TEXTURE_2D, texes[m->materials[j].tex_index]->texid);
			DrawElements(GL_TRIANGLES, m->materials[j].index_count, GL_UNSIGNED_SHORT, m->vertex_array.vertex_data.index + m->materials[j].index_start);
			oglBindTexture(GL_TEXTURE_2D, 0);
		}

#if 0 // render point and normal
	glDisable(GL_DEPTH_TEST);
	glLineWidth(4);
	glPointSize(25);
	GLfloat nv[6];
	int i;
	for(i = 0; i < m->count; i++)
	{
		int j;
		int vcount = m->materials[i].index_count;
		for(j = 0; j < vcount; j++)
		{
			int start = m->vertex_array.vertex_data.index[m->materials[i].index_start + j];
			vector3_t rv = VECTOR3V(m->vertex_array.vertex_data.vertex[start].position);
			nv[0] = VECTOR_X(rv);
			nv[1] = VECTOR_Y(rv);
			nv[2] = VECTOR_Z(rv);

			vector3_t rv2 = VECTOR3V(m->vertex_array.vertex_data.vertex[start].normal);
			Vector3_ScaleSelf(&rv2, 20);
			rv2 = Vector3_PlusVector3(&rv, &rv2);
			nv[3] = VECTOR_X(rv2);
			nv[4] = VECTOR_Y(rv2);
			nv[5] = VECTOR_Z(rv2);
			glVertexPointer(3, GL_FLOAT, 0, nv);
			glColor4f(1.0, 0.0, 1.0, 1.0);
			glDrawArrays(GL_LINES, 0, 2);
			glColor4f(0.0, 0.0, 1.0, 1.0);
			glDrawArrays(GL_POINTS, 0, 1);
		}
	}
	glEnable(GL_DEPTH_TEST);
	glLineWidth(1);
	glPointSize(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
#endif

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

GLvoid NETLizard_RenderGL3DItemMesh(const GL_NETLizard_3D_Mesh *m, const texture *tex)
{
	if(!m)
		return;

	if(m->vertex_array.gl & OPENGL_RENDER_VERTEX_BUFFER)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		if(tex)
			oglBindTexture(GL_TEXTURE_2D, tex->texid);
		glBindBuffer(GL_ARRAY_BUFFER, m->vertex_array.vertex_buffer.vertex_buffer);
		glNormalPointer(GL_FLOAT, sizeof(GL_NETLizard_3D_Vertex), (GLubyte *)NULL + sizeof(GLfloat) * 3);
		glTexCoordPointer(2, GL_FLOAT, sizeof(GL_NETLizard_3D_Vertex), (GLubyte *)NULL + sizeof(GLfloat) * 6);
		glVertexPointer(3, GL_FLOAT, sizeof(GL_NETLizard_3D_Vertex), NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->vertex_array.vertex_buffer.index_buffer);
		GLuint j;
		for(j = 0; j < m->count; j++)
		{
			DrawElements(GL_TRIANGLES, m->materials[j].index_count, GL_UNSIGNED_SHORT, (GLubyte *)NULL + sizeof(GLushort) * m->materials[j].index_start);
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		oglBindTexture(GL_TEXTURE_2D, 0);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	else if(m->vertex_array.gl & OPENGL_RENDER_VERTEX_DATA)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		if(tex)
			oglBindTexture(GL_TEXTURE_2D, tex->texid);

		glNormalPointer(GL_FLOAT, sizeof(GL_NETLizard_3D_Vertex), m->vertex_array.vertex_data.vertex[0].normal);
		glTexCoordPointer(2, GL_FLOAT, sizeof(GL_NETLizard_3D_Vertex), m->vertex_array.vertex_data.vertex[0].texcoord);
		glVertexPointer(3, GL_FLOAT, sizeof(GL_NETLizard_3D_Vertex), m->vertex_array.vertex_data.vertex[0].position);
		GLuint j;
		for(j = 0; j < m->count; j++)
		{
			DrawElements(GL_TRIANGLES, m->materials[j].index_count, GL_UNSIGNED_SHORT, m->vertex_array.vertex_data.index + m->materials[j].index_start);
		}

		if(tex)
			oglBindTexture(GL_TEXTURE_2D, 0);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void NETLizard_RenderGL3DMapModelScene(const GL_NETLizard_3D_Model *model, GLint *scene, GLuint count)
{
	if(!model)
		return;
	if(!scene || count == 0)
	{
		NETLizard_RenderGL3DModel(model);
		return;
	}

	if(model->meshes)
	{
		GLint c = model->count;
		GLuint i;
		for(i = 0; i < count; i++)
		{
			if(scene[i] >= 0 && scene[i] < c)
			{
				GL_NETLizard_3D_Mesh *m = model->meshes + scene[i];
				NETLizard_RenderGL3DMesh(m, model->texes);
				if(model->item_meshes)
				{
					GLuint j;
					for(j = m->item_index_range[0]; j < m->item_index_range[1]; j++) 
					{
						GL_NETLizard_3D_Item_Mesh *im = model->item_meshes + j;
						if(!im->item_mesh.materials) // REDO
							continue;
						if(im->item_type == Item_Box_Type)
							continue;
						glPushMatrix();
						{
							glTranslatef(im->pos[0], im->pos[1], im->pos[2]);
							glRotatef(im->angle[0], 1.0f, 0.0f, 0.0f);
							glRotatef(im->angle[1], 0.0f, 0.0f, 1.0f);
							NETLizard_RenderGL3DMesh(&(im->item_mesh), model->texes);
						}
						glPopMatrix();
					}
				}
			}
		}
	}
}

