#include "lol_render.h"
#include "math3d/base_algo.h"

#include <stdlib.h>
#include <string.h>

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

static void LOL_UpdateVertex(const LOL_Mesh *mesh, GLfloat *verteces);

void LOL_RenderStaticModel(const LOL_Mesh *mesh, const GLuint *tex, int count)
{
	if(!mesh)
		return;
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	GLushort *index_ptr = NULL;

	if(mesh -> vertex_array.gl == 2)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mesh -> vertex_array.vertex_buffer.buffers[LOL_Vertex_Buffer_Type]);
		glTexCoordPointer(2, GL_FLOAT, sizeof(GLfloat) * 8, (GLubyte *)NULL + (sizeof(GLfloat) * 6));
		glNormalPointer(GL_FLOAT, sizeof(GLfloat) * 8, (GLubyte *)NULL + (sizeof(GLfloat) * 3));
		glVertexPointer(3, GL_FLOAT, sizeof(GLfloat) * 8, NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh -> vertex_array.vertex_buffer.buffers[LOL_Index_Buffer_Type]);
		index_ptr = NULL;
	}
	else
	{
		glNormalPointer(GL_FLOAT, sizeof(LOL_Vertex), mesh -> vertex[0].normal);
		glTexCoordPointer(2, GL_FLOAT, sizeof(LOL_Vertex), mesh -> vertex[0].texcoord);
		glVertexPointer(3, GL_FLOAT, sizeof(LOL_Vertex), mesh -> vertex);
		index_ptr = mesh -> index;
	}
	int i;
	int j = count;
	for(i = mesh -> material_count - 1; i >= 0; i--)
	{
		if(j <= count && j > 0)
			j--;
		if(tex && glIsTexture(tex[j]))
		{
			oglBindTexture(GL_TEXTURE_2D, tex[j]);
		}
		DrawElements(GL_TRIANGLES, mesh -> material[i].index_count, GL_UNSIGNED_SHORT, index_ptr + mesh -> material[i].start_index);
		if(tex && glIsTexture(tex[j]))
		{
			oglBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	if(mesh -> vertex_array.gl == 2)
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void LOL_UpdateBone(LOL_Mesh_Bone *skl, const LOL_Animation *anm, int frame)
{
	if(!skl || !anm)
		return;
	unsigned int i;
	for(i = 0; i < skl -> bone_count; i++)
	{
		unsigned int j;
		int hasBone = 0;
		for(j = 0; j < anm -> bone_count; j++)
		{
			if(strcmp(skl -> bone[i].name, anm -> animation_bone[j].bone) == 0)
			{
				hasBone = 1;
				break;
			}
		}
		if(!hasBone)
			continue;
		LOL_Bone *bone = skl -> bone + i;
		const LOL_Frame *a = anm -> animation_bone[j].frame + frame;
		if(bone -> parent == -1)
		{
			bone -> incr_matrix = Math3D_MakeQuatAndToMatrix44(a -> rot, a -> pos, a -> scale);
			bone -> orig_matrix = bone -> incr_matrix;
		}
		else
		{
			const LOL_Bone *pBone = skl -> bone + bone -> parent;
			bone -> incr_matrix = Math3D_MakeQuatAndToMatrix44(a -> rot, a -> pos, a -> scale);
			//bone -> orig_matrix =  bone -> incr_matrix * pBone -> orig_matrix;
			bone -> orig_matrix =  Matrix44_MultiplyMatrix44(&bone -> incr_matrix, &pBone -> orig_matrix);
		}
	}
}

void LOL_RenderAnimationModel(const LOL_Mesh *mesh, const GLuint *tex, int count)
{
	if(!mesh)
		return;

	GLfloat *vertex = NULL;

	if(mesh -> vertex_array.gl == 2)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mesh -> vertex_array.vertex_buffer.buffers[LOL_Vertex_Buffer_Type]);
		vertex = calloc(8 * mesh -> vertex_count, sizeof(GLfloat));
		LOL_UpdateVertex(mesh, vertex);
		GLuint i;
		for(i = 0; i < mesh -> vertex_count; i++)
		{
			glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(GLfloat) * 8, sizeof(GLfloat) * 6, vertex + i * 8);
		}
		free(vertex);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else
	{
		vertex = calloc(8 * mesh -> vertex_count, sizeof(GLfloat));
		LOL_UpdateVertex(mesh, vertex);
	}

	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	GLushort *index_ptr = NULL;

	if(mesh -> vertex_array.gl == 2)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mesh -> vertex_array.vertex_buffer.buffers[LOL_Vertex_Buffer_Type]);
		glTexCoordPointer(2, GL_FLOAT, sizeof(GLfloat) * 8, (GLubyte *)NULL + (sizeof(GLfloat) * 6));
		glNormalPointer(GL_FLOAT, sizeof(GLfloat) * 8, (GLubyte *)NULL + (sizeof(GLfloat) * 3));
		glVertexPointer(3, GL_FLOAT, sizeof(GLfloat) * 8, NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh -> vertex_array.vertex_buffer.buffers[LOL_Index_Buffer_Type]);
		index_ptr = NULL;
	}
	else
	{
		glNormalPointer(GL_FLOAT, sizeof(GLfloat) * 8, vertex + 3);
		glTexCoordPointer(2, GL_FLOAT, sizeof(LOL_Vertex), mesh -> vertex[0].texcoord);
		glVertexPointer(3, GL_FLOAT, sizeof(GLfloat) * 8, vertex);
		index_ptr = mesh -> index;
	}
	int i;
	int j = count;
	for(i = mesh -> material_count - 1; i >= 0; i--)
	{
		if(j <= count && j > 0)
			j--;
		if(tex && glIsTexture(tex[j]))
		{
			oglBindTexture(GL_TEXTURE_2D, tex[j]);
		}
		DrawElements(GL_TRIANGLES, mesh -> material[i].index_count, GL_UNSIGNED_SHORT, index_ptr + mesh -> material[i].start_index);
		if(tex && glIsTexture(tex[j]))
		{
			oglBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	if(mesh -> vertex_array.gl == 2)
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	if(mesh -> vertex_array.gl != 2)
		free(vertex);
}

void LOL_UpdateVertex(const LOL_Mesh *mesh, GLfloat *verteces)
{
	if(!mesh || !verteces)
		return;
	const LOL_Mesh_Bone *skl = &(mesh -> bone_data);

	unsigned int i;
	for(i = 0; i < mesh -> vertex_count; i++)
	{
		const LOL_Vertex *vertex = mesh -> vertex + i;
		const vector3_t v = {vertex -> position[0], vertex -> position[1], vertex -> position[2]};
		const vector3_t n = {vertex -> normal[0], vertex -> normal[1], vertex -> normal[2]};
		vector3_t nv = {0.0, 0.0, 0.0};
		vector3_t nn = {0.0, 0.0, 0.0};
		unsigned int j;
		size_t len = sizeof(vertex -> bone_index) / sizeof(unsigned char);
		for(j = 0; j < len; j++)
		{
			if(vertex -> bone_weight[j] == 0.0) continue;
			unsigned int idx = vertex -> bone_index[j];
			if(idx < skl -> bone_count)
				idx = skl -> bone[idx].index;
			/*
				 if(idx >= skl -> numBones)
				 continue;
				 */

			matrix44_t mat = Matrix44_MultiplyMatrix44(&skl -> bone[idx].base_matrix, &skl -> bone[idx].orig_matrix);
			vector3_t vv = Math3D_Vector3MultiplyMatrix44(&v, &mat);
			vector3_t vn = Math3D_Vector3MultiplyMatrix44(&n, &mat);
			vv = Vector3_Scale(&vv, vertex -> bone_weight[j]);
			vn = Vector3_Scale(&vn, vertex -> bone_weight[j]);
			nv = Vector3_PlusVector3(&nv, &vv);
			nn = Vector3_PlusVector3(&nn, &vn);
		}
		verteces[i * 8] = nv.x;
		verteces[i * 8 + 1] = nv.y;
		verteces[i * 8 + 2] = nv.z;
		verteces[i * 8 + 3] = nn.x;
		verteces[i * 8 + 4] = nn.y;
		verteces[i * 8 + 5] = nn.z;
	}
}

