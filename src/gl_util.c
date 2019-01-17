#include "gl_util.h"
#include "SOIL/SOIL.h"
#include "netlizard/netlizard.h"
#include "openglu.h"
#include "nl_std.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>

#define CLAMP_COLOR_FLOAT(r, g, b) {r / 255.0f, g / 255.0f, b / 255.0f, 1.0f}

static GLfloat X11_Color[total_color][4] =
{
	CLAMP_COLOR_FLOAT(0,0,0),
	CLAMP_COLOR_FLOAT(0,0,128),
	CLAMP_COLOR_FLOAT(0,0,139),
	CLAMP_COLOR_FLOAT(0,0,205),
	CLAMP_COLOR_FLOAT(0,0,255),
	CLAMP_COLOR_FLOAT(0,100,0),
	CLAMP_COLOR_FLOAT(0,128,0),
	CLAMP_COLOR_FLOAT(0,128,128),
	CLAMP_COLOR_FLOAT(0,139,139),
	CLAMP_COLOR_FLOAT(0,191,255),
	CLAMP_COLOR_FLOAT(0,206,209),
	CLAMP_COLOR_FLOAT(0,250,154),
	CLAMP_COLOR_FLOAT(0,255,0),
	CLAMP_COLOR_FLOAT(0,255,127),
	CLAMP_COLOR_FLOAT(0,255,255),
	CLAMP_COLOR_FLOAT(25,25,112),
	CLAMP_COLOR_FLOAT(30,144,255),
	CLAMP_COLOR_FLOAT(32,178,170),
	CLAMP_COLOR_FLOAT(34,139,34),
	CLAMP_COLOR_FLOAT(46,139,87),
	CLAMP_COLOR_FLOAT(47,79,79),
	CLAMP_COLOR_FLOAT(50,205,50),
	CLAMP_COLOR_FLOAT(60,179,113),
	CLAMP_COLOR_FLOAT(64,224,208),
	CLAMP_COLOR_FLOAT(65,105,225),
	CLAMP_COLOR_FLOAT(70,130,180),
	CLAMP_COLOR_FLOAT(72,61,139),
	CLAMP_COLOR_FLOAT(72,209,204),
	CLAMP_COLOR_FLOAT(75,0,130),
	CLAMP_COLOR_FLOAT(85,107,47),
	CLAMP_COLOR_FLOAT(95,158,160),
	CLAMP_COLOR_FLOAT(100,149,237),
	CLAMP_COLOR_FLOAT(102,205,170),
	CLAMP_COLOR_FLOAT(105,105,105),
	CLAMP_COLOR_FLOAT(106,90,205),
	CLAMP_COLOR_FLOAT(107,142,35),
	CLAMP_COLOR_FLOAT(112,128,144),
	CLAMP_COLOR_FLOAT(119,136,153),
	CLAMP_COLOR_FLOAT(123,104,238),
	CLAMP_COLOR_FLOAT(124,252,0),
	CLAMP_COLOR_FLOAT(127,255,0),
	CLAMP_COLOR_FLOAT(127,255,212),
	CLAMP_COLOR_FLOAT(128,0,0),
	CLAMP_COLOR_FLOAT(128,0,128),
	CLAMP_COLOR_FLOAT(128,128,0),
	CLAMP_COLOR_FLOAT(128,128,128),
	CLAMP_COLOR_FLOAT(135,206,235),
	CLAMP_COLOR_FLOAT(135,206,250),
	CLAMP_COLOR_FLOAT(138,43,226),
	CLAMP_COLOR_FLOAT(139,0,0),
	CLAMP_COLOR_FLOAT(139,0,139),
	CLAMP_COLOR_FLOAT(139,69,19),
	CLAMP_COLOR_FLOAT(143,188,143),
	CLAMP_COLOR_FLOAT(144,238,144),
	CLAMP_COLOR_FLOAT(147,112,219),
	CLAMP_COLOR_FLOAT(148,0,211),
	CLAMP_COLOR_FLOAT(152,251,152),
	CLAMP_COLOR_FLOAT(153,50,204),
	CLAMP_COLOR_FLOAT(160,82,45),
	CLAMP_COLOR_FLOAT(165,42,42),
	CLAMP_COLOR_FLOAT(169,169,169),
	CLAMP_COLOR_FLOAT(173,216,230),
	CLAMP_COLOR_FLOAT(173,255,47),
	CLAMP_COLOR_FLOAT(175,238,238),
	CLAMP_COLOR_FLOAT(176,196,222),
	CLAMP_COLOR_FLOAT(176,224,230),
	CLAMP_COLOR_FLOAT(178,34,34),
	CLAMP_COLOR_FLOAT(184,134,11),
	CLAMP_COLOR_FLOAT(186,85,211),
	CLAMP_COLOR_FLOAT(188,143,143),
	CLAMP_COLOR_FLOAT(189,183,107),
	CLAMP_COLOR_FLOAT(192,192,192),
	CLAMP_COLOR_FLOAT(199,21,133),
	CLAMP_COLOR_FLOAT(205,92,92),
	CLAMP_COLOR_FLOAT(205,133,63),
	CLAMP_COLOR_FLOAT(210,105,30),
	CLAMP_COLOR_FLOAT(210,180,140),
	CLAMP_COLOR_FLOAT(211,211,211),
	CLAMP_COLOR_FLOAT(216,191,216),
	CLAMP_COLOR_FLOAT(218,112,214),
	CLAMP_COLOR_FLOAT(218,165,32),
	CLAMP_COLOR_FLOAT(219,112,147),
	CLAMP_COLOR_FLOAT(220,20,60),
	CLAMP_COLOR_FLOAT(220,220,220),
	CLAMP_COLOR_FLOAT(221,160,221),
	CLAMP_COLOR_FLOAT(222,184,135),
	CLAMP_COLOR_FLOAT(224,255,255),
	CLAMP_COLOR_FLOAT(230,230,250),
	CLAMP_COLOR_FLOAT(233,150,122),
	CLAMP_COLOR_FLOAT(238,130,238),
	CLAMP_COLOR_FLOAT(238,232,170),
	CLAMP_COLOR_FLOAT(240,128,128),
	CLAMP_COLOR_FLOAT(240,230,140),
	CLAMP_COLOR_FLOAT(240,248,255),
	CLAMP_COLOR_FLOAT(240,255,240),
	CLAMP_COLOR_FLOAT(240,255,255),
	CLAMP_COLOR_FLOAT(244,164,96),
	CLAMP_COLOR_FLOAT(245,222,179),
	CLAMP_COLOR_FLOAT(245,245,220),
	CLAMP_COLOR_FLOAT(245,245,245),
	CLAMP_COLOR_FLOAT(245,255,250),
	CLAMP_COLOR_FLOAT(248,248,255),
	CLAMP_COLOR_FLOAT(250,128,114),
	CLAMP_COLOR_FLOAT(250,235,215),
	CLAMP_COLOR_FLOAT(250,240,230),
	CLAMP_COLOR_FLOAT(250,250,210),
	CLAMP_COLOR_FLOAT(253,245,230),
	CLAMP_COLOR_FLOAT(255,0,0),
	CLAMP_COLOR_FLOAT(255,0,255),
	CLAMP_COLOR_FLOAT(255,20,147),
	CLAMP_COLOR_FLOAT(255,69,0),
	CLAMP_COLOR_FLOAT(255,99,71),
	CLAMP_COLOR_FLOAT(255,105,180),
	CLAMP_COLOR_FLOAT(255,127,80),
	CLAMP_COLOR_FLOAT(255,140,0),
	CLAMP_COLOR_FLOAT(255,160,122),
	CLAMP_COLOR_FLOAT(255,165,0),
	CLAMP_COLOR_FLOAT(255,182,193),
	CLAMP_COLOR_FLOAT(255,192,203),
	CLAMP_COLOR_FLOAT(255,215,0),
	CLAMP_COLOR_FLOAT(255,218,185),
	CLAMP_COLOR_FLOAT(255,222,173),
	CLAMP_COLOR_FLOAT(255,228,181),
	CLAMP_COLOR_FLOAT(255,228,196),
	CLAMP_COLOR_FLOAT(255,228,225),
	CLAMP_COLOR_FLOAT(255,235,205),
	CLAMP_COLOR_FLOAT(255,239,213),
	CLAMP_COLOR_FLOAT(255,240,245),
	CLAMP_COLOR_FLOAT(255,245,238),
	CLAMP_COLOR_FLOAT(255,248,220),
	CLAMP_COLOR_FLOAT(255,250,205),
	CLAMP_COLOR_FLOAT(255,250,240),
	CLAMP_COLOR_FLOAT(255,250,250),
	CLAMP_COLOR_FLOAT(255,255,0),
	CLAMP_COLOR_FLOAT(255,255,224),
	CLAMP_COLOR_FLOAT(255,255,240),
	CLAMP_COLOR_FLOAT(255,255,255),
	{1.0f, 1.0f, 1.0f, 1.0f}
};

float Algo_FormatAngle(float angle)
{
	int i = (int)angle;
	float f = angle - i;
	float r = 0.0;
	if(angle > 360)
	{
		r = i % 360 + f;
	}
	else if(angle < 0)
	{
		r = 360 - abs(i % 360 + f);
	}
	else
		r = angle;
	if(r == 360.0)
		r = 0.0;
	return r;
}

GLuint new_OpenGL_buffer_object(GLenum OpenGL_bufferobject_type, GLsizei size, const GLvoid *data, GLenum render_type)
{
	if(!data)
		return 0;
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(OpenGL_bufferobject_type, buffer);
	glBufferData(OpenGL_bufferobject_type, size, data, render_type);
	glBindBuffer(OpenGL_bufferobject_type, 0);
	return buffer;
}

texture * new_OpenGL_texture_2d(const char *dds)
{
	if(!dds)
		return NULL;
	int channel;
	int width = 0;
	int height = 0;
	unsigned char *data = SOIL_load_image((char *)dds, &width, &height, &channel, SOIL_LOAD_AUTO);
	if(data == NULL)
	{
		fprintf(stderr, "Unable to load texture file.\n");
		return NULL;
	}

	GLenum format = 0;
	switch(channel)
	{
		case SOIL_LOAD_L:
			format = GL_LUMINANCE;
			break;
		case SOIL_LOAD_LA:
			format = GL_LUMINANCE_ALPHA;
			break;
		case SOIL_LOAD_RGB:
			format = GL_RGB;
			break;
		case SOIL_LOAD_RGBA:
			format = GL_RGBA;
			break;
		default:
			break;
	}
	if(format != 0)
	{
		texture *g_tex = NEW(texture);
		ZERO(g_tex, texture);
		g_tex->width = width;
		g_tex->height = height;
		g_tex->format = format;
		// SOIL_load_OGL_texture()
		glGenTextures(1, &(g_tex->texid));
		oglBindTexture(GL_TEXTURE_2D, g_tex->texid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	
#ifdef _HARMATTAN_OPENGLES
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
#else
		glGenerateMipmap(GL_TEXTURE_2D);
#endif
#ifdef _HARMATTAN_OPENGLES
		OpenGL_TexImage2D(GL_TEXTURE_2D, 0, g_tex->format, g_tex->width, g_tex->height, 0, g_tex->format, GL_UNSIGNED_BYTE, data, SCALE_AUTO, NULL, NULL);
#else
		glTexImage2D(GL_TEXTURE_2D, 0, g_tex->format, g_tex->width, g_tex->height, 0, g_tex->format, GL_UNSIGNED_BYTE, data);
#endif

		oglBindTexture(GL_TEXTURE_2D, 0);

		free(data);

		//printf("tex %d: width->%d, height->%d, channel->%d(%s)\n", g_tex->texid, g_tex->width, g_tex->height, channel, (channel == 1 ? "luminance" : (channel == 2 ? "luminance-alpha" : (channel == 3 ? "RGB" : "RGBA"))));
		return g_tex;
	}
	else
	{
		fprintf(stderr, "Unsupport format of texture file.\n");
		free(data);
		return NULL;
	}
}

texture * new_OpenGL_texture_2d_from_memory(const unsigned char *d, size_t len)
{
	if(!d || !len)
		return NULL;
	int channel;
	int width = 0;
	int height = 0;
	unsigned char *data = SOIL_load_image_from_memory(d, len, &width, &height, &channel, SOIL_LOAD_AUTO);
	if(data == NULL)
	{
		fprintf(stderr, "Unable to load texture file.\n");
		return NULL;
	}

	GLenum format = 0;
	switch(channel)
	{
		case SOIL_LOAD_L:
			format = GL_LUMINANCE;
			break;
		case SOIL_LOAD_LA:
			format = GL_LUMINANCE_ALPHA;
			break;
		case SOIL_LOAD_RGB:
			format = GL_RGB;
			break;
		case SOIL_LOAD_RGBA:
			format = GL_RGBA;
			break;
		default:
			break;
	}
	if(format != 0)
	{
		// SOIL_load_OGL_texture()
		texture *g_tex = NEW(texture);
		ZERO(g_tex, texture);
		g_tex->width = width;
		g_tex->height = height;
		g_tex->format = format;
		glGenTextures(1, &(g_tex->texid));
		oglBindTexture(GL_TEXTURE_2D, g_tex->texid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	
#ifdef _HARMATTAN_OPENGLES
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
#else
		glGenerateMipmap(GL_TEXTURE_2D);
#endif
#ifdef _HARMATTAN_OPENGLES
		OpenGL_TexImage2D(GL_TEXTURE_2D, 0, g_tex->format, g_tex->width, g_tex->height, 0, g_tex->format, GL_UNSIGNED_BYTE, data, SCALE_AUTO, NULL, NULL);
#else
		glTexImage2D(GL_TEXTURE_2D, 0, g_tex->format, g_tex->width, g_tex->height, 0, g_tex->format, GL_UNSIGNED_BYTE, data);
#endif

		oglBindTexture(GL_TEXTURE_2D, 0);

		free(data);

		//printf("tex %d: width->%d, height->%d, channel->%d(%s)\n", g_tex->texid, g_tex->width, g_tex->height, channel, (channel == 1 ? "luminance" : (channel == 2 ? "luminance-alpha" : (channel == 3 ? "RGB" : "RGBA"))));
		return g_tex;
	}
	else
	{
		fprintf(stderr, "Unsupport format of texture file.\n");
		free(data);
		return NULL;
	}
}

GLvoid OpenGL_Render2D(GLdouble l, GLdouble r, GLdouble b, GLdouble t)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(l, r, b, t);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	oglDisable(GL_DEPTH_TEST);
}

GLvoid OpenGL_Render3DOrtho(GLdouble l, GLdouble r, GLdouble b, GLdouble t)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(l, r, b, t);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

GLvoid OpenGL_Render3D(GLdouble a, GLdouble w, GLdouble h, GLdouble zn, GLdouble zf)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-2.0, 2.0, -2.0, 2.0, 1.5, 20.0);
	GLdouble ht = h;
	if(ht == 0)
		ht = 1;
	gluPerspective(a, w / ht, zn, zf);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	oglEnable(GL_DEPTH_TEST);
}

#ifdef _HARMATTAN_OPENGL
OpenGL_frame_buffer_object * new_OpenGL_frame_buffer_object(GLsizei width, GLsizei height)
{
	OpenGL_frame_buffer_object *fbo = NEW(OpenGL_frame_buffer_object);
	ZERO(fbo, OpenGL_frame_buffer_object);
	glGenTextures(1, &fbo->texId);
	oglBindTexture(GL_TEXTURE_2D, fbo->texId);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#ifdef _HARMATTAN_OPENGLES
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap
#else
		glGenerateMipmap(GL_TEXTURE_2D);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	oglBindTexture(GL_TEXTURE_2D, 0);

	glGenRenderbuffersEXT(1, &fbo->rboId);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, fbo->rboId);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

	glGenFramebuffersEXT(1, &fbo->fboId);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo->fboId);

	// attach the texture to FBO color attachment point
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,        // 1. fbo target: GL_FRAMEBUFFER 
			GL_COLOR_ATTACHMENT0_EXT,  // 2. attachment point
			GL_TEXTURE_2D,         // 3. tex target: GL_TEXTURE_2D
			fbo->texId,             // 4. tex ID
			0);                    // 5. mipmap level: 0(base)

	// attach the renderbuffer to depth attachment point
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,      // 1. fbo target: GL_FRAMEBUFFER
			GL_DEPTH_ATTACHMENT_EXT, // 2. attachment point
			GL_RENDERBUFFER_EXT,     // 3. rbo target: GL_RENDERBUFFER
			fbo->rboId);              // 4. rbo ID

	// check FBO status
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	/*
	if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
		fprintf("OpenGL frame buffer status error.\n");
		*/

	// switch back to window-system-provided framebuffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	fbo->width = width;
	fbo->height = height;
	return fbo;
}

GLvoid delete_frame_buffer_object(OpenGL_frame_buffer_object *fbo)
{
	if(!fbo)
		return;
	if(glIsFramebufferEXT(fbo->fboId))
		glDeleteFramebuffersEXT(1, &fbo->fboId);
	if(glIsRenderbufferEXT(fbo->rboId))
		glDeleteRenderbuffersEXT(1, &fbo->rboId);
	if(glIsTexture(fbo->texId))
		glDeleteTextures(1, &fbo->texId);
	free(fbo);
}

GLuint * OpenGL_SelectMode(GLsizei size)
{
	GLvoid *buffer = NEW_II(GLuint, size);
	glSelectBuffer(size, buffer);
	glRenderMode(GL_SELECT);
	glInitNames();
	return buffer;
}
#endif

void Algo_ExtrameDistanceAlongDir(const vector3_t *dir, array* vertices, int *min, int *max)
{
	if(!dir || !vertices)
		return;
	float maxProj = - FLT_MAX , minProj = FLT_MAX ;
	float *v = (float *)(vertices->array);
	int i;
	for(i = 0 ; i < vertices->length; i += 3)
	{
		vector3_t p = {v[i], v[i + 1], v[i + 2]};
		float proj = Vector3_DotVector3(&p, dir);

		if(proj > maxProj)
		{
			maxProj = proj ;
			if(max)
				*max = i ;
		}

		if(proj < minProj)
		{
			minProj = proj ;
			if(min)
				*min = i ;
		}
	}// end for
}// end for extrameDistanceAlongDir

void Algo_ComputeAABBFromOriginalPointSet(array* vertices, vector3_t *min, vector3_t *max)
{
	if(!vertices)
		return;
	float *v = (float *)(vertices->array);
	int minX_i = 0 , maxX_i = 0 ;
	vector3_t vx = {1.0, 0.0, 0.0};
	Algo_ExtrameDistanceAlongDir(&vx, vertices, &minX_i, &maxX_i);
	if(min)
		min->x = v[minX_i];
	if(max)
		max->x = v[maxX_i];

	int minY_i = 0 , maxY_i = 0;
	vector3_t vy = {0.0, 1.0, 0.0};
	Algo_ExtrameDistanceAlongDir(&vy, vertices, &minY_i, &maxY_i);
	if(min)
		min->y = v[minY_i + 1];
	if(max)
		max->y = v[maxY_i + 1];

	int minZ_i = 0 , maxZ_i = 0;
	vector3_t vz = {0.0, 0.0, 1.0};
	Algo_ExtrameDistanceAlongDir(&vz, vertices, &minZ_i, &maxZ_i);
	if(min)
		min->z = v[minZ_i + 2];
	if(max)
		max->z = v[maxZ_i + 2];
}// end for computeAABBFromOriginalPointSet

void OpenGL_ExtractFrustum(GLfloat frustum[][4])
{
	memset(frustum, 0, sizeof(GLfloat) * 24);
	GLfloat proj[16];
	GLfloat modl[16];
	GLfloat clip[16];
	GLfloat t;
	/* Get the current PROJECTION matrix from OpenGL */
	oglGetFloatv( GL_PROJECTION_MATRIX, proj );
	/* Get the current MODELVIEW matrix from OpenGL */
	oglGetFloatv( GL_MODELVIEW_MATRIX, modl );
	/* Combine the two matrices (multiply projection by modelview)    */
	clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] +    modl[ 3] * proj[12];
	clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] +    modl[ 3] * proj[13];
	clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] +    modl[ 3] * proj[14];
	clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] +    modl[ 3] * proj[15];
	clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4]    + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
	clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] +    modl[ 7] * proj[13];
	clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] +    modl[ 7] * proj[14];
	clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] +    modl[ 7] * proj[15];
	clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4]    + modl[10] * proj[ 8] + modl[11] * proj[12];
	clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] +    modl[11] * proj[13];
	clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] +    modl[11] * proj[14];
	clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] +    modl[11] * proj[15];
	clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4]    + modl[14] * proj[ 8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] +    modl[15] * proj[13];
	clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] +    modl[15] * proj[14];
	clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] +    modl[15] * proj[15];
	/* Extract the numbers for the RIGHT plane */
	frustum[0][0] = clip[ 3] - clip[ 0];
	frustum[0][1] = clip[ 7] - clip[ 4];
	frustum[0][2] = clip[11] - clip[ 8];
	frustum[0][3] = clip[15] - clip[12];
	/* Normalize the result */
	t = sqrt( frustum[0][0] * frustum[0][0] + frustum[0][1] * frustum[0][1] + frustum[0][2]    * frustum[0][2] );
	frustum[0][0] /= t;
	frustum[0][1] /= t;
	frustum[0][2] /= t;
	frustum[0][3] /= t;
	/* Extract the numbers for the LEFT plane */
	frustum[1][0] = clip[ 3] + clip[ 0];
	frustum[1][1] = clip[ 7] + clip[ 4];
	frustum[1][2] = clip[11] + clip[ 8];
	frustum[1][3] = clip[15] + clip[12];
	/* Normalize the result */
	t = sqrt( frustum[1][0] * frustum[1][0] + frustum[1][1] * frustum[1][1] + frustum[1][2]    * frustum[1][2] );
	frustum[1][0] /= t;
	frustum[1][1] /= t;
	frustum[1][2] /= t;
	frustum[1][3] /= t;
	/* Extract the BOTTOM plane */
	frustum[2][0] = clip[ 3] + clip[ 1];
	frustum[2][1] = clip[ 7] + clip[ 5];
	frustum[2][2] = clip[11] + clip[ 9];
	frustum[2][3] = clip[15] + clip[13];
	/* Normalize the result */
	t = sqrt( frustum[2][0] * frustum[2][0] + frustum[2][1] * frustum[2][1] + frustum[2][2]    * frustum[2][2] );
	frustum[2][0] /= t;
	frustum[2][1] /= t;
	frustum[2][2] /= t;
	frustum[2][3] /= t;
	/* Extract the TOP plane */
	frustum[3][0] = clip[ 3] - clip[ 1];
	frustum[3][1] = clip[ 7] - clip[ 5];
	frustum[3][2] = clip[11] - clip[ 9];
	frustum[3][3] = clip[15] - clip[13];
	/* Normalize the result */
	t = sqrt( frustum[3][0] * frustum[3][0] + frustum[3][1] * frustum[3][1] + frustum[3][2]    * frustum[3][2] );
	frustum[3][0] /= t;
	frustum[3][1] /= t;
	frustum[3][2] /= t;
	frustum[3][3] /= t;
	/* Extract the FAR plane */
	frustum[4][0] = clip[ 3] - clip[ 2];
	frustum[4][1] = clip[ 7] - clip[ 6];
	frustum[4][2] = clip[11] - clip[10];
	frustum[4][3] = clip[15] - clip[14];
	/* Normalize the result */
	t = sqrt( frustum[4][0] * frustum[4][0] + frustum[4][1] * frustum[4][1] + frustum[4][2]    * frustum[4][2] );
	frustum[4][0] /= t;
	frustum[4][1] /= t;
	frustum[4][2] /= t;
	frustum[4][3] /= t;
	/* Extract the NEAR plane */
	frustum[5][0] = clip[ 3] + clip[ 2];
	frustum[5][1] = clip[ 7] + clip[ 6];
	frustum[5][2] = clip[11] + clip[10];
	frustum[5][3] = clip[15] + clip[14];
	/* Normalize the result */
	t = sqrt( frustum[5][0] * frustum[5][0] + frustum[5][1] * frustum[5][1] + frustum[5][2]    * frustum[5][2] );
	frustum[5][0] /= t;
	frustum[5][1] /= t;
	frustum[5][2] /= t;
	frustum[5][3] /= t;
}

int Algo_AABBInFrustum(GLfloat frustum[][4], GLfloat x, GLfloat y, GLfloat z, GLfloat x2, GLfloat y2, GLfloat z2)
{
	int p;
	for( p = 0; p < 6; p++ )
	{
		if( frustum[p][0] * x + frustum[p][1] * y + frustum[p][2]    * z + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * x2 + frustum[p][1] * y + frustum[p][2]    * z + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * x + frustum[p][1] * y2 + frustum[p][2]    * z + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * x2 + frustum[p][1] * y2 + frustum[p][2]    * z + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * x + frustum[p][1] * y + frustum[p][2]    * z2 + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * x2 + frustum[p][1] * y + frustum[p][2]    * z2 + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * x + frustum[p][1] * y2 + frustum[p][2]    * z2 + frustum[p][3] > 0 )
			continue;
		if( frustum[p][0] * x2 + frustum[p][1] * y2 + frustum[p][2]    * z2 + frustum[p][3] > 0 )
			continue;
		return 0;
	}
	return 1;
}

void OpenGL_InitFog(GLenum mode, GLfloat near, GLfloat far, GLfloat dis, GLfloat color[])
{
	glFogf(GL_FOG_MODE, mode);
	{
		glFogf(GL_FOG_START, near);
		glFogf(GL_FOG_END, far);
	}
	{
		glFogf(GL_FOG_DENSITY, dis);
	}
	glFogfv(GL_FOG_COLOR, color);
	//glFogi(GL_FOG_COORD_SRC, GL_FRAGMENT_DEPTH);
#ifndef _HARMATTAN_OPENGLES2
	glHint(GL_FOG_HINT, GL_FASTEST);
#endif
}

void OpenGLU_Project(GLdouble x, GLdouble y, GLdouble z, GLdouble *wx, GLdouble *wy, GLdouble *wz)
{
	if(!wx || !wy || !wz)
		return;
	GLdouble mv_m[16];
	GLdouble proj_m[16];
	GLint vp[4];
	glGetDoublev(GL_MODELVIEW_MATRIX, mv_m);
	glGetDoublev(GL_PROJECTION_MATRIX, proj_m);
	glGetIntegerv(GL_VIEWPORT, vp);
	gluProject(x, y, z, mv_m, proj_m, vp, wx, wy, wz);
}

void OpenGL_TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels, GLenum scale, GLsizei *rw, GLsizei *rh)
{
	if(scale == NO_SCALE)
	{
		glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
		return;
	}

	GLsizei fw = width;
	GLsizei fh = height;
	void *data = OpenGLU_ScaleImage(width, height, format, type, pixels, SCALE_AUTO, &fw, &fh);
	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, fw, fh, 0, format, type, data);
		if(rw)
			*rw = fw;
		if(rh)
			*rh = fh;
		free(data);
	}
	else
	{
		glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	}
}

texture * new_OpenGL_texture_2d_from_buffer_with_glCopyTexImage2D(GLint x, GLint y, GLsizei w, GLsizei h, GLenum format)
{
	if(w <= 0 || h <= 0)
		return NULL;
	texture *g_tex = NEW(texture);
	ZERO(g_tex, texture);
	g_tex->width = w;
	g_tex->height = h;
	g_tex->format = format;
	glGenTextures(1, &(g_tex->texid));
	oglBindTexture(GL_TEXTURE_2D, g_tex->texid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	
#ifdef _HARMATTAN_OPENGLES
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
#else
		glGenerateMipmap(GL_TEXTURE_2D);
#endif
	glCopyTexImage2D(GL_TEXTURE_2D, 0, g_tex->format, x, y, g_tex->width, g_tex->height, 0);
	oglBindTexture(GL_TEXTURE_2D, 0);

	return g_tex;
}

texture * new_OpenGL_texture_2d_from_buffer_with_glReadPixels(GLint x, GLint y, GLsizei w, GLsizei h, GLenum format)
{
	if(w <= 0 || h <= 0)
		return NULL;
	size_t u = 0;
	switch(format)
	{
		case GL_RGB:
			u = 3;
			break;
		case GL_RGBA:
			u = 4;
			break;
		case GL_ALPHA:
			u = 1;
			break;
		default:
			return NULL;
	}
	texture *g_tex = NEW(texture);
	ZERO(g_tex, texture);
	g_tex->width = w;
	g_tex->height = h;
	g_tex->format = format;
	glGenTextures(1, &(g_tex->texid));
	oglBindTexture(GL_TEXTURE_2D, g_tex->texid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	
#ifdef _HARMATTAN_OPENGLES
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
#else
		glGenerateMipmap(GL_TEXTURE_2D);
#endif
	u = u * sizeof(GLubyte) * g_tex->width * g_tex->height;
	GLubyte *data = NEW_II(GLubyte, u);
	OpenGL_ReadPixels(x, y, g_tex->width, g_tex->height, g_tex->format, GL_UNSIGNED_BYTE, data);
	GLsizei fw = g_tex->width;
	GLsizei fh = g_tex->height;
	void *dataout = OpenGLU_ScaleImage(g_tex->width, g_tex->height, g_tex->format, GL_UNSIGNED_BYTE, data, SCALE_AUTO, &fw, &fh);
	if(dataout)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, g_tex->format, fw, fh, 0, g_tex->format, GL_UNSIGNED_BYTE, dataout);
		free(dataout);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, g_tex->format, g_tex->width, g_tex->height, 0, g_tex->format, GL_UNSIGNED_BYTE, data);
	}
	oglBindTexture(GL_TEXTURE_2D, 0);
	free(data);

	return g_tex;
}

void * OpenGLU_ScaleImage(GLsizei width, GLsizei height, GLenum format, GLenum type, const void *datain, GLenum scale, GLsizei *rw, GLsizei *rh)
{
	if(scale == NO_SCALE)
		return NULL;
	double wn = log2((double)width);
	double w = 0.0;
	modf(wn, &w);
	double hn = log2((double)height);
	double h = 0.0;
	modf(hn, &h);
	if(w == wn && h == hn)
		return NULL;
	GLsizei fw = width;
	GLsizei fh = height;
	if(w != wn)
	{
		double n = (scale == SCALE_IN ? floor(wn) : (scale == SCALE_OUT ? ceil(wn) : Math_Round(wn)));
		fw = (GLsizei)pow(2, n);
		if(rw)
			*rw = fw;
	}
	if(h != hn)
	{
		double n = (scale == SCALE_IN ? floor(hn) : (scale == SCALE_OUT ? ceil(hn) : Math_Round(hn)));
		fh = (GLsizei)pow(2, n);
		if(rh)
			*rh = fh;
	}
	int bytes;
	int components;

	if ( type == GL_UNSIGNED_SHORT_5_6_5 || type == GL_UNSIGNED_SHORT_4_4_4_4
#ifndef _HARMATTAN_OPENGLES2
			|| type == GL_UNSIGNED_SHORT_4_4_4_4_REV 
#endif
			|| type == GL_UNSIGNED_SHORT_5_5_5_1
		 ) 
	{
		components = 1;
	}
	else
	{
		switch(format) {
			case GL_RGB:
				components = 3;
			case GL_LUMINANCE_ALPHA:
				components = 2;
			case GL_RGBA:
			case GL_BGRA:
				components = 4;
			default:
				components = 1;
		}
	}

	switch(type) {
		case GL_UNSIGNED_SHORT:
			bytes = sizeof(GLushort);
		case GL_SHORT:
			bytes = sizeof(GLshort);
		case GL_UNSIGNED_BYTE:
			bytes = sizeof(GLubyte);
		case GL_BYTE:
			bytes = sizeof(GLbyte);
		case GL_FLOAT:
			bytes = sizeof(GLfloat);
		case GL_UNSIGNED_SHORT_5_6_5:
		case GL_UNSIGNED_SHORT_4_4_4_4:
#ifndef _HARMATTAN_OPENGLES2
		case GL_UNSIGNED_SHORT_4_4_4_4_REV:
#endif
		case GL_UNSIGNED_SHORT_5_5_5_1:
			bytes = sizeof(GLushort);
		default:
			bytes = 4;
	}
	int size = bytes * fw * fh * components;
	char *dataout = NEW_II(char, size);
	/*
		 printfi(size);
		 printfi(fw);
		 printfi(fh);
		 printfi(width);
		 printfi(height);
		 */
	gluScaleImage(format, width, height, type, datain, fw, fh, type, dataout);
	if(rw)
		*rw = fw;
	if(*rh)
		*rh = fh;
	return dataout;
}

// invert height
void OpenGL_ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels)
{
	glReadPixels(x, y, width, height, format, type, pixels);
	GLsizei c = 0;
	switch(type)
	{
		case GL_UNSIGNED_BYTE:
			c = sizeof(GLubyte);
			break;
		default:
			return;
	}
	size_t u = 0;
	switch(format)
	{
		case GL_RGB:
			u = 3;
			break;
		case GL_RGBA:
			u = 4;
			break;
		case GL_ALPHA:
			u = 1;
			break;
		default:
			return;
	}
	size_t len = c * u * sizeof(GLubyte);
	GLubyte *temp = NEW_II(GLubyte, c * u);
	GLsizei h;
	for(h = 0; h < height / 2; h++)
	{
		GLsizei w;
		for(w = 0; w < width; w++)
		{
			memcpy(temp, ((GLubyte *)pixels) + (len * (h * width + w)), len);
			memcpy(((GLubyte *)pixels) + (c * u * (h * width + w)), ((GLubyte *)pixels) + (c * u * ((height - h - 1) * width + w)), len);
			memcpy(((GLubyte *)pixels) + (c * u * ((height - h - 1) * width + w)), temp, len);
		}
	}
	free(temp);
}

GLvoid OpenGL_Color3fv(x11_color_type c)
{
	if(c < other_color)
#ifdef _HARMATTAN_OPENGL
		glColor3fv(X11_Color[c]);
#else
		glColor4fv(X11_Color[c]);
#endif
}

GLvoid OpenGL_Color4fv(x11_color_type c, GLclampf alpha)
{
	if(c < other_color)
	{
		X11_Color[c][3] = alpha;
		glColor4fv(X11_Color[c]);
	}
}

const GLfloat * Color_GetColor(x11_color_type c, GLclampf alpha)
{
	if(c < other_color)
	{
		X11_Color[c][3] = alpha;
		return X11_Color[c];
	}
	return NULL;
}
