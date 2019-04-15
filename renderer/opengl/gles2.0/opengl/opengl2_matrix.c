#include "opengl2.h"

#include "opengl2_def.h"
#include "opengl2_math.h"

#include <string.h>

extern GLenum last_error;
extern GL2_Matrix44 *modelview_matrix;
extern GL2_Matrix44 *projection_matrix;

GLenum matrix_mode = GL2_MODELVIEW;
GLuint modelview_stack_current_depth = 0;
GLuint projection_stack_current_depth = 0;
GLuint texture_stack_current_depth = 0;

GL2_Matrix44 modelview_stack[MODELVIEW_STACK_DEPTH];
GL2_Matrix44 projection_stack[PROJECTION_STACK_DEPTH];
GL2_Matrix44 texture_stack[TEXTURE_STACK_DEPTH];

static GLvoid gl2SetCurrentMatrix()
{
	switch(matrix_mode)
	{
		case GL2_MODELVIEW:
			modelview_matrix = modelview_stack + modelview_stack_current_depth;
		case GL2_PROJECTION:
			projection_matrix = modelview_stack + projection_stack_current_depth;
		case GL2_TEXTURE:
			break;
		default:
			break;
	}
}

static GL2_Matrix44 * gl2SeekMatrix(GLint offset)
{
	switch(matrix_mode)
	{
		case GL2_MODELVIEW:
			if(modelview_stack_current_depth + offset < MODELVIEW_STACK_DEPTH)
				return modelview_stack + (modelview_stack_current_depth + offset);
			break;
		case GL2_PROJECTION:
			if(projection_stack_current_depth + offset < PROJECTION_STACK_DEPTH)
				return projection_stack + (projection_stack_current_depth + offset);
			break;
		case GL2_TEXTURE:
			if(texture_stack_current_depth + offset < TEXTURE_STACK_DEPTH)
				return texture_stack + (texture_stack_current_depth + offset);
			break;
		default:
			return NULL;
	}
	return NULL;
}

static GLuint * gl2GetCurrentMatrixStackDepth(GLvoid)
{
	switch(matrix_mode)
	{
		case GL2_MODELVIEW:
			return &modelview_stack_current_depth;
		case GL2_PROJECTION:
			return &projection_stack_current_depth;
		case GL2_TEXTURE:
			return &texture_stack_current_depth;
		default:
			return NULL;
	}
}

static GLuint gl2GetMaxMatrixStackDepth(GLvoid)
{
	switch(matrix_mode)
	{
		case GL2_MODELVIEW:
			return MODELVIEW_STACK_DEPTH;
		case GL2_PROJECTION:
			return PROJECTION_STACK_DEPTH;
		case GL2_TEXTURE_STACK_DEPTH:
			return TEXTURE_STACK_DEPTH;
		default:
			return 0;
	}
}

GLvoid gl2MatrixMode(GLenum mode)
{
	if(mode == GL2_MODELVIEW || mode == GL2_PROJECTION || mode == GL2_TEXTURE)
		matrix_mode = mode;
	else
		last_error = GL2_INVALID_ENUM;
}

GL2_Matrix44 * gl2GetTopMatrix()
{
	switch(matrix_mode)
	{
		case GL2_MODELVIEW:
			return modelview_stack + modelview_stack_current_depth;
		case GL2_PROJECTION:
			return projection_stack + projection_stack_current_depth;
		case GL2_TEXTURE:
			return texture_stack + texture_stack_current_depth;
		default:
			return NULL;
	}
}

GLvoid gl2PushMatrix()
{
	GLuint *p = gl2GetCurrentMatrixStackDepth();
	if(!p)
	{
		last_error = GL2_INVALID_ENUM;
		return;
	}
	if(*p >= gl2GetMaxMatrixStackDepth())
	{
		last_error = GL2_STACK_OVERFLOW;
		return;
	}
	(*p)++;
	GL2_Matrix44 *nmat = gl2GetTopMatrix();
	GL2_Matrix44 *mat = gl2SeekMatrix(-1);
	arrcpy16(nmat->m, mat->m);
	//printf("push %d\n", *p);
}

GLvoid gl2PopMatrix(GLvoid)
{
	GLuint *p = gl2GetCurrentMatrixStackDepth();
	if(!p)
	{
		last_error = GL2_INVALID_ENUM;
		return;
	}
	if(*p == 0)
	{
		last_error = GL2_STACK_UNDERFLOW;
		return;
	}
	(*p)--;
	//GL2_Matrix44 *mat = gl2SeekMatrix(1);
	//memset(mat, 0, sizeof(GL2_Matrix44));
	//printf("pop %d\n", *p);
	/*
	float *mat2 = gl2GetTopMatrix()->m;
	PRINT_MATEIX(mat2)
	*/
}

GL2_Matrix44 * gl2GetTopMatrixByMode(GLenum mode)
{
	switch(mode)
	{
		case GL2_MODELVIEW:
			return modelview_stack + modelview_stack_current_depth;
		case GL2_PROJECTION:
			return projection_stack + projection_stack_current_depth;
		case GL2_TEXTURE:
			return texture_stack + texture_stack_current_depth;
		default:
			return NULL;
	}
}

GLvoid gl2InitMatrixStack(GLvoid)
{
	int i;
	for(i = 0; i < MODELVIEW_STACK_DEPTH; i++)
		Mesa_glLoadIdentity(modelview_stack + i);
	for(i = 0; i < PROJECTION_STACK_DEPTH; i++)
		Mesa_glLoadIdentity(projection_stack + i);
	for(i = 0; i < TEXTURE_STACK_DEPTH; i++)
		Mesa_glLoadIdentity(texture_stack + i);
}
