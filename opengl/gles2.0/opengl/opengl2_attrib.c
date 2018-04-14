#include "opengl2.h"

#include "opengl2_def.h"

#include <string.h>

extern GLenum last_error;

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

GLuint attrib_stack_current_depth = 0;
static OpenGL_attrib attrib_stack[ATTRIB_STACK_DEPTH];

GLvoid gl2PushAttrib(GLbitfield mask)
{
	if(attrib_stack_current_depth >= GL2_ATTRIB_STACK_DEPTH)
	{
		last_error = GL2_STACK_OVERFLOW;
		return;
	}
	attrib_stack_current_depth++;
	attrib_stack[attrib_stack_current_depth - 1].mask = mask;
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_CURRENT_BIT)
	{
		gl2GetFloatv(GL2_CURRENT_COLOR, attrib_stack[attrib_stack_current_depth - 1].current.rgba_color);
		//glG2etFloatv(GL2_CURRENT_RASTER_POSITION, attrib_stack[attrib_stack_current_depth - 1].current.raster_pos);
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_LINE_BIT)
	{
		glGetFloatv(GL_LINE_WIDTH, &attrib_stack[attrib_stack_current_depth - 1].line.line_width);
		attrib_stack[attrib_stack_current_depth - 1].line.line_smooth = gl2IsEnabled(GL2_LINE_SMOOTH);
	}
	if(mask & GL2_POINT_BIT)
	{
		gl2GetFloatv(GL2_POINT_SIZE, &attrib_stack[attrib_stack_current_depth - 1].point.point_size);
		attrib_stack[attrib_stack_current_depth - 1].point.point_smooth = gl2IsEnabled(GL2_POINT_SMOOTH);
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_POLYGON_BIT)
	{
		attrib_stack[attrib_stack_current_depth - 1].polygon.cullface_enabled = glIsEnabled(GL_CULL_FACE);
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_SCISSOR_BIT)
	{
		attrib_stack[attrib_stack_current_depth - 1].scissor.scissor_enabled = glIsEnabled(GL_SCISSOR_TEST);
		glGetIntegerv(GL_SCISSOR_BOX, attrib_stack[attrib_stack_current_depth - 1].scissor.scissor_box);
	}
#if 0
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_POLYGON_STIPPLE_BIT)
	{
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_PIXEL_MODE_BIT)
	{
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_LIGHTING_BIT)
	{
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_FOG_BIT)
	{
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_DEPTH_BUFFER_BIT)
	{
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_ACCUM_BUFFER_BIT)
	{
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_STENCIL_BUFFER_BIT)
	{
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_VIEWPORT_BIT)
	{
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_TRANSFORM_BIT)
	{
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_ENABLE_BIT)
	{
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_COLOR_BUFFER_BIT)
	{
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_HINT_BIT)
	{
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_EVAL_BIT)
	{
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_LIST_BIT)
	{
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_TEXTURE_BIT)
	{
	}
#endif
	if((mask & 
			(GL2_CURRENT_BIT | GL2_POINT_BIT | GL2_LINE_BIT | GL2_POLYGON_BIT | GL2_POLYGON_STIPPLE_BIT | GL2_PIXEL_MODE_BIT | GL2_LIGHTING_BIT | GL2_FOG_BIT | GL2_DEPTH_BUFFER_BIT | GL2_ACCUM_BUFFER_BIT | GL2_STENCIL_BUFFER_BIT | GL2_VIEWPORT_BIT | GL2_TRANSFORM_BIT | GL2_ENABLE_BIT | GL2_COLOR_BUFFER_BIT | GL2_HINT_BIT | GL2_EVAL_BIT | GL2_LIST_BIT | GL2_TEXTURE_BIT | GL2_ALL_ATTRIB_BITS)) == 0)
	{
		last_error = GL2_INVALID_ENUM;
	}
}

GLvoid gl2PopAttrib(GLvoid)
{
	if(attrib_stack_current_depth == 0)
	{
		last_error = GL2_STACK_UNDERFLOW;
		return;
	}
	if(attrib_stack[attrib_stack_current_depth - 1].mask & GL2_ALL_ATTRIB_BITS || attrib_stack[attrib_stack_current_depth - 1].mask & GL2_CURRENT_BIT)
	{
		glColor4fv(attrib_stack[attrib_stack_current_depth - 1].current.rgba_color);
		//glRasterPos4fv(attrib_stack[attrib_stack_current_depth - 1].current.raster_pos);
	}
	if(attrib_stack[attrib_stack_current_depth - 1].mask & GL2_ALL_ATTRIB_BITS || attrib_stack[attrib_stack_current_depth - 1].mask & GL2_LINE_BIT)
	{
		glLineWidth(attrib_stack[attrib_stack_current_depth - 1].line.line_width);
		if(attrib_stack[attrib_stack_current_depth - 1].line.line_smooth != gl2IsEnabled(GL2_LINE_SMOOTH))
		{
			if(attrib_stack[attrib_stack_current_depth - 1].line.line_smooth)
				gl2Enable(GL2_LINE_SMOOTH);
			else
				gl2Disable(GL2_LINE_SMOOTH);
		}
	}
	if(attrib_stack[attrib_stack_current_depth - 1].mask & GL2_ALL_ATTRIB_BITS || attrib_stack[attrib_stack_current_depth - 1].mask & GL2_POINT_BIT)
	{
		glPointSize(attrib_stack[attrib_stack_current_depth - 1].point.point_size);
		if(attrib_stack[attrib_stack_current_depth - 1].point.point_smooth != gl2IsEnabled(GL2_POINT_SMOOTH))
		{
			if(attrib_stack[attrib_stack_current_depth - 1].point.point_smooth)
				gl2Enable(GL2_POINT_SMOOTH);
			else
				gl2Disable(GL2_POINT_SMOOTH);
		}
	}
	if(attrib_stack[attrib_stack_current_depth - 1].mask & GL2_ALL_ATTRIB_BITS || attrib_stack[attrib_stack_current_depth - 1].mask & GL2_POLYGON_BIT)
	{
		if(attrib_stack[attrib_stack_current_depth - 1].polygon.cullface_enabled != glIsEnabled(GL_CULL_FACE))
		{
			if(attrib_stack[attrib_stack_current_depth - 1].polygon.cullface_enabled)
				glEnable(GL_CULL_FACE);
			else
				glDisable(GL_CULL_FACE);
		}
	}
	if(attrib_stack[attrib_stack_current_depth - 1].mask & GL2_ALL_ATTRIB_BITS || attrib_stack[attrib_stack_current_depth - 1].mask & GL2_SCISSOR_BIT)
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

