#include "ada_convert.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int Ada_Pmd2Smd(ADA_smd *smd, const ADA_pmd *pmd)
{
	if(!smd || !pmd)
		return 0;

	smd->header = NULL;
	smd->node_list.node_count = pmd->bone_list.bone_count;
	smd->node_list.nodes = calloc(smd->node_list.node_count, sizeof(ADA_Node));
	smd->frame_list.frame_count = 1;
	smd->frame_list.frames = calloc(smd->frame_list.frame_count, sizeof(ADA_Frame));
	smd->frame_list.frames[0].time = 0;
	smd->frame_list.frames[0].skeleton_list.skeleton_count = pmd->bone_list.bone_count;
	smd->frame_list.frames[0].skeleton_list.skeletons = calloc(smd->frame_list.frames[0].skeleton_list.skeleton_count, sizeof(ADA_Skeleton));
	int i;
	for(i = 0; i < pmd->bone_list.bone_count; i++)
	{
		ADA_Node *node = smd->node_list.nodes + i;
		node->bone_id = i;
		node->bone_name = strdup(pmd->bone_info_list.bone_infos[i].bone_name);
		node->parent_bone_id = pmd->bone_list.bones[i].parent_bone_id;

		ADA_Skeleton *skeleton = smd->frame_list.frames[0].skeleton_list.skeletons + i;
		skeleton->bone_id = i;
		skeleton->position[0] = pmd->bone_list.bones[i].data[7];
		skeleton->position[1] = - pmd->bone_list.bones[i].data[9];
		skeleton->position[2] = pmd->bone_list.bones[i].data[8];
		skeleton->rotation[0] = 0.0f;
		skeleton->rotation[1] = 0.0f;
		skeleton->rotation[2] = 0.0f;
	}

	unsigned int vertex_count = 0;
	for(i = 0; i < pmd->mesh_list.mesh_count; i++)
	{
		int j;
		for(j = 0; j < pmd->mesh_list.meshes[i].primitive_list.primitive_count; j++)
			vertex_count += pmd->mesh_list.meshes[i].primitive_list.primitives[j].vertex_list.vertex_count;
	}
	smd->triangle_list.triangle_count = vertex_count / 3;
	smd->triangle_list.triangles = calloc(smd->triangle_list.triangle_count, sizeof(ADA_Triangle));
	int triangle_i = 0;
	for(i = 0; i < pmd->mesh_list.mesh_count; i++)
	{
		int j;
		for(j = 0; j < pmd->mesh_list.meshes[i].primitive_list.primitive_count; j++)
		{
			int k;
			for(k = 0; k < pmd->mesh_list.meshes[i].primitive_list.primitives[j].vertex_list.vertex_count; k += 3)
			{
				ADA_Vertex *vertex = smd->triangle_list.triangles[triangle_i].vertex;
				ADA_PMD_Vertex *pmd_vertex = pmd->mesh_list.meshes[i].primitive_list.primitives[j].vertex_list.vertices;
				smd->triangle_list.triangles[triangle_i].texture_file = strdup(pmd->texture_list.textures[i].texture_name);
				int l;
				for(l = 0; l < 3; l++)
				{
					vertex[l].parent_bone_id = 0;
					vertex[l].position[0] = pmd_vertex[k + l].position[0];
					vertex[l].position[1] = - pmd_vertex[k + l].position[2];
					vertex[l].position[2] = pmd_vertex[k + l].position[1];
					vertex[l].normal[0] = pmd_vertex[k + l].normal[0];
					vertex[l].normal[1] = - pmd_vertex[k + l].normal[2];
					vertex[l].normal[2] = pmd_vertex[k + l].normal[1];
					vertex[l].texcoord[0] = pmd_vertex[k + l].texcoord[0];
					vertex[l].texcoord[1] = pmd_vertex[k + l].texcoord[1];
					vertex[l].bone_count = pmd_vertex[k + l].weight0 == 1.0f ? 1 : 2;
					vertex[l].bones = calloc(vertex[l].bone_count, sizeof(ADA_Bone_Info));
					vertex[l].bones[0].bone_id = pmd->mesh_list.meshes[i].bone_transform_list.bone_transforms[(unsigned int)pmd_vertex[k + l].bone_id0 / 3].bone_id;
					vertex[l].bones[0].bone_weight = pmd_vertex[k + l].weight0;
					if(vertex[l].bone_count == 2)
					{
						vertex[l].bones[1].bone_id = pmd->mesh_list.meshes[i].bone_transform_list.bone_transforms[(unsigned int)pmd_vertex[k + l].bone_id1 / 3].bone_id;
						vertex[l].bones[1].bone_weight = pmd_vertex[k + l].weight1;
					}
				}
				triangle_i++;
			}
		}
	}
	return 1;
}
