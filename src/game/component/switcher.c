#include "switcher.h"
#include "nl_std.h"

#include <string.h>
#include <stdlib.h>

void UI_InitSwitcherBuffer(switcher *s);

switcher * new_switcher(switcher *sw, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, const GLfloat bg_color[], const GLfloat text_color[], const GLfloat block_color[], const GLfloat close_bg_color[], const GLfloat close_text_color[], const GLfloat close_block_color[], const GLfloat border_color[], const char *text)
{
	RETURN_PTR(s, sw, switcher)

		new_base_widget(&s -> base, x, y, z, width, height, GL_TRUE, 1.0);
	COPY_COLOR4(s -> bg_color, bg_color)
	COPY_COLOR4(s -> text_color, text_color)
	COPY_COLOR4(s -> block_color, block_color)
	COPY_COLOR4(s -> close_bg_color, close_bg_color)
	COPY_COLOR4(s -> close_text_color, close_text_color)
	COPY_COLOR4(s -> close_block_color, close_block_color)
	COPY_COLOR4(s -> border_color, border_color)

	UI_InitSwitcherBuffer(s);
	if(text)
		s -> text = strdup(text);
	s -> open = GL_FALSE;

	return s;
}

void UI_RenderSwitcher(const switcher *s)
{
	if(!s)
		return;
	if(!s -> base.visible)
		return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, s -> buffers[vertex_buffer_type]);
	glVertexPointer(2, GL_FLOAT, 0, NULL);
	glPushAttrib(GL_CURRENT_BIT);
	{
		if(s -> open)
			glColor4fv(s -> bg_color);
		else
			glColor4fv(s -> close_bg_color);
		oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glColor4fv(s -> border_color);
		oglDrawArrays(GL_LINE_LOOP, 4, 4);
		oglDrawArrays(GL_LINES, 8, 2);

		if(s -> open)
		{
			glColor4fv(s -> block_color);
			oglDrawArrays(GL_TRIANGLE_STRIP, 14, 4);
		}
		else
		{
			glColor4fv(s -> close_block_color);
			oglDrawArrays(GL_TRIANGLE_STRIP, 10, 4);
		}

	}
	glPopAttrib();

	if(s -> fnt && s -> text)
	{
		glPushAttrib(GL_CURRENT_BIT);
		{
			GLfloat y = 0.0;
			Font_GetStringCenterPosition(s -> fnt, 0, 0, s -> base.width, s -> base.height - 2, s -> text, NULL, &y);
			glPushMatrix();
			{
				glTranslatef(0.0, 0.0, 0.01);
				if(s -> open)
					Font_RenderString(s -> fnt, 0.0, y, s -> text_color[0], s -> text_color[1], s -> text_color[2], s -> text_color[3], s -> text);
				else
					Font_RenderString(s -> fnt, 0.0, y, s -> close_text_color[0], s -> close_text_color[1], s -> close_text_color[2], s -> close_text_color[3], s -> text);
			}
			glPopMatrix();
		}
		glPopAttrib();
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void delete_switcher(switcher *s)
{
	if(!s)
		return;
	int i;
	for(i = vertex_buffer_type; i < total_buffer_type; i++)
	{
		if(glIsBuffer(s -> buffers[i]))
			glDeleteBuffers(1, s -> buffers + i);
	}
	s -> fnt = NULL;
	FREE_PTR(s -> text)
}

void UI_InitSwitcherBuffer(switcher *s)
{
	if(!s)
		return;
	GLfloat block_w = KARIN_MIN(s -> base.width / 3, 80);
	GLfloat block_h = KARIN_MIN(s -> base.height - 4, 40);
	GLfloat block_w_2 = (block_w - 5) / 2;

	GLfloat vertex[] = 
	{
		0.0, 0.0,
		s -> base.width, 0.0,
		0.0, s -> base.height,
		s -> base.width, s -> base.height,

		s -> base.width - block_w, s -> base.height / 2 - block_h / 2,
		s -> base.width, s -> base.height / 2 - block_h / 2,
		s -> base.width, s -> base.height / 2 + block_h / 2,
		s -> base.width - block_w, s -> base.height / 2 + block_h / 2,

		s -> base.width - block_w_2 - 3, s -> base.height / 2 - block_h / 2 + 2,
		s -> base.width - block_w_2 - 3, s -> base.height / 2 + block_h / 2 - 2,

		s -> base.width - block_w + 1, s -> base.height / 2 - block_h / 2 + 2,
		s -> base.width - 4 - block_w_2, s -> base.height / 2 - block_h / 2 + 2,
		s -> base.width - block_w + 1, s -> base.height / 2 + block_h / 2 - 2,
		s -> base.width - block_w_2 - 4, s -> base.height / 2 + block_h / 2 - 2,

		s -> base.width - block_w + 1 + block_w_2 + 3, s -> base.height / 2 - block_h / 2 + 2,
		s -> base.width - 1, s -> base.height / 2 - block_h / 2 + 2,
		s -> base.width - block_w + 1 + block_w_2 + 3, s -> base.height / 2 + block_h / 2 - 2,
		s -> base.width - 1, s -> base.height / 2 + block_h / 2 - 2
	};
	if(glIsBuffer(s -> buffers[vertex_buffer_type]))
	{
		glBindBuffer(GL_ARRAY_BUFFER, s -> buffers[vertex_buffer_type]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 36, vertex);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else
		s -> buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 36, vertex, GL_STATIC_DRAW);

	s -> btn.x1 = s -> base.width - block_w;
	s -> btn.y1 = s -> base.height / 2 - block_h / 2;
	s -> btn.x2 = s -> base.width;
	s -> btn.y2 = s -> base.height / 2 + block_h / 2;
}

void UI_ResizeSwitcher(switcher *s, GLfloat width, GLfloat height)
{
	if(!s)
		return;
	if(s -> base.width == width && s -> base.height == height)
		return;
	UI_SetWidgetSize(&s -> base, width, height, geometry_wh_mask);
	UI_InitSwitcherBuffer(s);
}

void UI_ResetSwitcherPosition(switcher *s, GLfloat x, GLfloat y)
{
	if(!s)
		return;
	if(s -> base.x == x && s -> base.y == y)
		return;
	UI_SetWidgetPosition(&s -> base, x, y, 0, geometry_xy_mask);
}

void UI_ResetSwitcherGeometry(switcher *s, GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	if(!s)
		return;
	UI_ResetSwitcherPosition(s, x, y);
	UI_ResizeSwitcher(s, width, height);
}
