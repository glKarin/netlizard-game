#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ada_pmd.h"

static void Ada_FreePMDBoneInfo(ADA_PMD_Bone_Info *info);
static void Ada_FreePMDBoneInfoList(ADA_PMD_Bone_Info_List *list);
static void Ada_FreePMDMaterialInfo(ADA_PMD_Material_Info *info);
static void Ada_FreePMDMaterialInfoList(ADA_PMD_Material_Info_List *list);
static void Ada_FreePMDBoneList(ADA_PMD_Bone_List *list);
static void Ada_FreePMDVertexList(ADA_PMD_Vertex_List *list);
static void Ada_FreePMDBoneTransformList(ADA_PMD_Bone_Transform_List *list);
static void Ada_FreePMDPrimitive(ADA_PMD_Primitive *primitive);
static void Ada_FreePMDPrimitiveList(ADA_PMD_Primitive_List *list);
static void Ada_FreePMDTexture(ADA_PMD_Texture *texture);
static void Ada_FreePMDTextureList(ADA_PMD_Texture_List *list);
static void Ada_FreePMDMesh(ADA_PMD_Mesh *mesh);
static void Ada_FreePMDMeshList(ADA_PMD_Mesh_List *list);

void Ada_FreePMDBoneInfo(ADA_PMD_Bone_Info *info)
{
	if(!info)
		return;
	ADA_FREE(info -> bone_name)
}

void Ada_FreePMDBoneInfoList(ADA_PMD_Bone_Info_List *list)
{
	if(!list)
		return;
	if(!list -> bone_infos)
		return;
	int i;
	for(i = 0; i < list -> bone_count; i++)
		Ada_FreePMDBoneInfo(list -> bone_infos + i);
	free(list -> bone_infos);
	list -> bone_infos = NULL;
}

void Ada_FreePMDMaterialInfo(ADA_PMD_Material_Info *info)
{
	if(!info)
		return;
	ADA_FREE(info -> name)
}

void Ada_FreePMDMaterialInfoList(ADA_PMD_Material_Info_List *list)
{
	if(!list)
		return;
	if(!list -> material_infos)
		return;
	int i;
	for(i = 0; i < list -> material_count; i++)
		Ada_FreePMDMaterialInfo(list -> material_infos + i);
	free(list -> material_infos);
	list -> material_infos = NULL;
}

void Ada_FreePMDBoneList(ADA_PMD_Bone_List *list)
{
	if(!list)
		return;
	ADA_FREE(list -> bones)
}

void Ada_FreePMDVertexList(ADA_PMD_Vertex_List *list)
{
	if(!list)
		return;
	ADA_FREE(list -> vertices)
}

void Ada_FreePMDBoneTransformList(ADA_PMD_Bone_Transform_List *list)
{
	if(!list)
		return;
	ADA_FREE(list -> bone_transforms)
}

void Ada_FreePMDPrimitive(ADA_PMD_Primitive *primitive)
{
	if(!primitive)
		return;
	Ada_FreePMDVertexList(&primitive -> vertex_list);
}

void Ada_FreePMDPrimitiveList(ADA_PMD_Primitive_List *list)
{
	if(!list)
		return;
	if(!list -> primitives)
		return;
	int i;
	for(i = 0; i < list -> primitive_count; i++)
		Ada_FreePMDPrimitive(list -> primitives + i);
	free(list -> primitives);
	list -> primitives = NULL;
}

void Ada_FreePMDMesh(ADA_PMD_Mesh *mesh)
{
	if(!mesh)
		return;
	ADA_FREE(mesh -> texindex)
	Ada_FreePMDPrimitiveList(&mesh -> primitive_list);
	Ada_FreePMDBoneTransformList(&mesh -> bone_transform_list);
}

void Ada_FreePMDMeshList(ADA_PMD_Mesh_List *list)
{
	if(!list)
		return;
	if(!list -> meshes)
		return;
	int i;
	for(i = 0; i < list -> mesh_count; i++)
		Ada_FreePMDMesh(list -> meshes + i);
	free(list -> meshes);
	list -> meshes = NULL;
}

void Ada_FreePMDTexture(ADA_PMD_Texture *texture)
{
	if(!texture)
		return;
	ADA_FREE(texture -> texture_name)
}

void Ada_FreePMDTextureList(ADA_PMD_Texture_List *list)
{
	if(!list)
		return;
	if(!list -> textures)
		return;
	int i;
	for(i = 0; i < list -> texture_count; i++)
		Ada_FreePMDTexture(list -> textures + i);
	free(list -> textures);
	list -> textures = NULL;
}

void Ada_FreePmd(ADA_pmd *pmd)
{
	if(!pmd)
		return;
	Ada_FreePMDBoneInfoList(&pmd -> bone_info_list);
	Ada_FreePMDMaterialInfoList(&pmd -> material_info_list);
	Ada_FreePMDBoneList(&pmd -> bone_list);
	Ada_FreePMDMeshList(&pmd -> mesh_list);
	Ada_FreePMDTextureList(&pmd -> texture_list);
}

int Ada_ReadPmdFile(ADA_pmd *pmd, const char *file)
{
	if(!pmd || !file)
		return 0;
	FILE *is = fopen(file, "rb");
	if(!is)
		return 0;
	int b = Ada_ReadPmd(pmd, is);
	fclose(is);
	//Ada_PrintPmd(pmd);
	return b;
}

int Ada_ReadPmd(ADA_pmd *pmd, FILE *is)
{
	if(!pmd || !is)
		return 0;

	fread(pmd -> header.header, sizeof(char), 58, is); // header

	fread(&pmd -> bone_info_list.bone_count, sizeof(unsigned int), 1, is);
	pmd -> bone_info_list.bone_infos = calloc(pmd -> bone_info_list.bone_count, sizeof(ADA_PMD_Bone_Info));
	int i;
	for(i = 0; i < pmd -> bone_info_list.bone_count; i++)
	{
		unsigned int namelen = 0;
		fread(&namelen, sizeof(unsigned int), 1, is);
		char *name = calloc(namelen + 1, sizeof(char));
		fread(name, sizeof(char), namelen, is);
		name[namelen] = '\0';
		unsigned int index = 0;
		fread(&index, sizeof(unsigned int), 1, is);
		pmd -> bone_info_list.bone_infos[index].bone_id = index;
		pmd -> bone_info_list.bone_infos[index].bone_name = name;
	}

	fread(&pmd -> material_info_list.material_count, sizeof(unsigned int), 1, is);
	pmd -> material_info_list.material_infos = calloc(pmd -> material_info_list.material_count, sizeof(ADA_PMD_Material_Info));
	for(i = 0; i < pmd -> material_info_list.material_count; i++)
	{
		unsigned int namelen = 0;
		fread(&namelen, sizeof(unsigned int), 1, is);
		char *name = calloc(namelen + 1, sizeof(char));
		fread(name, sizeof(char), namelen, is);
		name[namelen] = '\0';
		unsigned int index = 0;
		fread(&index, sizeof(unsigned int), 1, is);
		pmd -> material_info_list.material_infos[index].index = index;
		pmd -> material_info_list.material_infos[index].name = name;
	}

	fseek(is, 4, SEEK_CUR); // zeros

	fread(&pmd -> bone_list.bone_count, sizeof(unsigned int), 1, is);
	pmd -> bone_list.bones = calloc(pmd -> bone_list.bone_count, sizeof(ADA_PMD_Bone));
	for(i = 0; i < pmd -> bone_list.bone_count; i++)
	{
		fread(&pmd -> bone_list.bones[i].parent_bone_id, sizeof(int), 1, is);
		fread(pmd -> bone_list.bones[i].data, sizeof(float), 26, is);
		//printf("%d - %f, %f, %f\n", i, values[7], -values[9], values[8]); // y and z replace
	}

	fread(&pmd -> mesh_list.mesh_count, sizeof(unsigned int), 1, is);
	pmd -> mesh_list.meshes = calloc(pmd -> mesh_list.mesh_count, sizeof(ADA_PMD_Mesh));
	for(i = 0; i < pmd -> mesh_list.mesh_count; i++)
	{
		ADA_PMD_Mesh *mesh = pmd -> mesh_list.meshes + i;
		unsigned int node_i = 0;
		fread(&node_i, sizeof(unsigned int), 1, is);
		mesh -> index = node_i;
		fseek(is, 32, SEEK_CUR); // all zeros
		unsigned int meshes = 0;
		fread(&meshes, sizeof(unsigned int), 1, is);
		unsigned int *texindex = calloc(meshes, sizeof(unsigned int));
		fread(texindex, sizeof(unsigned int), meshes, is);
		mesh -> texindex_count = meshes;
		mesh -> texindex = texindex;
		fseek(is, 4, SEEK_CUR); // zeros
		fseek(is, 4, SEEK_CUR); // number of meshes again

		mesh -> primitive_list.primitive_count = meshes;
		mesh -> primitive_list.primitives = calloc(mesh -> primitive_list.primitive_count, sizeof(ADA_PMD_Primitive));

		int j;
		for(j = 0; j < meshes; j++)
		{
			ADA_PMD_Primitive *primitive = mesh -> primitive_list.primitives + j;
			fread(&primitive -> magic, sizeof(unsigned int), 1, is);
			if(primitive -> magic != 64) // something is wrong
			{
				fprintf(stderr, "error in data %d\n", primitive -> magic);
				// return -1;
			}

			unsigned int groupsize = 0;
			fread(&groupsize, sizeof(unsigned int), 1, is);
			primitive -> vertex_list.vertex_count = groupsize;
			fseek(is, (groupsize + 1) * 2, SEEK_CUR); // predata
			fseek(is, 2, SEEK_CUR); // 2 zeros

			primitive -> vertex_list.vertices = calloc(primitive -> vertex_list.vertex_count, sizeof(ADA_PMD_Vertex));
			int k;
			for(k = 0; k < groupsize; k++)
			{
				fread(primitive -> vertex_list.vertices + k, sizeof(char), 64, is);
			}
		}

		unsigned int num_bones = 0;
		fread(&num_bones, sizeof(unsigned int), 1, is);
		mesh -> bone_transform_list.bone_transform_count = num_bones;
		mesh -> bone_transform_list.bone_transforms = calloc(mesh -> bone_transform_list.bone_transform_count, sizeof(ADA_PMD_Bone_Transform));
		for(j = 0; j < num_bones; j++)
		{
			ADA_PMD_Bone_Transform *transform = mesh -> bone_transform_list.bone_transforms + j;
			fread(&transform -> bone_id, sizeof(unsigned int), 1, is);
			fseek(is, 52, SEEK_CUR); // unused
			float position[4];
			fread(position, sizeof(float), 4, is); // bone's xyz, but redundant
			// float bx = position[0];
			// float bz = position[1];
			// float by = position[2];
			// by = -by; // y and z replace
			memcpy(transform -> position, position, sizeof(float) * 3);
		}
	}

	fread(&pmd -> texture_list.texture_count, sizeof(unsigned int), 1, is);
	pmd -> texture_list.textures = calloc(pmd -> texture_list.texture_count, sizeof(ADA_PMD_Texture));
	for(i = 0; i < pmd -> texture_list.texture_count; i++)
	{
		ADA_PMD_Texture *texture = pmd -> texture_list.textures + i;
		unsigned int filename_size = 0;
		fseek(is, 72, SEEK_CUR); // texture data + other
		fread(&filename_size, sizeof(unsigned int), 1, is);
		texture -> texture_name = calloc(filename_size + 1, sizeof(char));
		fread(texture -> texture_name, sizeof(char), filename_size, is);
		texture -> texture_name[filename_size] = '\0';
	}

	return 1;
}

void Ada_PrintPmd(const ADA_pmd *pmd)
{
	if(!pmd)
		return;
	printf("************************************************************\n");
	int i;
	for(i = 0; i < 58; i++)
		printf("%c", pmd -> header.header[i]);
	printf("\n");
	printf("************************************************************\n");

	printf("[BONE INFO -> %d]\n", pmd -> bone_info_list.bone_count);
	for(i = 0; i < pmd -> bone_info_list.bone_count; i++)
		printf("%d -> %s\n", pmd -> bone_info_list.bone_infos[i].bone_id, pmd -> bone_info_list.bone_infos[i].bone_name);
	printf("************************************************************\n");

	printf("[MATERIAL INFO -> %d]\n", pmd -> material_info_list.material_count);
	for(i = 0; i < pmd -> material_info_list.material_count; i++)
		printf("%d -> %s\n", pmd -> material_info_list.material_infos[i].index, pmd -> material_info_list.material_infos[i].name);
	printf("************************************************************\n");

	printf("[BONE -> %d]\n", pmd -> bone_list.bone_count);
	for(i = 0; i < pmd -> bone_list.bone_count; i++)
	{
		printf("%d -> parent: %d, \n", i, pmd -> bone_list.bones[i].parent_bone_id);
		int j;
		for(j = 0; j < 26; j++)
		{
			if(j == 7)
				printf(" [");
			printf(" %f ", pmd -> bone_list.bones[i].data[j]);
			if(j == 9)
				printf("] ");
		}
		printf("\n");
	}
	printf("************************************************************\n");

	printf("[MESH -> %d]\n", pmd -> mesh_list.mesh_count);
	for(i = 0; i < pmd -> mesh_list.mesh_count; i++)
	{
		const ADA_PMD_Mesh *mesh = pmd -> mesh_list.meshes + i;
		printf("%d -> \n", mesh -> index);

		printf("  tex_index -> %d\n", mesh -> texindex_count);
		int j;
		for(j = 0; j < mesh -> texindex_count; j++)
		{
			if(j == 0)
				printf("    ");
			printf("%d  ", mesh -> texindex[j]);
		}
		printf("\n");

		printf("  primitive -> %d\n", mesh -> primitive_list.primitive_count);
		for(j = 0; j < mesh -> primitive_list.primitive_count; j++)
		{
			const ADA_PMD_Primitive *primitive = mesh -> primitive_list.primitives + j;
			printf("    magic -> %d\n", primitive -> magic);
			printf("    vertex -> %d\n", primitive -> vertex_list.vertex_count);
			int k;
			for(k = 0; k < primitive -> vertex_list.vertex_count; k++)
			{
				const ADA_PMD_Vertex *vertex = primitive -> vertex_list.vertices + k;
				printf("      position[ %f, %f, %f ]  normal[ %f, %f, %f ]  texcoord[ %f, %f ]  color[ %f, %f, %f, %f ]  ", 
						vertex -> position[0], vertex -> position[1], vertex -> position[2], 
						vertex -> normal[0], vertex -> normal[1], vertex -> normal[2], 
						vertex -> texcoord[0], vertex -> texcoord[1],
						vertex -> color[0], vertex -> color[1], vertex -> color[2], vertex -> color[3]);
				// WARNING: float equal
				int effect_count = 0;
				if(vertex -> weight0 == 1.0f)
					effect_count = 1;
				else
					effect_count = 2;
				printf("bone_count -> %d,  bone -> ", effect_count);
				printf("[ bone id -> %d, weight -> %f ]  ", mesh -> bone_transform_list.bone_transforms[(unsigned int)vertex -> bone_id0 / 3].bone_id, vertex -> weight0);
				if(effect_count == 2)
				printf("[ bone id -> %d, weight -> %f ]  ", mesh -> bone_transform_list.bone_transforms[(unsigned int)vertex -> bone_id1 / 3].bone_id, vertex -> weight1);
				printf("\n");
				if(k % 3 == 2)
					printf("\n");
			}
		}

		printf("[BONE TRANSFORM -> %d]\n", mesh -> bone_transform_list.bone_transform_count);
		for(j = 0; j < mesh -> bone_transform_list.bone_transform_count; j++)
		printf("%d -> [ %f, %f, %f ]\n", mesh -> bone_transform_list.bone_transforms[j].bone_id, 
				mesh -> bone_transform_list.bone_transforms[j].position[0],
				mesh -> bone_transform_list.bone_transforms[j].position[1],
				mesh -> bone_transform_list.bone_transforms[j].position[2]);
	}
	printf("************************************************************\n");

	printf("[TEXTURE FILE -> %d]\n", pmd -> texture_list.texture_count);
	for(i = 0; i < pmd -> texture_list.texture_count; i++)
		printf("%d -> %s\n", i, pmd -> texture_list.textures[i].texture_name);
	printf("************************************************************\n");
}

#include "ada_convert.h"
#include "ada_smd.h"
int ddmain()
{
	ADA_pmd pmd;
	ADA_smd smd;
	memset(&pmd, 0, sizeof(ADA_pmd));
	memset(&smd, 0, sizeof(ADA_smd));
	printf("%d\n", Ada_ReadPmdFile(&pmd, "d:/pmd/pl0b0a.pmd"));
	//Ada_PrintPmd(&pmd);
	Ada_Pmd2Smd(&smd, &pmd);
	Ada_PrintSmd(&smd);
	Ada_FreeSmd(&smd);
	Ada_FreePmd(&pmd);
	return 0;
}
