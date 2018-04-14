#include "spin_box.h"
#include "nl_std.h"

#include <string.h>
#include <stdlib.h>

static void UI_InitSpinBoxBuffer(spin_box *s);

spin_box * new_spin_box(spin_box *sb, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, const GLfloat bg_color[], const GLfloat digit_color[], const GLfloat block_color[], const GLfloat text_color[], const GLfloat disable_block_color[], const GLfloat border_color[], int num, int min, int max, int step, const char *text)
{
	RETURN_PTR(s, sb, spin_box)

		new_base_widget(&s -> base, x, y, z, width, height, GL_TRUE, 1.0);
	COPY_COLOR4(s -> bg_color, bg_color)
	COPY_COLOR4(s -> digit_color, digit_color)
	COPY_COLOR4(s -> block_color, block_color)
	COPY_COLOR4(s -> disable_block_color, disable_block_color)
	COPY_COLOR4(s -> border_color, border_color)
	COPY_COLOR4(s -> text_color, text_color)

	UI_InitSpinBoxBuffer(s);
	s -> value = num;
	s -> step = step;
	s -> min = min;
	s -> max = max;
	if(text)
		s -> text = strdup(text);

	return s;
}

void UI_RenderSpinBox(const spin_box *s)
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
		glColor4fv(s -> bg_color);
		oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glColor4fv(s -> border_color);
		oglDrawArrays(GL_LINE_LOOP, 4, 4);

		if(s -> value <= s -> min)
			glColor4fv(s -> disable_block_color);
		else
			glColor4fv(s -> block_color);
		oglDrawArrays(GL_TRIANGLES, 8, 3);

		if(s -> value >= s -> max)
			glColor4fv(s -> disable_block_color);
		else
			glColor4fv(s -> block_color);
		oglDrawArrays(GL_TRIANGLES, 11, 3);

	}
	glPopAttrib();
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if(s -> fnt)
	{
		glPushAttrib(GL_CURRENT_BIT);
		{
			GLfloat x = 0.0;
			GLfloat y = 0.0;
			Font_GetDigitCenterPosition(s -> fnt, s -> limit, 0, s -> base.width - s -> limit, s -> base.height, s -> value, &x, &y);
			glPushMatrix();
			{
				glTranslatef(0.0, 0.0, 0.01);
				Font_RenderDigit(s -> fnt, x, y, s -> digit_color[0], s -> digit_color[1], s -> digit_color[2], s -> digit_color[3], s -> value);
			}
			glPopMatrix();
			if(s -> text)
			{
				glPushMatrix();
				{
					glTranslatef(0.0, 0.0, 0.01);
					Font_RenderString(s -> fnt, 0.0, y, s -> text_color[0], s -> text_color[1], s -> text_color[2], s -> text_color[3], s -> text);
				}
				glPopMatrix();
			}
		}
		glPopAttrib();
	}
	glDisableClientState(GL_VERTEX_ARRAY);
}

void delete_spin_box(spin_box *s)
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

int UI_ClickSpinBox(spin_box *sb, GLfloat x, GLfloat y)
{
	if(!sb)
		return 0;
	if(UI_PointInRect2(&sb -> left, x, y))
	{
		if(sb -> value - sb -> step >= sb -> min)
		{
			sb -> value -= sb -> step;
			return 1;
		}
	}
	else if(UI_PointInRect2(&sb -> right, x, y))
	{
		if(sb -> value + sb -> step <= sb -> max)
		{
			sb -> value += sb -> step;
			return 1;
		}
	}
	return 0;
}

void UI_InitSpinBoxBuffer(spin_box *s)
{
	if(!s)
		return;
	GLfloat base_width = KARIN_MIN(s -> base.width * 0.3, 180);
	GLfloat base = s -> base.width - base_width;
	GLfloat block_w = KARIN_MIN(base_width / 5, 40);
	GLfloat block_h = KARIN_MIN(s -> base.height - 4, 40);

	GLfloat vertex[] = 
	{
		0.0, 0.0,
		s -> base.width, 0.0,
		0.0, s -> base.height,
		s -> base.width, s -> base.height,

		base + 1 + 10 + block_w, s -> base.height / 2 - block_h / 2,
		s -> base.width - block_w - 10 - 1, s -> base.height / 2 - block_h / 2,
		s -> base.width - block_w - 10 - 1, s -> base.height / 2 + block_h / 2,
		base + 1 + 10 + block_w, s -> base.height / 2 + block_h / 2,

		base + 1, s -> base.height / 2,
		base + 1 + block_w, s -> base.height / 2 - block_h / 2,
		base + 1 + block_w, s -> base.height / 2 + block_h / 2,

		s -> base.width - 1, s -> base.height / 2,
		s -> base.width - 1 - block_w, s -> base.height / 2 + block_h / 2,
		s -> base.width - 1 - block_w, s -> base.height / 2 - block_h / 2
	};
	if(glIsBuffer(s -> buffers[vertex_buffer_type]))
	{
		glBindBuffer(GL_ARRAY_BUFFER, s -> buffers[vertex_buffer_type]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 28, vertex);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else
		s -> buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 28, vertex, GL_STATIC_DRAW);

	s -> left.x1 = base + 1;
	s -> left.y1 = s -> base.height / 2 - block_h / 2;
	s -> left.x2 = base + 1 + block_w;
	s -> left.y2 = s -> base.height / 2 + block_h / 2;

	s -> right.x1 = s -> base.width - 1 - block_w;
	s -> right.y1 = s -> base.height / 2 - block_h / 2;
	s -> right.x2 = s -> base.width - 1;
	s -> right.y2 = s -> base.height / 2 + block_h / 2;
	s -> limit = base;
}

void UI_ResizeSpinBox(spin_box *s, GLfloat width, GLfloat height)
{
	if(!s)
		return;
	if(s -> base.width == width && s -> base.height == height)
		return;
	UI_SetWidgetSize(&s -> base, width, height, geometry_wh_mask);
	UI_InitSpinBoxBuffer(s);
}

void UI_ResetSpinBoxPosition(spin_box *s, GLfloat x, GLfloat y)
{
	if(!s)
		return;
	if(s -> base.x == x && s -> base.y == y)
		return;
	UI_SetWidgetPosition(&s -> base, x, y, 0, geometry_xy_mask);
}

void UI_ResetSpinBoxGeometry(spin_box *s, GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	if(!s)
		return;
	UI_ResetSpinBoxPosition(s, x, y);
	UI_ResizeSpinBox(s, width, height);
}
