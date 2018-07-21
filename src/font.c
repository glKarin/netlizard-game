#include "font.h"
#include "nl_std.h"
#include "netlizard/netlizard.h"

#include <stdlib.h>
#include <string.h>

#define FONT_BEGIN 1
#define FONT_END '~'
#define DEFAULT_FONT_FAMILY "fixed"

static void Font_RenderXFontString(const x_font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, const char *str);
static void Font_RenderXFontDigit(const x_font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLint num);
static void Font_RenderXFontChar(const x_font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, char ch);

static void Font_RenderNETLizardFontString(const GL_NETLizard_Font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, const char *str);
static void Font_RenderNETLizardFontDigit(const GL_NETLizard_Font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLint num);
static void Font_RenderNETLizardFontChar(const GL_NETLizard_Font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, char ch);

font * new_netlizard_font(font *fnt, const char *mapf, const char *texf)
{
	if(!mapf || !texf)
		return NULL;
	RETURN_PTR(f, fnt, font)
		GL_NETLizard_Font *nf = NETLizard_ReadFont(mapf, texf);
	if(nf)
	{
		GLfloat w = 0;
		GLfloat h = 0;
		GLuint i;
		for(i = 0; i < nf->char_map_count; i++)
		{
			if(i == 0)
			{
				w = nf->char_map[i].width;
				h = nf->char_map[i].height;
			}
			else
			{
				if(w < nf->char_map[i].width)
					w = nf->char_map[i].width;
				if(h < nf->char_map[i].height)
					h = nf->char_map[i].height;
			}
		}
		f->width = (GLuint)w;
		f->height = (GLuint)h;
	}

	f->type = netlizard_font_type;
	f->fnt.netlizard = nf;
	return f;
}

font * new_x_font(font *fnt, const char *name, GLuint b, GLuint e)
{
#ifndef _HARMATTAN_OPENGL
	return NULL;
#else
	if(!name)
		return NULL;
	RETURN_PTR(f, fnt, font)
		if(b > e)
		{
			GLuint tmp = b;
			b = e;
			e = tmp;
		}
	f->fnt.x.begin = b;
	f->fnt.x.end = e;
	unsigned int w = 0;
	unsigned int h = 0;
	karinUseXFont(name, b, e, b, &w, &h);
	f->width = w;
	f->height = h;
	f->type = x11_font_type;
	return f;
#endif
}

void delete_font(font *f)
{
	if(!f)
		return;
	if(f->type == netlizard_font_type)
	{
		if(f->fnt.netlizard)
		{
			delete_GL_NETLizard_Font(f->fnt.netlizard);
			free(f->fnt.netlizard);
		}
	}
#ifdef _HARMATTAN_OPENGL
	else
		glDeleteLists(f->fnt.x.begin, f->fnt.x.end - f->fnt.x.begin);
#endif
}

void Font_RenderString(const font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, const char *str)
{
	if(!f || !str)
		return;

	if(f->type == netlizard_font_type)
		Font_RenderNETLizardFontString(f->fnt.netlizard, x, y, r, g, b, a, str);
	else
		Font_RenderXFontString(&f->fnt.x, x, y, r, g, b, a, str);
}

void Font_RenderDigit(const font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLint num)
{
	if(!f)
		return;

	if(f->type == netlizard_font_type)
		Font_RenderNETLizardFontDigit(f->fnt.netlizard, x, y, r, g, b, a, num);
	else
		Font_RenderXFontDigit(&f->fnt.x, x, y, r, g, b, a, num);
}

void Font_RenderChar(const font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, char ch)
{
	if(!f)
		return;

	if(f->type == netlizard_font_type)
		Font_RenderNETLizardFontChar(f->fnt.netlizard, x, y, r, g, b, a, ch);
	else
		Font_RenderXFontChar(&f->fnt.x, x, y, r, g, b, a, ch);
}

void Font_RenderXFontString(const x_font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, const char *str)
{
#ifdef _HARMATTAN_OPENGL
	if(!f || !str)
		return;

	glPushAttrib(GL_CURRENT_BIT);
	{
		glColor4f(r, g, b, a);
		if(x >= 0 && y >= 0)
		{
			glRasterPos2f(x, y);
			for(; *str; str++)
			{
				if(*str >= f->begin && *str <= f->end)
					glCallList(*str);
				else
					glCallList('?');
			}
		}
		else
		{
			for(; *str; str++)
			{
				if(*str >= f->begin && *str <= f->end)
					glCallList(*str);
				else
					glCallList('?');
			}
		}
	}
	glPopAttrib();
#endif
}

void Font_RenderXFontDigit(const x_font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLint num)
{
#ifdef _HARMATTAN_OPENGL
	if(!f)
		return;
	char *str = itostr(num);
	Font_RenderXFontString(f, x, y, r, g, b, a, str);
	//printf("|%s|\n", str);
	free(str);
#endif
}

void Font_RenderXFontChar(const x_font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, char ch)
{
#ifdef _HARMATTAN_OPENGL
	if(!f)
		return;

	glPushAttrib(GL_CURRENT_BIT);
	{
		glColor4f(r, g, b, a);
		if(x >= 0 && y >= 0)
		{
			glRasterPos2f(x, y);
			glCallList(ch);
		}
		else
			glCallList(ch);
	}
	glPopAttrib();
#endif
}

void Font_RenderNETLizardFontString(const GL_NETLizard_Font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, const char *str)
{
	if(!f || !str)
		return;

	glPushAttrib(GL_CURRENT_BIT);
	{
		glColor4f(r, g, b, a);
		glPushMatrix();
		{
			glTranslatef(x, y, 0.0);
			size_t len = strlen(str);
			unsigned int i;
			for(i = 0; i < len; i++)
			{
				GLint index = NETLizard_GetFontIndex(f, str[i]);
				if(index == -1)
					index = 0;
				NETLizard_RenderFontChar(f, index);
				glTranslatef(f->char_map[index].width + f->char_map[index].x_strip, 0.0, 0.0);
			}
		}
		glPopMatrix();
	}
	glPopAttrib();
}

void Font_RenderNETLizardFontDigit(const GL_NETLizard_Font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLint num)
{
	if(!f)
		return;
	char *str = itostr(num);
	Font_RenderNETLizardFontString(f, x, y, r, g, b, a, str);
	free(str);
}

void Font_RenderNETLizardFontChar(const GL_NETLizard_Font *f, GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, char ch)
{
	if(!f)
		return;

	glPushAttrib(GL_CURRENT_BIT);
	{
		glColor4f(r, g, b, a);
		glPushMatrix();
		{
			glTranslatef(x, y, 0.0);
			GLint index = NETLizard_GetFontIndex(f, ch);
			if(index == -1)
				index = 0;
			NETLizard_RenderFontChar(f, index);
		}
		glPopMatrix();
	}
	glPopAttrib();
}

GLfloat Font_GetStringWidth(const font *f, const char *str)
{
	if(!f || !str)
		return 0;
	size_t len = strlen(str);
	if(f->type == x11_font_type)
		return (GLfloat)(len * f->width);
	else
	{
		GLfloat w = 0.0;
		size_t i;
		for(i = 0; i < len; i++)
		{
			GLint index = NETLizard_GetFontIndex(f->fnt.netlizard, str[i]);
			if(index == -1)
				index = 0;
			w += f->fnt.netlizard->char_map[index].width;
			if(i < len - 1)
				w += f->fnt.netlizard->char_map[index].x_strip;
		}
		return w;
	}
}

GLint Font_GetCharCountOfWidth(const font *f, GLfloat width, const char *str)
{
	if(!f || !str)
		return -1;
	if(width <= 0.0)
		return -1;
	size_t len = strlen(str);
	if(f->type == x11_font_type)
		return(KARIN_MIN((GLuint)(width / f->width), len));
	else
	{
		GLfloat w = 0.0;
		size_t i;
		for(i = 0; i < len; i++)
		{
			GLint index = NETLizard_GetFontIndex(f->fnt.netlizard, str[i]);
			if(index == -1)
				index = 0;
			w += f->fnt.netlizard->char_map[index].width;
			if(i < len - 1)
				w += f->fnt.netlizard->char_map[index].x_strip;
			if(w >= width)
				break;
		}
		return i;
	}
}

int Font_GetDigitCenterPosition(const font *fnt, GLfloat x, GLfloat y, GLfloat w, GLfloat h, int num, GLfloat *rx, GLfloat *ry)
{
	if(!fnt || !rx || !ry)
		return 0;
	char *str = itostr(num);
	int r = Font_GetStringCenterPosition(fnt, x, y, w, h, str, rx, ry);
	free(str);
	return r;
}

int Font_GetStringCenterPosition(const font *fnt, GLfloat x, GLfloat y, GLfloat w, GLfloat h, const char *str, GLfloat *rx, GLfloat *ry)
{
	if(!fnt || !str || (!rx && !ry))
		return 0;
	GLfloat len = Font_GetStringWidth(fnt, str);
	if(len <= 0.0)
		return 0;
	if(rx)
		*rx = x + (w / 2 - len / 2);
	if(ry)
		*ry = y + (h / 2 - fnt->height / 2);
	return 1;
}
