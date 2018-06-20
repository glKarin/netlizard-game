#include "text_browser.h"
#include "nl_std.h"
#include "gl_util.h"

#include <string.h>
#include <stdlib.h>

static void UI_InitTextBrowserBuffer(text_browser *t);

text_browser * new_text_browser(text_browser *tb, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, const GLfloat spacing, GLfloat border_width, const GLfloat border_color[], const GLfloat bg_color[], const GLfloat bar_color[], const GLfloat bar_block_color[], const GLfloat text_color[], const char *text)
{
	RETURN_PTR(t, tb, text_browser)
	new_base_widget(&t -> base, x, y, z, width, height, GL_TRUE, 1.0);
		COPY_COLOR4(t -> bg_color, bg_color)
		COPY_COLOR4(t -> border_color, border_color)
		COPY_COLOR4(t -> text_color, text_color)
		t -> border_width = border_width;
	t -> spacing = spacing;
	t -> progress = 0.0;
	new_slider_bar(&t -> bar, 0.0, 0.0, 0.02, 4, 10, t -> base.height, t -> base.height, t -> base.height, bar_color, bar_block_color);
	GLushort index[4] = {
		0, 1, 3, 2
	};

	t -> buffers[index_buffer_type] = new_OpenGL_buffer_object(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 4, index, GL_STATIC_DRAW);
	UI_InitTextBrowserBuffer(t);
	t -> text = NULL;
	t -> fnt = NULL;
	return t;
}

void UI_SetBrowserText(text_browser *tb, const char *text)
{
	if(!tb || !text)
		return;
	if(!tb -> fnt)
		return;
	SET_TEXT(tb -> text, text)

	const char *p = tb -> text;
	size_t len = strlen(tb -> text);
	GLint count = 0;
	GLint line_count = 0;
	while(count < (GLint)len)
	{
		GLint c = Font_GetCharCountOfWidth(tb -> fnt, tb -> base.width - 2 * tb -> border_width - tb -> bar.base.width, p);
		if(c == -1)
			break;
		GLint i;
		for(i = 0; i < c; i++)
		{
			if(p[i] == '\n')
			{
				i++;
				break;
			}
		}
		count += i;
		line_count++;
		p += i;
	}
	line_count++;
	tb -> text_height = line_count * tb -> fnt -> height + (line_count - 1) * tb -> spacing;
	tb -> line_count = line_count;
	tb -> bar.map_total_height = tb -> text_height;
	tb -> progress = 0.0;
	tb -> bar.progress = 0.0;
}

void UI_RenderTextBrowser(text_browser *tb)
{
	if(!tb)
		return;
	if(!tb -> base.visible)
		return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, tb -> buffers[vertex_buffer_type]);
	glVertexPointer(2, GL_FLOAT, 0, NULL);
	glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT);
	{
		glColor4fv(tb -> bg_color);
		oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		if(tb -> border_width > 0.0)
		{
			glLineWidth(tb -> border_width);
			glColor4fv(tb -> border_color);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tb -> buffers[index_buffer_type]);
			oglDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, NULL);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
	glPopAttrib();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);

	if(!tb -> text || !tb -> fnt)
		return;

	if(tb -> text_height <= tb -> base.height - tb -> border_width * 2)
		tb -> progress = 1.0;

	GLfloat p = KARIN_MAX((tb -> text_height - tb -> base.height - tb -> border_width * 2) * tb -> progress, 0.0);
	GLfloat h = 0.0;
	glPushMatrix();
	{
		glTranslatef(tb -> border_width, tb -> base.height - tb -> border_width * 2, 0.01);
		const char *ptr = tb -> text;
		GLint count = 0;
		GLint i;
		for(i = 0; i < (GLint)tb -> line_count; i++)
		{
			h += tb -> fnt -> height;
			GLint c = Font_GetCharCountOfWidth(tb -> fnt, tb -> base.width - tb -> border_width * 2 - tb -> bar.base.width, ptr);
			if(c == -1)
				break;
			GLint j;
			for(j = 0; j < c; j++)
			{
				if(ptr[j] == '\n')
				{
					j++;
					break;
				}
			}
			count += j;
			if(h < p)
			{
				ptr += j;
				h += tb -> spacing;
				if(h > p)
				{
					if(h - tb -> spacing < p)
						glTranslatef(0.0, p - h, 0.0);
					else
						glTranslatef(0.0, -tb -> spacing, 0.0);
				}
				continue;
			}
			if(h > p)
			{
				if(h - tb -> fnt -> height < p)
					glTranslatef(0.0, p - h, 0.0);
				else
					glTranslatef(0.0, -(GLfloat)tb -> fnt -> height, 0.0);
			}
			char *str = NEW_II(char, j + 1);
			strncpy(str, ptr, j);
			str[j] = '\0';
			Font_RenderString(tb -> fnt, 0, 0, tb -> text_color[0], tb -> text_color[1], tb -> text_color[2], tb -> text_color[3], str);
			free(str);
			ptr += j;
			h += tb -> spacing;
			glTranslatef(0.0, -tb -> spacing, 0.0);
			if(h - p > tb -> base.height - tb -> border_width * 2)
				break;
		}
	}
	glPopMatrix();
	tb -> bar.progress = tb -> progress;
	if(tb -> text_height > tb -> base.height - tb -> border_width * 2)
	{
		glPushMatrix();
		{
			glTranslatef(tb -> base.width - tb -> bar.block_width, 0.0, tb -> bar.base.z);
			UI_RenderSliderBar(&tb -> bar);
		}
		glPopMatrix();
	}
}

int UI_SlideTextBrowser(text_browser *tb, GLfloat dis)
{
	if(!tb)
		return 0;
	if(dis == 0.0)
		return 0;
	if(tb -> progress == 0.0 && dis < 0.0)
		return 0;
	if(tb -> progress == 1.0 && dis > 0.0)
		return 0;
	if(tb -> text_height <= tb -> base.height - tb -> border_width * 2)
		return 0;
	GLfloat p = KARIN_MAX((tb -> text_height - tb -> base.height - tb -> border_width * 2) * tb -> progress, 0.0);
	p += dis;
	if(p < 0.0)
		p = 0.0;
	else if(p > tb -> text_height - tb -> base.height - tb -> border_width * 2)
		p = tb -> text_height - tb -> base.height - tb -> border_width * 2;
	tb -> progress = p / (tb -> text_height - tb -> base.height - tb -> border_width * 2); // if(th == tb -> base.height) return before this compute, else may be throw float exception.
	tb -> bar.progress = tb -> progress;
	return 1;
}

void delete_text_browser(text_browser *tb)
{
	if(!tb)
		return;
	delete_slider_bar(&tb -> bar);
	GLint i;
	for(i = vertex_buffer_type; i < total_buffer_type; i++)
	{
		if(glIsBuffer(tb -> buffers[i]))
			glDeleteBuffers(1, tb -> buffers + i);
	}
	FREE_PTR(tb -> text)
}

int UI_MoveTextBrowser(text_browser *tb, GLfloat step)
{
	if(!tb)
		return 0;
	if(step == 0)
		return 0;
	if(!tb -> text || !tb -> fnt)
		return 0;
	return UI_SlideTextBrowser(tb, step * (tb -> fnt -> height + tb -> spacing));
}

void UI_InitTextBrowserBuffer(text_browser *t)
{
	if(!t)
		return;
	GLfloat vertex[8] = {
		0.0, 0.0,
		t -> base.width, 0.0,
		0.0, t -> base.height,
		t -> base.width, t -> base.height
	};
	if(glIsBuffer(t -> buffers[vertex_buffer_type]))
	{
		glBindBuffer(GL_ARRAY_BUFFER, t -> buffers[vertex_buffer_type]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 8, vertex);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else
		t -> buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, vertex, GL_STATIC_DRAW);
}

void UI_ResizeTextBrowser(text_browser *t, GLfloat width, GLfloat height)
{
	if(!t)
		return;
	if(t -> base.width == width && t -> base.height == height)
		return;
	UI_SetWidgetSize(&t -> base, width, height, geometry_wh_mask);
	UI_InitTextBrowserBuffer(t);
	if(t -> base.height != height)
		UI_ResizeSliderBar(&t -> bar, 10, t -> base.height);
}

void UI_ResetTextBrowserPosition(text_browser *t, GLfloat x, GLfloat y)
{
	if(!t)
		return;
	if(t -> base.x == x && t -> base.y == y)
		return;
	UI_SetWidgetPosition(&t -> base, x, y, 0, geometry_xy_mask);
}

void UI_ResetTextBrowserGeometry(text_browser *t, GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	if(!t)
		return;
	UI_ResetTextBrowserPosition(t, x, y);
	UI_ResizeTextBrowser(t, width, height);
}
