#ifndef KARIN_RACINGEVOLUTION3D_MESH_READER_H
#define KARIN_RACINGEVOLUTION3D_MESH_READER_H

#include "netlizard.h"

typedef struct _RE3D_Mesh
{
	array *vertex;
	array *texcoord;
	array *index;
	array *strip;
	float translation[3];
	int tex_index;
	unsigned int primitive;
} RE3D_Mesh;

typedef struct _RE3D_Model
{
	array *meshes;
	array *texes;
} RE3D_Model;

int nlIsRE3DMeshFile(const char *name);
int nlIsRE3DMesh(const array *arr);
RE3D_Model * nlReadRE3DMesh(const array *arr);
RE3D_Model * nlReadRE3DMeshFile(const char *name);
void delete_RE3D_Mesh(RE3D_Mesh *mesh);
void delete_RE3D_Model(RE3D_Model *model);

#endif
