#include "nl_gl.h"
#include "gl_util.h"
#include "math3d/algo.h"
#include "netlizard/nl_util.h"
#include "netlizard/png_reader.h"
#include "netlizard/texture_v2_reader.h"
#include "netlizard/texture_v3_reader.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

texture * new_texture_from_nl_file(const char *name)
{
	if(!name)
		return NULL;
	array *arr = nlHandlePNG_File2Memory(name);
	if(!arr || !arr->array)
		return NULL;
	texture *tex = new_OpenGL_texture_2d_from_memory(arr->array, arr->length);
	delete_array(arr);
	free(arr);
	return tex;
}

texture * new_texture_from_nl_v2_3d_file(const char *name)
{
	if(!name)
		return NULL;
	png_texture * png = nlReadTextureV2_File(name);
	if(!png)
		return NULL;
	unsigned char * data;
	if(png->format != nl_rgb)
		data = nlMakeOpenGLTextureDataRGBA(png);
	else
		data = nlMakeOpenGLTextureDataRGB(png);

	texture *g_tex = NULL;
	if(data)
	{
		g_tex = NEW(texture);
		ZERO(g_tex, texture);
		g_tex->width = png->width;
		g_tex->height = png->height;
		g_tex->format = png->format != nl_rgb ? GL_RGBA : GL_RGB;
		glGenTextures(1, &(g_tex->texid));
		oglBindTexture(GL_TEXTURE_2D, g_tex->texid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	
#ifdef _HARMATTAN_OPENGLES
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
#else
		glGenerateMipmap(GL_TEXTURE_2D);
#endif
#ifdef _HARMATTAN_OPENGLES
		OpenGL_TexImage2D(GL_TEXTURE_2D, 0, g_tex->format, g_tex->width, g_tex->height, 0, g_tex->format, GL_UNSIGNED_BYTE, data, SCALE_AUTO, NULL, NULL);
#else
		glTexImage2D(GL_TEXTURE_2D, 0, g_tex->format, g_tex->width, g_tex->height, 0, g_tex->format, GL_UNSIGNED_BYTE, data);
#endif
		//glGenerateMipmapEXT(GL_TEXTURE_2D);

		oglBindTexture(GL_TEXTURE_2D, 0);
	}
	free(data);
	delete_png_texture(png);
	free(png);
	return g_tex;
}

texture * new_texture_from_nl_v3_3d_file(const char *name)
{
	if(!name)
		return NULL;
	png_texture * png = nlReadTextureV3_File(name, -1);
	if(!png)
		return NULL;
	unsigned char * data;
	if(png->format != nl_rgb)
		data = nlMakeOpenGLTextureDataRGBA(png);
	else
		data = nlMakeOpenGLTextureDataRGB(png);

	texture *g_tex = NULL;
	if(data)
	{
		g_tex = NEW(texture);
		ZERO(g_tex, texture);
		g_tex->width = png->width;
		g_tex->height = png->height;
		g_tex->format = png->format != nl_rgb ? GL_RGBA : GL_RGB;
		glGenTextures(1, &(g_tex->texid));
		oglBindTexture(GL_TEXTURE_2D, g_tex->texid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	
#ifdef _HARMATTAN_OPENGLES
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
#else
		glGenerateMipmap(GL_TEXTURE_2D);
#endif
#ifdef _HARMATTAN_OPENGLES
		OpenGL_TexImage2D(GL_TEXTURE_2D, 0, g_tex->format, g_tex->width, g_tex->height, 0, g_tex->format, GL_UNSIGNED_BYTE, data, SCALE_AUTO, NULL, NULL);
#else
		glTexImage2D(GL_TEXTURE_2D, 0, g_tex->format, g_tex->width, g_tex->height, 0, g_tex->format, GL_UNSIGNED_BYTE, data);
#endif

		oglBindTexture(GL_TEXTURE_2D, 0);
	}
	free(data);
	delete_png_texture(png);
	free(png);
	return g_tex;
}

texture * new_texture_from_nl_v3_3d_compress_file(const char *name)
{
	if(!name)
		return NULL;
	png_texture * png = nlReadCompressTextureV3_File(name);
	if(!png)
		return NULL;
	unsigned char * data;
	if(png->format != nl_rgb)
		data = nlMakeOpenGLTextureDataRGBACompress(png);
	else
		//data = nlMakeOpenGLTextureDataRGB(png);
	{
		delete_png_texture(png);
		free(png);
		return NULL;
	}

	texture *g_tex = NULL;
	if(data)
	{
		g_tex = NEW(texture);
		ZERO(g_tex, texture);
		g_tex->width = png->width;
		g_tex->height = png->height;
		g_tex->format = png->format != nl_rgb ? GL_RGBA : GL_RGB;
		glGenTextures(1, &(g_tex->texid));
		oglBindTexture(GL_TEXTURE_2D, g_tex->texid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	
#ifdef _HARMATTAN_OPENGLES
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
#else
		glGenerateMipmap(GL_TEXTURE_2D);
#endif
#ifdef _HARMATTAN_OPENGLES
		OpenGL_TexImage2D(GL_TEXTURE_2D, 0, g_tex->format, g_tex->width, g_tex->height, 0, g_tex->format, GL_UNSIGNED_BYTE, data, SCALE_AUTO, NULL, NULL);
#else
		glTexImage2D(GL_TEXTURE_2D, 0, g_tex->format, g_tex->width, g_tex->height, 0, g_tex->format, GL_UNSIGNED_BYTE, data);
#endif

		oglBindTexture(GL_TEXTURE_2D, 0);
	}
	free(data);
	delete_png_texture(png);
	free(png);
	return g_tex;
}

void delete_GL_NETLizard_3D_Mesh(GL_NETLizard_3D_Mesh *mesh)
{
	if(!mesh)
		return;
	if(mesh->vertex_array.gl & OPENGL_RENDER_VERTEX_DATA)
	{
		if(mesh->vertex_array.vertex_data.vertex)
			free(mesh->vertex_array.vertex_data.vertex);
		if(mesh->vertex_array.vertex_data.index)
			free(mesh->vertex_array.vertex_data.index);
	}
	else if(mesh->vertex_array.gl & OPENGL_RENDER_VERTEX_BUFFER)
	{
		if(glIsBuffer(mesh->vertex_array.vertex_buffer.vertex_buffer))
			glDeleteBuffers(1, &(mesh->vertex_array.vertex_buffer.vertex_buffer));
		if(glIsBuffer(mesh->vertex_array.vertex_buffer.index_buffer))
			glDeleteBuffers(1, &(mesh->vertex_array.vertex_buffer.index_buffer));
	}
	if(mesh->plane)
		free(mesh->plane);
	if(mesh->bsp)
		free(mesh->bsp);
	if(mesh->tex_index)
		free(mesh->tex_index);
	if(mesh->materials)
		free(mesh->materials);
}

void delete_GL_NETLizard_3D_Item_Mesh(GL_NETLizard_3D_Item_Mesh *mesh)
{
	if(!mesh)
		return;
	delete_GL_NETLizard_3D_Mesh(&mesh->item_mesh);
}

GLvoid delete_GL_NETLizard_3D_Animation_Model(GL_NETLizard_3D_Animation_Model *model)
{
	if(!model)
		return;
	if(model->meshes)
	{
		unsigned int i;
		for(i = 0; i < model->count; i++)
			delete_GL_NETLizard_3D_Mesh(model->meshes + i);
		free(model->meshes);
	}
	if(model->tex)
	{
		if(glIsTexture(model->tex->texid))
			glDeleteTextures(1, &model->tex->texid);
		free(model->tex);
	}
	if(model->animations)
		free(model->animations);
}

void delete_GL_NETLizard_3D_Model(GL_NETLizard_3D_Model *model)
{
	if(!model)
		return;
	if(model->meshes)
	{
		unsigned int i;
		for(i = 0; i < model->count; i++)
			delete_GL_NETLizard_3D_Mesh(model->meshes + i);
		free(model->meshes);
	}
	if(model->item_meshes)
	{
		unsigned int i;
		for(i = 0; i < model->item_count; i++)
			delete_GL_NETLizard_3D_Item_Mesh(model->item_meshes + i);
		free(model->item_meshes);
	}
	if(model->texes)
	{
		unsigned int i;
		for(i = 0; i < model->tex_count; i++)
		{
			if(!model->texes[i])
				continue;
			if(glIsTexture(model->texes[i]->texid))
				glDeleteTextures(1, &model->texes[i]->texid);
			free(model->texes[i]);
		}
		free(model->texes);
	}
	if(model->bg_tex)
	{
		if(glIsTexture(model->bg_tex->texid))
			glDeleteTextures(1, &model->bg_tex->texid);
		free(model->bg_tex);
	}
	if(model->bsp_data)
	{
		free(model->bsp_data);
	}
}

GL_NETLizard_3D_Model * NETLizard_MakeGL3DModel(const NETLizard_3D_Model *model)
{
	if(!model)
		return NULL;

	new_netlizard_texture_from_file new_OpenGL_texture_2d;
	GLint tex_count; // 最大纹理数
	game_name game;
	int invert_texcoord_y; // 纹理坐标y反转
	int item_invert_texcoord_y; // 纹理坐标y反转
	int index_factory; // 场景顶点索引因子
	int item_index_factory; // 物品顶点索引因子
	char subfix_str[SUBFIX_LENGTH];
	char sky_file[SKYFILE_LENGTH];
	memset(subfix_str, '\0', sizeof(char) * SUBFIX_LENGTH);
	memset(sky_file, '\0', sizeof(char) * SKYFILE_LENGTH);

	switch(model->game)
	{
		case CT_3D_Map:
		case CT_3D_Item:
			tex_count = CT3D_TEX_COUNT;
			game = nl_contr_terrorism_3d;
			strcpy(subfix_str, CT3D_TEX_SUBFIX);
			new_OpenGL_texture_2d = new_texture_from_nl_v2_3d_file;
			index_factory = 1;
			item_index_factory = 1;
			invert_texcoord_y = 1;
			item_invert_texcoord_y = 1;
			strcpy(sky_file, CT3D_SKY_FILE);
			break;
		case CT_3D_Ep2_Map:
		case CT_3D_Ep2_Item:
			tex_count = CT3DEP2_TEX_COUNT;
			game = nl_contr_terrorism_3d_episode_2;
			strcpy(subfix_str, CT3DEP2_TEX_SUBFIX);
			new_OpenGL_texture_2d = new_texture_from_nl_v2_3d_file;
			invert_texcoord_y = 1;
			index_factory = 3;
			item_index_factory = 1;
			item_invert_texcoord_y = 1;
			strcpy(sky_file, CT3DEP2_SKY_FILE);
			break;
		case Army_Ranger_3D_Map:
		case Army_Ranger_3D_Item:
			tex_count = SPECNAZ3D_TEX_COUNT;
			game = nl_army_ranger_3d;
			strcpy(subfix_str, SPECNAZ3D_TEX_SUBFIX);
			new_OpenGL_texture_2d = new_texture_from_nl_v2_3d_file;
			invert_texcoord_y = 1;
			index_factory = 1;
			item_index_factory = 1;
			item_invert_texcoord_y = 1;
			strcpy(sky_file, SPECNAZ3D_SKY_FILE);
			break;
		case Egypt_3D_Map:
		case Egypt_3D_Role:
		case Egypt_3D_Item:
			tex_count = EGYPT3D_TEX_COUNT;
			game = nl_shadow_of_egypt_3d;
			strcpy(subfix_str, EGYPT3D_TEX_SUBFIX);
			new_OpenGL_texture_2d = new_texture_from_nl_v3_3d_file;
			invert_texcoord_y = 1;
			index_factory = 3;
			item_index_factory = 3;
			item_invert_texcoord_y = 1;
			break;
		case Clone_3D_Map:
		case Clone_3D_Item:
		case Clone_3D_Role:
			tex_count = CLONE3D_TEX_COUNT;
			game = nl_clone_3d;
			strcpy(subfix_str, CLONE3D_TEX_SUBFIX);
			new_OpenGL_texture_2d = new_texture_from_nl_v3_3d_file;
			index_factory = 3;
			item_index_factory = 3;
			invert_texcoord_y = 0;
			item_invert_texcoord_y = 0;
			break;
		case CT_3D_Ep3_Map:
		case CT_3D_Ep3_Item:
			tex_count = CT3DEP3_TEX_COUNT;
			game = nl_contr_terrorism_3d_episode_3;
			strcpy(subfix_str, CT3DEP3_TEX_SUBFIX);
			new_OpenGL_texture_2d = new_texture_from_nl_v3_3d_file;
			invert_texcoord_y = 0;
			item_invert_texcoord_y = 0;
			index_factory = 3;
			item_index_factory = 1;
			strcpy(sky_file, CT3DEP3_SKY_FILE);
			break;
		default:
			return NULL;
	}
	texture **texes = NEW_II(texture *, tex_count);

	GL_NETLizard_3D_Mesh *meshes = NULL;
	if(model->data)
	{
		meshes = NEW_II(GL_NETLizard_3D_Mesh, model->data->length);
		GLint i;
		for(i = 0; i < model->data->length; i++)
		{
			NETLizard_3D_Mesh *mesh = ((NETLizard_3D_Mesh *)(model->data->array)) + i;
			GL_NETLizard_3D_Mesh *m = meshes + i;
			m->count = 0;
			m->materials = NULL;
			m->tex_index = NULL;
			m->plane_count = 0;
			m->plane = NULL;
			m->vertex_array.gl = OPENGL_RENDER_VERTEX_DATA;
			m->vertex_array.vertex_data.vertex = NULL;
			m->vertex_array.vertex_data.vertex_count = 0;
			m->vertex_array.vertex_data.index = NULL;
			m->vertex_array.vertex_data.index_count = 0;
			m->bsp_count = 0;
			m->bsp = NULL;

			if(mesh->primitive)
			{
				GLint o;
				GLuint tex_count_i = 0;
				GLint *tex_index_set = NEW_II(GLint, mesh->primitive->length);
				for(o = 0; o < mesh->primitive->length; o++)
				{
					tex_index_set[o] = -1;
				}
				for(o = 0; o < mesh->primitive->length; o++)
				{
					int tex_i = ((NETLizard_3D_Primitive *)(mesh->primitive->array))[o].tex_index;
					if(tex_i < 0)
						continue;
					GLuint n;
					for(n = 0; n < tex_count_i; n++)
					{
						if(tex_index_set[n] == -1)
							break;
						if(tex_index_set[n] == tex_i)
							break;
					}
					if(n == tex_count_i)
					{
						tex_index_set[tex_count_i] = tex_i;
						tex_count_i++;
					}
				}
				m->count = tex_count_i;
				m->tex_index = NEW_II(GLint, m->count);
				for(o = 0; o < (GLint)m->count; o++)
				{
					m->tex_index[o] = tex_index_set[o];
				}
				free(tex_index_set);

				GLuint vertex_count = mesh->primitive->length * 3;
				GLuint index_count = mesh->primitive->length * 3;
				GL_NETLizard_3D_Vertex *vertex = NEW_II(GL_NETLizard_3D_Vertex, vertex_count);
				GLushort *indexs = NEW_II(GLushort, index_count);
				GL_NETLizard_3D_Material *materials = NEW_II(GL_NETLizard_3D_Material, m->count);
				int *mesh_vertex = (int *)(mesh->vertex->array);
				GLint c = 0;
				for(o = 0; o < (GLint)m->count; o++)
				{
					texture *tex = texes[m->tex_index[o]];
					if(!tex && m->tex_index[o] < tex_count && m->tex_index[o] > 0)
					{
						char subfix[SUBFIX_LENGTH];
						memset(subfix, '\0', SUBFIX_LENGTH);
						sprintf(subfix, subfix_str, m->tex_index[o]);
						char *name = NULL;
						if(game_resource_path[game])
						{
							name = NEW_II(char, strlen(subfix) + strlen(game_resource_path[game]) + 1 + 1);
							memset(name, '\0', sizeof(char) * ((strlen(subfix) + strlen(game_resource_path[game]) + 1 + 1)));
							sprintf(name, "%s/%s", game_resource_path[game], subfix);
						}
						else
							name = strdup(subfix);
						tex = new_OpenGL_texture_2d(name);
						free(name);
						texes[m->tex_index[o]] = tex;
					}

					NETLizard_3D_Primitive *p = (NETLizard_3D_Primitive *)(mesh->primitive->array);
					GLint a = c;
					GLint n;
					for(n = 0; n < mesh->primitive->length; n++)
					{
						if(m->tex_index[o] == p[n].tex_index)
						{
							int i0 = p[n].index[0] / index_factory;
							int i1 = p[n].index[1] / index_factory;
							int i2 = p[n].index[2] / index_factory;

							vertex[a].position[0] = (GLfloat)mesh_vertex[i0 * 3];
							vertex[a].position[1] = (GLfloat)mesh_vertex[i0 * 3 + 1];
							vertex[a].position[2] = (GLfloat)mesh_vertex[i0 * 3 + 2];

							vertex[a + 1].position[0] = (GLfloat)mesh_vertex[i1 * 3];
							vertex[a + 1].position[1] = (GLfloat)mesh_vertex[i1 * 3 + 1];
							vertex[a + 1].position[2] = (GLfloat)mesh_vertex[i1 * 3 + 2];

							vertex[a + 2].position[0] = (GLfloat)mesh_vertex[i2 * 3];
							vertex[a + 2].position[1] = (GLfloat)mesh_vertex[i2 * 3 + 1];
							vertex[a + 2].position[2] = (GLfloat)mesh_vertex[i2 * 3 + 2];
							vector3_s v0 = VECTOR3V(vertex[a].position);
							vector3_s v1 = VECTOR3V(vertex[a + 1].position);
							vector3_s v2 = VECTOR3V(vertex[a + 2].position);
							vector3_s v_normal = Math3D_GetTriangleNormal(&v0, &v1, &v2);
							vertex[a].normal[0] = v_normal.x;
							vertex[a].normal[1] = v_normal.y;
							vertex[a].normal[2] = v_normal.z;
							vertex[a + 1].normal[0] = v_normal.x;
							vertex[a + 1].normal[1] = v_normal.y;
							vertex[a + 1].normal[2] = v_normal.z;
							vertex[a + 2].normal[0] = v_normal.x;
							vertex[a + 2].normal[1] = v_normal.y;
							vertex[a + 2].normal[2] = v_normal.z;

							GLfloat w = tex ? tex->width : 1.0;
							vertex[a].texcoord[0] = (GLfloat)p[n].texcoord[0] / w; 
							vertex[a].texcoord[1] = (GLfloat)p[n].texcoord[1] / w; 

							vertex[a + 1].texcoord[0] = (GLfloat)p[n].texcoord[2] / w; 
							vertex[a + 1].texcoord[1] = (GLfloat)p[n].texcoord[3] / w; 

							vertex[a + 2].texcoord[0] = (GLfloat)p[n].texcoord[4] / w; 
							vertex[a + 2].texcoord[1] = (GLfloat)p[n].texcoord[5] / w; 

							if(invert_texcoord_y && tex)
							{
								vertex[a].texcoord[1] = 1.0 - vertex[a].texcoord[1];
								vertex[a + 1].texcoord[1] = 1.0 - vertex[a + 1].texcoord[1];
								vertex[a + 2].texcoord[1] = 1.0 - vertex[a + 2].texcoord[1];
							}
							indexs[a] = a;
							indexs[a + 1] = a + 1;
							indexs[a + 2] = a + 2;
							a += 3;
						}
					}
					materials[o].tex_index = m->tex_index[o];
					materials[o].index_start = c;
					materials[o].index_count = a - c;

					c = a;
				}

				m->materials = materials;
				m->vertex_array.gl = OPENGL_RENDER_VERTEX_DATA;
				m->vertex_array.vertex_data.vertex = vertex;
				m->vertex_array.vertex_data.vertex_count = vertex_count;
				m->vertex_array.vertex_data.index_count = index_count;
				m->vertex_array.vertex_data.index = indexs;
			}

			if(mesh->plane)
			{
				GLuint plane_count = mesh->plane->length;
				GL_NETLizard_3D_Plane *planes = NEW_II(GL_NETLizard_3D_Plane, mesh->plane->length);
				GLint j;
				for(j = 0; j < mesh->plane->length; j++)
				{
					GL_NETLizard_3D_Plane *glplane = planes + j;
					NETLizard_3D_Plane *plane = ((NETLizard_3D_Plane *)(mesh->plane->array)) + j;
					vector3_s normal = VECTOR3V(plane->normal);
					glplane->position[0] = (GLfloat)plane->position[0];
					glplane->position[1] = (GLfloat)plane->position[1];
					glplane->position[2] = (GLfloat)plane->position[2];
					Vector3_Normalize(&normal);
					glplane->normal[0] = (GLfloat)normal.x;
					glplane->normal[1] = (GLfloat)normal.y;
					glplane->normal[2] = (GLfloat)normal.z;
				}
				m->plane_count = plane_count;
				m->plane = planes;
			}
			else if(mesh->primitive)
			{
				GLuint c = 0;
				GLuint j;
				for(j = 0; j < m->count; j++)
					c += m->materials[j].index_count;
				GLuint plane_count = c;
				GL_NETLizard_3D_Plane *planes = NEW_II(GL_NETLizard_3D_Plane, c);
				GLuint n = 0;
				for(j = 0; j < m->count; j++)
				{
					GLuint k;
					for(k = 0; k < m->materials[j].index_count; k++)
					{
						GLuint index = (m->materials[j].index_start + k) * 3;
						planes[n].position[0] = m->vertex_array.vertex_data.vertex[index].position[0];
						planes[n].position[1] = m->vertex_array.vertex_data.vertex[index].position[1];
						planes[n].position[2] = m->vertex_array.vertex_data.vertex[index].position[2];
						planes[n].normal[0] = m->vertex_array.vertex_data.vertex[index].normal[0];
						planes[n].normal[1] = m->vertex_array.vertex_data.vertex[index].normal[1];
						planes[n].normal[2] = m->vertex_array.vertex_data.vertex[index].normal[2];
						n++;
					}
				}
				m->plane_count = plane_count;
				m->plane = planes;
			}
			else
			{
				GLuint plane_count = 1;
				plane_t ps[6];
				bound_s item_box = {
					{
						(GLfloat)mesh->ortho[3],
						(GLfloat)mesh->ortho[4],
						(GLfloat)mesh->ortho[5]
					},
					{
						(GLfloat)mesh->ortho[0],
						(GLfloat)mesh->ortho[1],
						(GLfloat)mesh->ortho[2]
					}
				};
				GL_NETLizard_3D_Plane *planes = NEW_II(GL_NETLizard_3D_Plane, plane_count);
				Math3D_GetAABBPlanes(&item_box, ps);
				int o;
				int q = 0;
				for(o = 0; o < 6; o++)
				{
					if(o != 0)
						continue;
					planes[q].position[0] = ps[o].position.x;
					planes[q].position[1] = ps[o].position.y;
					planes[q].position[2] = ps[o].position.z;
					planes[q].normal[0] = ps[o].normal.x;
					planes[q].normal[1] = ps[o].normal.y;
					planes[q].normal[2] = ps[o].normal.z;
					q++;
				}
				m->plane_count = plane_count;
				m->plane = planes;
			}

			m->ortho[0] = (GLfloat)mesh->ortho[0];
			m->ortho[1] = (GLfloat)mesh->ortho[1];
			m->ortho[2] = (GLfloat)mesh->ortho[2];
			m->ortho[3] = (GLfloat)mesh->ortho[3];
			m->ortho[4] = (GLfloat)mesh->ortho[4];
			m->ortho[5] = (GLfloat)mesh->ortho[5];
			m->item_index_range[0] = (GLuint)mesh->item_index_range[0];
			m->item_index_range[1] = (GLuint)mesh->item_index_range[1];

			if(mesh->bsp)
			{
				m->bsp_count = mesh->bsp->length;
				m->bsp = NEW_II(GLint, mesh->bsp->length);
				GLint k;
				for(k = 0; k < mesh->bsp->length; k++)
				{
					m->bsp[k] = ((int *)(mesh->bsp->array))[k];
				}
			}
		}
	}

	GL_NETLizard_3D_Item_Mesh *item_meshes = NULL;
	GLuint item_data_length = 0;

	if(model->item_data)
	{
		item_meshes = NEW_II(GL_NETLizard_3D_Item_Mesh, model->item_data->length);
		item_data_length = model->item_data->length;

		GLint i;
		for(i = 0; i < model->item_data->length; i++)
		{
			NETLizard_3D_Item_Mesh *mesh = ((NETLizard_3D_Item_Mesh *)(model->item_data->array)) + i;
			GL_NETLizard_3D_Item_Mesh *m = item_meshes + i;
			m->item_mesh.count = 0;
			m->item_mesh.materials = NULL;
			m->item_mesh.tex_index = NULL;
			m->item_mesh.vertex_array.gl = OPENGL_RENDER_VERTEX_DATA;
			m->item_mesh.vertex_array.vertex_data.vertex = NULL;
			m->item_mesh.vertex_array.vertex_data.vertex_count = 0;
			m->item_mesh.vertex_array.vertex_data.index = NULL;
			m->item_mesh.vertex_array.vertex_data.index_count = 0;
			m->item_mesh.plane_count = 0;
			m->item_mesh.plane = NULL;

			m->pos[0] = (GLfloat)mesh->pos[0];
			m->pos[1] = (GLfloat)mesh->pos[1];
			m->pos[2] = (GLfloat)mesh->pos[2];
			m->angle[0] = (GLfloat)mesh->angle[0];
			m->angle[1] = (GLfloat)mesh->angle[1];
			m->item_type = nlGetItemType(game, mesh->obj_index);
			if(mesh->item_mesh.vertex && mesh->item_mesh.primitive)
			{
				GLint o;
				GLuint tex_count_i = 0;
				GLint *tex_index_set = NEW_II(GLint, mesh->item_mesh.primitive->length);
				for(o = 0; o < mesh->item_mesh.primitive->length; o++)
				{
					tex_index_set[o] = -1;
				}
				for(o = 0; o < mesh->item_mesh.primitive->length; o++)
				{
					int tex_i = ((NETLizard_3D_Primitive *)(mesh->item_mesh.primitive->array))[o].tex_index;
					if(tex_i < 0)
						continue;
					GLuint n;
					for(n = 0; n < tex_count_i; n++)
					{
						if(tex_index_set[n] == -1)
							break;
						if(tex_index_set[n] == tex_i)
							break;
					}
					if(n == tex_count_i)
					{
						tex_index_set[tex_count_i] = tex_i;
						tex_count_i++;
					}
				}
				m->item_mesh.count = tex_count_i;
				m->item_mesh.tex_index = NEW_II(GLint, m->item_mesh.count);
				for(o = 0; o < (GLint)m->item_mesh.count; o++)
				{
					m->item_mesh.tex_index[o] = tex_index_set[o];
				}
				free(tex_index_set);

				GLuint vertex_count = mesh->item_mesh.primitive->length * 3;
				GLuint index_count = mesh->item_mesh.primitive->length * 3;
				GL_NETLizard_3D_Vertex *vertex = NEW_II(GL_NETLizard_3D_Vertex, vertex_count);
				GLushort *indexs = NEW_II(GLushort, index_count);
				GL_NETLizard_3D_Material *materials = NEW_II(GL_NETLizard_3D_Material, m->item_mesh.count);
				GLuint plane_count = mesh->item_mesh.primitive->length;
				GL_NETLizard_3D_Plane *planes = NEW_II(GL_NETLizard_3D_Plane, plane_count);
				int *mesh_vertex = (int *)(mesh->item_mesh.vertex->array);
#if 0
				if(mesh->obj_index >= 40 && mesh->obj_index <= 43)
					printf("e=prop %d 0.2 0 0.0 40.0 0 10.0 0 0 0.0 360.0 0 0\n", i);
#endif

				GLint b = 0;
				GLint c = 0;
				for(o = 0; o < (GLint)m->item_mesh.count; o++)
				{
					texture *tex = texes[m->item_mesh.tex_index[o]];
					if(!tex && m->item_mesh.tex_index[o] < tex_count && m->item_mesh.tex_index[o] > 0)
					{
						char subfix[SUBFIX_LENGTH];
						memset(subfix, '\0', SUBFIX_LENGTH);
						sprintf(subfix, subfix_str, m->item_mesh.tex_index[o]);
						char *name = NULL;
						if(game_resource_path[game])
						{
							name = NEW_II(char, strlen(subfix) + strlen(game_resource_path[game]) + 1 + 1);
							memset(name, '\0', sizeof(char) * ((strlen(subfix) + strlen(game_resource_path[game]) + 1 + 1)));
							sprintf(name, "%s/%s", game_resource_path[game], subfix);
						}
						else
							name = strdup(subfix);
						tex = new_OpenGL_texture_2d(name);
						free(name);
						texes[m->item_mesh.tex_index[o]] = tex;
					}

					NETLizard_3D_Primitive *p = (NETLizard_3D_Primitive *)(mesh->item_mesh.primitive->array);
					GLint a = c;
					GLint n;
					for(n = 0; n < mesh->item_mesh.primitive->length; n++)
					{
						if(m->item_mesh.tex_index[o] == p[n].tex_index)
						{
							int i0 = p[n].index[0] / item_index_factory;
							int i1 = p[n].index[1] / item_index_factory;
							int i2 = p[n].index[2] / item_index_factory;

							vertex[a].position[0] = (GLfloat)mesh_vertex[i0 * 3];
							vertex[a].position[1] = (GLfloat)mesh_vertex[i0 * 3 + 1];
							vertex[a].position[2] = (GLfloat)mesh_vertex[i0 * 3 + 2];
							vertex[a + 1].position[0] = (GLfloat)mesh_vertex[i1 * 3];
							vertex[a + 1].position[1] = (GLfloat)mesh_vertex[i1 * 3 + 1];
							vertex[a + 1].position[2] = (GLfloat)mesh_vertex[i1 * 3 + 2];
							vertex[a + 2].position[0] = (GLfloat)mesh_vertex[i2 * 3];
							vertex[a + 2].position[1] = (GLfloat)mesh_vertex[i2 * 3 + 1];
							vertex[a + 2].position[2] = (GLfloat)mesh_vertex[i2 * 3 + 2];
							vector3_s v0 = VECTOR3V(vertex[a].position);
							vector3_s v1 = VECTOR3V(vertex[a + 1].position);
							vector3_s v2 = VECTOR3V(vertex[a + 2].position);
							vector3_s v_normal = Math3D_GetTriangleNormal(&v0, &v1, &v2);
							vertex[a].normal[0] = v_normal.x;
							vertex[a].normal[1] = v_normal.y;
							vertex[a].normal[2] = v_normal.z;
							vertex[a + 1].normal[0] = v_normal.x;
							vertex[a + 1].normal[1] = v_normal.y;
							vertex[a + 1].normal[2] = v_normal.z;
							vertex[a + 2].normal[0] = v_normal.x;
							vertex[a + 2].normal[1] = v_normal.y;
							vertex[a + 2].normal[2] = v_normal.z;

							GLfloat w = tex ? tex->width : 1.0;
							vertex[a].texcoord[0] = (GLfloat)p[n].texcoord[0] / w; 
							vertex[a].texcoord[1] = (GLfloat)p[n].texcoord[1] / w; 
							vertex[a + 1].texcoord[0] = (GLfloat)p[n].texcoord[2] / w; 
							vertex[a + 1].texcoord[1] = (GLfloat)p[n].texcoord[3] / w; 
							vertex[a + 2].texcoord[0] = (GLfloat)p[n].texcoord[4] / w; 
							vertex[a + 2].texcoord[1] = (GLfloat)p[n].texcoord[5] / w; 

							if(item_invert_texcoord_y && tex)
							{
								vertex[a].texcoord[1] = 1.0 - vertex[a].texcoord[1];
								vertex[a + 1].texcoord[1] = 1.0 - vertex[a + 1].texcoord[1];
								vertex[a + 2].texcoord[1] = 1.0 - vertex[a + 2].texcoord[1];
							}

							indexs[a] = a;
							indexs[a + 1] = a + 1;
							indexs[a + 2] = a + 2;

							planes[b].position[0] = vertex[a].position[0];
							planes[b].position[1] = vertex[a].position[1];
							planes[b].position[2] = vertex[a].position[2];
							planes[b].normal[0] = vertex[a].normal[0];
							planes[b].normal[1] = vertex[a].normal[1];
							planes[b].normal[2] = vertex[a].normal[2];
							b++;
							a += 3;
						}
					}
					materials[o].tex_index = m->item_mesh.tex_index[o];
					materials[o].index_start = c;
					materials[o].index_count = a - c;

					c = a;
				}

				m->item_mesh.materials = materials;
				m->item_mesh.vertex_array.gl = OPENGL_RENDER_VERTEX_DATA;
				m->item_mesh.vertex_array.vertex_data.vertex_count = vertex_count;
				m->item_mesh.vertex_array.vertex_data.vertex = vertex;
				m->item_mesh.vertex_array.vertex_data.index_count = index_count;
				m->item_mesh.vertex_array.vertex_data.index = indexs;
				m->item_mesh.plane_count = plane_count;
				m->item_mesh.plane = planes;
			}
			m->item_mesh.ortho[0] = (GLfloat)mesh->item_mesh.ortho[0];
			m->item_mesh.ortho[1] = (GLfloat)mesh->item_mesh.ortho[1];
			m->item_mesh.ortho[2] = (GLfloat)mesh->item_mesh.ortho[2];
			m->item_mesh.ortho[3] = (GLfloat)mesh->item_mesh.ortho[3];
			m->item_mesh.ortho[4] = (GLfloat)mesh->item_mesh.ortho[4];
			m->item_mesh.ortho[5] = (GLfloat)mesh->item_mesh.ortho[5];
		}
	}

	GL_NETLizard_BSP_Tree_Node *bsp_data = NULL;
	GLuint bsp_count = 0;
	if(model->bsp_data)
	{
		bsp_data = NEW_II(GL_NETLizard_BSP_Tree_Node, model->bsp_data->length);
		NETLizard_BSP_Tree_Node *bsp = (NETLizard_BSP_Tree_Node *)(model->bsp_data->array);
		bsp_count = model->bsp_data->length;
		GLint j;
		for(j = 0; j < model->bsp_data->length; j++)
		{
			GLint k;
			for(k = 0; k < 4; k++)
			{
				bsp_data[j].plane[k][0] = (GLfloat)bsp[j].plane[k][0];
				bsp_data[j].plane[k][1] = (GLfloat)bsp[j].plane[k][1];
				bsp_data[j].plane[k][2] = (GLfloat)bsp[j].plane[k][2];
			}
			bsp_data[j].direction = bsp[j].direction;
			bsp_data[j].prev_scene = bsp[j].prev_scene;
			bsp_data[j].next_scene = bsp[j].next_scene;
			vector3_s normal = VECTOR3V((float)bsp[j].normal);
			Vector3_Normalize(&normal);
			bsp_data[j].normal[0] = normal.x;
			bsp_data[j].normal[1] = normal.y;
			bsp_data[j].normal[2] = normal.z;
		}
	}

	texture *sky = NULL;
	if(model->has_sky && strlen(sky_file))
	{
		char *name = NULL;
		if(game_resource_path[game])
		{
			name = NEW_II(char, strlen(sky_file) + strlen(game_resource_path[game]) + 1 + 1);
			memset(name, '\0', sizeof(char) * ((strlen(sky_file) + strlen(game_resource_path[game]) + 1 + 1)));
			sprintf(name, "%s/%s", game_resource_path[game], sky_file);
		}
		else
			name = strdup(sky_file);
		sky = new_texture_from_nl_v2_3d_file(name);
		free(name);
	}

	GL_NETLizard_3D_Model *glmodel = NEW(GL_NETLizard_3D_Model);
	ZERO(glmodel, GL_NETLizard_3D_Model);
	glmodel->meshes = meshes;
	glmodel->count = model->data ? model->data->length : 0;
	glmodel->item_meshes = item_meshes;
	glmodel->item_count = item_data_length;
	glmodel->texes = texes;
	glmodel->tex_count = tex_count;
	glmodel->start_pos[0] = (GLfloat)model->start_pos[0];
	glmodel->start_pos[1] = (GLfloat)model->start_pos[1];
	glmodel->start_pos[2] = (GLfloat)model->start_pos[2];
	glmodel->start_angle[0] = (GLfloat)model->start_angle[0];
	glmodel->start_angle[1] = (GLfloat)model->start_angle[1];
	glmodel->bsp_data = bsp_data;
	glmodel->bsp_count = bsp_count;
	glmodel->bg_tex = sky;

	return glmodel;
}

GL_NETLizard_3D_Animation_Model * NETLizard_MakeGL3DAnimationModel(const NETLizard_3D_Model *model)
{
	if(!model)
		return NULL;

	GLint tex_count; // 最大纹理数
	game_name game;
	int item_invert_texcoord_y; // 纹理坐标y反转
	int item_index_factory; // 物品顶点索引因子
	new_netlizard_texture_from_file new_OpenGL_texture_2d = new_texture_from_nl_v3_3d_file;
	char subfix_str[SUBFIX_LENGTH];
	memset(subfix_str, '\0', sizeof(char) * SUBFIX_LENGTH);

	switch(model->game)
	{
		case Egypt_3D_Role:
			tex_count = EGYPT3D_TEX_COUNT;
			game = nl_shadow_of_egypt_3d;
			strcpy(subfix_str, EGYPT3D_TEX_SUBFIX);
			item_invert_texcoord_y = 1;
			item_index_factory = 3;
			break;
		case Clone_3D_Role:
			tex_count = CLONE3D_TEX_COUNT;
			game = nl_clone_3d;
			strcpy(subfix_str, CLONE3D_TEX_SUBFIX);
			item_invert_texcoord_y = 0;
			item_index_factory = 3;
			break;
		default:
			return NULL;
	}

	int obj_index = ((NETLizard_3D_Item_Mesh *)(model->item_data->array))->obj_index;
	GLuint len = 0;
	int anim[Animation_Total_Type * 2];
	ZERO_II(anim, int, Animation_Total_Type * 2);
	int anim_count = nlGetAnimationBeginAndEnd(game, obj_index, anim);
	//printfi(obj_index);
	if(anim_count > 0)
		len = anim_count;
	else
		len = 1;
	NETLizard_3D_Role_Animation *animations = NEW_II(NETLizard_3D_Role_Animation, len);
	//printfi(anim_count);
	if(anim_count > 0)
	{
		GLint k = 0;
		GLint i;
		for(i = 0; i < Animation_Total_Type * 2; i += 2)
		{
			if(anim[i] == -1 || anim[i + 1] == -1)
				continue;
			animations[k].begin = anim[i];
			animations[k].end = anim[i + 1];
			animations[k].type = (NETLizard_3D_Animation_Type)(i / 2);
			k++;
		}
	}
	else
	{
		animations[0].begin = 0;
		animations[0].end = model->item_data->length - 1;
		animations[0].type = Animation_Unknow_Type;
	}

	texture *tex = NULL;

	GL_NETLizard_3D_Mesh *item_meshes = NEW_II(GL_NETLizard_3D_Mesh, model->item_data->length);
	GLint i;
	for(i = 0; i < model->item_data->length; i++)
	{
		NETLizard_3D_Item_Mesh *mesh = ((NETLizard_3D_Item_Mesh *)(model->item_data->array)) + i;
		GL_NETLizard_3D_Mesh *m = item_meshes + i;
		m->count = 0;
		m->materials = NULL;
		m->tex_index = NULL;
		m->vertex_array.gl = OPENGL_RENDER_VERTEX_DATA;
		m->vertex_array.vertex_data.vertex = NULL;
		m->vertex_array.vertex_data.vertex_count = 0;
		m->vertex_array.vertex_data.index = NULL;
		m->vertex_array.vertex_data.index_count = 0;
		m->plane_count = 0;
		m->plane = NULL;

		if(mesh->item_mesh.vertex && mesh->item_mesh.primitive)
		{
			GLuint vertex_count = mesh->item_mesh.primitive->length * 3;
			GLuint index_count = mesh->item_mesh.primitive->length * 3;
			GL_NETLizard_3D_Vertex *vertex = NEW_II(GL_NETLizard_3D_Vertex, vertex_count);
			GLushort *indexs = NEW_II(GLushort, index_count);
			GLuint count = 1;
			GL_NETLizard_3D_Material *materials = NEW_II(GL_NETLizard_3D_Material, count);
			int *mesh_vertex = (int *)(mesh->item_mesh.vertex->array);

			int tex_i = ((NETLizard_3D_Primitive *)(mesh->item_mesh.primitive->array))[0].tex_index;
			if(!tex && tex_i > 0 && tex_i < tex_count)
			{
				char subfix[SUBFIX_LENGTH];
				memset(subfix, '\0', SUBFIX_LENGTH);
				sprintf(subfix, subfix_str, tex_i);
				char *name = NULL;
				if(game_resource_path[game])
				{
					name = NEW_II(char, strlen(subfix) + strlen(game_resource_path[game]) + 1 + 1);
					memset(name, '\0', sizeof(char) * ((strlen(subfix) + strlen(game_resource_path[game]) + 1 + 1)));
					sprintf(name, "%s/%s", game_resource_path[game], subfix);
				}
				else
					name = strdup(subfix);
				tex = new_OpenGL_texture_2d(name);
				free(name);
			}

			NETLizard_3D_Primitive *p = (NETLizard_3D_Primitive *)(mesh->item_mesh.primitive->array);
			GLint a = 0;
			GLint n;
			for(n = 0; n < mesh->item_mesh.primitive->length; n++)
			{
				int i0 = p[n].index[0] / item_index_factory;
				int i1 = p[n].index[1] / item_index_factory;
				int i2 = p[n].index[2] / item_index_factory;

				vertex[a].position[0] = (GLfloat)mesh_vertex[i0 * 3];
				vertex[a].position[1] = (GLfloat)mesh_vertex[i0 * 3 + 1];
				vertex[a].position[2] = (GLfloat)mesh_vertex[i0 * 3 + 2];
				vertex[a + 1].position[0] = (GLfloat)mesh_vertex[i1 * 3];
				vertex[a + 1].position[1] = (GLfloat)mesh_vertex[i1 * 3 + 1];
				vertex[a + 1].position[2] = (GLfloat)mesh_vertex[i1 * 3 + 2];
				vertex[a + 2].position[0] = (GLfloat)mesh_vertex[i2 * 3];
				vertex[a + 2].position[1] = (GLfloat)mesh_vertex[i2 * 3 + 1];
				vertex[a + 2].position[2] = (GLfloat)mesh_vertex[i2 * 3 + 2];
				vector3_s v0 = VECTOR3V(vertex[a].position);
				vector3_s v1 = VECTOR3V(vertex[a + 1].position);
				vector3_s v2 = VECTOR3V(vertex[a + 2].position);
				vector3_s v_normal = Math3D_GetTriangleNormal(&v0, &v1, &v2);
				vertex[a].normal[0] = v_normal.x;
				vertex[a].normal[1] = v_normal.y;
				vertex[a].normal[2] = v_normal.z;
				vertex[a + 1].normal[0] = v_normal.x;
				vertex[a + 1].normal[1] = v_normal.y;
				vertex[a + 1].normal[2] = v_normal.z;
				vertex[a + 2].normal[0] = v_normal.x;
				vertex[a + 2].normal[1] = v_normal.y;
				vertex[a + 2].normal[2] = v_normal.z;

				GLfloat w = tex ? tex->width : 1.0;
				vertex[a].texcoord[0] = (GLfloat)p[n].texcoord[0] / w; 
				vertex[a].texcoord[1] = (GLfloat)p[n].texcoord[1] / w; 
				vertex[a + 1].texcoord[0] = (GLfloat)p[n].texcoord[2] / w; 
				vertex[a + 1].texcoord[1] = (GLfloat)p[n].texcoord[3] / w; 
				vertex[a + 2].texcoord[0] = (GLfloat)p[n].texcoord[4] / w; 
				vertex[a + 2].texcoord[1] = (GLfloat)p[n].texcoord[5] / w; 

				if(item_invert_texcoord_y && tex)
				{
					vertex[a].texcoord[1] = 1.0 - vertex[a].texcoord[1];
					vertex[a + 1].texcoord[1] = 1.0 - vertex[a + 1].texcoord[1];
					vertex[a + 2].texcoord[1] = 1.0 - vertex[a + 2].texcoord[1];
				}

				indexs[a] = a;
				indexs[a + 1] = a + 1;
				indexs[a + 2] = a + 2;

				a += 3;
			}
			materials[0].tex_index = 0;
			materials[0].index_start = 0;
			materials[0].index_count = a;

			GLint *tex_index = NEW_II(GLuint, 1);
			tex_index[0] = 0;

			m->tex_index = tex_index;
			m->materials = materials;
			m->count = count;
			m->vertex_array.gl = OPENGL_RENDER_VERTEX_DATA;
			m->vertex_array.vertex_data.vertex_count = vertex_count;
			m->vertex_array.vertex_data.vertex = vertex;
			m->vertex_array.vertex_data.index_count = index_count;
			m->vertex_array.vertex_data.index = indexs;
		}
	}

	GL_NETLizard_3D_Animation_Model *glmodel = NEW(GL_NETLizard_3D_Animation_Model);
	ZERO(glmodel, GL_NETLizard_3D_Animation_Model);
	glmodel->meshes = item_meshes;
	glmodel->count = model->item_data ? model->item_data->length : 0;
	glmodel->tex = tex;
	glmodel->animations = animations;
	glmodel->anim_count = len;
	glmodel->item_type = Item_Role_Type;
	return glmodel;
}

GLvoid NETLizard_MakeGL23DModel(GL_NETLizard_3D_Model *model)
{
	if(!model)
		return;
	if(model->meshes)
	{
		GLuint i;
		for(i = 0; i < model->count; i++)
		{
			GL_NETLizard_3D_Mesh *mesh = model->meshes + i;
			if((mesh->vertex_array.gl & OPENGL_RENDER_VERTEX_DATA) == 0 || (mesh->vertex_array.gl & OPENGL_RENDER_VERTEX_BUFFER))
				continue;
			GLuint vertex_buffer = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, mesh->vertex_array.vertex_data.vertex_count * sizeof(GL_NETLizard_3D_Vertex), mesh->vertex_array.vertex_data.vertex, GL_STATIC_DRAW);
			GLuint index_buffer = new_OpenGL_buffer_object(GL_ELEMENT_ARRAY_BUFFER, mesh->vertex_array.vertex_data.index_count * sizeof(GLushort), mesh->vertex_array.vertex_data.index, GL_STATIC_DRAW);

#if OPENGL_RENDER_VERTEX_USING_UNION
			free(mesh->vertex_array.vertex_data.vertex);
			free(mesh->vertex_array.vertex_data.index);

			memset(&mesh->vertex_array, 0, sizeof(GL_NETLizard_3D_Vertex_Array));
#endif

			GLuint vertex_count = mesh->vertex_array.vertex_data.vertex_count;
			GLuint index_count = mesh->vertex_array.vertex_data.index_count;
			mesh->vertex_array.gl |= OPENGL_RENDER_VERTEX_BUFFER;
			mesh->vertex_array.vertex_buffer.vertex_buffer = vertex_buffer;
			mesh->vertex_array.vertex_buffer.index_buffer = index_buffer;
			mesh->vertex_array.vertex_buffer.vertex_count = vertex_count;
			mesh->vertex_array.vertex_buffer.index_count = index_count;
		}
	}

	if(model->item_meshes)
	{
		GLuint i;
		for(i = 0; i < model->item_count; i++)
		{
			GL_NETLizard_3D_Item_Mesh *mesh = model->item_meshes + i;
			if((mesh->item_mesh.vertex_array.gl & OPENGL_RENDER_VERTEX_DATA) == 0 || (mesh->item_mesh.vertex_array.gl & OPENGL_RENDER_VERTEX_BUFFER))
				continue;
			GLuint vertex_buffer = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, mesh->item_mesh.vertex_array.vertex_data.vertex_count * sizeof(GL_NETLizard_3D_Vertex), mesh->item_mesh.vertex_array.vertex_data.vertex, GL_STATIC_DRAW);
			GLuint index_buffer = new_OpenGL_buffer_object(GL_ELEMENT_ARRAY_BUFFER, mesh->item_mesh.vertex_array.vertex_data.index_count * sizeof(GLushort), mesh->item_mesh.vertex_array.vertex_data.index, GL_STATIC_DRAW);

#if OPENGL_RENDER_VERTEX_USING_UNION
			free(mesh->item_mesh.vertex_array.vertex_data.vertex);
			free(mesh->item_mesh.vertex_array.vertex_data.index);

			memset(&mesh->item_mesh.vertex_array, 0, sizeof(GL_NETLizard_3D_Vertex_Array));
#endif

			GLuint vertex_count = mesh->item_mesh.vertex_array.vertex_data.vertex_count;
			GLuint index_count = mesh->item_mesh.vertex_array.vertex_data.index_count;
			mesh->item_mesh.vertex_array.gl |= OPENGL_RENDER_VERTEX_BUFFER;
			mesh->item_mesh.vertex_array.vertex_buffer.vertex_buffer = vertex_buffer;
			mesh->item_mesh.vertex_array.vertex_buffer.index_buffer = index_buffer;
			mesh->item_mesh.vertex_array.vertex_buffer.vertex_count = vertex_count;
			mesh->item_mesh.vertex_array.vertex_buffer.index_count = index_count;
		}
	}
}

GLvoid NETLizard_MakeGL23DAnimationModel(GL_NETLizard_3D_Animation_Model *model)
{
	if(!model)
		return;
	if(model->meshes)
	{
		GLuint i;
		for(i = 0; i < model->count; i++)
		{
			GL_NETLizard_3D_Mesh *mesh = model->meshes + i;
			if((mesh->vertex_array.gl & OPENGL_RENDER_VERTEX_DATA) == 0 || (mesh->vertex_array.gl & OPENGL_RENDER_VERTEX_BUFFER))
				continue;
			GLuint vertex_buffer = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, mesh->vertex_array.vertex_data.vertex_count * sizeof(GL_NETLizard_3D_Vertex), mesh->vertex_array.vertex_data.vertex, GL_STATIC_DRAW);
			GLuint index_buffer = new_OpenGL_buffer_object(GL_ELEMENT_ARRAY_BUFFER, mesh->vertex_array.vertex_data.index_count * sizeof(GLushort), mesh->vertex_array.vertex_data.index, GL_STATIC_DRAW);

#if OPENGL_RENDER_VERTEX_USING_UNION
			free(mesh->vertex_array.vertex_data.vertex);
			free(mesh->vertex_array.vertex_data.index);

			memset(&mesh->vertex_array, 0, sizeof(GL_NETLizard_3D_Vertex_Array));
#endif

			GLuint vertex_count = mesh->vertex_array.vertex_data.vertex_count;
			GLuint index_count = mesh->vertex_array.vertex_data.index_count;
			mesh->vertex_array.gl |= OPENGL_RENDER_VERTEX_BUFFER;
			mesh->vertex_array.vertex_buffer.vertex_buffer = vertex_buffer;
			mesh->vertex_array.vertex_buffer.index_buffer = index_buffer;
			mesh->vertex_array.vertex_buffer.vertex_count = vertex_count;
			mesh->vertex_array.vertex_buffer.index_count = index_count;
		}
	}
}

GLvoid NETLizard_MoveItemModel(GL_NETLizard_3D_Item_Mesh *dst, GL_NETLizard_3D_Item_Mesh *src)
{
	if(!dst || !src)
		return;
	dst->item_type = src->item_type;
	memcpy(dst->pos, src->pos, sizeof(GLfloat) * 3);
	memcpy(dst->angle, src->angle, sizeof(GLfloat) * 2);

	dst->item_mesh.count = src->item_mesh.count;
	dst->item_mesh.tex_index = src->item_mesh.tex_index;
	src->item_mesh.tex_index = NULL;
	dst->item_mesh.materials = src->item_mesh.materials;
	src->item_mesh.materials = NULL;
	dst->item_mesh.plane_count = src->item_mesh.plane_count;
	dst->item_mesh.plane = src->item_mesh.plane;
	src->item_mesh.plane = NULL;

	memcpy(dst->item_mesh.ortho, src->item_mesh.ortho, sizeof(GLfloat) * 6);

	dst->item_mesh.vertex_array.gl = src->item_mesh.vertex_array.gl;
	if(src->item_mesh.vertex_array.gl & OPENGL_RENDER_VERTEX_DATA)
	{
		memcpy(&dst->item_mesh.vertex_array.vertex_data, &src->item_mesh.vertex_array.vertex_data, sizeof(GL_NETLizard_3D_Vertex_Data));
		src->item_mesh.vertex_array.vertex_data.vertex = NULL;
		src->item_mesh.vertex_array.vertex_data.index = NULL;
	}
	else if(src->item_mesh.vertex_array.gl & OPENGL_RENDER_VERTEX_BUFFER)
	{
		memcpy(&dst->item_mesh.vertex_array.vertex_buffer, &src->item_mesh.vertex_array.vertex_buffer, sizeof(GL_NETLizard_3D_Vertex_Buffer));
		src->item_mesh.vertex_array.vertex_buffer.vertex_buffer = 0;
		src->item_mesh.vertex_array.vertex_buffer.index_buffer = 0;
	}
}
