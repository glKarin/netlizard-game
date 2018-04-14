#ifndef KARKN_LOL_STRUCT_H
#define KARKN_LOL_STRUCT_H

#include "math3d/matrix44.h"
#include "opengl.h"

#include <stdio.h>

// mesh

typedef struct _LOL_Vertex
{
	float position[3];
	float normal[3];
	float texcoord[2];
	unsigned char bone_index[4];
	float bone_weight[4];
} LOL_Vertex;

typedef struct _LOL_Material
{
	char *name;
	unsigned int start_vertex;
	unsigned int vertex_count;
	unsigned int start_index;
	unsigned int index_count;
} LOL_Material;

typedef struct _LOL_Bone
{
	int index;
	char* name;
	int parent;
	float scale;
	matrix44_t orig_matrix; // global matrix
	matrix44_t base_matrix; // global matrix inverse
	matrix44_t incr_matrix; // local matrix
} LOL_Bone;

typedef struct _LOL_Mesh_Bone
{
	unsigned int bone_count;
	LOL_Bone *bone;
} LOL_Mesh_Bone;

typedef enum _LOL_Buffer_Type
{
	LOL_Vertex_Buffer_Type = 0,
	LOL_Index_Buffer_Type,
	LOL_Total_Buffer
} LOL_Buffer_Type;

typedef struct _LOL_Vertex_Buffer
{
	GLint gl; // = 2
	GLuint buffers[LOL_Total_Buffer];
} LOL_Vertex_Buffer;

typedef struct _LOL_Vertex_Data
{
	GLint gl; // = 1
} LOL_Vertex_Data;

typedef union _LOL_GL_Vertex_Array
{
	GLint gl;
	LOL_Vertex_Data vertex_data;
	LOL_Vertex_Buffer vertex_buffer;
} LOL_GL_Vertex_Array;

typedef struct _LOL_Mesh
{
	unsigned int magic;
	unsigned int version;
	char *animation_file;
	char *texture_file;
	unsigned int material_count;
	LOL_Material *material;
	unsigned int vertex_count;
	LOL_Vertex *vertex;
	unsigned int index_count;
	unsigned short *index;
	LOL_Mesh_Bone bone_data;
	LOL_GL_Vertex_Array vertex_array;
} LOL_Mesh;

typedef struct _LOL_Frame
{
	float pos[3];
	float rot[4];
	float scale[3];
} LOL_Frame;

typedef struct _LOL_Animation_Bone
{
	unsigned int frame_count;
	char *bone;
	unsigned int flag;
	LOL_Frame *frame;
} LOL_Animation_Bone;

typedef struct _LOL_Animation
{
	char *name;
	int fps;
	float duration;
	unsigned int bone_count;
	LOL_Animation_Bone *animation_bone;
} LOL_Animation;

typedef struct _LOL_Anim
{
	unsigned int magic;
	unsigned int version;
	unsigned int animation_count;
	LOL_Animation *animation;
} LOL_Anim;

char * LOL_ReadLowerStringData(FILE *data, unsigned short len);
char * LOL_ReadStringData(FILE *data, unsigned short len);

#endif
