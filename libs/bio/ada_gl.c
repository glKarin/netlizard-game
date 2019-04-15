#include "ada_gl.h"
#include "SOIL/SOIL.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static GLuint Ada_LoadTexture(const char *file);

int Ada_MakeGLSmd(ADA_GL_Material_List *list, const ADA_smd *smd, const char *path)
{
	if(!list || !smd)
		return 0;
	int count = 0;
	const char **files = calloc(smd->triangle_list.triangle_count, sizeof(const char *));
	int i;
	for(i = 0; i < smd->triangle_list.triangle_count; i++)
	{
		int j;
		for(j = 0; j < count; j++)
		{
			if(files[j] == NULL)
				break;
			if(strcmp(files[j], smd->triangle_list.triangles[i].texture_file) == 0)
				break;
		}
		if(j == count)
		{
			files[count] = smd->triangle_list.triangles[i].texture_file;
			count++;
		}
	}
	list->material_count = count;
	list->materials = calloc(list->material_count * 3, sizeof(ADA_GL_Material));
	count = 0;
	for(i = 0; i < list->material_count; i++)
	{
		ADA_GL_Material *material = list->materials + i;
		size_t len = strlen(files[i]);
		if(path)
			len += strlen(path) + 1;
		len += 1;
		char *file = calloc(len, sizeof(char));
		memset(file, '\0', sizeof(char) * len);
		if(path)
			sprintf(file, "%s/%s", path, files[i]);
		else
			file = strdup(files[i]);
		material->texture = Ada_LoadTexture(file);
		free(file);
		int j;	
		for(j = 0; j < smd->triangle_list.triangle_count; j++)
		{
			if(strcmp(files[i], smd->triangle_list.triangles[j].texture_file) == 0)
				count++;
		}
		material->primitive_count = count;
		material->vertex = calloc(material->primitive_count * 3, sizeof(ADA_GL_Vertex));
		count = 0;
		for(j = 0; j < smd->triangle_list.triangle_count; j++)
		{
			if(strcmp(files[i], smd->triangle_list.triangles[j].texture_file) == 0)
			{
				int k;
				for(k = 0; k < 3; k++)
				{
					material->vertex[count * 3 + k].position[0] = smd->triangle_list.triangles[j].vertex[k].position[0];
					material->vertex[count * 3 + k].position[1] = smd->triangle_list.triangles[j].vertex[k].position[1];
					material->vertex[count * 3 + k].position[2] = smd->triangle_list.triangles[j].vertex[k].position[2];
					material->vertex[count * 3 + k].normal[0] = smd->triangle_list.triangles[j].vertex[k].normal[0];
					material->vertex[count * 3 + k].normal[1] = smd->triangle_list.triangles[j].vertex[k].normal[1];
					material->vertex[count * 3 + k].normal[2] = smd->triangle_list.triangles[j].vertex[k].normal[2];
					material->vertex[count * 3 + k].texcoord[0] = smd->triangle_list.triangles[j].vertex[k].texcoord[0];
					material->vertex[count * 3 + k].texcoord[1] = smd->triangle_list.triangles[j].vertex[k].texcoord[1];
				}
				count++;
			}
		}
	}
	free(files);
	return 1;
}

void Ada_FreeGLMaterial(ADA_GL_Material *material)
{
	if(!material)
		return;
	if(material->texture != 0)
	{
		if(glIsTexture(material->texture))
			glDeleteTextures(1, &material->texture);
	}
	ADA_FREE(material->vertex)
	material->primitive_count = 0;
}

void Ada_FreeGLMaterialList(ADA_GL_Material_List *list)
{
	if(!list)
		return;
	if(!list->materials)
		return;
	int i;
	for(i = 0; i < list->material_count; i++)
		Ada_FreeGLMaterial(list->materials + i);
	free(list->materials);
	list->materials = NULL;
	list->material_count = 0;
}

GLuint Ada_LoadTexture(const char *dds)
{
	if(!dds)
		return 0;
	int channel;
	int width = 0;
	int height = 0;
	GLuint texid = 0;
	unsigned char *data = SOIL_load_image((char *)dds, &width, &height, &channel, SOIL_LOAD_AUTO);
	if(!data)
		return 0;

	GLenum format = 0;
	switch(channel)
	{
		case SOIL_LOAD_L:
			format = GL_LUMINANCE;
			break;
		case SOIL_LOAD_LA:
			format = GL_LUMINANCE_ALPHA;
			break;
		case SOIL_LOAD_RGB:
			format = GL_RGB;
			break;
		case SOIL_LOAD_RGBA:
			format = GL_RGBA;
			break;
		default:
			break;
	}
	if(format != 0)
	{
		glGenTextures(1, &texid);
		glBindTexture(GL_TEXTURE_2D, texid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#ifdef _HARMATTAN_OPENGLES
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
#else
		glGenerateMipmap(GL_TEXTURE_2D);
#endif
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

		glBindTexture(GL_TEXTURE_2D, 0);

		free(data);

		return texid;
	}
	else
	{
		free(data);
		return 0;
	}
}

int Ada_MakeGLPmd(ADA_GL_Material_List *list, const ADA_pmd *pmd, const char *path)
{
	if(!list || !pmd)
		return 0;
	list->material_count = pmd->mesh_list.mesh_count;
	list->materials = calloc(list->material_count, sizeof(ADA_GL_Material));
	int count = 0;
	int i;
	for(i = 0; i < list->material_count; i++)
	{
		const ADA_PMD_Mesh *mesh = pmd->mesh_list.meshes + i;
		ADA_GL_Material *material = list->materials + i;
		size_t len = strlen(pmd->texture_list.textures[i].texture_name);
		if(path)
			len += strlen(path) + 1;
		len += 1;
		char *file = calloc(len, sizeof(char));
		memset(file, '\0', sizeof(char) * len);
		if(path)
			sprintf(file, "%s/%s", path, pmd->texture_list.textures[i].texture_name);
		else
			file = strdup(pmd->texture_list.textures[i].texture_name);
		material->texture = Ada_LoadTexture(file);
		printf("%d - %s\n", i, file);
		free(file);
		int j;	
		for(j = 0; j < mesh->primitive_list.primitive_count; j++)
		{
			count += mesh->primitive_list.primitives[j].vertex_list.vertex_count;
		}
		material->primitive_count = count / 3;
		material->vertex = calloc(material->primitive_count * 3, sizeof(ADA_GL_Vertex));
		count = 0;
		for(j = 0; j < mesh->primitive_list.primitive_count; j++)
		{
			const ADA_PMD_Primitive *primitive = mesh->primitive_list.primitives + j;
			int k;
			for(k = 0; k < primitive->vertex_list.vertex_count; k++)
			{
				const ADA_PMD_Vertex *vertex = primitive->vertex_list.vertices + k;
				material->vertex[count].position[0] = vertex->position[0];
				material->vertex[count].position[1] = - vertex->position[2];
				material->vertex[count].position[2] = vertex->position[1];
				material->vertex[count].normal[0] = vertex->normal[0];
				material->vertex[count].normal[1] = - vertex->normal[2];
				material->vertex[count].normal[2] = vertex->normal[1];
				material->vertex[count].texcoord[0] = vertex->texcoord[0];
				material->vertex[count].texcoord[1] = vertex->texcoord[1];
				count++;
			}
		}
	}
	return 1;
}
