#ifndef KARKN_CAITLYN_STRUCT_H
#define KARKN_CAITLYN_STRUCT_H

#include <GL/gl.h>

#define READ_DATA(v, data, T, count, p) \
	memcpy(v, data + p, sizeof(T) * count); \
p += count * sizeof(T) / sizeof(char);

// skn

typedef struct _Caitlyn_Vertex
{
	float position[3];
	char bone_index[4];
	float bone_weight[4];
	float normal[3];
	float texcoord[2];
} Caitlyn_Vertex;

typedef struct _Caitlyn_Material
{
	char name[64];
	int start_vertex;
	int vertex_count;
	int start_index;
	int index_count;
} Caitlyn_Material;

typedef struct _Caitlyn_Skn_Model
{
	int magic;
	short version;
	short primitive_count;
	int material_count;
	Caitlyn_Material *material;
	int index_count;
	int vertex_count;
	short *index;
	Caitlyn_Vertex *vertex;
} Caitlyn_Skn_Model;

void caitlynRenderStaticModel(const Caitlyn_Skn_Model *skn, GLuint texid)
{
	if(!skn)
		return;
	if(glIsTexture(texid))
	{
		glBindTexture(GL_TEXTURE_2D,texid);
	}
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glNormalPointer(GL_FLOAT, sizeof(Caitlyn_Vertex), &(skn -> vertex[0].normal[0]));
	glVertexPointer(3, GL_FLOAT, sizeof(Caitlyn_Vertex), skn -> vertex);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Caitlyn_Vertex), &(skn -> vertex[0].texcoord[0]));
	int i;
	for(i = 0; i < skn -> material_count; i++)
	{
		glDrawElements(GL_TRIANGLES, skn -> material[i].index_count, GL_UNSIGNED_SHORT, skn -> index + skn -> material[i].start_index);
	}


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	if(glIsTexture(texid))
	{
		glBindTexture(GL_TEXTURE_2D,0);
	}
}

#endif
