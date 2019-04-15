#include "nl_gl.h"
#include "netlizard/font_reader.h"
#include "gl_util.h"

#include <string.h>
#include <stdlib.h>

GL_NETLizard_Font * NETLizard_ReadFont(const char *map_file, const char *tex_file)
{
	if(!map_file || !tex_file)
		return NULL;
	NETLizard_Font *o = nlReadNETLizardFont(map_file);
	if(!o)
		return NULL;
	texture *tex = new_OpenGL_texture_2d(tex_file);
	if(!tex)
	{
		delete_NETLizard_Font(o);
		free(o);
		return NULL;
	}
	GL_NETLizard_Font *fnt = NEW(GL_NETLizard_Font);
	ZERO(fnt, GL_NETLizard_Font);
	fnt->tex = tex;
	fnt->private_m = o->private_m;
	fnt->private_l = o->private_l;
	fnt->private_e = o->private_e;
	fnt->char_count = o->char_count;
	fnt->offset = NEW_II(GLbyte, o->offset->length);
	signed char *offset = (signed char *)(o->offset->array);
	int i;
	for(i = 0; i < o->offset->length; i++)
	{
		fnt->offset[i] = offset[i];
	}
	fnt->char_map_count = o->char_raster_map->length;
	fnt->char_map = NEW_II(GL_NETLizard_Font_Char, o->char_raster_map->length);
	NETLizard_Font_Char_Raster *f = (NETLizard_Font_Char_Raster *)(o->char_raster_map->array);
	for(i = 0; i < o->char_raster_map->length; i++)
	{
		GL_NETLizard_Font_Char *c = fnt->char_map + i;
		c->width = (GLfloat)f[i].width;
		c->height = (GLfloat)f[i].height;
		c->x_strip = (GLfloat)f[i].x_strip;
		c->y_strip = (GLfloat)f[i].y_strip;
		GLfloat vertex[] = {
			0.0, 0.0,
			c->width, 0.0,
			0.0, c->height,
			c->width, c->height
		};
		GLfloat texcoord[] = {
			(GLfloat)f[i].x / tex->width, ((GLfloat)f[i].y + c->height) / tex->height,
			((GLfloat)f[i].x + c->width) / tex->width, ((GLfloat)f[i].y + c->height) / tex->height,
			(GLfloat)f[i].x / tex->width, ((GLfloat)f[i].y) / tex->height,
			((GLfloat)f[i].x + c->width) / tex->width, ((GLfloat)f[i].y)  / tex->height
		};
			c->buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), vertex, GL_STATIC_DRAW);
			c->buffers[texcoord_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), texcoord, GL_STATIC_DRAW);
	}
	return fnt;
}

GLvoid delete_GL_NETLizard_Font(GL_NETLizard_Font *fnt)
{
	if(!fnt)
		return;
	if(fnt->tex)
	{
		if(glIsTexture(fnt->tex->texid))
			glDeleteTextures(1, &fnt->tex->texid);
	}
	free(fnt->offset);
	GLuint i;
	for(i = 0; i < fnt->char_map_count; i++)
	{
		GL_NETLizard_Font_Char *c = fnt->char_map + i;
		int j;
		for(j = vertex_buffer_type; j < total_buffer_type; j++)

		{
			if(glIsBuffer(c->buffers[j]))
				glDeleteBuffers(1, c->buffers + j);
		}
	}
	free(fnt->char_map);
}

GLvoid NETLizard_RenderFontChar(const GL_NETLizard_Font *fnt, GLuint i)
{
	if(!fnt)
		return;
	if(i >= fnt->char_map_count)
		return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	if(fnt->tex)
		oglBindTexture(GL_TEXTURE_2D, fnt->tex->texid);
	const GL_NETLizard_Font_Char *c = fnt->char_map + i;
	glBindBuffer(GL_ARRAY_BUFFER, c->buffers[vertex_buffer_type]);
	glVertexPointer(2, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, c->buffers[texcoord_buffer_type]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glPushMatrix();
	{
		glTranslatef(0.0, c->y_strip, 0.0);
		oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	glPopMatrix();
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	oglBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

GLint NETLizard_GetFontIndex(const GL_NETLizard_Font *fnt, int paramInt)
{
	if(!fnt)
		return -1;
	int ch = paramInt;
	int n = ch;
	if (ch == 946) {
		n = 223;
	}
	if ((n >= 192) && (n - 192 < fnt->offset_count))
	{
		if ((ch = fnt->offset[(n - 192)]) < 0)
		{
			ch = -ch;
			n = 100;
			if (fnt->private_e) {
				n = 201;
			}
			return n + ch;
		}
		n = 100;
		if (fnt->private_e) {
			n = 165;
		}
		return n + ch;
	}
	if (n > 848) {
		n = ch - 848;
	}
	if ((n >= 97) && (n <= 122))
	{
		if (fnt->private_l) {
			n += 35;
		} else {
			n -= 32;
		}
	}
	else if ((n >= 192) && (n <= 223)) {
		n -= 96;
	} else if ((n >= 224) && (n <= 255))
	{
		if (fnt->private_m) {
			n -= 61;
		} else {
			n -= 128;
		}
	}
	else if ((n >= 154) && (n <= 191)) {
		n -= 26;
	}
	n -= 32;
	if ((n < 0) || (n >= fnt->char_count)) {
		n = 0;
	}
	return n;
}
