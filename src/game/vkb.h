#ifndef KARIN_VKB_H
#define KARIN_VKB_H

#include "game_util.h"

#define SECOND_VKB_COUNT 1

#define VKB_COUNT SECOND_VKB_COUNT + 14
#define JOYSTICK_COUNT 1
#define SWIPE_COUNT 1
#define CURSOR_COUNT 2
#define TOTAL_VKB_COUNT (VKB_COUNT + SWIPE_COUNT + JOYSTICK_COUNT + CURSOR_COUNT)

#define VKB_TEX_COUNT 2

typedef enum _vkb_type
{
	vkb_button_type = 0,
	vkb_joystick_type,
	vkb_swipe_type,
	vkb_cursor_type,
	vkb_total_type
} vkb_type;

typedef int (*VKB_Key_Action_Function)(int, int, int);

typedef struct _virtual_control_base
{
	vkb_type type;
	GLfloat x;
	GLfloat y;
	GLint z;
	GLfloat width;
	GLfloat height;
	GLfloat e_min_x;
	GLfloat e_min_y;
	GLfloat e_max_x;
	GLfloat e_max_y;
	GLboolean pressed;
	GLboolean enabled;
	GLboolean visible;
	GLuint tex_index;
	GLuint buffers[total_buffer_type];
} virtual_control_base;

typedef struct _virtual_cursor
{
	virtual_control_base base;

	Game_Action action;
	Harmattan_Key key;
	Game_Action actions[4];
	Harmattan_Key keys[4];
	GLuint mask[4];
	GLfloat angle;
	GLfloat distance;
	GLfloat ignore_distance;
	GLfloat e_radius;
	GLfloat pos_x;
	GLfloat pos_y;
	GLboolean render_bg;
} virtual_cursor;

typedef struct _virtual_swipe
{
	virtual_control_base base;

	Game_Action actions[4];
	Harmattan_Key keys[4];
	GLuint mask[4];
	GLfloat angle;
	GLfloat distance;
	GLfloat ignore_distance;
} virtual_swipe;

typedef struct _virtual_joystick
{
	virtual_control_base base;

	Game_Action actions[4];
	Harmattan_Key keys[4];
	GLfloat e_radius;
	GLfloat angle;
	GLclampf percent;
	GLfloat e_ignore_radius;
	GLfloat pos_x;
	GLfloat pos_y;
} virtual_joystick;

typedef struct _virtual_button
{
	virtual_control_base base;

	Game_Action action;
	Harmattan_Key key;
} virtual_button;

typedef union _virtual_control_item
{
	vkb_type type;
	virtual_control_base base;
	virtual_cursor cursor;
	virtual_swipe swipe;
	virtual_joystick joystick;
	virtual_button button;
} virtual_control_item;

typedef struct _vkb
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat width;
	GLfloat height;
	texture *tex[VKB_TEX_COUNT];
	virtual_control_item vb[TOTAL_VKB_COUNT];
} vkb;

int UI_VKBMouseMotionEvent(vkb *v, int b, int p, int x, int y, int dx, int dy, VKB_Key_Action_Function f);
int UI_VKBMouseEvent(vkb *v, int b, int p, int x, int y, VKB_Key_Action_Function f);
vkb * new_vkb(vkb *v, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h);
void delete_vkb(vkb *v);
void UI_RenderVKB(const vkb *v);
void UI_ResizeVKB(const vkb *v, GLfloat w, GLfloat h);

#endif
