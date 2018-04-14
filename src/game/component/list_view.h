#ifndef KARIN_GAME_LISTVIEW_H
#define KARIN_GAME_LISTVIEW_H

#include "widget_base.h"
#include "slider_bar.h"
#include "comp_util.h"

typedef void (*List_Action_Function)(void *args);

typedef enum _list_view_action_type
{
	listview_nothing_action_type = 0,
	listview_list_action_type,
	listview_user_action_type
} list_view_action_type;

typedef struct _list_view_user_action
{
	list_view_action_type type;
	GLvoid *action_func;
	GLvoid *func_args;
} list_view_user_action;

typedef struct _list_view_list_action
{
	list_view_action_type type;
	GLvoid *data;
	GLuint count;
} list_view_list_action;

typedef union _list_view_action
{
	list_view_action_type type;
	list_view_user_action user;
	list_view_list_action list;
} list_view_action;

typedef struct _list_view_data
{
	//list_view_action action;
	char *text;
	List_Action_Function func;
	GLvoid *args;
} list_view_data;

typedef struct _list_view_delegate
{
	GLvoid *component;
	Update_Text_Function update_func;
	Render_Delegate_Function render_func;
	Get_Geometry_Function get_geometry_func;
} list_view_delegate;

typedef struct _list_view
{
	base_widget base;
	GLfloat spacing;
	GLfloat header_spacing;
	GLfloat footer_spacing;
	GLint current_index;
	GLclampf progress;
	list_view_delegate delegate;
	list_view_data *data; // support by other, list view only use this, and do not free this.
	GLuint count;
	GLuint buffers[vertex_buffer_type];
	GLfloat bg_color[4];
	slider_bar bar;
} list_view;

list_view * new_list_view(list_view *lst, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, const GLfloat spacing, GLfloat header_spacing, GLfloat footer_spacing, const GLfloat bg_color[], const GLfloat bar_color[], const GLfloat bar_block_color[]);
void UI_RenderListView(list_view *lst);
void delete_list_view(list_view *lst);

// list view event. if return non zero, the list view is changed.
int UI_SlideListView(list_view *lst, GLfloat dis);
int UI_ClickListView(list_view *lst, GLfloat x, GLfloat y);
int UI_MoveListViewCurrentIndex(list_view *lst, GLint step);
void UI_ResetListViewPosition(list_view *l, GLfloat x, GLfloat y);
void UI_ResizeListView(list_view *l, GLfloat width, GLfloat height);
void UI_ResetListViewGeometry(list_view *l, GLfloat x, GLfloat y, GLfloat width, GLfloat height);
#endif
