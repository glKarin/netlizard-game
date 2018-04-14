#include "label.h"

#include "nl_std.h"

#include <string.h>
#include <stdlib.h>

static void UI_InitLabelBuffer(label *l);

label * new_label(label *lb, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat border_width, const GLfloat bg_color[], const GLfloat text_color[], const GLfloat border_color[], const char *text, const char *tex)
{
	RETURN_PTR(l, lb, label)
		new_base_widget(&l -> base, x, y, z, width, height, GL_TRUE, 1.0);
	l -> border_width = border_width;
	if(text)
		l -> text = strdup(text);
	if(tex)
		l -> tex = new_OpenGL_texture_2d(tex);
	COPY_COLOR4(l -> bg_color, bg_color)
		COPY_COLOR4(l -> text_color, text_color)
		COPY_COLOR4(l -> border_color, border_color)
	GLfloat texcoord[8] = {
		0.0, 1.0,
		1.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,
	};
	GLushort index[4] = {
		0, 1, 3, 2
	};

	UI_InitLabelBuffer(l);
	l -> buffers[texcoord_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, texcoord, GL_STATIC_DRAW);
	l -> buffers[index_buffer_type] = new_OpenGL_buffer_object(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 4, index, GL_STATIC_DRAW);
	return l;
}

void UI_RenderLabel(const label *l)
{
	if(!l)
		return;
	if(!l -> base.visible)
		return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, l -> buffers[vertex_buffer_type]);
	glVertexPointer(2, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, l -> buffers[texcoord_buffer_type]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT);
	{
		if(l -> tex && glIsTexture(l -> tex -> texid))
			oglBindTexture(GL_TEXTURE_2D, l -> tex -> texid);
		else
			glColor4fv(l -> bg_color);
		oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		if(l -> border_width > 0.0)
		{
			glLineWidth(l -> border_width);
			glColor4fv(l -> border_color);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, l -> buffers[index_buffer_type]);
			oglDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, NULL);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
	glPopAttrib();

	if(l -> fnt && l -> text)
	{
		GLfloat x = 0.0;
		GLfloat y = 0.0;
		Font_GetStringCenterPosition(l -> fnt, 0, 0, l -> base.width, l -> base.height, l -> text, &x, &y);
		glPushMatrix();
		{
			glTranslatef(0.0, 0.0, 0.01);
			Font_RenderString(l -> fnt, x, y, l -> text_color[0], l -> text_color[1], l -> text_color[2], l -> text_color[3], l -> text);
		}
		glPopMatrix();
	}
	oglBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void delete_label(label *l)
{
	if(!l)
		return;
	FREE_PTR(l -> text)
	if(l -> tex)
	{
		if(glIsTexture(l -> tex -> texid))
			glDeleteTextures(1, &l -> tex -> texid);
		free(l -> tex);
		l -> tex = NULL;
	}
	l -> fnt = NULL;
	int i;
	for(i = vertex_buffer_type; i < total_buffer_type; i++)
	{
		if(glIsBuffer(l -> buffers[i]))
			glDeleteBuffers(1, l -> buffers + i);
	}
}

void UI_ResizeLabel(label *l, GLfloat width, GLfloat height)
{
	if(!l)
		return;
	if(l -> base.width == width && l -> base.height == height)
		return;
	UI_SetWidgetSize(&l -> base, width, height, geometry_wh_mask);
	UI_InitLabelBuffer(l);
}

void UI_ResetLabelPosition(label *l, GLfloat x, GLfloat y)
{
	if(!l)
		return;
	if(l -> base.x == x && l -> base.y == y)
		return;
	UI_SetWidgetPosition(&l -> base, x, y, 0, geometry_xy_mask);
}

void UI_InitLabelBuffer(label *l)
{
	if(!l)
		return;
	GLfloat vertex[] = {
		0.0, 0.0,
		l -> base.width, 0.0,
		0.0, l -> base.height,
		l -> base.width, l -> base.height
	};
	if(glIsBuffer(l -> buffers[vertex_buffer_type]))
	{
		glBindBuffer(GL_ARRAY_BUFFER, l -> buffers[vertex_buffer_type]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 8, vertex);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else
		l -> buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, vertex, GL_STATIC_DRAW);
}

void UI_ResetLabelGeometry(label *l, GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	if(!l)
		return;
	UI_ResetLabelPosition(l, x, y);
	UI_ResizeLabel(l, width, height);
}
