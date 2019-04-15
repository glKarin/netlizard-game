#include "skn_reader.h"
#include "netlizard/nl_util.h"

#include <stdlib.h>
#include <string.h>

static int caitlynReadSknV4(const char *data, int p, Caitlyn_Skn_Model *header);
static int caitlynReadSknV0(const char *data, int p, Caitlyn_Skn_Model *header);
static int caitlynReadSknV1(const char *data, int p, Caitlyn_Skn_Model *header);

Caitlyn_Skn_Model * caitlynReadSknModel(const char *file)
{
	if(!file)
		return NULL;
	array *arr = nlReadFile(file);
	if(!arr)
		return NULL;
	char *data = (char *)(arr -> array);

	Caitlyn_Skn_Model *header = NEW(Caitlyn_Skn_Model);
	ZERO(header, Caitlyn_Skn_Model);

	int s = 0;
	READ_DATA(&header -> magic, data, int, 1, s)
	READ_DATA(&header -> version, data, short, 1, s)
	READ_DATA(&header -> primitive_count, data, short, 1, s)

	printfi(header -> version);
	printfi(header -> primitive_count);

	if(header -> version == 1 || header -> version == 2 || header -> version == 3)
		caitlynReadSknV1(data, s, header);
	else if(header -> version == 0)
		caitlynReadSknV0(data, s, header);
	else if(header -> version == 4)
		caitlynReadSknV4(data, s, header);
	else
	{
		fprintf(stderr, "Unsupported skn version -> %d\n", header -> version);
		free(header);
		header = NULL;
	}

	int k;
	for (k = 0; k < header -> vertex_count; k++)
	{
		Caitlyn_Vertex *i = header -> vertex + k;
		float total = i -> bone_weight[0] + i -> bone_weight[1] + i -> bone_weight[2] + i -> bone_weight[3];
		float error = 1.0 - total;

		if (error != 0.0)
		{
			int j;
			for (j = 0; j < 4; ++j)
			{
				if (i -> bone_weight[j] > 0.0)
				{
					i -> bone_weight[j] += (i -> bone_weight[j] / total) * error;
				}
			}	
		}
	}
	return header;
}

void free_Caitlyn_Skn_model(Caitlyn_Skn_Model *headerPtr)
{
	if(!headerPtr)
		return;
	if(headerPtr -> material)
		free(headerPtr -> material);
	if(headerPtr -> index)
		free(headerPtr -> index);
	if(headerPtr -> vertex)
		free(headerPtr -> vertex);
}

// static

int caitlynReadSknV4(const char *data, int p, Caitlyn_Skn_Model *header)
{
	if(!data || !header)
		return p;
	READ_DATA(&header -> material_count, data, int, 1, p)
	header -> material = NEW_II(Caitlyn_Material, header -> material_count);
	int i;
	for(i = 0; i < header -> material_count; i++)
	{
		READ_DATA(header -> material[i].name, data, char, 64, p)
			printfs(header -> material[i].name);
		READ_DATA(&header -> material[i].start_vertex, data, int, 1, p)
		READ_DATA(&header -> material[i].vertex_count, data, int, 1, p)
		READ_DATA(&header -> material[i].start_index, data, int, 1, p)
		READ_DATA(&header -> material[i].index_count, data, int, 1, p)
	}
	p += 4;
	READ_DATA(&header -> index_count, data, int, 1, p)
	READ_DATA(&header -> vertex_count, data, int, 1, p)
	p += 2 * 24;
	printfi(header -> index_count);
	printfi(header -> vertex_count);
	header -> index = NEW_II(short, header -> index_count);
	READ_DATA(header -> index, data, short, header -> index_count, p)
	header -> vertex = NEW_II(Caitlyn_Vertex, header -> vertex_count);
	READ_DATA(header -> vertex, data, Caitlyn_Vertex, header -> vertex_count, p)
	return p;
}

int caitlynReadSknV1(const char *data, int p, Caitlyn_Skn_Model *header)
{
	if(!data || !header)
		return p;
	READ_DATA(&header -> material_count, data, int, 1, p)
	header -> material = NEW_II(Caitlyn_Material, header -> material_count);
	int i;
	for(i = 0; i < header -> material_count; i++)
	{
		READ_DATA(header -> material[i].name, data, char, 64, p)
		READ_DATA(&header -> material[i].start_vertex, data, int, 1, p)
		READ_DATA(&header -> material[i].vertex_count, data, int, 1, p)
		READ_DATA(&header -> material[i].start_index, data, int, 1, p)
		READ_DATA(&header -> material[i].index_count, data, int, 1, p)
	}
	READ_DATA(&header -> index_count, data, int, 1, p)
	READ_DATA(&header -> vertex_count, data, int, 1, p)
	header -> index = NEW_II(short, header -> index_count);
	READ_DATA(header -> index, data, short, header -> index_count, p)
	header -> vertex = NEW_II(Caitlyn_Vertex, header -> vertex_count);
	READ_DATA(header -> vertex, data, Caitlyn_Vertex, header -> vertex_count, p)
	return p;
}

int caitlynReadSknV0(const char *data, int p, Caitlyn_Skn_Model *header)
{
	header -> material_count = 0;
	header -> material = NULL;
	READ_DATA(&header -> index_count, data, int, 1, p)
	READ_DATA(&header -> vertex_count, data, int, 1, p)
	header -> index = NEW_II(short, header -> index_count);
	READ_DATA(header -> index, data, short, header -> index_count, p)
	header -> vertex = NEW_II(Caitlyn_Vertex, header -> vertex_count);
	READ_DATA(header -> vertex, data, Caitlyn_Vertex, header -> vertex_count, p)
	return p;
}

