#if 0
#include "opengl.h"

#include <stdio.h>

#define HGL_DBG_NORET(func, args...) \
{##func(##args);} \
GLenum error = glGetError(); \
if(error != GL_NO_ERROR) \
{ \
	fprintf(stderr, "[%s]: %s\n", __func__, OpenGL_ErrorString(error)); \
}

#define HGL_DBG(func, T, args...) \
	T r = func(##args); \
GLenum error = glGetError(); \
if(error != GL_NO_ERROR) \
{ \
	fprintf(stderr, "[%s]: %s\n", __func__, OpenGL_ErrorString(error)); \
} \
return r;

static const char * OpenGL_ErrorString(GLenum error)
{
	static const char *Error_Strings[] = {
		"GL_NO_ERROR",
		"GL_INVALID_ENUM",
		"GL_INVALID_VALUE",
		"GL_INVALID_OPERATION",
		"GL_STACK_OVERFLOW",
		"GL_STACK_UNDERFLOW",
		"GL_OUT_OF_MEMORY"
	};
	switch(error)
	{
		case GL_NO_ERROR:
			return Error_Strings[0];
		case GL_INVALID_ENUM:
			return Error_Strings[1];
		case GL_INVALID_VALUE:
			return Error_Strings[2];
		case GL_INVALID_OPERATION:
			return Error_Strings[3];
		case GL_STACK_OVERFLOW:
			return Error_Strings[4];
		case GL_STACK_UNDERFLOW:
			return Error_Strings[5];
		case GL_OUT_OF_MEMORY:
			return Error_Strings[6];
		default:
			break;
	}
	return NULL;
}

void hglAlphaFunc (GLenum func, GLclampf ref)
{
	HGL_DBG_NORET(glAlphaFunc, func, ref) 
}

void hglClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	HGL_DBG_NORET(glClearColor, red, green, blue, alpha)
}

void hglClearDepthf (GLclampf depth)
{
	HGL_DBG_NORET(glClearDepthf, depth)
}

void hglClipPlanef (GLenum plane, const GLfloat *equation)
{
	HGL_DBG_NORET(glClipPlanef, plane, equation)
}

void hglColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	HGL_DBG_NORET(glColor4f, red, green, blue, alpha)
}

void hglDepthRangef (GLclampf zNear, GLclampf zFar)
{
	HGL_DBG_NORET(glDepthRangef, zNear, zFar)
}

void hglFogf (GLenum pname, GLfloat param)
{
	HGL_DBG_NORET(glFogf, pname, param)
}

void hglFogfv (GLenum pname, const GLfloat *params)
{
	HGL_DBG_NORET(glFogfv, pname, params)
}

void hglFrustumf (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
	HGL_DBG_NORET(glFrustumf, left, right, bottom, top, zNear, zFar)
}

void hglGetClipPlanef (GLenum pname, GLfloat eqn[4])
{
	HGL_DBG_NORET(glGetClipPlanef, pname, eqn)
}

void hglGetFloatv (GLenum pname, GLfloat *params)
{
	HGL_DBG_NORET(glGetFloatv, pname, params)
}

void hglGetLightfv (GLenum light, GLenum pname, GLfloat *params)
{
	HGL_DBG_NORET(glGetLightfv, light, pname, params)
}

void hglGetMaterialfv (GLenum face, GLenum pname, GLfloat *params)
{
	HGL_DBG_NORET(glGetMaterialfv, face, pname, params)
}

void hglGetTexEnvfv (GLenum env, GLenum pname, GLfloat *params)
{
	HGL_DBG_NORET(glGetTexEnvfv, env, pname, params)
}

void hglGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params)
{
	HGL_DBG_NORET(glGetTexParameterfv, target, pname, params)
}

void hglLightModelf (GLenum pname, GLfloat param)
{
	HGL_DBG_NORET(glLightModelf, pname, param)
}

void hglLightModelfv (GLenum pname, const GLfloat *params)
{
	HGL_DBG_NORET(glLightModelfv, pname, params)
}

void hglLightf (GLenum light, GLenum pname, GLfloat param)
{
	HGL_DBG_NORET(glLightf, light, pname, param)
}

void hglLightfv (GLenum light, GLenum pname, const GLfloat *params)
{
	HGL_DBG_NORET(glLightfv, light, pname, params)
}

void hglLineWidth (GLfloat width)
{
	HGL_DBG_NORET(glLineWidth, width)
}

void hglLoadMatrixf (const GLfloat *m)
{
	HGL_DBG_NORET(glLoadMatrixf, m)
}

void hglMaterialf (GLenum face, GLenum pname, GLfloat param)
{
	HGL_DBG_NORET(glMaterialf, face, pname, param)
}

void hglMaterialfv (GLenum face, GLenum pname, const GLfloat *params)
{
	HGL_DBG_NORET(glMaterialfv, face, pname, params)
}

void hglMultMatrixf (const GLfloat *m)
{
	HGL_DBG_NORET(glMultMatrixf, m)
}

void hglMultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
	HGL_DBG_NORET(glMultiTexCoord4f, target, s, t, r, q)
}

void hglNormal3f (GLfloat nx, GLfloat ny, GLfloat nz)
{
	HGL_DBG_NORET(glNormal3f, GLfloat nx, GLfloat ny, GLfloat nz)
}

void hglOrthof (left, right, bottom, top, zNear, zFar)
{
	HGL_DBG_NORET(glOrthof, left, right, bottom, top, zNear, zFar)
}

void hglPointParameterf (GLenum pname, GLfloat param)
{
	HGL_DBG_NORET(glPointParameterf, pname, param)
}

void hglPointParameterfv (GLenum pname, const GLfloat *params)
{
	HGL_DBG_NORET(glPointParameterfv, pname, params)
}

void hglPointSize (GLfloat size)
{
	HGL_DBG_NORET(glPointSize, size)
}

void hglPolygonOffset (GLfloat factor, GLfloat units)
{
	HGL_DBG_NORET(glPolygonOffset, factor, units)
}

void hglRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	HGL_DBG_NORET(glRotatef, angle, x, y, z)
}

void hglScalef (GLfloat x, GLfloat y, GLfloat z)
{
	HGL_DBG_NORET(glScalef, x, y, z)
}

void hglTexEnvf (GLenum target, GLenum pname, GLfloat param)
{
	HGL_DBG_NORET(glTexEnvf, target, pname, param)
}

void hglTexEnvfv (GLenum target, GLenum pname, const GLfloat *params)
{
	HGL_DBG_NORET(glTexEnvfv, target, pname, params)
}

void hglTexParameterf (GLenum target, GLenum pname, GLfloat param)
{
	HGL_DBG_NORET(glTexParameterf, target, pname, param)
}

void hglTexParameterfv (GLenum target, GLenum pname, const GLfloat *params)
{
	HGL_DBG_NORET(glTexParameterfv, target, pname, params)
}

void hglTranslatef (GLfloat x, GLfloat y, GLfloat z)
{
	HGL_DBG_NORET(glTranslatef, x, y, z)
}

void glActiveTexture (GLenum texture)
{
	HGL_DBG_NORET(glActiveTexture, texture)
}

void hglAlphaFuncx (GLenum func, GLclampx ref)
{
	HGL_DBG_NORET(glAlphaFuncx, func, ref)
}

void hglBindBuffer (GLenum target, GLuint buffer)
{
	HGL_DBG_NORET(glBindBuffer, target, buffer)
}

void hglBindTexture (GLenum target, GLuint texture)
{
	HGL_DBG_NORET(glBindTexture, target, texture)
}

void hglBlendFunc (GLenum sfactor, GLenum dfactor)
{
	HGL_DBG_NORET(glBlendFunc, sfactor, dfactor)
}

void hglBufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
{
	HGL_DBG_NORET(glBufferData, target, size, data, usage)
}

void hglBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)
{
	HGL_DBG_NORET(glBufferSubData, target, offset, size, data)
}

void hglClear (GLbitfield mask)
{
	HGL_DBG_NORET(glClear, mask)
}

void hglClearColorx (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha)
{
	HGL_DBG_NORET(glClearColorx, red, green, blue, alpha)
}

void hglClearDepthx (GLclampx depth)
{
	HGL_DBG_NORET(glClearDepthx, depth)
}

void hglClearStencil (GLint s)
{
	HGL_DBG_NORET(glClearStencil, s)
}

void hglClientActiveTexture (GLenum texture)
{
	HGL_DBG_NORET(glClientActiveTexture, texture)
}

void hglClipPlanex (GLenum plane, const GLfixed *equation)
{
	HGL_DBG_NORET(glClipPlanex, plane, equation)
}

void hglColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
{
	HGL_DBG_NORET(glColor4ub, red, green, blue, alpha)
}

void hglColor4x (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha)
{
	HGL_DBG_NORET(glColor4x, red, green, blue, alpha)
}

void hglColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	HGL_DBG_NORET(glColorMask, red, green, blue, alpha)
}

void hglColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	HGL_DBG_NORET(glColorPointer, size, type, stride, pointer)
}

void hglCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data)
{
	HGL_DBG_NORET(glCompressedTexImage2D, target, level, internalformat, width, height, border, imageSize, data)
}

void hglCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data)
{
	HGL_DBG_NORET(glCompressedTexSubImage2D, target, level, xoffset, yoffset, width, height, format, imageSize, data)
}

void hglCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
	HGL_DBG_NORET(glCopyTexImage2D, target, level, internalformat, x, y, width, height, border)
}

void hglCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	HGL_DBG_NORET(glCopyTexSubImage2D, target, level, xoffset, yoffset, x, y, width, height)
}

void hglCullFace (GLenum mode)
{
	HGL_DBG_NORET(glCullFace, mode)
}

void hglDeleteBuffers (GLsizei n, const GLuint *buffers)
{
	HGL_DBG_NORET(glDeleteBuffers, n, buffers)
}

void hglDeleteTextures (GLsizei n, const GLuint *textures)
{
	HGL_DBG_NORET(glDeleteTextures, n, textures)
}

void hglDepthFunc (GLenum func)
{
	HGL_DBG_NORET(glDepthFunc, func)
}

void hglDepthMask (GLboolean flag)
{
	HGL_DBG_NORET(glDepthMask, flag)
}

void hglDepthRangex (GLclampx zNear, GLclampx zFar)
{
	HGL_DBG_NORET(glDepthRangex, zNear, zFar)
}

void hglDisable (GLenum cap)
{
	HGL_DBG_NORET(glDisable, cap)
}

void hglDisableClientState (GLenum array)
{
	HGL_DBG_NORET(glDisableClientState, array)
}

void hglDrawArrays (GLenum mode, GLint first, GLsizei count)
{
	HGL_DBG_NORET(glDrawArrays, mode, first, count)
}

void hglDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
{
	HGL_DBG_NORET(glDrawElements, mode, count, type, indices)
}

void hglEnable (GLenum cap)
{
	HGL_DBG_NORET(glEnable, cap)
}

void hglEnableClientState (GLenum array)
{
	HGL_DBG_NORET(glEnableClientState, array)
}

void hglFinish (void)
{
	HGL_DBG_NORET(glFinish, 1)
}

void hglFlush (void)
{
	HGL_DBG_NORET(glFlush, 1)
}

void hglFogx (GLenum pname, GLfixed param)
{
	HGL_DBG_NORET(glFogx, pname, param)
}

void hglFogxv (GLenum pname, const GLfixed *params)
{
	HGL_DBG_NORET(glFogxv, pname, params)
}

void hglFrontFace (GLenum mode)
{
	HGL_DBG_NORET(glFrontFace, mode)
}

void hglFrustumx (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar)
{
	HGL_DBG_NORET(glFrustumx, left, right, bottom, top, zNear, zFar)
}

void hglGetBooleanv (GLenum pname, GLboolean *params)
{
	HGL_DBG_NORET(glGetBooleanv, pname, )
}

void hglGetBufferParameteriv (GLenum target, GLenum pname, GLint *params)
{
	HGL_DBG_NORET(glGetBufferParameteriv, target, pname, params)
}

void hglGetClipPlanex (GLenum pname, GLfixed eqn[4])
{
	HGL_DBG_NORET(glGetClipPlanex, pname, eqn)
}

void hglGenBuffers (GLsizei n, GLuint *buffers)
{
	HGL_DBG_NORET(glGenBuffers, n, buffers)
}

void hglGenTextures (GLsizei n, GLuint *textures)
{
	HGL_DBG_NORET(glGenTextures, n, textures)
}

void hglGetFixedv (GLenum pname, GLfixed *params)
{
	HGL_DBG_NORET(glGetFixedv, pname, params)
}

void hglGetIntegerv (GLenum pname, GLint *params)
{
	HGL_DBG_NORET(glGetIntegerv, pname, params)
}

void hglGetLightxv (GLenum light, GLenum pname, GLfixed *params)
{
	HGL_DBG_NORET(glGetLightxv, GLenum , GLenum , params)
}

void hglGetMaterialxv (GLenum face, GLenum pname, GLfixed *params)
{
	HGL_DBG_NORET(glGetMaterialxv, face, pname, params)
}

void hglGetPointerv (GLenum pname, void **params)
{
	HGL_DBG_NORET(glGetPointerv, pname, params)
}

const char * GL_APIENTRY glGetString (GLenum name)
{
	HGL_DBG(glGetString, const char *, name)
}

void hglGetTexEnviv (GLenum env, GLenum pname, GLint *params)
{
	HGL_DBG_NORET(glGetTexEnviv, env, pname, params)
}

void hglGetTexEnvxv (GLenum env, GLenum pname, GLfixed *params)
{
	HGL_DBG_NORET(glGetTexEnvxv, env, pname, params)
}

void hglGetTexParameteriv (GLenum target, GLenum pname, GLint *params)
{
	HGL_DBG_NORET(glGetTexParameteriv, target, pname, params)
}

void hglGetTexParameterxv (GLenum target, GLenum pname, GLfixed *params)
{
	HGL_DBG_NORET(glGetTexParameterxv, target, pname, params)
}

void hglHint (GLenum target, GLenum mode)
{
	HGL_DBG_NORET(glHint, target, mode)
}

GLboolean hglIsBuffer (GLuint buffer)
{
	HGL_DBG(glIsBuffer, GLboolean, buffer)
}

GLboolean hglIsEnabled (GLenum cap)
{
	HGL_DBG(glIsEnabled, GLboolean, cap)
}

GLboolean hglIsTexture (GLuint texture)
{
	HGL_DBG(glIsTexture, GLboolean, texture)
}

void hglLightModelx (GLenum pname, GLfixed param)
{
	HGL_DBG_NORET(glLightModelx, GLenum pname, GLfixed param)
}

void hglLightModelxv (GLenum pname, const GLfixed *params)
{
	HGL_DBG_NORET(glLightModelxv, pname, params)
}

void hglLightx (GLenum light, GLenum pname, GLfixed param)
{
	HGL_DBG_NORET(glLightx, light, pname, param)
}

void hglLightxv (GLenum light, GLenum pname, const GLfixed *params)
{
	HGL_DBG_NORET(glLightxv, light, pname, params)
}

void hglLineWidthx (GLfixed width)
{
	HGL_DBG_NORET(glLineWidthx, width)
}

void hglLoadIdentity (void)
{
	HGL_DBG_NORET(glLoadIdentity, 1)
}

void hglLoadMatrixx (const GLfixed *m)
{
	HGL_DBG_NORET(glLoadMatrixx, m)
}

void hglLogicOp (GLenum opcode)
{
	HGL_DBG_NORET(glLogicOp, opcode)
}

void hglMaterialx (GLenum face, GLenum pname, GLfixed param)
{
	HGL_DBG_NORET(glMaterialx, face, pname, param)
}

void hglMaterialxv (GLenum face, GLenum pname, const GLfixed *params)
{
	HGL_DBG_NORET(glMaterialxv, face, pname, params)
}

void hglMatrixMode (GLenum mode)
{
	HGL_DBG_NORET(glMatrixMode, mode)
}

void hglMultMatrixx (const GLfixed *m)
{
	HGL_DBG_NORET(glMultMatrixx, m)
}

void hglMultiTexCoord4x (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q)
{
	HGL_DBG_NORET(glMultiTexCoord4x, target, s, t, r, q)
}

void hglNormal3x (GLfixed nx, GLfixed ny, GLfixed nz)
{
	HGL_DBG_NORET(glNormal3x, nx, ny, nz)
}

void hglNormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer)
{
	HGL_DBG_NORET(glNormalPointer, type, stride, pointer)
}

void hglOrthox (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar)
{
	HGL_DBG_NORET(glOrthox, left, right, bottom, top, zNear, zFar)
}

void hglPixelStorei (GLenum pname, GLint param)
{
	HGL_DBG_NORET(glPixelStorei, pname, param)
}

void hglPointParameterx (GLenum pname, GLfixed param)
{
	HGL_DBG_NORET(glPointParameterx, pname, param)
}

void hglPointParameterxv (GLenum pname, const GLfixed *params)
{
	HGL_DBG_NORET(glPointParameterxv, pname, params)
}

void hglPointSizex (GLfixed size)
{
	HGL_DBG_NORET(glPointSizex, size)
}

void hglPolygonOffsetx (GLfixed factor, GLfixed units)
{
	HGL_DBG_NORET(glPolygonOffsetx, factor, units)
}

void hglPopMatrix (void)
{
	HGL_DBG_NORET(glPopMatrix, 1)
}

void hglPushMatrix (void)
{
	HGL_DBG_NORET(glPushMatrix, 1)
}

void hglReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels)
{
	HGL_DBG_NORET(glReadPixels, x, y, width, height, format, type, pixels)
}

void hglRotatex (GLfixed angle, GLfixed x, GLfixed y, GLfixed z)
{
	HGL_DBG_NORET(glRotatex, angle, x, y, z)
}

void hglSampleCoverage (GLclampf value, GLboolean invert)
{
	HGL_DBG_NORET(glSampleCoverage, value, invert)
}

void hglSampleCoveragex (GLclampx value, GLboolean invert)
{
	HGL_DBG_NORET(glSampleCoveragex, value, invert)
}

void hglScalex (GLfixed x, GLfixed y, GLfixed z)
{
	HGL_DBG_NORET(glScalex, x, y, z)
}

void hglScissor (GLint x, GLint y, GLsizei width, GLsizei height)
{
	HGL_DBG_NORET(glScissor, x, y, width, height)
}

void hglShadeModel (GLenum mode)
{
	HGL_DBG_NORET(glShadeModel, mode)
}

void hglStencilFunc (GLenum func, GLint ref, GLuint mask)
{
	HGL_DBG_NORET(glStencilFunc, func, ref, mask)
}

void hglStencilMask (GLuint mask)
{
	HGL_DBG_NORET(glStencilMask, mask)
}

void hglStencilOp (GLenum fail, GLenum zfail, GLenum zpass)
{
	HGL_DBG_NORET(glStencilOp, fail, zfail, zpass)
}

void hglTexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	HGL_DBG_NORET(glTexCoordPointer, size, type, stride, pointer)
}

void hglTexEnvi (GLenum target, GLenum pname, GLint param)
{
	HGL_DBG_NORET(glTexEnvi, target, pname, param)
}

void hglTexEnvx (GLenum target, GLenum pname, GLfixed param)
{
	HGL_DBG_NORET(glTexEnvx, target, pname, param)
}

void hglTexEnviv (GLenum target, GLenum pname, const GLint *params)
{
	HGL_DBG_NORET(glTexEnviv, target, pname, params)
}

void hglTexEnvxv (GLenum target, GLenum pname, const GLfixed *params)
{
	HGL_DBG_NORET(glTexEnvxv, target, pname, params)
}

void hglTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
	HGL_DBG_NORET(glTexImage2D, target, level, internalformat, width, height, border, format, type, pixels)
}

void hglTexParameteri (GLenum target, GLenum pname, GLint param)
{
	HGL_DBG_NORET(glTexParameteri, GLenum target, GLenum pname, GLint param)
}

void hglTexParameterx (GLenum target, GLenum pname, GLfixed param)
{
	HGL_DBG_NORET(glTexParameterx, GLenum target, GLenum pname, GLfixed param)
}

void hglTexParameteriv (GLenum target, GLenum pname, const GLint *params)
{
	HGL_DBG_NORET(glTexParameteriv, target, pname, params)
}

void hglTexParameterxv (GLenum target, GLenum pname, const GLfixed *params)
{
	HGL_DBG_NORET(glTexParameterxv, target, pname, params)
}

void hglTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
{
	HGL_DBG_NORET(glTexSubImage2D, target, level, xoffset, yoffset, width, height, format, type, pixels)
}

void hglTranslatex (GLfixed x, GLfixed y, GLfixed z)
{
	HGL_DBG_NORET(glTranslatex, x, y, z)
}

void hglVertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	HGL_DBG_NORET(glVertexPointer, size, type, stride, pointer)
}

void hglViewport (GLint x, GLint y, GLsizei width, GLsizei height)
{
	HGL_DBG_NORET(glViewport, x, y, width, height)
}
#endif
