#ifndef KARIN_GAME_WIDGETBASE_H
#define KARIN_GAME_WIDGETBASE_H

#include "opengl.h"
#include "font.h"
#include "gl_util.h"

#define SET_TEXT(dst, src) \
{ \
	if(dst) \
	{ \
		free(dst); \
		dst = NULL; \
	} \
	if(src) \
	{ \
		dst = strdup(src); \
	} \
}

typedef enum _widget_geometry_mask
{
	geometry_x_mask = 1,
	geometry_y_mask = 1 << 1,
	geometry_z_mask = 1 << 2,
	geometry_w_mask = 1 << 3,
	geometry_h_mask = 1 << 4,
	geometry_xy_mask = geometry_x_mask | geometry_y_mask,
	geometry_xyz_mask = geometry_x_mask | geometry_y_mask | geometry_z_mask,
	geometry_wh_mask = geometry_w_mask | geometry_h_mask,
	geometry_xywh_mask = geometry_xy_mask | geometry_wh_mask,
	geometry_xyzwh_mask = geometry_xyz_mask | geometry_wh_mask
} geometry_geometry_mask;

typedef struct _base_widget
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat width;
	GLfloat height;
	GLboolean visible;
	GLfloat scale;
} base_widget;

typedef struct _rect1
{
	GLfloat x;
	GLfloat y;
	GLfloat w;
	GLfloat h;
} rect1;

typedef struct _rect2
{
	GLfloat x1;
	GLfloat y1;
	GLfloat x2;
	GLfloat y2;
} rect2;

typedef struct _font_widget
{
	base_widget base;
	char *text;
	const font *fnt;
	GLfloat color[4];
} font_widget;

typedef struct _frame_widget
{
	base_widget base;
	GLfloat border_width;
	GLfloat border_color[4];
	GLfloat bg_color[4];
	texture *bg_tex;
} frame_widget;

base_widget * new_base_widget(base_widget *wid, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLboolean visible, GLfloat scale);
void UI_SetWidgetSize(base_widget *base, GLfloat w, GLfloat h, GLbitfield mask);
void UI_SetWidgetPosition(base_widget *base, GLfloat x, GLfloat y, GLfloat z, GLbitfield mask);
void UI_SetWidgetGeometry(base_widget *base, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLbitfield mask);
GLboolean UI_PointInRect1(const rect1 *r, GLfloat x, GLfloat y);
GLboolean UI_PointInRect2(const rect2 *r, GLfloat x, GLfloat y);
GLboolean UI_PointInWidget(const base_widget *w, GLfloat x, GLfloat y);

#endif
