#ifndef KARIN_GL_UTIL_H
#define KARIN_GL_UTIL_H

#include "math3d/vector3.h"
#include "netlizard/netlizard.h"

#include "opengl/opengl.h"

#define VEC_X(v) v[0]
#define VEC_Y(v) v[1]
#define VEC_Z(v) v[2]
#define VEC_W(v) v[3]

// not use memcpy, for source data type is not same as dest.
#define COPY_COLOR4(d, s) \
{ \
	d[0] = s[0]; \
	d[1] = s[1]; \
	d[2] = s[2]; \
	d[3] = s[3]; \
}

#define COPY_COLOR3(d, s) \
{ \
	d[0] = s[0]; \
	d[1] = s[1]; \
	d[2] = s[2]; \
}

#define COPY_VERTEX3(d, s) COPY_COLOR3(d, s)

#define ator(a) ((double)(a) / 180.0 * M_PI)
#define rtoa(r) ((double)(r) / M_PI * 180.0)

#define BUFFER_OFFSET(type, size) ((GLubyte *)NULL + sizeof(type) * size)

#define SCALE_OUT 3
#define SCALE_IN 2
#define NO_SCALE 0
#define SCALE_AUTO 1

#define X11_COLOR(c) Color_GetColor(c##_color, 1.0)

typedef enum _x11_color_type
{
	black_color = 0,
	navy_color,
	darkblue_color,
	mediumblue_color,
	blue_color,
	darkgreen_color,
	green_color,
	teal_color,
	darkcyan_color,
	deepskyblue_color,
	darkturquoise_color,
	mediumspringgreen_color,
	lime_color,
	springgreen_color,
	aqua_color,
	midnightblue_color,
	dodgerblue_color,
	lightseagreen_color,
	forestgreen_color,
	seagreen_color,
	darkslategray_color,
	limegreen_color,
	mediumseagreen_color,
	turquoise_color,
	royalblue_color,
	steelblue_color,
	darkslateblue_color,
	mediumturquoise_color,
	indigo_color,
	darkolivegreen_color,
	cadetblue_color,
	cornflowerblue_color,
	mediumaquamarine_color,
	dimgray_color,
	slateblue_color,
	olivedrab_color,
	slategray_color,
	lightslategray_color,
	mediumslateblue_color,
	lawngreen_color,
	chartreuse_color,
	aquamarine_color,
	maroon_color,
	purple_color,
	olive_color,
	gray_color,
	skyblue_color,
	lightskyblue_color,
	blueviolet_color,
	darkred_color,
	darkmagenta_color,
	saddlebrown_color,
	darkseagreen_color,
	lightgreen_color,
	mediumpurple_color,
	darkviolet_color,
	palegreen_color,
	darkorchid_color,
	sienna_color,
	brown_color,
	darkgray_color,
	lightblue_color,
	greenyellow_color,
	paleturquoise_color,
	lightsteelblue_color,
	powderblue_color,
	firebrick_color,
	darkgoldenrod_color,
	mediumorchid_color,
	rosybrown_color,
	darkkhaki_color,
	silver_color,
	mediumvioletred_color,
	indianred_color,
	peru_color,
	chocolate_color,
	tan_color,
	lightgray_color,
	thistle_color,
	orchid_color,
	goldenrod_color,
	palevioletred_color,
	crimson_color,
	gainsboro_color,
	plum_color,
	burlywood_color,
	lightcyan_color,
	lavender_color,
	darksalmon_color,
	violet_color,
	palegoldenrod_color,
	lightcoral_color,
	khaki_color,
	aliceblue_color,
	honeydew_color,
	azure_color,
	sandybrown_color,
	wheat_color,
	beige_color,
	whitesmoke_color,
	mintcream_color,
	ghostwhite_color,
	salmon_color,
	antiquewhite_color,
	linen_color,
	lightgoldenrodyellow_color,
	oldlace_color,
	red_color,
	fuchsia_color,
	deeppink_color,
	orangered_color,
	tomato_color,
	hotpink_color,
	coral_color,
	darkorange_color,
	lightsalmon_color,
	orange_color,
	lightpink_color,
	pink_color,
	gold_color,
	peachpuff_color,
	navajowhite_color,
	moccasin_color,
	bisque_color,
	mistyrose_color,
	blanchedalmond_color,
	papayawhip_color,
	lavenderblush_color,
	seashell_color,
	cornsilk_color,
	lemonchiffon_color,
	floralwhite_color,
	snow_color,
	yellow_color,
	lightyellow_color,
	ivory_color,
	white_color,
	other_color,
	total_color
} x11_color_type;

typedef struct _texture
{
	GLuint texid;
	int width;
	int height;
	GLenum format;
} texture;

typedef enum _OpenGL_bufferobject_type
{
	vertex_buffer_type = 0,
	texcoord_buffer_type,
	normal_buffer_type,
	index_buffer_type,
	total_buffer_type
} OpenGL_bufferobject_type;

void OpenGL_TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels, GLenum scale, GLsizei *rw, GLsizei *rh);

float  Algo_FormatAngle(float angle);
GLuint new_OpenGL_buffer_object(GLenum OpenGL_bufferobject_type, GLsizei size, const GLvoid *data, GLenum render_type);
texture * new_OpenGL_texture_2d(const char *dds);
texture * new_OpenGL_texture_2d_from_memory(const unsigned char *d, size_t len);
texture * new_OpenGL_texture_2d_from_buffer_with_glCopyTexImage2D(GLint x, GLint y, GLsizei w, GLsizei h, GLenum format);
texture * new_OpenGL_texture_2d_from_buffer_with_glReadPixels(GLint x, GLint y, GLsizei w, GLsizei h, GLenum format);
GLvoid OpenGL_Render3DOrtho(GLdouble l, GLdouble r, GLdouble b, GLdouble t);
GLvoid OpenGL_Render2D(GLdouble l, GLdouble r, GLdouble b, GLdouble t);
GLvoid OpenGL_Render3D(GLdouble a, GLdouble w, GLdouble h, GLdouble zn, GLdouble zf);
#ifndef _HARMATTAN_OPENGLES
typedef struct _OpenGL_frame_buffer_object
{
	GLuint fboId;
	GLuint rboId;
	GLuint texId;
	GLsizei width;
	GLsizei height;
} OpenGL_frame_buffer_object;

OpenGL_frame_buffer_object * new_OpenGL_frame_buffer_object(GLsizei width, GLsizei height);
GLvoid delete_frame_buffer_object(OpenGL_frame_buffer_object *fbo);
GLuint * OpenGL_SelectMode(GLsizei size);
#endif

//void nlCastAABB(array *vertex, GLfloat *min_x_r, GLfloat *min_y_r, GLfloat *min_z_r, GLfloat *max_x_r, GLfloat *max_y_r, GLfloat *max_z_r);
void Algo_ExtrameDistanceAlongDir(const vector3_s *dir, array* vertices, int *min, int *max);
void Algo_ComputeAABBFromOriginalPointSet(array* vertices, vector3_s *min, vector3_s *max);

// 取得当前的模型视图投影矩阵
void OpenGL_ExtractFrustum(GLfloat frustum[][4]);
int Algo_AABBInFrustum(GLfloat frustum[][4], GLfloat x, GLfloat y, GLfloat z, GLfloat x2, GLfloat y2, GLfloat z2);

void OpenGL_InitFog(GLenum mode, GLfloat near, GLfloat far, GLfloat dis, GLfloat color[]);

void OpenGLU_Project(GLdouble x, GLdouble y, GLdouble z, GLdouble *wx, GLdouble *wy, GLdouble *wz);
void * OpenGLU_ScaleImage(GLsizei width, GLsizei height, GLenum format, GLenum type, const void *datain, GLenum scale, GLsizei *rw, GLsizei *rh);
void OpenGL_ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
GLvoid OpenGL_Color3fv(x11_color_type c);
GLvoid OpenGL_Color4fv(x11_color_type c, GLclampf alpha);
const GLfloat * Color_GetColor(x11_color_type c, GLclampf alpha);

#endif
