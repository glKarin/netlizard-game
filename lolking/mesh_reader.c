#include "mesh_reader.h"

#include <string.h>
#include <stdlib.h>

void delete_LOL_Mesh(LOL_Mesh *mesh)
{
	if(!mesh)
		return;
	free(mesh->animation_file);
	free(mesh->texture_file);
	unsigned int i;
	for(i = 0; i < mesh->material_count; i++)
		free(mesh->material[i].name);
	free(mesh->material);
	free(mesh->vertex);
	free(mesh->index);
	for(i = 0; i < mesh->bone_data.bone_count; i++)
		free(mesh->bone_data.bone[i].name);
	free(mesh->bone_data.bone);
	if(mesh->vertex_array.gl & LOLKING_OPENGL_RENDER_VERTEX_BUFFER)
		glDeleteBuffers(LOL_Total_Buffer, mesh->vertex_array.vertex_buffer.buffers);
}

LOL_Mesh * new_LOL_Mesh(const char *file)
{
	if(!file)
		return NULL;
	FILE *in = fopen(file, "rb");
	if(!in)
		return NULL;
	unsigned int magic = 0;
	fread(&magic, 4, 1, in);
	if(magic != 604210091)
	{
		fclose(in);
		return NULL;
	}
	LOL_Mesh *mesh = malloc(sizeof(LOL_Mesh));
	memset(mesh, 0, sizeof(LOL_Mesh));
	mesh->magic = magic;
	fread(&mesh->version, 4, 1, in);

	mesh->animation_file = LOL_ReadStringData(in, 0);
	if(mesh->version < 4)
		mesh->texture_file = LOL_ReadStringData(in, 0);

	fread(&mesh->material_count, 4, 1, in);
	mesh->material = calloc(mesh->material_count, sizeof(LOL_Mesh));
	unsigned int i;
	for(i = 0; i < mesh->material_count; i++)
	{
		if(i == 0 && mesh->version >= 4)
		{
			mesh->texture_file = LOL_ReadLowerStringData(in, 0);
		}

		mesh->material[i].name = LOL_ReadStringData(in, 0);
		fread(&mesh->material[i].start_vertex, 4, 1, in);
		fread(&mesh->material[i].vertex_count, 4, 1, in);
		fread(&mesh->material[i].start_index, 4, 1, in);
		fread(&mesh->material[i].index_count, 4, 1, in);
	}

	fread(&mesh->vertex_count, 4, 1, in);
	mesh->vertex = calloc(mesh->vertex_count, sizeof(LOL_Vertex));
	fread(mesh->vertex, sizeof(LOL_Vertex), mesh->vertex_count, in);

	fread(&mesh->index_count, 4, 1, in);
	mesh->index = calloc(mesh->index_count, 2);
	fread(mesh->index, 2, mesh->index_count, in);

	fread(&mesh->bone_data.bone_count, 4, 1, in);
	mesh->bone_data.bone = calloc(mesh->bone_data.bone_count, sizeof(LOL_Bone));
	for(i = 0; i < mesh->bone_data.bone_count; i++)
	{
		LOL_Bone *bone = mesh->bone_data.bone + i;
		bone->index = i;
		bone->name = LOL_ReadLowerStringData(in, 0);
		fread(&bone->parent, 4, 1, in);
		fread(&bone->scale, 4, 1, in);
		Matrix44_Identity(&bone->orig_matrix);
		int j;
		for(j = 0; j < 16; j++)
		{
			float f = 0.0;
			fread(&f, 4, 1, in);
			((NLfloat *)(bone->orig_matrix.x))[j] = f; // TEST
		}

		bone->base_matrix = bone->orig_matrix;
		Matrix44_TransposeSelf(&bone->base_matrix);
		Matrix44_GjInverseNotSingularSelf(&bone->base_matrix);
		Matrix44_TransposeSelf(&bone->orig_matrix);
		Matrix44_Identity(&bone->incr_matrix);
		if(mesh->version >= 2)
		{
			for(j = 0; j < 16; j++)
			{
				float f = 0.0;
				fread(&f, 4, 1, in);
					((NLfloat *)(bone->incr_matrix.x))[j] = f; // TEST
			}
			Matrix44_TransposeSelf(&bone->incr_matrix);
		}
	}

#if 0
	QMap<QString, int32> boneLookup;
	for(int i = 0; i < meshBone->numBones; i++)
	{
		if(boneLookup.contains(QString(meshBone->bones[i].name)))
		{
			size_t len = strlen(meshBone->bones[i].name);
			int8 *new_name = (int8 *)malloc(len + 1 + 1);
			strcpy(new_name, meshBone->bones[i].name);
			new_name[len] = '2';
			new_name[len + 1] = '\0';
			free(meshBone->bones[i].name);
			meshBone->bones[i].name = new_name;
		}
		boneLookup.insert(QString(meshBone->bones[i].name), i);
	}
#endif

	return mesh;
}

void LOL_MakeGL2Mesh(LOL_Mesh *mesh)
{
	if(!mesh)
		return;
	if((mesh->vertex_array.gl & LOLKING_OPENGL_RENDER_VERTEX_DATA) == 0 || (mesh->vertex_array.gl & LOLKING_OPENGL_RENDER_VERTEX_BUFFER))
		return;
	if(!mesh->vertex || !mesh->index)
		return;

	GLuint buffers[LOL_Total_Buffer] = {0, 0};
	glGenBuffers(LOL_Total_Buffer, buffers);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[LOL_Vertex_Buffer_Type]);
	GLfloat *vertex = calloc(8 * mesh->vertex_count, sizeof(GLfloat));
	unsigned int i;
	for(i = 0; i < mesh->vertex_count; i++)
	{
		vertex[i * 8] = mesh->vertex[i].position[0];
		vertex[i * 8 + 1] = mesh->vertex[i].position[1];
		vertex[i * 8 + 2] = mesh->vertex[i].position[2];

		vertex[i * 8 + 3] = mesh->vertex[i].normal[0];
		vertex[i * 8 + 4] = mesh->vertex[i].normal[1];
		vertex[i * 8 + 5] = mesh->vertex[i].normal[2];

		vertex[i * 8 + 6] = mesh->vertex[i].texcoord[0];
		vertex[i * 8 + 7] = mesh->vertex[i].texcoord[1];
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8 * mesh->vertex_count, vertex, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	free(vertex);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[LOL_Index_Buffer_Type]);
	GLushort *index = calloc(mesh->index_count, sizeof(GLushort));
	for(i = 0; i < mesh->index_count; i++)
	{
		index[i] = mesh->index[i];
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * mesh->index_count, index, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	free(index);

	mesh->vertex_array.vertex_buffer.gl |= LOLKING_OPENGL_RENDER_VERTEX_BUFFER;
	memcpy(mesh->vertex_array.vertex_buffer.buffers, buffers, sizeof(GLuint) * LOL_Total_Buffer);
}
