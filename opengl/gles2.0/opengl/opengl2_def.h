#ifndef KARIN_OPENGL2_DEF_H
#define KARIN_OPENGL2_DEF_H

#define ATTRIB_STACK_DEPTH 16
#define MODELVIEW_STACK_DEPTH 16
#define PROJECTION_STACK_DEPTH 2
#define TEXTURE_STACK_DEPTH 2

#define arrcpy16(n, o) {\
	n[0] = o[0]; \
	n[1] = o[1]; \
	n[2] = o[2]; \
	n[3] = o[3]; \
	n[4] = o[4]; \
	n[5] = o[5]; \
	n[6] = o[6]; \
	n[7] = o[7]; \
	n[8] = o[8]; \
	n[9] = o[9]; \
	n[10] = o[10]; \
	n[11] = o[11]; \
	n[12] = o[12]; \
	n[13] = o[13]; \
	n[14] = o[14]; \
	n[15] = o[15]; \
}

#define arrcpy12(n, o) {\
	n[0] = o[0]; \
	n[1] = o[1]; \
	n[2] = o[2]; \
	n[3] = o[3]; \
	n[4] = o[4]; \
	n[5] = o[5]; \
	n[6] = o[6]; \
	n[7] = o[7]; \
	n[8] = o[8]; \
	n[9] = o[9]; \
	n[10] = o[10]; \
	n[11] = o[11]; \
}

#define arrcpy4(n, o) {\
	n[0] = o[0]; \
	n[1] = o[1]; \
	n[2] = o[2]; \
	n[3] = o[3]; \
}

#define PRINT_MATEIX(m) \
	int m##_i; \
for(m##_i = 0; m##_i < 16; m##_i++) \
{ \
	if(m##_i == 0) \
	printf("#####################\n"); \
	printf("%.2f", m[m##_i]); \
	if(m##_i % 4 == 3) \
	printf("\n"); \
	else \
	printf(" "); \
}

typedef struct _GL2_Matrix44
{
	float m[16];
} GL2_Matrix44;

typedef struct _GL2_Alpha_Test
{
	unsigned char enabled;
	unsigned int func;
	float ref;
} GL2_Alpha_Test;

typedef struct _GL2_Fog
{
	unsigned char enabled;
	unsigned int mode;
	float density;
	float start;
	float end;
	float color[4];
} GL2_Fog;

#endif
