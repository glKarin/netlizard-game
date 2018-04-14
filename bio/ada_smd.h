#ifndef KARIN_ADA_SMD_H
#define KARIN_ADA_SMD_H

#include "ada_smd_struct.h"

#include <stdio.h>

int Ada_ReadSmdFile(ADA_smd *smd, const char *file);

char * Ada_ReadHeader(FILE *is);
int Ada_ReadNode(ADA_Node *node, FILE *is);
int Ada_ReadSkeleton(ADA_Skeleton *skeleton, FILE *is);
int Ada_ReadTriangle(ADA_Triangle *triangle, FILE *is);
int Ada_ReadVertex(ADA_Vertex *vertex, FILE *is);
int Ada_ReadNodeList(ADA_Node_list *list, FILE *is);
//int Ada_ReadSkeletonList(ADA_Skeleton_List *list, FILE *is);
int Ada_ReadFrame(ADA_Frame *frame, FILE *is);
int Ada_ReadFrameList(ADA_Frame_List *list, FILE *is);
int Ada_ReadTriangleList(ADA_Triangle_List *list, FILE *is);
int Ada_ReadSmd(ADA_smd *smd, FILE *is);

void Ada_FreeNode(ADA_Node *node);
void Ada_FreeNodeList(ADA_Node_list *list);
void Ada_FreeFrame(ADA_Frame *frame);
void Ada_FreeFrameList(ADA_Frame_List *list);
void Ada_FreeSkeletonList(ADA_Skeleton_List *list);
void Ada_FreeTriangle(ADA_Triangle *triangle);
void Ada_FreeVertex(ADA_Vertex *vertex);
void Ada_FreeTriangleList(ADA_Triangle_List *list);
void Ada_FreeSmd(ADA_smd * smd);

void Ada_PrintNode(const ADA_Node *node);
void Ada_PrintSkeleton(const ADA_Skeleton *skeleton);
void Ada_PrintVertex(const ADA_Vertex *vertex);
void Ada_PrintTriangle(const ADA_Triangle *triangle);
void Ada_PrintNodeList(const ADA_Node_list *list);
void Ada_PrintSkeletonList(const ADA_Skeleton_List *list);
void Ada_PrintFrame(const ADA_Frame *frame);
void Ada_PrintFrameList(const ADA_Frame_List *list);
void Ada_PrintTriangleList(const ADA_Triangle_List *list);
void Ada_PrintSmd(const ADA_smd *smd);

#endif
