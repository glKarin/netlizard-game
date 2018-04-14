#ifndef KARIN_GAME_FLICKABLE_H
#define KARIN_GAME_FLICKABLE_H

#include "widget_base.h"
#include "slider_bar.h"
#include "comp_util.h"

typedef struct _flickable_item
{
	GLvoid *component;
	Render_Delegate_Function render_func;
	Get_Geometry_Function get_geometry_func;
	Item_Action_Function action_func;
} flickable_item;

typedef struct _flickable
{
	base_widget base;
	GLfloat spacing;
	GLfloat header_spacing;
	GLfloat footer_spacing;
	GLint current_index;
	GLclampf progress;
	slider_bar bar;
	flickable_item *items;
	GLuint count;
	GLfloat bg_color[4];
	GLuint buffers[total_buffer_type];
} flickable;

flickable * new_flickable(flickable *fl, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, const GLfloat spacing, GLfloat header_spacing, GLfloat footer_spacing, const GLfloat bg_color[], const GLfloat bar_color[], const GLfloat bar_block_color[]);
void UI_RenderFlickable(flickable *f);
void delete_flickable(flickable *f);

int UI_SlideFlickable(flickable *f, GLfloat dis);
int UI_ClickFlickable(flickable *f, GLfloat x, GLfloat y);
void UI_ResizeFlickable(flickable *f, GLfloat width, GLfloat height);
void UI_ResetFlickablePosition(flickable *f, GLfloat x, GLfloat y);
void UI_ResetFlickableGeometry(flickable *f, GLfloat x, GLfloat y, GLfloat width, GLfloat height);
#endif

