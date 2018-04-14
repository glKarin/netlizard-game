#include "time_spin_box.h"
#include "nl_std.h"

#include <string.h>
#include <stdlib.h>

static void UI_InitTimeSpinBoxBuffer(time_spin_box *s);

time_spin_box * new_time_spin_box(time_spin_box *sb, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, const GLfloat bg_color[], const GLfloat digit_color[], const GLfloat block_color[], const GLfloat text_color[], const GLfloat disable_block_color[], const GLfloat border_color[], int step, long long min, long long max, long long time, const char *text)
{
	RETURN_PTR(s, sb, time_spin_box)

		new_base_widget(&s -> base, x, y, z, width, height, GL_TRUE, 1.0);
	COPY_COLOR4(s -> bg_color, bg_color)
	COPY_COLOR4(s -> digit_color, digit_color)
	COPY_COLOR4(s -> block_color, block_color)
	COPY_COLOR4(s -> disable_block_color, disable_block_color)
	COPY_COLOR4(s -> border_color, border_color)
	COPY_COLOR4(s -> text_color, text_color)

	UI_InitTimeSpinBoxBuffer(s);
	s -> step = step;
	s -> time = time;
	s -> min = min;
	s -> max = max;
	s -> second = s -> time % 60;
	s -> minuts = s -> time / 60 % 60;
	s -> hour = s -> time % 3600;
	if(text)
		s -> text = strdup(text);

	return s;
}

void UI_RenderTimeSpinBox(const time_spin_box *s)
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
		oglDrawArrays(GL_LINE_LOOP, 8, 4);
		oglDrawArrays(GL_TRIANGLE_STRIP, 12, 4);
		oglDrawArrays(GL_TRIANGLE_STRIP, 16, 4);

		if(s -> minuts >= 60)
			glColor4fv(s -> disable_block_color);
		else
			glColor4fv(s -> block_color);
		oglDrawArrays(GL_TRIANGLES, 20, 3);
		if(s -> minuts == 0)
			glColor4fv(s -> disable_block_color);
		else
			glColor4fv(s -> block_color);
		oglDrawArrays(GL_TRIANGLES, 23, 3);

		if(s -> second >= 60)
			glColor4fv(s -> disable_block_color);
		else
			glColor4fv(s -> block_color);
		oglDrawArrays(GL_TRIANGLES, 26, 3);
		if(s -> second == 0)
			glColor4fv(s -> disable_block_color);
		else
			glColor4fv(s -> block_color);
		oglDrawArrays(GL_TRIANGLES, 29, 3);
	}
	glPopAttrib();
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if(s -> fnt)
	{
		glPushAttrib(GL_CURRENT_BIT);
		{
			GLfloat x = 0.0;
			GLfloat y = 0.0;
			Font_GetDigitCenterPosition(s -> fnt, s -> min_limit, 0, s -> box_width, s -> base.height, s -> minuts, &x, &y);
			glPushMatrix();
			{
				glTranslatef(0.0, 0.0, 0.01);
				Font_RenderDigit(s -> fnt, x, y, s -> digit_color[0], s -> digit_color[1], s -> digit_color[2], s -> digit_color[3], s -> minuts);
			}
			glPopMatrix();
			Font_GetDigitCenterPosition(s -> fnt, s -> sec_limit, 0, s -> box_width, s -> base.height, s -> second, &x, &y);
			glPushMatrix();
			{
				glTranslatef(0.0, 0.0, 0.01);
				Font_RenderDigit(s -> fnt, x, y, s -> digit_color[0], s -> digit_color[1], s -> digit_color[2], s -> digit_color[3], s -> second);
			}
			glPopMatrix();
			if(s -> text)
			{
				glPushMatrix();
				{
					Font_GetStringCenterPosition(s -> fnt, 0, 0, 0, s -> base.height, s -> text, NULL, &y);
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

void delete_time_spin_box(time_spin_box *s)
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

void UI_SetTimeSpinBoxTime(time_spin_box *s, long long t)
{
	if(!s)
		return;
	if(s -> time == t)
		return;
	s -> time = t;
	s -> second = s -> time % 60;
	s -> minuts = s -> time / 60 % 60;
	s -> hour = s -> time % 3600;
}

int UI_ClickTimeSpinBox(time_spin_box *sb, GLfloat x, GLfloat y)
{
	if(!sb)
		return 0;
	int res = 0;
	long long time = 0;

	if(UI_PointInRect2(&sb -> min_top, x, y))
	{
		if(sb -> time + 60 * sb -> step <= sb -> max)
		{
			time = sb -> time + 60 * sb -> step;
			res = 1;
		}
	}
	else if(UI_PointInRect2(&sb -> min_bottom, x, y))
	{
		if(sb -> time - 60 * sb -> step >= sb -> min)
		{
			time = sb -> time - 60 * sb -> step;
			res = 1;
		}
	}
	else if(UI_PointInRect2(&sb -> sec_top, x, y))
	{
		if(sb -> time + 1 * sb -> step <= sb -> max && sb -> second + 1 * sb -> step < 60)
		{
			time = sb -> time + 1 * sb -> step;
			res = 1;
		}
	}
	else if(UI_PointInRect2(&sb -> sec_bottom, x, y))
	{
		if(sb -> time - 1 * sb -> step >= sb -> min && sb -> second - 1 * sb -> step >= 0)
		{
			time = sb -> time - 1 * sb -> step;
			res = 1;
		}
	}

	if(res)
		UI_SetTimeSpinBoxTime(sb, time);
	return res;
}

void UI_InitTimeSpinBoxBuffer(time_spin_box *s)
{
	if(!s)
		return;
	GLfloat base_width = KARIN_MIN(s -> base.width * 0.4, 200);
	GLfloat base = s -> base.width - base_width;
	GLfloat block_w = (base_width - 27) / 2;
	GLfloat btn_w = KARIN_MIN(block_w - 2, 50);
	GLfloat btn_h = KARIN_MIN(s -> base.height / 2, 30);
	GLfloat block_h = KARIN_MIN(s -> base.height - btn_h * 2 - 4, 40);

	GLfloat vertex[] = 
	{
		// border
		0.0, 0.0,
		s -> base.width, 0.0,
		0.0, s -> base.height,
		s -> base.width, s -> base.height,

		// minuts box
		base + 1, s -> base.height / 2 - block_h / 2,
		base + 1 + block_w, s -> base.height / 2 - block_h / 2,
		base + 1 + block_w, s -> base.height / 2 + block_h / 2,
		base + 1, s -> base.height / 2 + block_h / 2,

		// second box
		base + 26 + block_w, s -> base.height / 2 - block_h / 2,
		s -> base.width - 1, s -> base.height / 2 - block_h / 2,
		s -> base.width - 1, s -> base.height / 2 + block_h / 2,
		base + 26 + block_w, s -> base.height / 2 + block_h / 2,

		// middle comma
		base + 11 + block_w, s -> base.height / 2 - block_h / 2 / 2 - 5,
		base + 16 + block_w, s -> base.height / 2 - block_h / 2 / 2 - 5,
		base + 11 + block_w, s -> base.height / 2 - block_h / 2 / 2,
		base + 16 + block_w, s -> base.height / 2 - block_h / 2 / 2,

		base + 11 + block_w, s -> base.height / 2 + block_h / 2 / 2,
		base + 16 + block_w, s -> base.height / 2 + block_h / 2 / 2,
		base + 11 + block_w, s -> base.height / 2 + block_h / 2 / 2 + 5,
		base + 16 + block_w, s -> base.height / 2 + block_h / 2 / 2 + 5,

		// left top button
		base + 1 + block_w / 2 - btn_w / 2, s -> base.height / 2 + block_h / 2 + 2,
		base + 1 + block_w / 2 + btn_w / 2, s -> base.height / 2 + block_h / 2 + 2,
		base + 1 + block_w / 2, s -> base.height / 2 + block_h / 2 + 2 + btn_h,

		// left bottom button
		base + 1 + block_w / 2 - btn_w / 2, s -> base.height / 2 - block_h / 2 - 2,
		base + 1 + block_w / 2, s -> base.height / 2 - block_h / 2 - 2 - btn_h,
		base + 1 + block_w / 2 + btn_w / 2, s -> base.height / 2 - block_h / 2 - 2,

		// right top button
		base + 26 + block_w + block_w / 2 - btn_w / 2, s -> base.height / 2 + block_h / 2 + 2,
		base + 26 + block_w + block_w / 2 + btn_w / 2, s -> base.height / 2 + block_h / 2 + 2,
		base + 26 + block_w + block_w / 2, s -> base.height / 2 + block_h / 2 + 2 + btn_h,

		// right bottom button
		base + 26 + block_w + block_w / 2 - btn_w / 2, s -> base.height / 2 - block_h / 2 - 2,
		base + 26 + block_w + block_w / 2, s -> base.height / 2 - block_h / 2 - 2 - btn_h,
		base + 26 + block_w + block_w / 2 + btn_w / 2, s -> base.height / 2 - block_h / 2 - 2,
	};
	if(glIsBuffer(s -> buffers[vertex_buffer_type]))
	{
		glBindBuffer(GL_ARRAY_BUFFER, s -> buffers[vertex_buffer_type]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 64, vertex);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else
		s -> buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 64, vertex, GL_STATIC_DRAW);

	s -> min_limit = base + 1;
	s -> sec_limit = base + 16 + block_w;
	s -> box_width = block_w;

	s -> min_top.x1 = base + 1 + block_w / 2 - btn_w / 2;
	s -> min_top.y1 = s -> base.height / 2 + block_h / 2 + 2,
		s -> min_top.x2 = base + 1 + block_w / 2 + btn_w / 2;
	s -> min_top.y2 = s -> base.height / 2 + block_h / 2 + 2 + btn_h;

	s -> min_bottom.x1 = base + 1 + block_w / 2 - btn_w / 2;
	s -> min_bottom.y1 = s -> base.height / 2 - block_h / 2 - 2 - btn_h;
	s -> min_bottom.x2 = base + 1 + block_w / 2 + btn_w / 2;
	s -> min_bottom.y2 = s -> base.height / 2 - block_h / 2 - 2;

	s -> sec_top.x1 = base + 26 + block_w + block_w / 2 - btn_w / 2;
	s -> sec_top.y1 = s -> base.height / 2 + block_h / 2 + 2;
	s -> sec_top.x2 = base + 26 + block_w + block_w / 2 + btn_w / 2;
	s -> sec_top.y2 = s -> base.height / 2 + block_h / 2 + 2 + btn_h;

	s -> sec_bottom.x1 = base + 26 + block_w + block_w / 2 - btn_w / 2;
	s -> sec_bottom.y1 = s -> base.height / 2 - block_h / 2 - 2 - btn_h;
	s -> sec_bottom.x2 = base + 26 + block_w + block_w / 2 + btn_w / 2;
	s -> sec_bottom.y2 = s -> base.height / 2 - block_h / 2 - 2;
}

void UI_ResizeTimeSpinBox(time_spin_box *s, GLfloat width, GLfloat height)
{
	if(!s)
		return;
	if(s -> base.width == width && s -> base.height == height)
		return;
	UI_SetWidgetSize(&s -> base, width, height, geometry_wh_mask);
	UI_InitTimeSpinBoxBuffer(s);
}

void UI_ResetTimeSpinBoxPosition(time_spin_box *s, GLfloat x, GLfloat y)
{
	if(!s)
		return;
	if(s -> base.x == x && s -> base.y == y)
		return;
	UI_SetWidgetPosition(&s -> base, x, y, 0, geometry_xy_mask);
}

void UI_ResetTimeSpinBoxGeometry(time_spin_box *t, GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	if(!t)
		return;
	UI_ResetTimeSpinBoxPosition(t, x, y);
	UI_ResizeTimeSpinBox(t, width, height);
}
