#ifndef KARIN_OPENGLES2_H
#define KARIN_OPENGLES2_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#define GL2_VERTEX_ATTRIB 1
#define GL2_TEXCOORD_ATTRIB (1 << 1)
#define GL2_TEXCOORD2_ATTRIB (1 << 2)
#define GL2_TEXCOORD3_ATTRIB (1 << 3)
#define GL2_TEXCOORD4_ATTRIB (1 << 4)
#define GL2_TEXCOORD5_ATTRIB (1 << 5)
#define GL2_TEXCOORD6_ATTRIB (1 << 6)
#define GL2_TEXCOORD7_ATTRIB (1 << 7)
#define GL2_TEXCOORD8_ATTRIB (1 << 8)
#define GL2_COLOR_ATTRIB (1 << 9)
#define GL2_SECONDARY_COLOR_ATTRIB (1 << 10)
#define GL2_NORMAL_ATTRIB (1 << 11)

/* Errors */
#define GL2_NO_ERROR                       0
#define GL2_INVALID_ENUM                   0x0500
#define GL2_INVALID_VALUE                  0x0501
#define GL2_INVALID_OPERATION              0x0502
#define GL2_OUT_OF_MEMORY                  0x0505
#define GL2_STACK_OVERFLOW			0x0503
#define GL2_STACK_UNDERFLOW			0x0504

/* Matrix Mode */
#define GL2_MATRIX_MODE				0x0BA0
#define GL2_MODELVIEW				0x1700
#define GL2_PROJECTION				0x1701
#define GL2_TEXTURE				0x1702

/* Implementation limits */
#define GL2_MAX_ATTRIB_STACK_DEPTH		0x0D35
#define GL2_MAX_MODELVIEW_STACK_DEPTH		0x0D36
#define GL2_MAX_PROJECTION_STACK_DEPTH		0x0D38
#define GL2_MAX_TEXTURE_STACK_DEPTH		0x0D39
#define GL2_MAX_CLIENT_ATTRIB_STACK_DEPTH	0x0D3B

/* Gets */
#define GL2_ATTRIB_STACK_DEPTH			0x0BB0
#define GL2_CLIENT_ATTRIB_STACK_DEPTH		0x0BB1
#define GL2_MODELVIEW_MATRIX			0x0BA6
#define GL2_MODELVIEW_STACK_DEPTH		0x0BA3
#define GL2_PROJECTION_MATRIX			0x0BA7
#define GL2_PROJECTION_STACK_DEPTH		0x0BA4
#define GL2_TEXTURE_MATRIX			0x0BA8
#define GL2_TEXTURE_STACK_DEPTH			0x0BA5

#define GL2_CURRENT_COLOR			0x0B00
#define GL2_POINT_SMOOTH				0x0B10
#define GL2_POINT_SIZE				0x0B11
#define GL2_LINE_SMOOTH				0x0B20

// for texture
#ifndef GL_CLAMP
#define GL_CLAMP GL_CLAMP_TO_EDGE
#endif

// for attributes bit defines
#define GL2_CURRENT_BIT				0x00000001
#define GL2_POINT_BIT				0x00000002
#define GL2_LINE_BIT				0x00000004
#define GL2_POLYGON_BIT				0x00000008
#define GL2_POLYGON_STIPPLE_BIT			0x00000010
#define GL2_PIXEL_MODE_BIT			0x00000020
#define GL2_LIGHTING_BIT				0x00000040
#define GL2_FOG_BIT				0x00000080
#define GL2_DEPTH_BUFFER_BIT			0x00000100
#define GL2_ACCUM_BUFFER_BIT			0x00000200
#define GL2_STENCIL_BUFFER_BIT			0x00000400
#define GL2_VIEWPORT_BIT				0x00000800
#define GL2_TRANSFORM_BIT			0x00001000
#define GL2_ENABLE_BIT				0x00002000
#define GL2_COLOR_BUFFER_BIT			0x00004000
#define GL2_HINT_BIT				0x00008000
#define GL2_EVAL_BIT				0x00010000
#define GL2_LIST_BIT				0x00020000
#define GL2_TEXTURE_BIT				0x00040000
#define GL2_SCISSOR_BIT				0x00080000
#define GL2_ALL_ATTRIB_BITS			0x000FFFFF

// client state
#define GL2_VERTEX_ARRAY				0x8074
#define GL2_NORMAL_ARRAY				0x8075
#define GL2_COLOR_ARRAY				0x8076
#define GL2_TEXTURE_COORD_ARRAY			0x8078

// other
#define GL2_SHADE_MODEL				0x0B54
#define GL2_FLAT					0x1D00
#define GL2_SMOOTH				0x1D01
#define GL2_ALPHA_TEST				0x0BC0
#define GL2_ALPHA_TEST_REF			0x0BC2
#define GL2_ALPHA_TEST_FUNC			0x0BC1
#define GL2_BLEND_SRC GL_BLEND_SRC_RGB
#define GL2_BLEND_DST GL_BLEND_DST_RGB

// fog
#define GL2_FOG                            0x0B60
#define GL2_FOG_DENSITY                    0x0B62
#define GL2_FOG_START                      0x0B63
#define GL2_FOG_END                        0x0B64
#define GL2_FOG_MODE                       0x0B65
#define GL2_FOG_COLOR                      0x0B66
#define GL2_EXP                            0x0800
#define GL2_EXP2                           0x0801

#include "opengl2_port.h"

#ifdef GL_OES_mapbuffer
#define glMapBuffer glMapBufferOES
#define glUnmapBuffer glUnmapBufferOES
#define GL_WRITE_ONLY GL_WRITE_ONLY_OES
#endif

// for data type
typedef float GLdouble;
typedef float GLclampd;

// extern
extern GLuint program;

// shader program
GLboolean gl2LinkShaderToProgram(GLuint program, GLuint vshader, GLuint fshader);
GLboolean gl2ProgramIsLinked(GLuint program);
GLboolean gl2ShaderIsCompiled(GLuint shader);
GLuint gl2LoadShader(GLenum type, const char *src);
char * gl2LoadShaderSource(const char *file);
GLboolean gl2LoadProgramByFile(const char *vfile, const char *ffile, GLuint *rp, GLuint *rvs, GLuint *rfs);
GLboolean gl2LoadProgram(char *vsrc, char *fsrc, GLuint *rp, GLuint *rvs, GLuint *rfs);
GLvoid gl2InitProgram(GLvoid);
GLvoid gl2DestroyProgram(GLvoid);

// vertex array
GLvoid gl2VertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *ptr);
GLvoid gl2NormalPointer(GLenum type, GLsizei stride, const GLvoid *ptr);
GLvoid gl2ColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *ptr);
GLvoid gl2TexCoordPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *ptr);
GLvoid gl2EnableClientState(GLenum cap);
GLvoid gl2DisableClientState(GLenum cap);

// render
GLvoid gl2DrawArrays(GLenum mode, GLint first, GLsizei count);
GLvoid gl2DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
GLvoid gl2Render(GLvoid);

// matrix
GLvoid gl2Translate(GLfloat x, GLfloat y, GLfloat z);
GLvoid gl2Rotate(GLfloat a, GLfloat x, GLfloat y, GLfloat z);
GLvoid gl2Scale(GLfloat x, GLfloat y, GLfloat z);

GLvoid gl2Frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearval, GLfloat farval);
GLvoid gl2Ortho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearval, GLfloat farval);

GLvoid gl2PushMatrix(GLvoid);
GLvoid gl2PopMatrix(GLvoid);
GLvoid gl2MatrixMode(GLenum type);

GLvoid gl2LoadIdentity(GLvoid);
GLvoid gl2LoadMatrix(const GLfloat *m);
GLvoid gl2MultMatrix(const GLfloat *m);

// get
GLvoid gl2GetIntegerv(GLenum type, GLint *r);
GLvoid gl2GetFloatv(GLenum type, GLfloat *r);
GLenum gl2GerError(GLvoid);

// state
GLvoid gl2Enable(GLenum t);
GLvoid gl2Disable(GLenum t);
GLboolean gl2IsEnabled(GLenum t);

// attrib
GLvoid gl2PushAttrib(GLbitfield mask);
GLvoid gl2PopAttrib(GLvoid);

// port
GLvoid gl2Color4(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
GLvoid gl2PointSize(GLfloat size);
GLvoid gl2ShadeModel(GLenum model);
GLvoid gl2AlphaFunc(GLenum func, GLclampf ref);
GLvoid gl2BindTexture(GLenum tar, GLuint tex);
GLvoid gl2Fogf(GLenum pname, GLfloat param);
GLvoid gl2Fogfv(GLenum pname, const GLfloat *params);
GLvoid gl2Fogi(GLenum pname, GLint param);
GLvoid gl2Fogiv(GLenum pname, const GLint *params);

#endif
