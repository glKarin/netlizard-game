#ifndef KARIN_FONT_H
#define KARIN_FONT_H

#include "glk/glk.h"
#include "nl_gl.h"

typedef enum _font_type
{
	x11_font_type = 0,
	netlizard_font_type
} font_type;

typedef struct _x_font
{
	GLuint begin;
	GLuint end;
} x_font;

typedef struct _font
{
	font_type type;
	union
	{
		x_font x;
		GL_NETLizard_Font *netlizard;
	} fnt;
	GLuint width;
	GLuint height;
} font;

font * new_x_font(font *fnt, const char *name, GLuint b, GLuint e);
font * new_netlizard_font(font *fnt, const char *mapf, const char *texf);
void delete_font(font *f);
void Font_RenderString(const font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, const char *str);
void Font_RenderDigit(const font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLint num);
void Font_RenderChar(const font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, char ch);

GLfloat Font_GetStringWidth(const font *f, const char *str);
GLint Font_GetCharCountOfWidth(const font *f, GLfloat width, const char *str);

int Font_GetDigitCenterPosition(const font *fnt, GLfloat x, GLfloat y, GLfloat w, GLfloat h, int num, GLfloat *rx, GLfloat *ry);
int Font_GetStringCenterPosition(const font *fnt, GLfloat x, GLfloat y, GLfloat w, GLfloat h, const char *str, GLfloat *rx, GLfloat *ry);
#endif
