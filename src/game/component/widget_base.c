#include "widget_base.h"

#include "nl_std.h"

base_widget * new_base_widget(base_widget *wid, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLboolean visible, GLfloat scale)
{
	RETURN_PTR(w, wid, base_widget)

		w -> x = x;
	w -> y = y;
	w -> z = z;
	w -> width = width;
	w -> height = height;
	w -> visible = visible;
	w -> scale = scale;
	return w;
}

void UI_SetWidgetSize(base_widget *base, GLfloat w, GLfloat h, GLbitfield mask)
{
	if(!base)
		return;
	if(mask & geometry_w_mask && w > 0.0)
		base -> width = w;
	if(mask & geometry_h_mask && h > 0.0)
		base -> height = h;
}

void UI_SetWidgetPosition(base_widget *base, GLfloat x, GLfloat y, GLfloat z, GLbitfield mask)
{
	if(!base)
		return;
	if(mask & geometry_x_mask)
		base -> x = x;
	if(mask & geometry_y_mask)
		base -> y = y;
	if(mask & geometry_z_mask)
		base -> z = z;
}

void UI_SetWidgetGeometry(base_widget *base, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLbitfield mask)
{
	if(!base)
		return;
	UI_SetWidgetSize(base, w, h, mask);
	UI_SetWidgetPosition(base, x, y, z, mask);
}

GLboolean UI_PointInRect1(const rect1 *r, GLfloat x, GLfloat y)
{
	if(!r)
		return GL_FALSE;
	return((x >= r -> x && x <= r -> x + r -> w) 
			&& (y >= r -> y && y <= r -> y + r -> h) ? GL_TRUE : GL_FALSE);
}
GLboolean UI_PointInRect2(const rect2 *r, GLfloat x, GLfloat y)
{
	if(!r)
		return GL_FALSE;
	return((x >= r -> x1 && x <= r -> x2) 
			&& (y >= r -> y1 && y <= r -> y2) ? GL_TRUE : GL_FALSE);
}

GLboolean UI_PointInWidget(const base_widget *w, GLfloat x, GLfloat y)
{
	if(!w)
		return GL_FALSE;
	return((x >= w -> x && x <= w -> x + w -> width) 
			&& (y >= w -> y && y <= w -> y + w -> height) ? GL_TRUE : GL_FALSE);
}
