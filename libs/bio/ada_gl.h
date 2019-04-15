#ifndef KARIN_ADA_GL_H
#define KARIN_ADA_GL_H

#include "ada_smd_struct.h"
#include "ada_pmd_struct.h"

#include "opengl/opengl.h"

typedef struct _ADA_GL_Vertex
{
	GLfloat position[3];
	GLfloat normal[3];
	GLfloat texcoord[2];
} ADA_GL_Vertex;

typedef struct _ADA_GL_Material
{
	GLuint texture;
	GLuint primitive_count;
	struct _ADA_GL_Vertex *vertex;
} ADA_GL_Material;

typedef struct _ADA_GL_Material_List
{
	GLuint material_count;
	struct _ADA_GL_Material *materials;
} ADA_GL_Material_List;

int Ada_MakeGLSmd(ADA_GL_Material_List *list, const ADA_smd *smd, const char *path);
int Ada_MakeGLPmd(ADA_GL_Material_List *list, const ADA_pmd *pmd, const char *path);
void Ada_FreeGLMaterial(ADA_GL_Material *material);
void Ada_FreeGLMaterialList(ADA_GL_Material_List *list);

#endif
