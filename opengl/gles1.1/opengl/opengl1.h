#ifndef KARIN_OPENGLES_H
#define KARIN_OPENGLES_H

#ifdef _HARMATTAN_OPENGLES
	#include <GLES/gl.h>
	#include <GLES/glext.h>
//	#include <EGL/egl.h>

	#define OPENGLES2OPENGL_PORT

// for texture
	#ifndef GL_CLAMP
		#define GL_CLAMP GL_CLAMP_TO_EDGE
	#endif
// for header file
	#ifndef APIENTRY
		#define APIENTRY GL_APIENTRY
	#endif
// for data type
	typedef float GLdouble;
	typedef float GLclampd;
// for attributes bit defines
	#define GL_CURRENT_BIT				0x00000001
	#define GL_POINT_BIT				0x00000002
	#define GL_LINE_BIT				0x00000004
	#define GL_POLYGON_BIT				0x00000008
	#define GL_POLYGON_STIPPLE_BIT			0x00000010
	#define GL_PIXEL_MODE_BIT			0x00000020
	#define GL_LIGHTING_BIT				0x00000040
	#define GL_FOG_BIT				0x00000080
	#define GL_DEPTH_BUFFER_BIT			0x00000100
	#define GL_ACCUM_BUFFER_BIT			0x00000200
	#define GL_STENCIL_BUFFER_BIT			0x00000400
	#define GL_VIEWPORT_BIT				0x00000800
	#define GL_TRANSFORM_BIT			0x00001000
	#define GL_ENABLE_BIT				0x00002000
	#define GL_COLOR_BUFFER_BIT			0x00004000
	#define GL_HINT_BIT				0x00008000
	#define GL_EVAL_BIT				0x00010000
	#define GL_LIST_BIT				0x00020000
	#define GL_TEXTURE_BIT				0x00040000
	#define GL_SCISSOR_BIT				0x00080000
	#define GL_ALL_ATTRIB_BITS			0x000FFFFF

	#ifdef GL_OES_mapbuffer
		#define GL_WRITE_ONLY GL_WRITE_ONLY_OES
	#endif

// for functions
	GLvoid glkPushAttrib(GLbitfield mask);
	GLvoid glkPopAttrib(GLvoid);
	GLvoid glkGetIntegerv(GLenum pname, GLint *params);
	GLenum glkGetError(GLvoid);

	#define glPushAttrib glkPushAttrib
	#define glPopAttrib glkPopAttrib
	#define glOrtho glOrthof
	#define glGetDoublev glGetFloatv
	#define glPointParameteri glPointParameterf
	#define glColor4fv(v) glColor4f(v[0], v[1], v[2], v[3])

#ifdef GL_OES_mapbuffer
	#define glMapBuffer glMapBufferOES
	#define glUnmapBuffer glUnmapBufferOES
#endif
//	#define

// my

	#define GL_ATTRIB_STACK_DEPTH 0x0BB0
	#define GL_MAX_ATTRIB_STACK_DEPTH		0x0D39

#endif

#endif
