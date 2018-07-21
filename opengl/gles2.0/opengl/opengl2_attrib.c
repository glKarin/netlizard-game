#include "opengl2.h"

#include "opengl2_def.h"

#include <string.h>

extern GLenum last_error;

typedef struct _OpenGL_alphatest_attrib
{
	GLboolean alphatest_enabled;
	GLint alphatest_func;
	GLfloat alphatest_ref;
} OpenGL_alphatest_attrib;

typedef struct _OpenGL_depthtest_attrib
{
	GLboolean depthtest_enabled;
	GLint depthtest_func;
	GLfloat depthtest_ref;
	GLboolean depthmask;
} OpenGL_depthtest_attrib;

typedef struct _OpenGL_blend_attrib
{
	GLboolean blend_enabled;
	GLint blend_src;
	GLint blend_dst;
} OpenGL_blend_attrib;

typedef struct _OpenGL_scissor_attrib
{
	GLboolean scissortest_enabled;
	GLint scissortest_box[4];
} OpenGL_scissortest_attrib;

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
	GLint cullface_mode;
} OpenGL_polygon_attrib;

typedef struct _OpenGL_attrib
{
	GLbitfield mask;
	OpenGL_current_attrib current;
	OpenGL_line_attrib line;
	OpenGL_point_attrib point;
	OpenGL_polygon_attrib polygon;
	OpenGL_scissortest_attrib scissortest;
	OpenGL_alphatest_attrib alphatest;
	OpenGL_depthtest_attrib depthtest;
	OpenGL_blend_attrib blend;
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
	OpenGL_attrib *a = attrib_stack + (attrib_stack_current_depth - 1);
	a->mask = mask;
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_CURRENT_BIT)
	{
		gl2GetFloatv(GL2_CURRENT_COLOR, a->current.rgba_color);
		//glG2etFloatv(GL2_CURRENT_RASTER_POSITION, attrib_stack[attrib_stack_current_depth - 1].current.raster_pos);
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_LINE_BIT)
	{
		glGetFloatv(GL_LINE_WIDTH, &a->line.line_width);
		a->line.line_smooth = gl2IsEnabled(GL2_LINE_SMOOTH);
	}
	if(mask & GL2_POINT_BIT)
	{
		gl2GetFloatv(GL2_POINT_SIZE, &a->point.point_size);
		a->point.point_smooth = gl2IsEnabled(GL2_POINT_SMOOTH);
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_POLYGON_BIT)
	{
		a->polygon.cullface_enabled = glIsEnabled(GL_CULL_FACE);
		glGetIntegerv(GL_CULL_FACE_MODE, &a->polygon.cullface_mode);
	}
	if(mask & GL2_ALL_ATTRIB_BITS || mask & GL2_SCISSOR_BIT)
	{
		a->scissortest.scissortest_enabled = glIsEnabled(GL_SCISSOR_TEST);
		glGetIntegerv(GL_SCISSOR_BOX, a->scissortest.scissortest_box);
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_COLOR_BUFFER_BIT)
	{
		a->alphatest.alphatest_enabled = gl2IsEnabled(GL2_ALPHA_TEST);
		gl2GetIntegerv(GL2_ALPHA_TEST_FUNC, &a->alphatest.alphatest_func);
		gl2GetFloatv(GL2_ALPHA_TEST_REF, &a->alphatest.alphatest_ref);

		a->blend.blend_enabled = glIsEnabled(GL_BLEND);
		glGetIntegerv(GL_BLEND_SRC, &a->blend.blend_src);
		glGetIntegerv(GL_BLEND_DST, &a->blend.blend_dst);
	}
	if(mask & GL_ALL_ATTRIB_BITS || mask & GL_DEPTH_BUFFER_BIT)
	{
		a->depthtest.depthtest_enabled = glIsEnabled(GL_DEPTH_TEST);
		glGetIntegerv(GL_DEPTH_FUNC, &a->depthtest.depthtest_func);
		glGetBooleanv(GL_DEPTH_WRITEMASK, &a->depthtest.depthmask);
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
	OpenGL_attrib *a = attrib_stack + (attrib_stack_current_depth - 1);
	if(a->mask & GL2_ALL_ATTRIB_BITS || a->mask & GL2_CURRENT_BIT)
	{
		glColor4fv(a->current.rgba_color);
		//glRasterPos4fv(attrib_stack[attrib_stack_current_depth - 1].current.raster_pos);
	}
	if(a->mask & GL2_ALL_ATTRIB_BITS || a->mask & GL2_LINE_BIT)
	{
		glLineWidth(a->line.line_width);
		if(a->line.line_smooth != gl2IsEnabled(GL2_LINE_SMOOTH))
		{
			if(a->line.line_smooth)
				gl2Enable(GL2_LINE_SMOOTH);
			else
				gl2Disable(GL2_LINE_SMOOTH);
		}
	}
	if(a->mask & GL2_ALL_ATTRIB_BITS || a->mask & GL2_POINT_BIT)
	{
		glPointSize(a->point.point_size);
		if(a->point.point_smooth != gl2IsEnabled(GL2_POINT_SMOOTH))
		{
			if(a->point.point_smooth)
				gl2Enable(GL2_POINT_SMOOTH);
			else
				gl2Disable(GL2_POINT_SMOOTH);
		}
	}
	if(a->mask & GL2_ALL_ATTRIB_BITS || a->mask & GL2_POLYGON_BIT)
	{
		if(a->polygon.cullface_enabled != glIsEnabled(GL_CULL_FACE))
		{
			if(a->polygon.cullface_enabled)
				glEnable(GL_CULL_FACE);
			else
				glDisable(GL_CULL_FACE);
		}
		glCullFace(a->polygon.cullface_mode);
	}
	if(a->mask & GL2_ALL_ATTRIB_BITS || a->mask & GL2_SCISSOR_BIT)
	{
		if(a->scissortest.scissortest_enabled != glIsEnabled(GL_SCISSOR_TEST))
		{
			if(a->scissortest.scissortest_enabled)
				glEnable(GL_SCISSOR_TEST);
			else
				glDisable(GL_SCISSOR_TEST);
		}
		glScissor(a->scissortest.scissortest_box[0], a->scissortest.scissortest_box[1], a->scissortest.scissortest_box[2], a->scissortest.scissortest_box[3]);
	}
	if(a->mask & GL_ALL_ATTRIB_BITS || a->mask & GL_COLOR_BUFFER_BIT)
	{
		if(a->alphatest.alphatest_enabled != gl2IsEnabled(GL2_ALPHA_TEST))
		{
			if(a->alphatest.alphatest_enabled)
				gl2Enable(GL2_ALPHA_TEST);
			else
				gl2Disable(GL2_ALPHA_TEST);
		}
		gl2AlphaFunc(a->alphatest.alphatest_func, a->alphatest.alphatest_ref);

		if(a->blend.blend_enabled != glIsEnabled(GL_BLEND))
		{
			if(a->blend.blend_enabled)
				glEnable(GL_BLEND);
			else
				glDisable(GL_BLEND);
		}
		glBlendFunc(a->blend.blend_src, a->blend.blend_dst);
	}
	if(a->mask & GL_ALL_ATTRIB_BITS || a->mask & GL_DEPTH_BUFFER_BIT)
	{
		if(a->depthtest.depthtest_enabled != glIsEnabled(GL_DEPTH_TEST))
		{
			if(a->depthtest.depthtest_enabled)
				glEnable(GL_DEPTH_TEST);
			else
				glDisable(GL_DEPTH_TEST);
		}
		glDepthFunc(a->depthtest.depthtest_func);
		glDepthMask(a->depthtest.depthmask);
	}
	memset(a, 0, sizeof(OpenGL_attrib));
	attrib_stack_current_depth--;
}

