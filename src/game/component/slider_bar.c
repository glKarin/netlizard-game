#include "slider_bar.h"

#include "gl_util.h"
#include "nl_std.h"

#include <string.h>

static void UI_InitSliderBarBuffer(slider_bar *b);

slider_bar * new_slider_bar(slider_bar *bar, GLfloat x, GLfloat y, GLfloat z, GLfloat bar_width, GLfloat block_width, GLfloat height, GLfloat map_height, GLfloat map_total_height, const GLfloat color[], const GLfloat block_color[])
{
	RETURN_PTR(b, bar, slider_bar)
		new_base_widget(&b->base, x, y, z, block_width, height, GL_TRUE, 1.0);
	b->bar_width = bar_width;
	b->block_width = block_width;
	b->map_height = map_height;
	b->map_total_height = map_total_height;
	COPY_COLOR4(b->color, color)
	COPY_COLOR4(b->block_color, block_color)
	UI_InitSliderBarBuffer(b);
	b->progress = 0.0;
	return b;
}

void UI_RenderSliderBar(const slider_bar *bar)
{
	if(!bar)
		return;
	if(!bar->base.visible)
		return;
	GLfloat bh = bar->map_height * bar->base.height / bar->map_total_height;
	GLfloat p = (bar->base.height - bh) * bar->progress;
	GLfloat vertex[] = {
		0.0, bar->base.height - p,
		0.0, bar->base.height - (p + bh),
		bar->block_width, bar->base.height - p,
		bar->block_width, bar->base.height - (p + bh)
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, bar->buffers[vertex_buffer_type]);
	glVertexPointer(2, GL_FLOAT, 0, NULL);
	WIDGETPTR_CLIP_RENDER_BEGIN(bar)
	glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT);
	{
		glLineWidth(bar->bar_width);
		glColor4fv(bar->color);
		oglDrawArrays(GL_LINES, 0, 2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexPointer(2, GL_FLOAT, 0, vertex);
		glColor4fv(bar->block_color);
		oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	glPopAttrib();
	WIDGETPTR_CLIP_RENDER_END(bar)
	glDisableClientState(GL_VERTEX_ARRAY);
}

void delete_slider_bar(slider_bar *bar)
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

void UI_ResizeSliderBar(slider_bar *b, GLfloat width, GLfloat height)
{
	if(!b)
		return;
	if(b->base.width == width && b->base.height == height)
		return;
	UI_SetWidgetSize(&b->base, width, height, geometry_wh_mask);
	b->block_width = b->base.width;
	UI_InitSliderBarBuffer(b);
}

void UI_ResetSliderBarPosition(slider_bar *b, GLfloat x, GLfloat y)
{
	if(!b)
		return;
	if(b->base.x == x && b->base.y == y)
		return;
	UI_SetWidgetPosition(&b->base, x, y, 0, geometry_xy_mask);
}

void UI_InitSliderBarBuffer(slider_bar *b)
{
	if(!b)
		return;
	GLfloat vertex[4] = {
		b->block_width / 2, 0.0, // bar bottom
		b->block_width / 2, b->base.height, // bar top
	};

	if(glIsBuffer(b->buffers[vertex_buffer_type]))
	{
		glBindBuffer(GL_ARRAY_BUFFER, b->buffers[vertex_buffer_type]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 4, vertex);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else
		b->buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4, vertex, GL_STATIC_DRAW);
}

void UI_ResetSliderBarGeometry(slider_bar *b, GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	if(!b)
		return;
	UI_ResetSliderBarPosition(b, x, y);
	UI_ResizeSliderBar(b, width, height);
}
