#ifndef KARIN_ADA_PMD_STRUCT_H
#define KARIN_ADA_PMD_STRUCT_H

#include "ada_std.h"

typedef struct _ADA_PMD_Bone_Info
{
	unsigned int bone_id;
	char *bone_name;
} ADA_PMD_Bone_Info;

typedef struct _ADA_PMD_Bone_Info_list
{
	unsigned int bone_count;
	struct _ADA_PMD_Bone_Info *bone_infos;
} ADA_PMD_Bone_Info_List;

typedef struct _ADA_PMD_Material_Info
{
	unsigned int index;
	char *name;
} ADA_PMD_Material_Info;

typedef struct _ADA_PMD_Material_Info_List
{
	unsigned int material_count;
	struct _ADA_PMD_Material_Info *material_infos;
} ADA_PMD_Material_Info_List;

typedef struct _ADA_PMD_Bone
{
	int parent_bone_id;
	float data[26];
} ADA_PMD_Bone;

typedef struct _ADA_PMD_Bone_List
{
	unsigned int bone_count;
	struct _ADA_PMD_Bone *bones;
} ADA_PMD_Bone_List;

typedef struct _ADA_PMD_Vertex // 64 bytes
{
	float position[3];
	float weight0;
	float weight1;
	float bone_id0;
	float bone_id1;
	float normal[3];
	float texcoord[2];
	float color[4];
} ADA_PMD_Vertex;

typedef struct _ADA_PMD_Vertex_List
{
	unsigned int vertex_count;
	struct _ADA_PMD_Vertex *vertices;
} ADA_PMD_Vertex_List;

typedef struct _ADA_PMD_Bone_Transform
{
	unsigned int bone_id;
	float position[3];
} ADA_PMD_Bone_Transform;

typedef struct _ADA_PMD_Bone_Transform_List
{
	unsigned int bone_transform_count;
	struct _ADA_PMD_Bone_Transform *bone_transforms;
} ADA_PMD_Bone_Transform_List;

typedef struct _ADA_PMD_Primitive
{
	int magic; // 64
	struct _ADA_PMD_Vertex_List vertex_list;
} ADA_PMD_Primitive;

typedef struct _ADA_PMD_Primitive_List
{
	unsigned int primitive_count;
	struct _ADA_PMD_Primitive *primitives;
} ADA_PMD_Primitive_List;

typedef struct _ADA_PMD_Mesh
{
	unsigned int index;
	unsigned int texindex_count;
	unsigned int *texindex;
	struct _ADA_PMD_Primitive_List primitive_list;
	struct _ADA_PMD_Bone_Transform_List bone_transform_list;
} ADA_PMD_Mesh;

typedef struct _ADA_PMD_Mesh_List
{
	unsigned int mesh_count;
	struct _ADA_PMD_Mesh *meshes;
} ADA_PMD_Mesh_List;

typedef struct _ADA_PMD_Texture
{
	//unsigned int index;
	char *texture_name;
} ADA_PMD_Texture;

typedef struct _ADA_PMD_Texture_List
{
	unsigned int texture_count;
	struct _ADA_PMD_Texture *textures;
} ADA_PMD_Texture_List;

typedef struct _ADA_PMD_Header
{
	char header[58];
} ADA_PMD_Header;

typedef struct _ADA_pmd
{
	struct _ADA_PMD_Header header;
	struct _ADA_PMD_Bone_Info_list bone_info_list;
	struct _ADA_PMD_Material_Info_List material_info_list;
	struct _ADA_PMD_Bone_List bone_list;
	struct _ADA_PMD_Mesh_List mesh_list;
	struct _ADA_PMD_Texture_List texture_list;
} ADA_pmd;

#endif
