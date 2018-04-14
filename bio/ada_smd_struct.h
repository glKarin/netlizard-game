#ifndef KARIN_ADA_STRUCT_H
#define KARIN_ADA_STRUCT_H

#include "ada_std.h"

#define NODE_BEGIN "nodes"
#define SKELETON_BEGIN "skeleton"
#define TIME_BEGIN "time"
#define TRIANGLE_BEGIN "triangles"
#define END "end"

typedef struct _ADA_Node
{
	int bone_id;
	char *bone_name;
	int parent_bone_id;
} ADA_Node;

typedef struct _ADA_Node_List
{
	unsigned int node_count;
	struct _ADA_Node *nodes;
} ADA_Node_list;

typedef struct _ADA_Skeleton
{
	int bone_id;
	float position[3];
	float rotation[3]; // radius
} ADA_Skeleton;

typedef struct _ADA_Skeleton_List
{
	unsigned int skeleton_count;
	struct _ADA_Skeleton *skeletons;
} ADA_Skeleton_List;

typedef struct _ADA_Frame
{
	int time;
	ADA_Skeleton_List skeleton_list;
} ADA_Frame;

typedef struct _ADA_Frame_List
{
	unsigned int frame_count;
	struct _ADA_Frame *frames;
} ADA_Frame_List;

typedef struct _ADA_Bone_Info
{
	int bone_id;
	clampf_t bone_weight;
} ADA_Bone_Info;

typedef struct _ADA_Vertex
{
	int parent_bone_id;
	float position[3];
	clampf_t normal[3]; 
	clampf_t texcoord[2]; // UV
	unsigned int bone_count;
	struct _ADA_Bone_Info *bones;
} ADA_Vertex;

typedef struct _ADA_Triangle
{
	char *texture_file;
	struct _ADA_Vertex vertex[3];
} ADA_Triangle;

typedef struct _ADA_Triangle_List
{
	unsigned int triangle_count;
	struct _ADA_Triangle *triangles;
} ADA_Triangle_List;

typedef struct _ADA_smd
{
	char *header;
	struct _ADA_Node_List node_list;
	struct _ADA_Frame_List frame_list;
	struct _ADA_Triangle_List triangle_list;
} ADA_smd;

#endif
