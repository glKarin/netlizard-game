#include "opengl2.h"

#include "opengl2_def.h"
#include "opengl2_math.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define VSHADER_FILE "./glsl/vertex_shader.vert"
#define FSHADER_FILE "./glsl/fragment_shader.frag"

// attribute
// vertex shader
#define A_POSITION "vPosition"
#define A_NORMAL "vNormal"
#define A_TEXCOORD "vTexcoord"
#define A_COLOR "vColor"

// uniform
// vertex shader
#define U_MODELVIEW_MATRIX "vModelviewMatrix"
#define U_PROJECTION_MATRIX "vProjectionMatrix"
#define U_MODELVIEWPROJECTION_MATRIX "vModelviewProjectionMatrix"
#define U_POINT_SIZE "vPointSize"

// fragment shader
#define U_TEXTURE "fTexture"
#define U_ALPHA_TEST__ENABLED "fAlphaTest.enabled"
#define U_ALPHA_TEST__FUNC "fAlphaTest.func"
#define U_ALPHA_TEST__REF "fAlphaTest.ref"
#define U_COLOR "fColor"
#define U_BIND_TEXTURE "fBindTexture"
#define U_FOG__ENABLED "fFog.enabled"
#define U_FOG__MODE "fFog.mode"
#define U_FOG__DENSITY "fFog.density"
#define U_FOG__COLOR "fFog.color"
#define U_FOG__START "fFog.start"
#define U_FOG__END "fFog.end"

extern GL2_Matrix44 * gl2GetTopMatrixByMode(GLenum mode);
extern GLvoid gl2InitMatrixStack(GLvoid);

typedef enum _Shader_Attribute_Name
{
	vPosition = 0,
	vNormal,
	vTexcoord,
	vColor,
	Total_Attribute_Name
} Shader_Attribute_Name;

typedef enum _Shader_Uniform_Name
{
	vModelviewMatrix = 0,
	vProjectionMatrix,
	vModelviewProjectionMatrix,
	vPointSize,
	fAlphaTest_enabled,
	fAlphaTest_func,
	fAlphaTest_ref,
	fTexture,
	fColor,
	fBindTexture,
	fFog_enabled,
	fFog_mode,
	fFog_density,
	fFog_color,
	fFog_start,
	fFog_end,
	Total_Uniform_Name
} Shader_Uniform_Name;

static GLuint attribute_locations[Total_Attribute_Name];
static GLuint uniform_locations[Total_Uniform_Name];
static const char *Attribute_Names[Total_Attribute_Name] = {
	A_POSITION,
	A_NORMAL,
	A_TEXCOORD,
	A_COLOR
};
static const char *Uniform_Names[Total_Uniform_Name] = {
	U_MODELVIEW_MATRIX,
	U_PROJECTION_MATRIX,
	U_MODELVIEWPROJECTION_MATRIX,
	U_POINT_SIZE,
	U_ALPHA_TEST__ENABLED,
	U_ALPHA_TEST__FUNC,
	U_ALPHA_TEST__REF,
	U_TEXTURE,
	U_COLOR,
	U_BIND_TEXTURE,
	U_FOG__ENABLED,
	U_FOG__MODE,
	U_FOG__DENSITY,
	U_FOG__COLOR,
	U_FOG__START,
	U_FOG__END
};

GLfloat point_size = 1.0;
GLfloat current_color[4] = {1.0, 1.0, 1.0, 1.0};
GL2_Matrix44 *modelview_matrix = NULL;
GL2_Matrix44 *projection_matrix = NULL;
GL2_Matrix44 modelview_projection_matrix;
GL2_Alpha_Test alpha_test = {GL_FALSE, GL_ALWAYS, 0.0};
GL2_Fog fog = {GL_FALSE, GL_EXP, 1.0, 0.0, 1.0, {0.0, 0.0, 0.0, 0.0}};
GLboolean bind_texture = GL_FALSE;

GLuint program = 0;
GLuint vshader = 0;
GLuint fshader = 0;

GLboolean gl2_init = GL_FALSE;
static GLuint blank_tex = 0;

extern GLenum last_error;

static GLuint gl2MakeBlankTexture(const GLfloat color[], GLuint width, GLuint height)
{
	GLfloat c[] = {1.0, 1.0, 1.0, 1.0};
	if(color)
	{
		arrcpy16(c, color)
	}
	GLuint w = width;
	GLuint h = height;
	if(w < 2)
		w = 2;
	if(h < 2)
		h = 2;
	unsigned int size = w * h;
	GLfloat *data = calloc(size * 4, sizeof(GLfloat));
	int i;
	for(i = 0; i < size; i++)
	{
		data[i * 4] = c[0];
		data[i * 4 + 1] = c[1];
		data[i * 4 + 2] = c[2];
		data[i * 4 + 3] = c[3];
	}
	GLuint t = 0;
	glGenTextures(1, &t);
	glBindTexture(GL_TEXTURE_2D, t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_FLOAT, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	free(data);
	return t;
}

GLvoid gl2Color4(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
{
	current_color[0] = r;
	current_color[1] = g;
	current_color[2] = b;
	current_color[3] = a;
}

GLvoid gl2PointSize(GLfloat size)
{
	if(size <= 0.0f)
		last_error = GL2_INVALID_VALUE;
	point_size = size;
}

GLvoid gl2InitProgram(GLvoid)
{
	if(gl2_init)
		return;
	gl2_init = gl2LoadProgramByFile(VSHADER_FILE, FSHADER_FILE, &program, &vshader, &fshader);
	if(!gl2_init)
		return;

	glUseProgram(program);

	unsigned int i;
	for(i = 0; i < Total_Attribute_Name; i++)
	{
		attribute_locations[i] = glGetAttribLocation(program, Attribute_Names[i]);
	}
	for(i = 0; i < Total_Uniform_Name; i++)
	{
		uniform_locations[i] = glGetUniformLocation(program, Uniform_Names[i]);
	}

	gl2InitMatrixStack();
	modelview_matrix = gl2GetTopMatrixByMode(GL2_MODELVIEW);
	projection_matrix = gl2GetTopMatrixByMode(GL2_PROJECTION);

	blank_tex = gl2MakeBlankTexture(NULL, 2, 2);
}

GLvoid gl2DestroyProgram(GLvoid)
{
	if(!gl2_init)
		return;
	if(glIsTexture(blank_tex))
		glDeleteTextures(1, &blank_tex);
	glUseProgram(0);
	glDetachShader(program, vshader);
	glDetachShader(program, fshader);
	glDeleteShader(vshader);
	glDeleteShader(fshader);
	glDeleteProgram(program);
}

GLvoid gl2Render(GLvoid)
{
	if(!gl2_init)
		return;

	modelview_matrix = gl2GetTopMatrixByMode(GL2_MODELVIEW);
	projection_matrix = gl2GetTopMatrixByMode(GL2_PROJECTION);
	arrcpy16(modelview_projection_matrix.m, projection_matrix->m);
	Mesa_glMultMatrix(&modelview_projection_matrix, modelview_matrix->m);

	// matrix
	glUniformMatrix4fv(uniform_locations[vModelviewMatrix], 1, GL_FALSE, modelview_matrix->m);
	glUniformMatrix4fv(uniform_locations[vProjectionMatrix], 1, GL_FALSE, projection_matrix->m);
	glUniformMatrix4fv(uniform_locations[vModelviewProjectionMatrix], 1, GL_FALSE, modelview_projection_matrix.m);

	// current
	glUniform1i(uniform_locations[vPointSize], point_size);
	glUniform4fv(uniform_locations[fColor], 1, current_color);

	/*
	// Alpha test
	glUniform1i(uniform_locations[fAlphaTest_enabled], alpha_test.enabled);
	glUniform1i(uniform_locations[fAlphaTest_func], alpha_test.func);
	glUniform1i(uniform_locations[fAlphaTest_ref], alpha_test.ref);
	*/

	// Fog
	glUniform1i(uniform_locations[fFog_enabled], fog.enabled);
	glUniform1i(uniform_locations[fFog_mode], fog.mode);
	glUniform1f(uniform_locations[fFog_density], fog.density);
	glUniform1f(uniform_locations[fFog_start], fog.start);
	glUniform1f(uniform_locations[fFog_end], fog.end);
	glUniform4fv(uniform_locations[fFog_color], 1, fog.color);

	// texture0
	glActiveTexture(GL_TEXTURE0);
	//glUniform1i(uniform_locations[fBindTexture], bind_texture);
	glUniform1i(uniform_locations[fTexture], 0); // active texture is GL_TEXTURE0
}

GLvoid gl2DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
{
	gl2Render();
	glDrawElements(mode, count, type, indices);
}

GLvoid gl2DrawArrays(GLenum mode, GLint first, GLsizei count)
{
	gl2Render();
	glDrawArrays(mode, first, count);
}

GLvoid gl2EnableClientState(GLenum cap)
{
	switch(cap)
	{
		case GL2_VERTEX_ARRAY:
			glEnableVertexAttribArray(attribute_locations[vPosition]);
			break;
		case GL2_NORMAL_ARRAY:
			glEnableVertexAttribArray(attribute_locations[vNormal]);
			break;
		case GL2_COLOR_ARRAY:
			glEnableVertexAttribArray(attribute_locations[vColor]);
			break;
		case GL2_TEXTURE_COORD_ARRAY:
			glEnableVertexAttribArray(attribute_locations[vTexcoord]);
			break;
		default:
			last_error = GL2_INVALID_ENUM;
			break;
	}
}

GLvoid gl2DisableClientState(GLenum cap)
{
	switch(cap)
	{
		case GL2_VERTEX_ARRAY:
			glDisableVertexAttribArray(attribute_locations[vPosition]);
			break;
		case GL2_NORMAL_ARRAY:
			glDisableVertexAttribArray(attribute_locations[vNormal]);
			break;
		case GL2_COLOR_ARRAY:
			glDisableVertexAttribArray(attribute_locations[vColor]);
			break;
		case GL2_TEXTURE_COORD_ARRAY:
			glDisableVertexAttribArray(attribute_locations[vTexcoord]);
			break;
		default:
			last_error = GL2_INVALID_ENUM;
			break;
	}
}

GLvoid gl2VertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *ptr)
{
	glVertexAttribPointer(attribute_locations[vPosition], size, type, GL_FALSE, stride, ptr);
}

GLvoid gl2NormalPointer(GLenum type, GLsizei stride, const GLvoid *ptr)
{
	glVertexAttribPointer(attribute_locations[vNormal], 3, type, GL_FALSE, stride, ptr);
}

GLvoid gl2ColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *ptr)
{
	glVertexAttribPointer(attribute_locations[vColor], size, type, GL_FALSE, stride, ptr);
}

GLvoid gl2TexCoordPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *ptr)
{
	glVertexAttribPointer(attribute_locations[vTexcoord], size, type, GL_FALSE, stride, ptr);
}

GLvoid glShadeModel(GLenum model)
{
}

GLvoid gl2AlphaFunc(GLenum func, GLclampf ref)
{
	switch(func)
	{
		case GL_NEVER:
		case GL_LESS:
		case GL_EQUAL:
		case GL_LEQUAL:
		case GL_GREATER:
		case GL_NOTEQUAL:
		case GL_GEQUAL:
		case GL_ALWAYS:
			alpha_test.func = func;
			alpha_test.ref = ref;
			break;
		default:
			last_error = GL2_INVALID_VALUE;
			break;
	}
}

GLvoid gl2BindTexture(GLenum tar, GLuint tex)
{
	bind_texture = glIsTexture(tex);
	if(tex == 0)
		glBindTexture(tar, blank_tex);
	else
		glBindTexture(tar, tex);
}

GLvoid gl2Fogf(GLenum pname, GLfloat param)
{
	switch(pname)
	{
		case GL2_FOG_DENSITY:
			fog.density = param;
			break;
		case GL2_FOG_START:
			fog.start = param;
			break;
		case GL2_FOG_END:
			fog.end = param;
			break;
		case GL2_FOG_MODE:
			glFogi(pname, (GLenum)param);
			break;
		case GL2_FOG_COLOR:
		default:
			last_error = GL2_INVALID_ENUM;
			break;
	}
}

GLvoid gl2Fogfv(GLenum pname, const GLfloat *params)
{
	switch(pname)
	{
		case GL2_FOG_COLOR:
			arrcpy4(fog.color, params)
			break;
		case GL2_FOG_DENSITY:
			fog.density = *params;
			break;
		case GL2_FOG_START:
			fog.start = *params;
			break;
		case GL2_FOG_END:
			fog.end = *params;
			break;
		case GL2_FOG_MODE:
			glFogi(pname, (GLenum)(*params));
			break;
		default:
			last_error = GL2_INVALID_ENUM;
			break;
	}
}

GLvoid gl2Fogi(GLenum pname, GLint param)
{
	switch(pname)
	{
		case GL2_FOG_MODE:
			if(param == GL_LINEAR || param == GL2_EXP || param == GL2_EXP2)
				fog.mode = param;
			else
				last_error = GL2_INVALID_VALUE;
			break;
		case GL2_FOG_DENSITY:
			fog.density = (GLfloat)param;
			break;
		case GL2_FOG_START:
			fog.start = (GLfloat)param;
			break;
		case GL2_FOG_END:
			fog.end = (GLfloat)param;
			break;
		case GL2_FOG_COLOR:
		default:
			last_error = GL2_INVALID_ENUM;
			break;
	}
}

GLvoid gl2Fogiv(GLenum pname, const GLint *params)
{
	switch(pname)
	{
		case GL2_FOG_MODE:
			glFogi(pname, *params);
			break;
		case GL2_FOG_DENSITY:
			fog.density = (GLfloat)(*params);
			break;
		case GL2_FOG_START:
			fog.start = (GLfloat)(*params);
			break;
		case GL2_FOG_END:
			fog.end = (GLfloat)(*params);
			break;
		case GL2_FOG_COLOR:
			arrcpy4(fog.color, (GLfloat)params)
			break;
		default:
			last_error = GL2_INVALID_ENUM;
			break;
	}
}
