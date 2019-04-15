#ifndef KARIN_ADA_H
#define KARIN_ADA_H

#include "ada_smd.h"
#include "ada_pmd.h"
#include "ada_render.h"

typedef struct _ADA_GL_Model
{
	GLuint model_count;
	struct _ADA_GL_Material_List *models;
} ADA_GL_Model;

int Ada_LoadPmdModel(ADA_GL_Model *model, const char *files[], int len, const char *path);
void Ada_RenderStaticModel(const ADA_GL_Model *model);

#endif
