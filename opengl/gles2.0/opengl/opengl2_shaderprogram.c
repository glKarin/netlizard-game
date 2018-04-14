#include "opengl2.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * gl2LoadShaderSource(const char *file)
{
	if(!file)
		return NULL;
	FILE *in = fopen(file, "r");
	fseek(in, 0, SEEK_END);
	long len = ftell(in);
	fseek(in, 0, SEEK_SET);
	char *src = calloc(len + sizeof(char), sizeof(char));
	fread(src, sizeof(char), len, in);
	fclose(in);
	//printf("%s\n", src);
	return src;
}

GLuint gl2LoadShader(GLenum type, const char *src)
{
	if(!src)
		return 0;
	GLuint shader = glCreateShader(type);
	if(shader == 0)
		return 0;
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);
	if(gl2ShaderIsCompiled(shader))
		return shader;
	else
	{
		glDeleteShader(shader);
		return 0;
	}
}

GLboolean gl2ShaderIsCompiled(GLuint shader)
{
	if(!glIsShader(shader))
		return GL_FALSE;
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if(!compiled)
	{
		GLint len = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		if(len > 1)
		{
			char *log = calloc(len, sizeof(char));
			glGetShaderInfoLog(shader, len, NULL, log);
			fprintf(stderr, "%d - %s\n", shader, log);
			free(log);
		}
		return GL_FALSE;
	}
	return GL_TRUE;
}

GLboolean gl2ProgramIsLinked(GLuint program)
{
	if(!glIsProgram(program))
		return GL_FALSE;
	GLint linked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if(!linked)
	{
		GLint len = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
		if(len > 1)
		{
			char *log = calloc(len, sizeof(char));
			glGetProgramInfoLog(program, len, NULL, log);
			fprintf(stderr, "%d - %s\n", program, log);
			free(log);
		}
		return GL_FALSE;
	}
	return GL_TRUE;
}

GLboolean gl2LinkShaderToProgram(GLuint program, GLuint vshader, GLuint fshader)
{
	if(!glIsProgram(program))
		return GL_FALSE;
	GLboolean vis = glIsShader(vshader);
	GLboolean fis = glIsShader(fshader);
	if(!vis && !fis)
		return GL_FALSE;
	if(vis)
		glAttachShader(program, vshader);
	if(fis)
		glAttachShader(program, fshader);
	glLinkProgram(program);
	return gl2ProgramIsLinked(program);
}

GLboolean gl2LoadProgramByFile(const char *vfile, const char *ffile, GLuint *rp, GLuint *rvs, GLuint *rfs)
{
	if(!vfile || !ffile || !rp || !rvs || !rfs)
		return GL_FALSE;
	char *vsrc = gl2LoadShaderSource(vfile);
	if(!vsrc)
		return GL_FALSE;
	char *fsrc = gl2LoadShaderSource(ffile);
	if(!fsrc)
	{
		free(vsrc);
		return GL_FALSE;
	}
	GLboolean r = gl2LoadProgram(vsrc, fsrc, rp, rvs, rfs);

	free(vsrc);
	free(fsrc);
	return r;
}

GLboolean gl2LoadProgram(char *vsrc, char *fsrc, GLuint *rp, GLuint *rvs, GLuint *rfs)
{
	if(!vsrc || !fsrc || !rp || !rvs || !rfs)
		return GL_FALSE;

	GLuint vshader = 0;
	GLuint fshader = 0;
	GLuint program = 0;
	GLboolean r = GL_FALSE;

	vshader = gl2LoadShader(GL_VERTEX_SHADER, vsrc);
	if(glIsShader(vshader))
	{
		fshader = gl2LoadShader(GL_FRAGMENT_SHADER, fsrc);
		if(glIsShader(fshader))
		{
			program = glCreateProgram();
			if(glIsProgram(program))
			{
				if(gl2LinkShaderToProgram(program, vshader, fshader))
				{
					*rp = program;
					*rvs = vshader;
					*rfs = fshader;
					r = GL_TRUE;
				}
			}
		}
	}

	if(!r)
	{
		if(glIsShader(vshader))
			glDeleteShader(vshader);
		if(glIsShader(fshader))
			glDeleteShader(fshader);
		if(glIsProgram(program))
			glDeleteProgram(program);
	}
	return r;
}
