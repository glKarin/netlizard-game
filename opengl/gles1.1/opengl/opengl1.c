#include "opengl1.h"

#ifdef _HARMATTAN_OPENGLES
#include <string.h>

#define ATTRIB_STACK_DEPTH 64

typedef struct _OpenGL_scissor_attrib
{
	GLboolean scissor_enabled;
	GLint scissor_box[4];
} OpenGL_scissor_attrib;

typedef struct _OpenGL_current_attrib
{
	GLfloat rgba_color[4];
	//GLfloat raster_pos[4];
} OpenGL_current_attrib;

typedef struct _OpenGL_line_attrib
{
	GLboolean line_smooth;
	GLfloat line_width;
} OpenGL_line_attrib;

typedef struct _OpenGL_point_attrib
{
	GLboolean point_smooth;
	GLfloat point_size;
} OpenGL_point_attrib;

typedef struct _OpenGL_polygon_attrib
{
	GLboolean cullface_enabled;
} OpenGL_polygon_attrib;

typedef struct _OpenGL_attrib
{
	GLbitfield mask;
	OpenGL_current_attrib current;
	OpenGL_line_attrib line;
	OpenGL_point_attrib point;
	OpenGL_polygon_attrib polygon;
	OpenGL_scissor_attrib scissor;
} OpenGL_attrib;

static GLuint attrib_stack_current_depth = 0;
static OpenGL_attrib attrib_stack[ATTRIB_STACK_DEPTH];
static GLenum last_error = GL_NO_ERROR;

GLvoid glkPushAttrib(GLbitfield mask)
{
	if(attrib_stack_current_depth >= GL_ATTRIB_STACK_DEPTH)
	{
		last_error = GL_STACK_OVERFLOW;
		return;
	}
	attrib_stack_current_depth++;
	attrib_stack[attrib_stack_current_depth - 1].mask = mask;
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_CURRENT_BIT)
	{
		glGetFloatv(GL_CURRENT_COLOR, attrib_stack[attrib_stack_current_depth - 1].current.rgba_color);
		//glGetFloatv(GL_CURRENT_RASTER_POSITION, attrib_stack[attrib_stack_current_depth - 1].current.raster_pos);
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_LINE_BIT)
	{
		glGetFloatv(GL_LINE_WIDTH, &attrib_stack[attrib_stack_current_depth - 1].line.line_width);
		attrib_stack[attrib_stack_current_depth - 1].line.line_smooth = glIsEnabled(GL_LINE_SMOOTH);
	}
	if(mask & GL_POINT_BIT)
	{
		glGetFloatv(GL_POINT_SIZE, &attrib_stack[attrib_stack_current_depth - 1].point.point_size);
		attrib_stack[attrib_stack_current_depth - 1].point.point_smooth = glIsEnabled(GL_POINT_SMOOTH);
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_POLYGON_BIT)
	{
		attrib_stack[attrib_stack_current_depth - 1].polygon.cullface_enabled = glIsEnabled(GL_CULL_FACE);
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_SCISSOR_BIT)
	{
		attrib_stack[attrib_stack_current_depth - 1].scissor.scissor_enabled = glIsEnabled(GL_SCISSOR_TEST);
		glGetIntegerv(GL_SCISSOR_BOX, attrib_stack[attrib_stack_current_depth - 1].scissor.scissor_box);
	}
#if 0
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_POLYGON_STIPPLE_BIT)
	{
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_PIXEL_MODE_BIT)
	{
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_LIGHTING_BIT)
	{
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_FOG_BIT)
	{
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_DEPTH_BUFFER_BIT)
	{
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_ACCUM_BUFFER_BIT)
	{
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_STENCIL_BUFFER_BIT)
	{
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_VIEWPORT_BIT)
	{
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_TRANSFORM_BIT)
	{
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_ENABLE_BIT)
	{
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_COLOR_BUFFER_BIT)
	{
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_HINT_BIT)
	{
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_EVAL_BIT)
	{
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_LIST_BIT)
	{
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_TEXTURE_BIT)
	{
	}
#endif
	if((mask & 
			(GL_CURRENT_BIT | GL_POINT_BIT | GL_LINE_BIT | GL_POLYGON_BIT | GL_POLYGON_STIPPLE_BIT | GL_PIXEL_MODE_BIT | GL_LIGHTING_BIT | GL_FOG_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_VIEWPORT_BIT | GL_TRANSFORM_BIT | GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_HINT_BIT | GL_EVAL_BIT | GL_LIST_BIT | GL_TEXTURE_BIT | GL_ALL_ATTRIB_BITS)) == 0)
	{
		last_error = GL_INVALID_ENUM;
	}
}

GLvoid glkPopAttrib(GLvoid)
{
	if(attrib_stack_current_depth == 0)
	{
		last_error = GL_STACK_UNDERFLOW;
		return;
	}
	if(attrib_stack[attrib_stack_current_depth - 1].mask & GL_ALL_ATTRIB_BITS || attrib_stack[attrib_stack_current_depth - 1].mask & GL_CURRENT_BIT)
	{
		glColor4fv(attrib_stack[attrib_stack_current_depth - 1].current.rgba_color);
		//glRasterPos4fv(attrib_stack[attrib_stack_current_depth - 1].current.raster_pos);
	}
	if(attrib_stack[attrib_stack_current_depth - 1].mask & GL_ALL_ATTRIB_BITS || attrib_stack[attrib_stack_current_depth - 1].mask & GL_LINE_BIT)
	{
		glLineWidth(attrib_stack[attrib_stack_current_depth - 1].line.line_width);
		if(attrib_stack[attrib_stack_current_depth - 1].line.line_smooth != glIsEnabled(GL_LINE_SMOOTH))
		{
			if(attrib_stack[attrib_stack_current_depth - 1].line.line_smooth)
				glEnable(GL_LINE_SMOOTH);
			else
				glDisable(GL_LINE_SMOOTH);
		}
	}
	if(attrib_stack[attrib_stack_current_depth - 1].mask & GL_ALL_ATTRIB_BITS || attrib_stack[attrib_stack_current_depth - 1].mask & GL_POINT_BIT)
	{
		glPointSize(attrib_stack[attrib_stack_current_depth - 1].point.point_size);
		if(attrib_stack[attrib_stack_current_depth - 1].point.point_smooth != glIsEnabled(GL_POINT_SMOOTH))
		{
			if(attrib_stack[attrib_stack_current_depth - 1].point.point_smooth)
				glEnable(GL_POINT_SMOOTH);
			else
				glDisable(GL_POINT_SMOOTH);
		}
	}
	if(attrib_stack[attrib_stack_current_depth - 1].mask & GL_ALL_ATTRIB_BITS || attrib_stack[attrib_stack_current_depth - 1].mask & GL_POLYGON_BIT)
	{
		if(attrib_stack[attrib_stack_current_depth - 1].polygon.cullface_enabled != glIsEnabled(GL_CULL_FACE))
		{
			if(attrib_stack[attrib_stack_current_depth - 1].polygon.cullface_enabled)
				glEnable(GL_CULL_FACE);
			else
				glDisable(GL_CULL_FACE);
		}
	}
	if(attrib_stack[attrib_stack_current_depth - 1].mask & GL_ALL_ATTRIB_BITS || attrib_stack[attrib_stack_current_depth - 1].mask & GL_SCISSOR_BIT)
	{
		if(attrib_stack[attrib_stack_current_depth - 1].scissor.scissor_enabled != glIsEnabled(GL_SCISSOR_TEST))
		{
			if(attrib_stack[attrib_stack_current_depth - 1].scissor.scissor_enabled)
				glEnable(GL_SCISSOR_TEST);
			else
				glDisable(GL_SCISSOR_TEST);
		}
		glScissor(attrib_stack[attrib_stack_current_depth - 1].scissor.scissor_box[0], attrib_stack[attrib_stack_current_depth - 1].scissor.scissor_box[1], attrib_stack[attrib_stack_current_depth - 1].scissor.scissor_box[2], attrib_stack[attrib_stack_current_depth - 1].scissor.scissor_box[3]);
	}
	memset(attrib_stack + (attrib_stack_current_depth - 1), 0, sizeof(OpenGL_attrib));
	attrib_stack_current_depth--;
}

GLvoid glkGetIntegerv(GLenum pname, GLint *params)
{
	switch(pname)
	{
		case GL_MAX_ATTRIB_STACK_DEPTH:
			*params = ATTRIB_STACK_DEPTH;
			break;
		case GL_ATTRIB_STACK_DEPTH:
			*params = attrib_stack_current_depth;
			break;
		default:
			last_error = GL_INVALID_ENUM;
			break;
	}
}

GLenum glkGetError(GLvoid)
{
	return last_error;
}

#endif
