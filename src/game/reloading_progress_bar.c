#include "reloading_progress_bar.h"

#include "gl_util.h"
#include "nl_std.h"

reloading_progress_bar * new_reloading_progress_bar(reloading_progress_bar *rb, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat border_width, const GLfloat bg_color[], const GLfloat text_color[], const GLfloat border_color[], const GLfloat block_color[], const GLfloat bar_color[])
{
	RETURN_PTR(r, rb, reloading_progress_bar)

		r->x = x;
	r->y = y;
	r->z = z;
	r->width = width;
	r->height = height;
	r->border_width = border_width;
	COPY_COLOR4(r->bg_color, bg_color)
	COPY_COLOR4(r->border_color, border_color)
	COPY_COLOR4(r->text_color, text_color)

	GLfloat vertex[8] = {
		0.0, 0.0,
		r->width, 0.0,
		0.0, r->height,
		r->width, r->height
	};
	GLushort index[4] = {
		0, 1, 3, 2
	};
	r->buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, vertex, GL_STATIC_DRAW);
	r->buffers[index_buffer_type] = new_OpenGL_buffer_object(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 4, index, GL_STATIC_DRAW);

	GLfloat p_w = KARIN_MIN(r->width - r->border_width * 2 - 4, 320);
	GLfloat p_h = KARIN_MIN((r->height - 2 - r->border_width * 2) / 2, 15);
	GLfloat p_x = r->width / 2 - p_w / 2;
	GLfloat p_y = r->height / 2 - 5 - p_h;
	new_progress_bar(&r->bar, p_x, p_y, z + 0.01, p_w, p_h, 1, 1, block_color, bar_color, block_color);
	r->bar.base.clip = GL_FALSE;

	r->limit = p_y + p_h + 5;
	return r;
}

void UI_RenderReloadingProgressBar(reloading_progress_bar *rb)
{
	if(!rb)
		return;
	if(!rb->game_mode)
		return;
	const weapon *wp = Game_CharacterCurrentWeapon(rb->game_mode->characters + rb->game_mode->current_character);
	if(!wp)
		return;
	if(wp->status != reload_type)
		return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT);
	{
		glBindBuffer(GL_ARRAY_BUFFER, rb->buffers[vertex_buffer_type]);
		glVertexPointer(2, GL_FLOAT, 0, NULL);
		glColor4fv(rb->bg_color);
		oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		if(rb->border_width != 0.0)
		{
			glColor4fv(rb->border_color);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rb->buffers[index_buffer_type]);
			oglDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, NULL);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		float tt = wp->reload_time * 1000;
		long long ct = rb->game_mode->characters[rb->game_mode->current_character].ai.time - wp->time;
		rb->bar.progress = (float)ct / tt;
		glPushMatrix();
		{
			glTranslatef(rb->bar.base.x, rb->bar.base.y, rb->bar.base.z);
			UI_RenderProgressBar(&rb->bar);
		}
		glPopMatrix();

		if(rb->fnt)
		{
			char str[15];
			memset(str, '\0', sizeof(char) * 15);
			strncat(str, "Reloading.....", 9 + 1 + ct / 200 % 5);
			glColor4fv(rb->text_color);
			GLfloat x = 0.0;
			GLfloat y = 0.0;
			Font_GetStringCenterPosition(rb->fnt, 0, rb->limit, rb->width, rb->height - rb->limit, "Reloading", &x, &y);
			Font_RenderString(rb->fnt, x, y, rb->text_color[0], rb->text_color[1], rb->text_color[2], rb->text_color[3], str);
		}
	}
	glPopAttrib();
	glDisableClientState(GL_VERTEX_ARRAY);
}

void delete_reloading_progress_bar(reloading_progress_bar *rb)
{
	if(!rb)
		return;
	rb->fnt = NULL;
	rb->game_mode = NULL;

	int i;
	for(i = vertex_buffer_type; i < total_buffer_type; i++)
	{
		if(glIsBuffer(rb->buffers[i]))
			glDeleteBuffers(1, rb->buffers + i);
	}
	delete_progress_bar(&rb->bar);
}
