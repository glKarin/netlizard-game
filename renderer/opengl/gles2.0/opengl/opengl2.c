#include "opengl2.h"

#include "opengl2_def.h"

#include <string.h>

extern GLuint attrib_stack_current_depth;
extern GLuint modelview_stack_current_depth;
extern GLuint projection_stack_current_depth;
extern GLuint texture_stack_current_depth;
extern GLenum matrix_mode;
extern GLfloat point_size;
extern GLfloat current_color[];
extern GL2_Alpha_Test alpha_test;
extern GL2_Fog fog;

extern GL2_Matrix44 * gl2GetTopMatrixByMode(GLenum mode);

GLenum last_error = GL2_NO_ERROR;

GLenum gl2GetError(GLvoid)
{
	return last_error;
}

GLvoid gl2GetIntegerv(GLenum pname, GLint *params)
{
	switch(pname)
	{
		case GL2_MAX_ATTRIB_STACK_DEPTH:
			*params = ATTRIB_STACK_DEPTH;
			break;
		case GL2_MAX_MODELVIEW_STACK_DEPTH:
			*params = MODELVIEW_STACK_DEPTH;
			break;
		case GL2_MAX_PROJECTION_STACK_DEPTH:
			*params = PROJECTION_STACK_DEPTH;
			break;
		case GL2_MAX_TEXTURE_STACK_DEPTH:
			*params = TEXTURE_STACK_DEPTH;
			break;
		case GL2_ATTRIB_STACK_DEPTH:
			*params = attrib_stack_current_depth;
			break;
		case GL2_MODELVIEW_STACK_DEPTH:
			*params = modelview_stack_current_depth;
			break;
		case GL2_PROJECTION_STACK_DEPTH:
			*params = projection_stack_current_depth;
			break;
		case GL2_TEXTURE_STACK_DEPTH:
			*params = texture_stack_current_depth;
			break;
		case GL2_MATRIX_MODE:
			*params = matrix_mode;
			break;
		default:
			glGetIntegerv(pname, params);
			break;
	}
}

GLvoid gl2GetFloatv(GLenum pname, GLfloat *params)
{
	GL2_Matrix44 *m = NULL;
	switch(pname)
	{
		case GL2_CURRENT_COLOR:
			arrcpy4(params, current_color);
			break;
		case GL2_MODELVIEW_MATRIX:
			m = gl2GetTopMatrixByMode(GL2_MODELVIEW);
			arrcpy16(params, m->m);
			break;
		case GL2_PROJECTION_MATRIX:
			m = gl2GetTopMatrixByMode(GL2_PROJECTION);
			arrcpy16(params, m->m);
			break;
		case GL2_TEXTURE_MATRIX:
			break;
		default:
			glGetFloatv(pname, params);
			break;
	}
}

GLvoid gl2Enable(GLenum t)
{
	switch(t)
	{
		case GL2_POINT_SMOOTH:
		case GL2_LINE_SMOOTH:
			break;
		case GL2_ALPHA_TEST:
			alpha_test.enabled = GL_TRUE;
			break;
		case GL2_FOG:
			fog.enabled = GL_TRUE;
			break;
		default:
			glEnable(t);
			break;
	}
}

GLvoid gl2Disable(GLenum t)
{
	switch(t)
	{
		case GL2_POINT_SMOOTH:
		case GL2_LINE_SMOOTH:
			break;
		case GL2_ALPHA_TEST:
			alpha_test.enabled = GL_FALSE;
			break;
		case GL2_FOG:
			fog.enabled = GL_FALSE;
			break;
		default:
			glDisable(t);
			break;
	}
}

GLboolean gl2IsEnabled(GLenum t)
{
	switch(t)
	{
		case GL2_POINT_SMOOTH:
		case GL2_LINE_SMOOTH:
			return GL_FALSE;
		case GL2_ALPHA_TEST:
			return alpha_test.enabled;
		case GL2_FOG:
			return fog.enabled;
		default:
			return glIsEnabled(t);
	}
}
