#include "list_view.h"
#include "nl_std.h"
#include "button.h"

#include <string.h>
#include <stdlib.h>

static void UI_InitListViewBuffer(list_view *l);

list_view * new_list_view(list_view *lst, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat spacing, GLfloat header_spacing, GLfloat footer_spacing, const GLfloat bg_color[], const GLfloat bar_color[], const GLfloat bar_block_color[])
{
	RETURN_PTR(l, lst, list_view)
	new_base_widget(&l->base, x, y, z, width, height, GL_TRUE, 1.0);
		COPY_COLOR4(l->bg_color, bg_color)
	l->spacing = spacing;
	l->header_spacing = header_spacing;
	l->footer_spacing = footer_spacing;
	l->current_index = -1;
	l->progress = 0.0;

	UI_InitListViewBuffer(l);
	l->data = NULL;
	l->count = 0;
	l->delegate.component = NULL;
	l->delegate.update_func = NULL;
	l->delegate.get_geometry_func = NULL;
	new_slider_bar(&l->bar, 0.0, 0.0, 0.02, 4, 10, l->base.height, l->base.height, l->base.height, bar_color, bar_block_color);
	l->bar.base.clip = GL_FALSE;
	return l;
}

void UI_RenderListView(list_view *lst)
{
	if(!lst)
		return;
	if(!lst->base.visible)
		return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, lst->buffers[vertex_buffer_type]);
	glVertexPointer(2, GL_FLOAT, 0, NULL);
	WIDGETPTR_CLIP_RENDER_BEGIN(lst)
	glPushAttrib(GL_CURRENT_BIT);
	{
		glColor4fv(lst->bg_color);
		oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	glPopAttrib();
	WIDGETPTR_CLIP_RENDER_END(lst)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);

	if(!lst->delegate.component || lst->delegate.update_func == NULL || lst->delegate.render_func == NULL || lst->delegate.get_geometry_func == NULL)
		return;
	if(!lst->data || lst->count == 0)
		return;
	GLfloat cw;
	GLfloat ch;
	lst->delegate.get_geometry_func(lst->delegate.component, &cw, &ch);
	GLfloat h = 0.0;
	GLfloat th = lst->header_spacing + lst->footer_spacing + (lst->count - 1) * lst->spacing + ch * lst->count;
	if(th <= lst->base.height)
		lst->progress = 1.0;

	GLfloat p = KARIN_MAX((th - lst->base.height) * lst->progress, 0.0);

	WIDGETPTR_CLIP_RENDER_BEGIN(lst)
	glPushMatrix();
	{
		glTranslatef(0.0, lst->base.height, 0.0);
		h += lst->header_spacing;
		if(h > p)
		{
			if(h - lst->header_spacing < p)
				glTranslatef(0.0, p - h, 0.0);
			else
				glTranslatef(0.0, -lst->header_spacing, 0.0);
		}
		GLint i;
		for(i = 0; i < (GLint)lst->count; i++)
		{
			h += ch;
			if(h < p)
			{
				h += lst->spacing;
				if(h > p)
				{
					if(h - lst->spacing < p)
						glTranslatef(0.0, p - h, 0.0);
					else
						glTranslatef(0.0, -lst->spacing, 0.0);
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
			lst->delegate.update_func(lst->delegate.component, lst->data[i].text, lst->current_index == i ? GL_TRUE : GL_FALSE);
			glPushMatrix();
			{
				glTranslatef(lst->base.width / 2 - cw / 2, 0.0, 0.01);
				lst->delegate.render_func(lst->delegate.component);
			}
			glPopMatrix();
			h += lst->spacing;
			glTranslatef(0.0, -lst->spacing, 0.0);
			if(h - p > lst->base.height)
				break;
		}
	}
	glPopMatrix();
	lst->bar.progress = lst->progress;
	lst->bar.map_total_height = th;
	if(th > lst->base.height)
	{
		glPushMatrix();
		{
			glTranslatef(lst->base.width - lst->bar.block_width, 0.0, lst->bar.base.z);
			UI_RenderSliderBar(&lst->bar);
		}
		glPopMatrix();
	}
	WIDGETPTR_CLIP_RENDER_END(lst)
}

int UI_SlideListView(list_view *lst, GLfloat dis)
{
	if(!lst)
		return 0;
	if(dis == 0.0)
		return 0;
	if(!lst->delegate.component || lst->delegate.update_func == NULL || lst->delegate.render_func == NULL || lst->delegate.get_geometry_func == NULL)
		return 0;
	if(!lst->data || lst->count == 0)
		return 0;
	if(lst->progress == 0.0 && dis < 0.0)
		return 0;
	if(lst->progress == 1.0 && dis > 0.0)
		return 0;
	GLfloat ch;
	lst->delegate.get_geometry_func(lst->delegate.component, NULL, &ch);
	GLfloat th = lst->header_spacing + lst->footer_spacing + (lst->count - 1) * lst->spacing + ch * lst->count;
	if(th <= lst->base.height)
		return 0;
	GLfloat p = KARIN_MAX((th - lst->base.height) * lst->progress, 0.0);
	p += dis;
	if(p < 0.0)
		p = 0.0;
	else if(p > th - lst->base.height)
		p = th - lst->base.height;
	lst->progress = p / (th - lst->base.height); // if(th == lst->base.height) return before this compute, else may be throw float exception.
	lst->bar.progress = lst->progress;
	return 1;
}

int UI_ClickListView(list_view *lst, GLfloat x, GLfloat y)
{
	if(!lst)
		return 0;
	if(!lst->delegate.component || lst->delegate.update_func == NULL || lst->delegate.render_func == NULL || lst->delegate.get_geometry_func == NULL)
		return 0;
	if(!lst->data || lst->count == 0)
		return 0;

	GLfloat cw;
	GLfloat ch;
	lst->delegate.get_geometry_func(lst->delegate.component, &cw, &ch);
	GLfloat h = 0.0;
	GLfloat th = lst->header_spacing + lst->footer_spacing + (lst->count - 1) * lst->spacing + ch * lst->count;
	GLfloat p = KARIN_MAX((th - lst->base.height) * lst->progress, 0.0);

	h += lst->header_spacing;
	GLuint i;
	for(i = 0; i < lst->count; i++)
	{
		h += ch;
		if(h < p)
		{
			h += lst->spacing;
			continue;
		}
		GLfloat dx = lst->base.width / 2 - cw / 2;
		GLfloat dy = lst->base.height - (h - p);
		GLfloat dh = ch;
		if(h > p && h - ch < p)
			dh = h - p;
		else if(h > p + lst->base.height && h - ch < p + lst->base.height)
			dh = p + lst->base.height - (h - ch);
		if((x >= dx && x <= dx + cw)
				&& (y >= dy && y <= dy + dh))
		{
			lst->current_index = i;
			if(dh != ch)
			{
				if(h > p && h - ch < p)
				{
					lst->progress = (h - ch) / (th - lst->base.height); // if(th == lst->base.height) return before this compute, else may be throw float exception.
					lst->bar.progress = lst->progress;
				}
				else if(h > p + lst->base.height && h - ch < p + lst->base.height)
				{
					lst->progress = (h - lst->base.height) / (th - lst->base.height); // if(th == lst->base.height) return before this compute, else may be throw float exception.
					lst->bar.progress = lst->progress;
				}
			}
			if(lst->data[lst->current_index].func)
				lst->data[lst->current_index].func(lst->data[lst->current_index].args);
			return 1;
		}
		h += lst->spacing;
		if(h - p > lst->base.height)
			break;
	}
	return 0;
}

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
	return UI_SetListCurrentIndex(lst, index);
}

void delete_list_view(list_view *lst)
{
	if(!lst)
		return;
	int i;
	for(i = vertex_buffer_type; i < total_buffer_type; i++)
	{
		if(glIsBuffer(lst->buffers[i]))
			glDeleteBuffers(1, lst->buffers + i);
	}
	delete_slider_bar(&lst->bar);
	lst->delegate.component = NULL;
	lst->delegate.update_func = NULL;
	lst->delegate.render_func = NULL;
	lst->delegate.get_geometry_func = NULL;
	lst->data = NULL;
	lst->count = 0;
}

void UI_ResizeListView(list_view *l, GLfloat width, GLfloat height)
{
	if(!l)
		return;
	if(l->base.width == width && l->base.height == height)
		return;
	UI_SetWidgetSize(&l->base, width, height, geometry_wh_mask);
	UI_InitListViewBuffer(l);
	if(l->base.height != height)
		UI_ResizeSliderBar(&l->bar, 10, l->base.height);
}

void UI_ResetListViewPosition(list_view *l, GLfloat x, GLfloat y)
{
	if(!l)
		return;
	if(l->base.x == x && l->base.y == y)
		return;
	UI_SetWidgetPosition(&l->base, x, y, 0, geometry_xy_mask);
}

void UI_InitListViewBuffer(list_view *l)
{
	if(!l)
		return;
	GLfloat vertex[] = {
		0.0, 0.0,
		l->base.width, 0.0,
		0.0, l->base.height,
		l->base.width, l->base.height
	};
	if(glIsBuffer(l->buffers[vertex_buffer_type]))
	{
		glBindBuffer(GL_ARRAY_BUFFER, l->buffers[vertex_buffer_type]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 8, vertex);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else
		l->buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, vertex, GL_STATIC_DRAW);
}

void UI_ResetListViewGeometry(list_view *l, GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	if(!l)
		return;
	UI_ResetListViewPosition(l, x, y);
	UI_ResizeListView(l, width, height);
}

unsigned UI_SetListCurrentIndex(list_view *lst, unsigned int index)
{
	if(!lst)
		return 0;
	if(!lst->delegate.component || lst->delegate.update_func == NULL || lst->delegate.render_func == NULL || lst->delegate.get_geometry_func == NULL)
		return 0;
	if(!lst->data || lst->count == 0)
		return 0;
	if(index >= lst->count - 1)
		return 0;
	lst->current_index = index;

	GLfloat ch;
	lst->delegate.get_geometry_func(lst->delegate.component, NULL, &ch);
	GLfloat th = lst->header_spacing + lst->footer_spacing + (lst->count - 1) * lst->spacing + ch * lst->count;
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
