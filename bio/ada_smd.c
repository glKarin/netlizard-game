#include "ada_smd.h"
#include "ada_util.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ----------------------- READ -------------------- */

char * Ada_ReadHeader(FILE *is)
{
	char *str = Ada_ReadLine(is);
	return str;
}

int Ada_ReadSmdFile(ADA_smd *smd, const char *file)
{
	if(!smd || !file)
		return 0;
	FILE *is = fopen(file, "r");
	if(!is)
		return 0;
	int b = Ada_ReadSmd(smd, is);
	fclose(is);
	//Ada_PrintSmd(smd);
	return b;
}

int Ada_ReadSmd(ADA_smd *smd, FILE *is)
{
	if(!smd || !is)
		return 0;
	memset(smd , 0, sizeof(ADA_smd));
	smd -> header = Ada_ReadHeader(is);
	Ada_ReadNodeList(&smd -> node_list, is);
	Ada_ReadFrameList(&smd -> frame_list, is);
	Ada_ReadTriangleList(&smd -> triangle_list, is);
	return 1;
}

int Ada_ReadNode(ADA_Node *node, FILE *is)
{
	if(!node || !is)
		return 0;
	char *str = Ada_ReadLine(is);
	if(!str)
		return 0;
	char *p = str;
	int c = 0;
	Ada_ReadInt(p, &node -> bone_id, &c);
	p += c;
	c = 0;
	Ada_ReadString(p, &node -> bone_name, &c);
	p += c;
	c = 0;
	Ada_ReadInt(p, &node -> parent_bone_id, &c);
	free(str);
	return 1;
}

int Ada_ReadNodeList(ADA_Node_list *list, FILE *is)
{
	if(!list || !is)
		return 0;
	long start = ftell(is);
	char *str = Ada_ReadLine(is);
	if(!str)
		return 0;
	if(strcasecmp(str, NODE_BEGIN) != 0)
	{
		fseek(is, start, SEEK_SET);
		fprintf(stderr, "not a node block data\n");
		free(str);
		return 0;
	}
	free(str);
	int res = 1;
	long start2 = ftell(is);
	int count = 0;
	while(1)
	{
		str = Ada_ReadLine(is);
		if(!str)
		{
			fprintf(stderr, "node block data not a end flag\n");
			free(str);
			res = 0;
			break;
		}
		if(strcasecmp(str, END) == 0)
		{
			free(str);
			break;
		}
		count++;
		free(str);
	}
	if(res == 0)
	{
		fseek(is, start, SEEK_SET);
		return 0;
	}
	fseek(is, start2, SEEK_SET);
	list -> node_count = count;
	list -> nodes = calloc(list -> node_count, sizeof(ADA_Node));
	int i;
	for(i = 0; i < list -> node_count; i++)
	{
		Ada_ReadNode(list -> nodes + i, is);
	}
	Ada_SkipLine(is);
	return 1;
}

int Ada_ReadSkeleton(ADA_Skeleton *skeleton, FILE *is)
{
	if(!skeleton || !is)
		return 0;
	char *str = Ada_ReadLine(is);
	if(!str)
		return 0;
	char *p = str;
	int c = 0;
	Ada_ReadInt(p, &skeleton -> bone_id, &c);
	p += c;
	int i;
	for(i = 0; i < 3; i++)
	{
		c = 0;
		Ada_ReadFloat(p, skeleton -> position + i, &c);
		p += c;
	}
	for(i = 0; i < 3; i++)
	{
		c = 0;
		Ada_ReadFloat(p, skeleton -> rotation + i, &c);
		p += c;
	}
	free(str);
	return 1;
}

int Ada_ReadFrame(ADA_Frame *frame, FILE *is)
{
	if(!frame || !is)
		return 0;
	long start = ftell(is);
	char *str = Ada_ReadLine(is);
	if(!str)
		return 0;
	if(strncasecmp(str, TIME_BEGIN, strlen(TIME_BEGIN)) != 0)
	{
		fseek(is, start, SEEK_SET);
		fprintf(stderr, "not a frame block data.\n");
		free(str);
		return 0;
	}
	int time = -1;
	if(Ada_ReadInt(str + strlen(TIME_BEGIN), &time, NULL) == 0)
	{
		fseek(is, start, SEEK_SET);
		fprintf(stderr, "no frame id.\n");
		free(str);
		return 0;
	}
	free(str);
	int res = 1;
	long start2 = ftell(is);
	int count = 0;
	while(1)
	{
		str = Ada_ReadLine(is);
		if(!str)
		{
			fprintf(stderr, "frame block data not a end flag\n");
			free(str);
			res = 0;
			break;
		}
		if(strcasecmp(str, END) == 0 || strncasecmp(str, TIME_BEGIN, strlen(TIME_BEGIN)) == 0)
		{
			free(str);
			break;
		}
		count++;
		free(str);
	}
	if(res == 0)
	{
		fseek(is, start, SEEK_SET);
		return 0;
	}
	fseek(is, start2, SEEK_SET);
	frame -> time = time;
	frame -> skeleton_list.skeleton_count = count;
	frame -> skeleton_list.skeletons = calloc(frame -> skeleton_list.skeleton_count, sizeof(ADA_Skeleton));
	int i;
	for(i = 0; i < frame -> skeleton_list.skeleton_count; i++)
	{
		Ada_ReadSkeleton(frame -> skeleton_list.skeletons + i, is);
	}
	return 1;
}

int Ada_ReadFrameList(ADA_Frame_List *list, FILE *is)
{
	if(!list || !is)
		return 0;
	long start = ftell(is);
	char *str = Ada_ReadLine(is);
	if(!str)
		return 0;
	if(strcasecmp(str, SKELETON_BEGIN) != 0)
	{
		fseek(is, start, SEEK_SET);
		fprintf(stderr, "not a skeleton block data\n");
		free(str);
		return 0;
	}
	free(str);
	int res = 1;
	long start2 = ftell(is);
	int count = 0;
	while(1)
	{
		str = Ada_ReadLine(is);
		if(!str)
		{
			fprintf(stderr, "skeleton block data not a end flag\n");
			free(str);
			res = 0;
			break;
		}
		if(strcasecmp(str, END) == 0)
		{
			free(str);
			break;
		}
		if(strncasecmp(str, TIME_BEGIN, strlen(TIME_BEGIN)) == 0)
		{
			count++;
		}
		free(str);
	}
	if(res == 0)
	{
		fseek(is, start, SEEK_SET);
		return 0;
	}
	fseek(is, start2, SEEK_SET);
	list -> frame_count = count;
	list -> frames = calloc(list -> frame_count, sizeof(ADA_Frame));
	int i;
	for(i = 0; i < list -> frame_count; i++)
	{
		Ada_ReadFrame(list -> frames + i, is);
	}
	Ada_SkipLine(is);
	return 1;
}

int Ada_ReadVertex(ADA_Vertex *vertex, FILE *is)
{
	if(!vertex || !is)
		return 0;
	char *str = Ada_ReadLine(is);
	if(!str)
		return 0;
	char *p = str;
	int c = 0;
	Ada_ReadInt(p, &vertex -> parent_bone_id, &c);
	p += c;
	int i;
	for(i = 0; i < 3; i++)
	{
		c = 0;
		Ada_ReadFloat(p, vertex -> position + i, &c);
		p += c;
	}
	for(i = 0; i < 3; i++)
	{
		c = 0;
		Ada_ReadFloat(p, vertex -> normal + i, &c);
		p += c;
	}
	for(i = 0; i < 2; i++)
	{
		c = 0;
		Ada_ReadFloat(p, vertex -> texcoord + i, &c);
		p += c;
	}
	c = 0;
	Ada_ReadInt(p, (int *)&vertex -> bone_count, &c);
	p += c;
	vertex -> bones = calloc(vertex -> bone_count, sizeof(ADA_Bone_Info));
	for(i = 0; i < vertex -> bone_count; i++)
	{
		c = 0;
		Ada_ReadInt(p, &vertex -> bones[i].bone_id, &c);
		p += c;
		c = 0;
		Ada_ReadFloat(p, &vertex -> bones[i].bone_weight, &c);
		p += c;
	}
	free(str);
	return 1;
}

int Ada_ReadTriangle(ADA_Triangle *triangle, FILE *is)
{
	if(!triangle || !is)
		return 0;
	triangle -> texture_file = Ada_ReadLine(is);
	int i;
	for(i = 0; i < 3; i++)
	{
		Ada_ReadVertex(triangle -> vertex + i, is);
	}
	return 1;
}

int Ada_ReadTriangleList(ADA_Triangle_List *list, FILE *is)
{
	if(!list || !is)
		return 0;
	long start = ftell(is);
	char *str = Ada_ReadLine(is);
	if(!str)
		return 0;
	if(strcasecmp(str, TRIANGLE_BEGIN) != 0)
	{
		fseek(is, start, SEEK_SET);
		fprintf(stderr, "not a triangle block data\n");
		free(str);
		return 0;
	}
	free(str);
	int res = 1;
	long start2 = ftell(is);
	int count = 0;
	while(1)
	{
		str = Ada_ReadLine(is);
		if(!str)
		{
			fprintf(stderr, "triangle block data not a end flag\n");
			free(str);
			res = 0;
			break;
		}
		if(strcasecmp(str, END) == 0)
		{
			free(str);
			break;
		}
		int res = 1;
		char *p = str;
		while(*p)
		{
			if(isspace(*p))
			{
				res = 0;
				break;
			}
			p++;
		}
		if(res)
		{
			count++;
		}
		free(str);
	}
	if(res == 0)
	{
		fseek(is, start, SEEK_SET);
		return 0;
	}
	fseek(is, start2, SEEK_SET);
	list -> triangle_count = count;
	list -> triangles = calloc(list -> triangle_count, sizeof(ADA_Triangle));
	int i;
	for(i = 0; i < list -> triangle_count; i++)
	{
		Ada_ReadTriangle(list -> triangles + i, is);
	}
	Ada_SkipLine(is);
	return 1;
}

/* ------------------ FREE ---------------------- */

void Ada_FreeNode(ADA_Node *node)
{
	if(!node)
		return;
	ADA_FREE(node -> bone_name)
}

void Ada_FreeNodeList(ADA_Node_list *list)
{
	if(!list)
		return;
	if(!list -> nodes)
		return;
	int i;
	for(i = 0; i < list -> node_count; i++)
		Ada_FreeNode(list -> nodes + i);
	free(list -> nodes);
}

void Ada_FreeFrame(ADA_Frame *frame)
{
	if(!frame)
		return;
	Ada_FreeSkeletonList(&frame -> skeleton_list);
}

void Ada_FreeFrameList(ADA_Frame_List *list)
{
	if(!list)
		return;
	if(!list -> frames)
		return;
	int i;
	for(i = 0; i < list -> frame_count; i++)
		Ada_FreeFrame(list -> frames + i);
	free(list -> frames);
}

void Ada_FreeSkeletonList(ADA_Skeleton_List *list)
{
	if(!list)
		return;
	if(!list -> skeletons)
		return;
	free(list -> skeletons);
}

void Ada_FreeTriangle(ADA_Triangle *triangle)
{
	if(!triangle)
		return;
	ADA_FREE(triangle -> texture_file)
	int i;
	for(i = 0; i < 3; i++)
		Ada_FreeVertex(triangle -> vertex + i);
}

void Ada_FreeVertex(ADA_Vertex *vertex)
{
	if(!vertex)
		return;
	ADA_FREE(vertex -> bones)
}

void Ada_FreeTriangleList(ADA_Triangle_List *list)
{
	if(!list)
		return;
	if(!list -> triangles)
		return;
	int i;
	for(i = 0; i < list -> triangle_count; i++)
		Ada_FreeTriangle(list -> triangles + i);
	free(list -> triangles);
}

void Ada_FreeSmd(ADA_smd * smd)
{
	if(!smd)
		return;
	ADA_FREE(smd -> header)
	Ada_FreeNodeList(&smd -> node_list);
	Ada_FreeFrameList(&smd -> frame_list);
	Ada_FreeTriangleList(&smd -> triangle_list);
}

/* ---------------------- PRINT ------------------ */
void Ada_PrintNode(const ADA_Node *node)
{
	if(!node)
		return;
	printf("Node -> [%d: %s %d]\n", 
			node -> bone_id, 
			node -> bone_name, 
			node -> parent_bone_id);
}

void Ada_PrintSkeleton(const ADA_Skeleton *skeleton)
{
	if(!skeleton)
		return;
	printf("Skeleton -> [%d: (%f, %f, %f) (%f, %f, %f)]\n", 
			skeleton -> bone_id, 
			skeleton -> position[0], skeleton -> position[1], skeleton -> position[2], 
			skeleton -> rotation[0], skeleton -> rotation[1], skeleton -> rotation[2]);
}

void Ada_PrintVertex(const ADA_Vertex *vertex)
{
	if(!vertex)
		return;
	printf("Vertex -> [%d: (%f, %f, %f) (%f, %f, %f) (%f, %f)", 
			vertex -> parent_bone_id,
			vertex -> position[0], vertex -> position[1], vertex -> position[2], 
			vertex -> normal[0], vertex -> normal[1], vertex -> normal[2], 
			vertex -> texcoord[0], vertex -> texcoord[1]
			);
	printf(" %d (", vertex -> bone_count);
	int i;
	for(i = 0; i < vertex -> bone_count; i++)
	{
		printf("%d - %f", vertex -> bones[i].bone_id, vertex -> bones[i].bone_weight);
		if(i < vertex -> bone_count - 1)
			printf(", ");
		else
			printf(")\n");
	}
}

void Ada_PrintTriangle(const ADA_Triangle *triangle)
{
	if(!triangle)
		return;
	printf("Triangle -> [%s: (\n", triangle -> texture_file);
	int i;
	for(i = 0; i < 3; i++)
	{
		printf("  %d -> ", i);
		Ada_PrintVertex(triangle -> vertex + i);
	}
	printf(")]\n");
}

void Ada_PrintNodeList(const ADA_Node_list *list)
{
	if(!list)
		return;
	printf("------------ adaBegin( ADA_NODE ) ------------\n");
	int i;
	for(i = 0; i < list -> node_count; i++)
		Ada_PrintNode(list -> nodes + i);
	printf("------------ adaEnd( ADA_NODE ) ------------\n");
}

void Ada_PrintSkeletonList(const ADA_Skeleton_List *list)
{
	if(!list)
		return;
	int i;
	for(i = 0; i < list -> skeleton_count; i++)
		Ada_PrintSkeleton(list -> skeletons + i);
}

void Ada_PrintFrame(const ADA_Frame *frame)
{
	if(!frame)
		return;
	printf("------------ adaBegin( ADA_SKELETON ) ------------\n");
	printf("Time -> %d\n", frame -> time);
	int i;
	for(i = 0; i < frame -> skeleton_list.skeleton_count; i++)
		Ada_PrintSkeleton(frame -> skeleton_list.skeletons + i);
	printf("------------ adaEnd( ADA_SKELETON ) ------------\n");
}

void Ada_PrintFrameList(const ADA_Frame_List *list)
{
	if(!list)
		return;
	printf("------------ adaBegin( ADA_FRAME ) ------------\n");
	int i;
	for(i = 0; i < list -> frame_count; i++)
		Ada_PrintFrame(list -> frames + i);
	printf("------------ adaEnd( ADA_FRAME ) ------------\n");
}

void Ada_PrintTriangleList(const ADA_Triangle_List *list)
{
	if(!list)
		return;
	printf("------------ adaBegin( ADA_TRIANGLE ) ------------\n");
	int i;
	for(i = 0; i < list -> triangle_count; i++)
		Ada_PrintTriangle(list -> triangles + i);
	printf("------------ adaEnd( ADA_TRIANGLE ) ------------\n");
}

void Ada_PrintSmd(const ADA_smd *smd)
{
	if(!smd)
		return;
	printf("Header -> %s\n", smd -> header);
	Ada_PrintNodeList(&smd -> node_list);
	Ada_PrintFrameList(&smd -> frame_list);
	Ada_PrintTriangleList(&smd -> triangle_list);
}

