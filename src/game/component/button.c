#include "button.h"
#include "nl_std.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

static void UI_InitButtonBuffer(button *b);

button * new_button(button *btn, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat border_width, const GLfloat bg_color[], const GLfloat text_color[], const GLfloat border_color[], const GLfloat hl_bg_color[], const GLfloat hl_text_color[], const GLfloat hl_border_color[], const char *text)
{
	RETURN_PTR(b, btn, button)

	GLuint count = 360;
	new_base_widget(&b->base, x, y, z, width, height, GL_TRUE, 1.0);
	b->count = count + 2;
	b->fnt = NULL;
	b->border_width = border_width;
	COPY_COLOR4(b->bg_color, bg_color);
	COPY_COLOR4(b->hl_bg_color, hl_bg_color);
	COPY_COLOR4(b->text_color, text_color);
	COPY_COLOR4(b->hl_text_color, hl_text_color);
	COPY_COLOR4(b->border_color, border_color);
	COPY_COLOR4(b->hl_border_color, hl_border_color);
	UI_InitButtonBuffer(b);

	GLushort *index = NEW_II(GLushort, 3 * (count + 2) + 2 * (count + 2));
	unsigned int j = 0;
	GLuint k;
	for(k = 0; k < count / 2; k++)
	{
		index[j] = 0;
		index[j + 1] = k + 1;
		index[j + 2] = k + 2;
		j += 3;
	}
	for(k = 0; k < count / 2; k++)
	{
		index[j] = count / 2 + 1 + 1;
		index[j + 1] = count / 2 + 1 + 1 + k + 1;
		index[j + 2] = count / 2 + 1 + 1 + k + 2;
		j += 3;
	}
	index[j] = 1;
	index[j + 1] = count / 2 + 1;
	index[j + 2] = count / 2 + 1 + 1 + 1;
	index[j + 3] = 1;
	index[j + 4] = count / 2 + 1 + 1 + 1;
	index[j + 5] = count + 2 + 1;
	j += 6;
	for(k = 0; k < count / 2; k++)
	{
		index[j] = k + 1;
		index[j + 1] = k + 2;
		j += 2;
	}
	for(k = 0; k < count / 2; k++)
	{
		index[j] = count / 2 + 1 + 1 + k + 1;
		index[j + 1] = count / 2 + 1 + 1 + k + 2;
		j += 2;
	}
	index[j] = 1;
	index[j + 1] = count + 2 + 1;
	index[j + 2] = count / 2 + 1 + 1 + 1;
	index[j + 3] = count / 2 + 1;
	b->buffers[index_buffer_type] = new_OpenGL_buffer_object(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 5 * (count + 2), index, GL_STATIC_DRAW);
	free(index);
	if(text)
		b->text = strdup(text);

	b->highlight = GL_FALSE;
	return b;
}

void UI_RenderButton(const button *b)
{
	if(!b)
		return;
	if(!b->base.visible)
		return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, b->buffers[vertex_buffer_type]);
	glVertexPointer(2, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b->buffers[index_buffer_type]);

	WIDGETPTR_CLIP_RENDER_BEGIN(b)
	glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT);
	{
		if(b->highlight)
			glColor4fv(b->hl_bg_color);
		else
			glColor4fv(b->bg_color);
		oglDrawElements(GL_TRIANGLES, 3 * b->count, GL_UNSIGNED_SHORT, NULL);

		if(b->border_width > 0.0)
		{
			oglEnable(GL_LINE_SMOOTH);
			glLineWidth(b->border_width);
			if(b->highlight)
				glColor4fv(b->hl_border_color);
			else
				glColor4fv(b->border_color);
			oglDrawElements(GL_LINES, 2 * b->count, GL_UNSIGNED_SHORT, (GLushort *)NULL + 3 * b->count);
		}
	}
	glPopAttrib();

	if(b->fnt && b->text)
	{
		GLfloat x = 0.0;
		GLfloat y = 0.0;
		Font_GetStringCenterPosition(b->fnt, 0, 0, b->base.width, b->base.height, b->text, &x, &y);
		glPushMatrix();
		{
			glTranslatef(0.0, 0.0, 0.01);
			if(b->highlight)
				Font_RenderString(b->fnt, x, y, b->hl_text_color[0], b->hl_text_color[1], b->hl_text_color[2], b->hl_text_color[3], b->text);
			else
				Font_RenderString(b->fnt, x, y, b->text_color[0], b->text_color[1], b->text_color[2], b->text_color[3], b->text);
		}
		glPopMatrix();
	}
	WIDGETPTR_CLIP_RENDER_END(b)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void delete_button(button *b)
{
	if(!b)
		return;
	int i;
	for(i = 0; i < total_buffer_type; i++)
	{
		if(glIsBuffer(b->buffers[i]))
			glDeleteBuffers(1, b->buffers + i);
	}
	FREE_PTR(b->text)
		b->fnt = NULL;
}

void UI_ResizeButton(button *b, GLfloat width, GLfloat height)
{
	if(!b)
		return;
	if(width == b->base.width && height == b->base.height)
		return;
	UI_SetWidgetSize(&b->base, width, height, geometry_wh_mask);

	UI_InitButtonBuffer(b);
}

void UI_ResetButtonPosition(button *b, GLfloat x, GLfloat y)
{
	if(!b)
		return;
	if(b->base.x == x && b->base.y == y)
		return;
	UI_SetWidgetPosition(&b->base, x, y, 0, geometry_xy_mask);
}

void UI_InitButtonBuffer(button *b)
{
	if(!b)
		return;
	GLfloat i;
	GLuint count = 360;
	GLfloat w = b->base.height / 2;
	GLfloat left_x = b->base.height / 2;
	GLfloat left_y = b->base.height / 2;
	GLfloat right_x = b->base.width - b->base.height / 2;
	GLfloat right_y = b->base.height / 2;
	GLfloat *vertex = NEW_II(GLfloat, 2 * (count + 2 + 2));
	unsigned int j = 2;
	vertex[0] = left_x;
	vertex[1] = left_y;
	for(i = 90.0; i <= 270.0; i += 1.0)
	{
		GLfloat r = ator(i);
		vertex[j] = cos(r) * w + left_x;
		vertex[j + 1] = sin(r) * w + left_y;
		j += 2;
	}
	vertex[j] = right_x;
	vertex[j + 1] = right_y;
	j += 2;
	for(i = 270.0; i <= 270.0 + 180.0; i += 1.0)
	{
		GLfloat r = ator(Algo_FormatAngle(i));
		vertex[j] = cos(r) * w + right_x;
		vertex[j + 1] = sin(r) * w + right_y;
		j += 2;
	}

	if(glIsBuffer(b->buffers[vertex_buffer_type]))
	{
		glBindBuffer(GL_ARRAY_BUFFER, b->buffers[vertex_buffer_type]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 2 * (count + 2 + 2), vertex);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else
		b->buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * (count + 2 + 2), vertex, GL_STATIC_DRAW);

	free(vertex);
}

void UI_ResetButtonGeometry(button *b, GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	if(!b)
		return;
	UI_ResetButtonPosition(b, x, y);
	UI_ResizeButton(b, width, height);
}
