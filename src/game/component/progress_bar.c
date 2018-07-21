#include "progress_bar.h"

#include "nl_std.h"

#include <string.h>

static void UI_InitProgressBarBuffer(progress_bar *b);

progress_bar * new_progress_bar(progress_bar *bar, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat spacing, GLfloat border_width, const GLfloat border_color[], const GLfloat color[], const GLfloat block_color[])
{
	RETURN_PTR(b, bar, progress_bar)
		new_base_widget(&b->base, x, y, z, width, height, GL_TRUE, 1.0);
	COPY_COLOR4(b->color, color)
	COPY_COLOR4(b->border_color, border_color)
	COPY_COLOR4(b->block_color, block_color)
		b->progress = 0.0;

	UI_InitProgressBarBuffer(b);
	GLushort index[4] = {
		0, 1, 3, 2
	};

	b->buffers[index_buffer_type] = new_OpenGL_buffer_object(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 4, index, GL_STATIC_DRAW);
	b->spacing = spacing;
	b->border_width = border_width;
	return b;
}

void UI_RenderProgressBar(const progress_bar *bar)
{
	if(!bar)
		return;
	if(!bar->base.visible)
		return;
	GLfloat p = (bar->base.width - bar->border_width * 2 - bar->spacing * 2) * bar->progress;
	GLfloat x = bar->border_width + bar->spacing;
	GLfloat y = bar->border_width + bar->spacing;
	GLfloat h = bar->base.height - bar->border_width * 2 - bar->spacing * 2;
	GLfloat vertex[] = {
		x, y,
		x + p, y,
		x, y + h,
		x + p, y + h
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, bar->buffers[vertex_buffer_type]);
	glVertexPointer(2, GL_FLOAT, 0, NULL);
	WIDGETPTR_CLIP_RENDER_BEGIN(bar)
	glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT);
	{
		glColor4fv(bar->color);
		oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		if(bar->border_width > 0.0)
		{
			glLineWidth(bar->border_width);
			glColor4fv(bar->border_color);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bar->buffers[index_buffer_type]);
			oglDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, NULL);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		glVertexPointer(2, GL_FLOAT, 0, vertex);
		glColor4fv(bar->block_color);
		oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	glPopAttrib();
	WIDGETPTR_CLIP_RENDER_END(bar)
	glDisableClientState(GL_VERTEX_ARRAY);
}

void delete_progress_bar(progress_bar *bar)
{
	if(!bar)
		return;
	int i;
	for(i = vertex_buffer_type; i < total_buffer_type; i++)
	{
		if(glIsBuffer(bar->buffers[i]))
			glDeleteBuffers(1, bar->buffers + i);
	}
}

void UI_ResizeProgressBar(progress_bar *b, GLfloat width, GLfloat height)
{
	if(!b)
		return;
	if(b->base.width == width && b->base.height == height)
		return;
	UI_SetWidgetSize(&b->base, width, height, geometry_wh_mask);
	UI_InitProgressBarBuffer(b);
}

void UI_ResetProgressBarPosition(progress_bar *b, GLfloat x, GLfloat y)
{
	if(!b)
		return;
	if(b->base.x == x && b->base.y == y)
		return;
	UI_SetWidgetPosition(&b->base, x, y, 0, geometry_xy_mask);
}

void UI_InitProgressBarBuffer(progress_bar *b)
{
	if(!b)
		return;
	GLfloat vertex[] = {
		0.0, 0.0,
		b->base.width, 0.0,
		0.0, b->base.height,
		b->base.width, b->base.height
	};
	if(glIsBuffer(b->buffers[vertex_buffer_type]))
	{
		glBindBuffer(GL_ARRAY_BUFFER, b->buffers[vertex_buffer_type]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 8, vertex);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else
		b->buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, vertex, GL_STATIC_DRAW);
}

void UI_ResetProgressBarGeometry(progress_bar *b, GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	if(!b)
		return;
	UI_ResetProgressBarPosition(b, x, y);
	UI_ResizeProgressBar(b, width, height);
}
