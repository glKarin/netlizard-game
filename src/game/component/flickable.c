#include "flickable.h"
#include "nl_std.h"

#include <string.h>
#include <stdlib.h>

static void UI_GetFlickableTotalHeightAndMaxWidth(const flickable *f, float *w, float *h);
static void UI_InitFlickableBuffer(flickable *f);

flickable * new_flickable(flickable *fl, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat spacing, GLfloat header_spacing, GLfloat footer_spacing, const GLfloat bg_color[], const GLfloat bar_color[], const GLfloat bar_block_color[])
{
	RETURN_PTR(f, fl, flickable)
	new_base_widget(&f->base, x, y, z, width, height, GL_TRUE, 1.0);
		COPY_COLOR4(f->bg_color, bg_color)
	f->spacing = spacing;
	f->header_spacing = header_spacing;
	f->footer_spacing = footer_spacing;
	f->progress = 0.0;
	new_slider_bar(&f->bar, 0.0, 0.0, 0.02, 4, 10, f->base.height, f->base.height, f->base.height, bar_color, bar_block_color);
	f->bar.base.clip = GL_FALSE;

	UI_InitFlickableBuffer(f);
	return f;
}

void UI_RenderFlickable(flickable *f)
{
	if(!f)
		return;
	if(!f->base.visible)
		return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, f->buffers[vertex_buffer_type]);
	glVertexPointer(2, GL_FLOAT, 0, NULL);
	WIDGETPTR_CLIP_RENDER_BEGIN(f)
	glPushAttrib(GL_CURRENT_BIT);
	{
		glColor4fv(f->bg_color);
		oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	glPopAttrib();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);

	if(!f->items || f->count == 0)
		return;
	GLfloat mw = 0.0;
	GLfloat ah = 0.0;
	UI_GetFlickableTotalHeightAndMaxWidth(f, &mw, &ah);
	GLfloat h = 0.0;
	GLfloat th = f->header_spacing + f->footer_spacing + ah;
	if(th <= f->base.height)
		f->progress = 1.0;

	GLfloat p = KARIN_MAX((th - f->base.height) * f->progress, 0.0);

	glPushMatrix();
	{
		glTranslatef(0.0, f->base.height, 0.0);
		h += f->header_spacing;
		if(h > p)
		{
			if(h - f->header_spacing < p)
				glTranslatef(0.0, p - h, 0.0);
			else
				glTranslatef(0.0, -f->header_spacing, 0.0);
		}
		GLint i;
		for(i = 0; i < (GLint)f->count; i++)
		{
			GLfloat cw = 0.0;
			GLfloat ch = 0.0;
			f->items[i].get_geometry_func(f->items[i].component, &cw, &ch);
			h += ch;
			if(h < p)
			{
				h += f->spacing;
				if(h > p)
				{
					if(h - f->spacing < p)
						glTranslatef(0.0, p - h, 0.0);
					else
						glTranslatef(0.0, -f->spacing, 0.0);
				}
				continue;
			}
			if(h > p)
			{
				if(h - ch < p)
					glTranslatef(0.0, p - h, 0.0);
				else
					glTranslatef(0.0, -ch, 0.0);
			}
			glPushMatrix();
			{
				glTranslatef(f->base.width / 2 - cw / 2, 0.0, 0.01);
				f->items[i].render_func(f->items[i].component);
			}
			glPopMatrix();
			h += f->spacing;
			glTranslatef(0.0, -f->spacing, 0.0);
			if(h - p > f->base.height)
				break;
		}
	}
	glPopMatrix();
	f->bar.progress = f->progress;
	f->bar.map_total_height = th;
	if(th > f->base.height)
	{
		glPushMatrix();
		{
			glTranslatef(f->base.width - f->bar.block_width, 0.0, f->bar.base.z);
			UI_RenderSliderBar(&f->bar);
		}
		glPopMatrix();
	}
	WIDGETPTR_CLIP_RENDER_END(f)
}

int UI_SlideFlickable(flickable *f, GLfloat dis)
{
	if(!f)
		return 0;
	if(dis == 0.0)
		return 0;
	if(!f->items || f->count == 0)
		return 0;
	if(f->progress == 0.0 && dis < 0.0)
		return 0;
	if(f->progress == 1.0 && dis > 0.0)
		return 0;
	GLfloat ah = 0.0;
	UI_GetFlickableTotalHeightAndMaxWidth(f, NULL, &ah);
	GLfloat th = f->header_spacing + f->footer_spacing + ah;
	if(th <= f->base.height)
		return 0;
	GLfloat p = KARIN_MAX((th - f->base.height) * f->progress, 0.0);
	p += dis;
	if(p < 0.0)
		p = 0.0;
	else if(p > th - f->base.height)
		p = th - f->base.height;
	f->progress = p / (th - f->base.height); // if(th == f->base.height) return before this compute, else may be throw float exception.
	f->bar.progress = f->progress;
	return 1;
}

int UI_ClickFlickable(flickable *f, GLfloat x, GLfloat y)
{
	if(!f)
		return 0;
	if(!f->items || f->count == 0)
		return 0;

	GLfloat ah = 0.0;
	UI_GetFlickableTotalHeightAndMaxWidth(f, NULL, &ah);
	GLfloat h = 0.0;
	GLfloat th = f->header_spacing + f->footer_spacing + ah;
	GLfloat p = KARIN_MAX((th - f->base.height) * f->progress, 0.0);

	h += f->header_spacing;
	GLuint i;
	for(i = 0; i < f->count; i++)
	{
		GLfloat cw;
		GLfloat ch;
		f->items[i].get_geometry_func(f->items[i].component, &cw, &ch);
		h += ch;
		if(h < p)
		{
			h += f->spacing;
			continue;
		}
		GLfloat dx = f->base.width / 2 - cw / 2;
		GLfloat dy = f->base.height - (h - p);
		GLfloat dh = ch;
		if(h > p && h - ch < p)
			dh = h - p;
		else if(h > p + f->base.height && h - ch < p + f->base.height)
			dh = p + f->base.height - (h - ch);
		if((x >= dx && x <= dx + cw)
				&& (y >= dy && y <= dy + dh))
		{
			if(dh != ch)
			{
				if(h > p && h - ch < p)
				{
					f->progress = (h - ch) / (th - f->base.height); // if(th == lst->base.height) return before this compute, else may be throw float exception.
					f->bar.progress = f->progress;
				}
				else if(h > p + f->base.height && h - ch < p + f->base.height)
				{
					f->progress = (h - f->base.height) / (th - f->base.height); // if(th == f->base.height) return before this compute, else may be throw float exception.
					f->bar.progress = f->progress;
				}
			}
			if(f->items[i].action_func)
				f->items[i].action_func(f->items[i].component, x - dx, y - dy);
			return 1;
		}
		h += f->spacing;
		if(h - p > f->base.height)
			break;
	}
	return 0;
}

#if 0
int UI_MoveListViewCurrentIndex(list_view *lst, GLint step)
{
	if(!lst)
		return 0;
	if(step == 0)
		return 0;
	if(!lst->delegate.component || lst->delegate.update_func == NULL || lst->delegate.render_func == NULL || lst->delegate.get_geometry_func == NULL)
		return 0;
	if(!lst->data || lst->count == 0)
		return 0;
	if(step < 0 && lst->current_index <= 0)
		return 0;
	if(step > 0 && lst->current_index >= (GLint)lst->count - 1)
		return 0;
	GLint index = lst->current_index + step;
	if(index < 0)
		index = 0;
	else if(index > (GLint)lst->count - 1)
		index = lst->count - 1;
	lst->current_index = index;

	GLfloat ch;
	lst->delegate.get_geometry_func(lst->delegate.component, NULL, &ch);
	GLfloat th = lst->header_spacing/* + lst->footer_spacing */+ (lst->count - 1) * lst->spacing + ch * lst->count;
	GLfloat ih = lst->header_spacing/* + lst->footer_spacing */+ (lst->current_index - 1 + 1) * lst->spacing + ch * (lst->current_index + 1);
	GLfloat p = KARIN_MAX((th - lst->base.height) * lst->progress, 0.0);
	if((ih > p && ih <= p + lst->base.height)
			&& (ih - ch >= p && ih - ch < p + lst->base.height))
		return 1;
	else if(ih - ch < p)
	{
		lst->progress = (ih - ch) / (th - lst->base.height); // if(th == lst->base.height) return before this compute, else may be throw float exception.
		lst->bar.progress = lst->progress;
		return 1;
	}
	else if(ih > p + lst->base.height)
	{
		lst->progress = (ih - lst->base.height) / (th - lst->base.height); // if(th == lst->base.height) return before this compute, else may be throw float exception.
		lst->bar.progress = lst->progress;
		return 1;
	}
	return 0;
}
#endif

void delete_flickable(flickable *f)
{
	if(!f)
		return;
	int i;
	for(i = vertex_buffer_type; i < total_buffer_type; i++)
	{
		if(glIsBuffer(f->buffers[i]))
			glDeleteBuffers(1, f->buffers + i);
	}
	delete_slider_bar(&f->bar);
	f->items = NULL;
	f->count = 0;
}

void UI_GetFlickableTotalHeightAndMaxWidth(const flickable *f, float *w, float *h)
{
	if(!f || (!w && !h))
		return;
	if(!f->items || f->count == 0)
		return;
	GLfloat width = 0.0;
	GLfloat height = 0.0;
	GLuint i;
	for(i = 0; i < f->count; i++)
	{
		GLfloat cw = 0.0;
		GLfloat ch = 0.0;
		f->items[i].get_geometry_func(f->items[i].component, &cw, &ch);
		width = KARIN_MAX(width, cw);
		height += ch;
		if(i < f->count - 1)
			height += f->spacing;
	}
	if(w)
		*w = width;
	if(h)
		*h = height;
}

void UI_ResizeFlickable(flickable *f, GLfloat width, GLfloat height)
{
	if(!f)
		return;
	if(f->base.width == width && f->base.height == height)
		return;
	UI_SetWidgetSize(&f->base, width, height, geometry_wh_mask);
	UI_InitFlickableBuffer(f);
	if(f->base.height != height)
		UI_ResizeSliderBar(&f->bar, 10, f->base.height);
}

void UI_ResetFlickablePosition(flickable *f, GLfloat x, GLfloat y)
{
	if(!f)
		return;
	if(f->base.x == x && f->base.y == y)
		return;
	UI_SetWidgetPosition(&f->base, x, y, 0, geometry_xy_mask);
}

void UI_InitFlickableBuffer(flickable *f)
{
	if(!f)
		return;
	GLfloat vertex[] = {
		0.0, 0.0,
		f->base.width, 0.0,
		0.0, f->base.height,
		f->base.width, f->base.height
	};
	if(glIsBuffer(f->buffers[vertex_buffer_type]))
	{
		glBindBuffer(GL_ARRAY_BUFFER, f->buffers[vertex_buffer_type]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 8, vertex);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else
		f->buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, vertex, GL_STATIC_DRAW);
}

void UI_ResetFlickableGeometry(flickable *f, GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	if(!f)
		return;
	UI_ResetFlickablePosition(f, x, y);
	UI_ResizeFlickable(f, width, height);
}
