#ifndef KARIN_MESH_H
#define KARIN_MESH_H

#include "gl_util.h"

typedef enum
{
	VertexBuffer = 0,
	TexcoordBuffer,
	IndexBuffer,
	TotalBuffer
} Buffer;

typedef struct _Vec3f
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Vec3f;

typedef struct _Mesh
{
	GLuint buffers[TotalBuffer];
	Vec3f translate;
	GLuint *strips;
	GLuint primitive;
} Mesh;

typedef struct _NL_Mesh
{
	Mesh *meshes;
	GLuint mesh_count;
	Tex tex;
} NL_Mesh;

extern NL_Mesh mesh;

void a_ReadMeshFile(const char *paramString);
void a_ParseFile(char paramArrayOfByte[], int paramInt);
int a_Appearance(int paramInt1, char paramArrayOfByte[], int paramInt2);
int a_k(Mesh *m, int paramArrayOfInt[], int paramInt1, char paramArrayOfByte[], int paramInt2);


#endif
