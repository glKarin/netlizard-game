#include "vkb.h"
#include "nl_std.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define VKB_BUTTON_Z_BASE 200
#define VKB_SWIPE_Z_BASE 100
#define VKB_JOYSTICK_Z_BASE 300 
#define VKB_CURSOR_Z_BASE 400

#define VKB_TEXTURE_FILE _KARIN_RESOURCE_DIR"resource/anna_buttons.png"


#define VKB_JOY_TEXTURE_FILE _KARIN_RESOURCE_DIR"resource/circle_joystick.png"

#define CIRCLECENTERX 182
#define CIRCLECENTERY 308
#define JOYSTICKOFFSET 70
//small circle 139x139 center point (70,70)
//x offset=69 y offset=69
#define BIGCIRCLEX 0
#define BIGCIRCLEY 0
#define SMALLCIRCLEX 294
#define SMALLCIRCLEY 89
#define BIGCIRCLEWIDTH 283
#define SMALLCIRCLEWIDTH 139
#define MYARG 22.5

#define CIRCLEHALFLENGTH 185.0
#define CIRCLEHALFLENGTHWITHOUTLISTENER 25.0


#define TRANSLUCENTLEVEL 157

#define VB_WIDTH 64
#define VB_HEIGHT 64
#define VB_SPACING 10

#define VB_S(n) (n * VB_SPACING)
#define VB_W(n) (n * VB_WIDTH)
#define VB_H(n) (n * VB_HEIGHT)

#define TEX_WIDTH 64
#define TEX_HEIGHT 64
#define TEX_FULL_WIDTH 512
#define TEX_FULL_HEIGHT 512
#define TEX_W(n) (n * TEX_WIDTH)
#define TEX_H(n) (n * TEX_HEIGHT)

#define MOUSE_IN_RANGE(b, x, y) \
	((x >= (b).e_min_x && x <= (b).e_max_x ) && (y >= (b).e_min_y && y <= (b).e_max_y))

typedef enum _circle_direction
{
	circle_center = 0,
	circle_top_direction,
	circle_righttop_direction,
	circle_right_direction,
	circle_rightbottom_direction,
	circle_bottom_direction,
	circle_leftbottom_direction,
	circle_left_direction,
	circle_lefttop_direction,
	circle_outside
} circle_direction;

typedef enum _coord_base
{
	opengl_s_base = 0,
	opengl_mf_base,
	opengl_mb_base,
	opengl_e_base
} coord_base;

typedef enum _mouse_motion_button_status
{
	all_out_range_status = 0,
	last_out_now_in_range_status = 1,
	last_in_now_out_range_status = 1 << 1,
	all_in_range_status = last_out_now_in_range_status | last_in_now_out_range_status
} mouse_motion_button_status;

struct vkb_cursor
{
	GLuint x;
	GLuint y;
	GLuint r;
	GLclampf eminr;
	GLclampf emaxr;
	GLboolean render;
	GLuint tex_index;
	GLuint tx;
	GLuint ty;
	GLuint tw;
	GLfloat joy_r;
	GLuint joy_tx;
	GLuint joy_ty;
	GLuint joy_tw;
	GLuint joy_ptx;
	GLuint joy_pty;
	GLuint joy_ptw;
	GLenum x_base;
	GLenum y_base;
	GLboolean ava;
	GLint z;
	Game_Action action;
	Game_Action action0;
	Game_Action action1;
	Game_Action action2;
	Game_Action action3;
} VKB_Cursor[CURSOR_COUNT] = {
	{VB_S(4) + VB_W(6), 0, VB_W(2) + VB_S(1), 
		0.5, 5.0, GL_TRUE, 1,
		BIGCIRCLEX, BIGCIRCLEY + BIGCIRCLEWIDTH, BIGCIRCLEWIDTH,
		0.5, SMALLCIRCLEX, SMALLCIRCLEY + SMALLCIRCLEWIDTH, SMALLCIRCLEWIDTH,
		SMALLCIRCLEX, SMALLCIRCLEY + SMALLCIRCLEWIDTH, SMALLCIRCLEWIDTH,
		opengl_e_base, opengl_s_base, GL_TRUE, VKB_CURSOR_Z_BASE + 1,
		FreeViewMode_Action, FreeViewTurnUp_Action, FreeViewTurnDown_Action, FreeViewTurnLeft_Action, FreeViewTurnRight_Action},
	{VB_S(5) + VB_W(2), VB_S(2) + VB_W(1), VB_W(1) + VB_S(2),
		1.0, 3.0, GL_FALSE, 0,
		0, 0, 0,
		1.0, TEX_W(2), TEX_W(3), TEX_W(1),
		TEX_W(2), TEX_W(4), TEX_W(1),
		opengl_e_base, opengl_s_base, GL_TRUE, VKB_CURSOR_Z_BASE + 2,
		Attack_Action, TurnUp_Action, TurnDown_Action, TurnLeft_Action, TurnRight_Action
	}
};

struct vkb_swipe
{
	GLuint x;
	GLuint y;
	GLuint w;
	GLuint h;
	GLuint ex;
	GLuint ey;
	GLuint ew;
	GLuint eh;
	GLboolean render;
	GLuint tx;
	GLuint ty;
	GLuint tw;
	GLuint th;
	GLenum x_base;
	GLenum y_base;
	GLboolean ava;
	GLint z;
	Game_Action action0;
	Game_Action action1;
	Game_Action action2;
	Game_Action action3;
} VKB_Swipe[SWIPE_COUNT] = {
	{854 / 4 * 3, 0, 854, 480,
		854 / 4 * 3, 0, 854, 480, GL_FALSE,
		BIGCIRCLEX, BIGCIRCLEY + BIGCIRCLEWIDTH, BIGCIRCLEWIDTH, BIGCIRCLEWIDTH,
		opengl_e_base, opengl_s_base, GL_TRUE, VKB_BUTTON_Z_BASE + 1,
		TurnUp_Action, TurnDown_Action, TurnLeft_Action, TurnRight_Action}
};

struct vkb_joystick
{
	GLuint x;
	GLuint y;
	GLuint r;
	GLclampf eminr;
	GLclampf emaxr;
	GLuint tx;
	GLuint ty;
	GLuint tw;
	GLfloat joy_r;
	GLuint joy_tx;
	GLuint joy_ty;
	GLuint joy_tw;
	GLenum x_base;
	GLenum y_base;
	GLboolean ava;
	GLint z;
	Game_Action action0;
	Game_Action action1;
	Game_Action action2;
	Game_Action action3;
} VKB_Joystick[JOYSTICK_COUNT] = {
	{VB_S(1), VB_S(1), VB_W(3) + VB_S(2), 
		0.0f, 1.8f,
		BIGCIRCLEX, BIGCIRCLEY + BIGCIRCLEWIDTH, BIGCIRCLEWIDTH,
		0.5, SMALLCIRCLEX, SMALLCIRCLEY + SMALLCIRCLEWIDTH, SMALLCIRCLEWIDTH,
		opengl_s_base, opengl_s_base, GL_TRUE, VKB_CURSOR_Z_BASE + 1,
		Forward_Action, Backward_Action, MoveLeft_Action, MoveRight_Action}
};

struct vkb_button
{
	GLuint x;
	GLuint y;
	GLuint w;
	GLuint h;
	GLuint ex;
	GLuint ey;
	GLuint ew;
	GLuint eh;
	GLuint tx;
	GLuint ty;
	GLuint tw;
	GLuint th;
	GLuint ptx;
	GLuint pty;
	GLuint ptw;
	GLuint pth;
	GLenum x_base;
	GLenum y_base;
	GLboolean ava;
	GLint z;
	Game_Action action;
} VKB_Button[VKB_COUNT] = {
	// main
	{VB_S(1) + VB_W(1), VB_S(2) + VB_W(2), VB_W(1), VB_H(1), 
		VB_S(1) + VB_W(1), VB_S(2) + VB_W(2), VB_W(1), VB_H(1),  
		TEX_W(4), TEX_W(3), TEX_W(1), TEX_W(1),
		TEX_W(4), TEX_W(4), TEX_W(1), TEX_W(1),
		opengl_e_base, opengl_s_base, GL_TRUE, VKB_BUTTON_Z_BASE + 1,
		Jump_Action},
	{VB_S(1) + VB_W(1), VB_S(1) + VB_W(1), VB_W(1), VB_H(1), 
		VB_S(1) + VB_W(1), VB_S(1) + VB_W(1), VB_W(1), VB_H(1),  
		TEX_W(4), TEX_W(2), TEX_W(1), -TEX_W(1),
		TEX_W(4), TEX_W(3), TEX_W(1), -TEX_W(1),
		opengl_e_base, opengl_s_base, GL_TRUE, VKB_BUTTON_Z_BASE + 1,
		Crouch_Action},
	{VB_S(2) + VB_W(1), VB_H(1), VB_W(1), VB_H(1), 
		VB_S(2) + VB_W(1), VB_H(1), VB_W(1), VB_H(1),  
		TEX_W(3), TEX_W(3), TEX_W(1), TEX_W(1),
		TEX_W(3), TEX_W(4), TEX_W(1), TEX_W(1),
		opengl_s_base, opengl_e_base, GL_TRUE, VKB_BUTTON_Z_BASE + 1,
		PersonMode_Action},
	{VB_S(3) + VB_W(2), VB_S(2), VB_W(1), VB_H(1), 
		VB_S(3) + VB_W(2), VB_S(2), VB_W(1), VB_H(1),  
		TEX_W(1), TEX_W(5), TEX_W(1), TEX_W(1),
		TEX_W(1), TEX_W(6), TEX_W(1), TEX_W(1),
		opengl_mb_base, opengl_s_base, GL_TRUE, VKB_BUTTON_Z_BASE + 1,
		PrevWeapon_Action},
	{VB_S(2) + VB_W(1), VB_S(2), VB_W(1), VB_H(1), 
		VB_S(2) + VB_W(1), VB_S(2), VB_W(1), VB_H(1),  
		TEX_W(2), TEX_W(5), TEX_W(1), TEX_W(1),
		TEX_W(2), TEX_W(6), TEX_W(1), TEX_W(1),
		opengl_mb_base, opengl_s_base, GL_TRUE, VKB_BUTTON_Z_BASE + 1,
		NextWeapon_Action},
	{VB_S(4) + VB_W(4), VB_H(1), VB_W(1), VB_H(1), 
		VB_S(4) + VB_W(4), VB_H(1), VB_W(1), VB_H(1),  
		TEX_W(6), TEX_W(1), TEX_W(1), TEX_W(1),
		TEX_W(6), TEX_W(2), TEX_W(1), TEX_W(1),
		opengl_e_base, opengl_e_base, GL_TRUE, VKB_BUTTON_Z_BASE + 1,
		OperateGo_Action},
	{VB_S(3) + VB_W(3), VB_H(1), VB_W(1), VB_H(1), 
		VB_S(3) + VB_W(3), VB_H(1), VB_W(1), VB_H(1),  
		TEX_W(7), TEX_W(1), TEX_W(1), TEX_W(1),
		TEX_W(7), TEX_W(2), TEX_W(1), TEX_W(1),
		opengl_e_base, opengl_e_base, GL_TRUE, VKB_BUTTON_Z_BASE + 1,
		OperateBack_Action},
	{VB_S(2) + VB_W(2), VB_H(1), VB_W(1), VB_H(1), 
		VB_S(2) + VB_W(2), VB_H(1), VB_W(1), VB_H(1),  
		TEX_W(7), TEX_W(5), TEX_W(1), TEX_W(1),
		TEX_W(7), TEX_W(6), TEX_W(1), TEX_W(1),
		opengl_e_base, opengl_e_base, GL_TRUE, VKB_BUTTON_Z_BASE + 1,
		OperateStand_Action},
	{0, VB_H(1), VB_W(1), VB_H(1), 
		0, VB_H(1), VB_W(1), VB_H(1),  
		TEX_W(4), TEX_W(5), TEX_W(1), TEX_W(1),
		TEX_W(4), TEX_W(6), TEX_W(1), TEX_W(1),
		opengl_s_base, opengl_e_base, GL_TRUE, VKB_BUTTON_Z_BASE + 1,
		OpenScore_Action},
	{VB_S(3) + VB_W(2), VB_H(1), VB_W(1), VB_H(1), 
		VB_S(3) + VB_W(2), VB_H(1), VB_W(1), VB_H(1),  
		TEX_W(5), TEX_W(5), TEX_W(1), TEX_W(1),
		TEX_W(5), TEX_W(6), TEX_W(1), TEX_W(1),
		opengl_s_base, opengl_e_base, GL_TRUE, VKB_BUTTON_Z_BASE + 1,
		OpenRadar_Action},
	{VB_S(3) + VB_W(3), VB_S(0), VB_W(1), VB_H(1), 
		VB_S(3) + VB_W(3), VB_S(0), VB_W(1), VB_H(1),  
		TEX_W(2), TEX_W(5), TEX_W(1), TEX_W(1),
		TEX_W(2), TEX_W(6), TEX_W(1), TEX_W(1),
		opengl_e_base, opengl_s_base, GL_TRUE, VKB_BUTTON_Z_BASE + 1,
		Reload_Action},
	{VB_S(2) + VB_W(2), VB_S(0), VB_W(1), VB_H(1), 
		VB_S(2) + VB_W(2), VB_H(0), VB_W(1), VB_H(1),  
		TEX_W(2), TEX_W(3), TEX_W(1), TEX_W(1),
		TEX_W(2), TEX_W(4), TEX_W(1), TEX_W(1),
		opengl_e_base, opengl_s_base, GL_TRUE, VKB_BUTTON_Z_BASE + 1,
		ViewCenter_Action},
	{VB_W(1), VB_H(1), VB_W(1), VB_H(1), 
		VB_W(1), VB_H(1), VB_W(1), VB_H(1),  
		TEX_W(1), TEX_W(1), TEX_W(1), TEX_W(1),
		TEX_W(1), TEX_W(2), TEX_W(1), TEX_W(1),
		opengl_e_base, opengl_e_base, GL_TRUE, VKB_BUTTON_Z_BASE + 1,
		Quit_Action},

	// second
	{0, VB_S(4) + VB_W(3), VB_W(1), VB_H(1), 
		0, VB_S(4) + VB_W(3), VB_W(1), VB_H(1),  
		TEX_W(2), TEX_W(3), TEX_W(1), TEX_W(1),
		TEX_W(2), TEX_W(4), TEX_W(1), TEX_W(1),
		opengl_s_base, opengl_s_base, GL_TRUE, VKB_BUTTON_Z_BASE + 1,
		Attack_Action}
};

static mouse_motion_button_status UI_ButtonMouseMotion(const virtual_control_item *b, int nx, int ny, int lx, int ly);
static circle_direction UI_GetJoystickDirection(int x, int y, GLfloat cx, GLfloat cy, GLfloat ir, GLfloat or, float *angle, float *percent);
static circle_direction UI_GetSwipeDirection(int dx, int dy, float *angle, float *distance);
static void UI_MakeJoystick(virtual_control_item *b, struct vkb_joystick *joystick, unsigned int width, unsigned int height);
static void UI_MakeSwipe(virtual_control_item *b, struct vkb_swipe *swipe, unsigned int width, unsigned int height);
static void UI_MakeButton(virtual_control_item *b, struct vkb_button *btn, unsigned int width, unsigned int height);
static void UI_MakeCursor(virtual_control_item *b, struct vkb_cursor *cursor, unsigned int width, unsigned int height);
static int UI_GetControlItemOnPosition(const vkb *v, int x, int y, int *r);
static int UI_GetControlItemOnPosition2(const vkb *v, int x, int y, int lx, int ly, int *r, mouse_motion_button_status *s);
static void UI_RenderVKBCursor(const virtual_cursor *b, texture * const tex[]);
static void UI_RenderVKBJoystick(const virtual_joystick *b, texture * const tex[]);
static void UI_RenderVKBSwipe(const virtual_swipe *b, texture * const tex[]);
static void UI_RenderVKBButton(const virtual_button *b, texture * const tex[]);

vkb * new_vkb(vkb *vv, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h)
{
	RETURN_PTR(v, vv, vkb)

		v -> x = x;
	v -> y = y;
	v -> z = z;
	v -> width = w;
	v -> height = h;
	v -> tex[0] = new_OpenGL_texture_2d(VKB_TEXTURE_FILE);
	v -> tex[1] = new_OpenGL_texture_2d(VKB_JOY_TEXTURE_FILE);

	int i;
	int j = 0;

	// btn
	for(i = 0; i < VKB_COUNT; i++)
	{
		UI_MakeButton(v -> vb + j, VKB_Button + i, v -> width, v -> height);
		j++;
	}

	// joy
	for(i = 0; i < JOYSTICK_COUNT; i++)
	{
		UI_MakeJoystick(v -> vb + j, VKB_Joystick + i, v -> width, v -> height);
		j++;
	}

	// cursor
	for(i = 0; i < CURSOR_COUNT; i++)
	{
		UI_MakeCursor(v -> vb + j, VKB_Cursor + i, v -> width, v -> height);
		j++;
	}

	// swipe
	for(i = 0; i < SWIPE_COUNT; i++)
	{
		UI_MakeSwipe(v -> vb + j, VKB_Swipe + i, v -> width, v -> height);
		j++;
	}

	return v;
}

void delete_vkb(vkb *v)
{
	if(!v)
		return;
	int count = TOTAL_VKB_COUNT;
	int i;
	for(i = 0; i < count; i++)
	{
		int j;
		for(j = vertex_buffer_type; j < total_buffer_type; j++)
		{
			if(glIsBuffer(v -> vb[i].base.buffers[j]))
				glDeleteBuffers(1, v -> vb[i].base.buffers + j);
			v -> vb[i].base.buffers[j] = 0;
		}
	}
	for(i = 0; i < VKB_TEX_COUNT; i++)
	{
		if(v -> tex[i])
		{
			if(glIsTexture(v -> tex[i] -> texid))
				glDeleteTextures(1, &v -> tex[i] -> texid);
			FREE_PTR(v -> tex[i])
		}
	}
}

void UI_RenderVKB(const vkb *v)
{
	if(!v)
		return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	int i;
	int count = TOTAL_VKB_COUNT;
	for(i = 0; i < count; i++)
	{
		const virtual_control_item *b = v -> vb + i;
		switch(b -> type)
		{
			case vkb_button_type:
				UI_RenderVKBButton(&b -> button, v -> tex);
				break;
			case vkb_joystick_type:
				UI_RenderVKBJoystick(&b -> joystick, v -> tex);
				break;
			case vkb_swipe_type:
				UI_RenderVKBSwipe(&b -> swipe, v -> tex);
				break;
			case vkb_cursor_type:
				UI_RenderVKBCursor(&b -> cursor, v -> tex);
				break;
			default:
				continue;
		}
		//#define RENDER_CI_RANGE
#ifdef RENDER_CI_RANGE
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		GLfloat vv[] = {
			(b -> cursor.base.x), (b -> cursor.base.y),
			(b -> cursor.base.x + b -> cursor.base.width), (b -> cursor.base.y),
			(b -> cursor.base.x), (b -> cursor.base.y + b -> cursor.base.height),
			(b -> cursor.base.x + b -> cursor.base.width), (b -> cursor.base.y + b -> cursor.base.height),

			(b -> cursor.base.e_min_x), (b -> cursor.base.e_min_y),
			(b -> cursor.base.e_max_x), (b -> cursor.base.e_min_y),
			(b -> cursor.base.e_min_x), (b -> cursor.base.e_max_y),
			(b -> cursor.base.e_max_x), (b -> cursor.base.e_max_y),
		};
		oglBindTexture(GL_TEXTURE_2D, 0);
		glVertexPointer(2, GL_FLOAT, 0, vv);
		glColor4f(1,0,0,0.5);
		oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glColor4f(0,1,0,0.2);
		oglDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
		glColor4f(1,1,1,1);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
#endif
	}
	oglBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

//void UI_ResizeVKB(const vkb *v, GLfloat w, GLfloat h);
int UI_VKBMouseMotionEvent(vkb *v, int b, int p, int x, int y, int dx, int dy, VKB_Key_Action_Function f)
{
	if(!v)
		return 0;
	if(!p)
		return 0;
	int nres = 0;
	int last_x = x - dx;
	int last_y = y - dy;
	int last_nz = INT_MIN;
	int clicked[TOTAL_VKB_COUNT];
	mouse_motion_button_status status[TOTAL_VKB_COUNT];
	int count = UI_GetControlItemOnPosition2(v, x, y, last_x, last_y, clicked, status);
	if(count > 0)
	{
		int i;
		for(i = 0; i < count; i++)
		{
			virtual_control_item *b = v -> vb + clicked[i];
			mouse_motion_button_status s = status[i];
			// normal button
			//printf("%d  %d %d\n", i, b->type, b->base.z);
			if(b -> type == vkb_button_type)
			{
				/*
					 if(s == last_out_now_in_range_status)
					 {
					 if(nres && b -> button.base.z < last_nz)
					 break;
					 last_nz = b -> button.base.z;
					 b -> base.pressed = GL_TRUE;
					 if(f)
					 f(b -> button.key, b -> button.action, b -> button.base.pressed);
					 nres = 1;
					 }
					 else 
					 */
				if(s == last_in_now_out_range_status)
				{
					b -> button.base.pressed = GL_FALSE;
					if(f)
						f(b -> button.key, b -> button.action, GL_FALSE);
				}
				else if(s == all_in_range_status)
				{
					if(nres && b -> button.base.z < last_nz)
						break;
					last_nz = b -> button.base.z;
					nres = 1;
				}
			}

			// joystick
			else if(b -> type == vkb_joystick_type)
			{
				if(s == last_out_now_in_range_status)
				{
					if(nres && b -> joystick.base.z < last_nz)
						break;
					last_nz = b -> joystick.base.z;
					b -> joystick.base.pressed = GL_TRUE;
					GLfloat cx = b -> joystick.base.x + b -> joystick.base.width / 2;
					GLfloat cy = b -> joystick.base.y + b -> joystick.base.height / 2;
					circle_direction d = UI_GetJoystickDirection(x, y, cx, cy, b -> joystick.e_ignore_radius, b -> joystick.e_radius, &b -> joystick.angle, &b -> joystick.percent);
					if(d != circle_outside)
					{
						b -> joystick.pos_x = x - cx;
						b -> joystick.pos_y = y - cy;
					}
					else
					{
						b -> joystick.pos_x = 0;
						b -> joystick.pos_y = 0;
					}
					if(f)
					{
						switch(d)
						{
							case circle_top_direction:
								f(b -> joystick.keys[0], b -> joystick.actions[0], GL_TRUE);
								break;
							case circle_bottom_direction:
								f(b -> joystick.keys[1], b -> joystick.actions[1], GL_TRUE);
								break;
							case circle_right_direction:
								f(b -> joystick.keys[3], b -> joystick.actions[3], GL_TRUE);
								break;
							case circle_left_direction:
								f(b -> joystick.keys[2], b -> joystick.actions[2], GL_TRUE);
								break;
							case circle_lefttop_direction:
								f(b -> joystick.keys[0], b -> joystick.actions[0], GL_TRUE);
								f(b -> joystick.keys[2], b -> joystick.actions[2], GL_TRUE);
								break;
							case circle_leftbottom_direction:
								f(b -> joystick.keys[1], b -> joystick.actions[1], GL_TRUE);
								f(b -> joystick.keys[2], b -> joystick.actions[2], GL_TRUE);
								break;
							case circle_righttop_direction:
								f(b -> joystick.keys[0], b -> joystick.actions[0], GL_TRUE);
								f(b -> joystick.keys[3], b -> joystick.actions[3], GL_TRUE);
								break;
							case circle_rightbottom_direction:
								f(b -> joystick.keys[1], b -> joystick.actions[1], GL_TRUE);
								f(b -> joystick.keys[3], b -> joystick.actions[3], GL_TRUE);
								break;
							default:
								break;
						}
					}
					nres = 1;
				}
				else if(s == last_in_now_out_range_status)
				{
					b -> joystick.base.pressed = GL_FALSE;
					if(f)
					{
						GLfloat cx = b -> joystick.base.x + b -> joystick.base.width / 2;
						GLfloat cy = b -> joystick.base.y + b -> joystick.base.height / 2;
						circle_direction d = UI_GetJoystickDirection(last_x, last_y, cx, cy, b -> joystick.e_ignore_radius, b -> joystick.e_radius, NULL, NULL);
						switch(d)
						{
							case circle_top_direction:
								f(b -> joystick.keys[0], b -> joystick.actions[0], GL_FALSE);
								break;
							case circle_bottom_direction:
								f(b -> joystick.keys[1], b -> joystick.actions[1], GL_FALSE);
								break;
							case circle_right_direction:
								f(b -> joystick.keys[3], b -> joystick.actions[3], GL_FALSE);
								break;
							case circle_left_direction:
								f(b -> joystick.keys[2], b -> joystick.actions[2], GL_FALSE);
								break;
							case circle_lefttop_direction:
								f(b -> joystick.keys[0], b -> joystick.actions[0], GL_FALSE);
								f(b -> joystick.keys[2], b -> joystick.actions[2], GL_FALSE);
								break;
							case circle_leftbottom_direction:
								f(b -> joystick.keys[1], b -> joystick.actions[1], GL_FALSE);
								f(b -> joystick.keys[2], b -> joystick.actions[2], GL_FALSE);
								break;
							case circle_righttop_direction:
								f(b -> joystick.keys[0], b -> joystick.actions[0], GL_FALSE);
								f(b -> joystick.keys[3], b -> joystick.actions[3], GL_FALSE);
								break;
							case circle_rightbottom_direction:
								f(b -> joystick.keys[1], b -> joystick.actions[1], GL_FALSE);
								f(b -> joystick.keys[3], b -> joystick.actions[3], GL_FALSE);
								break;
							default:
								break;
						}
					}
					b -> joystick.angle = -1.0f;
					b -> joystick.percent = 0.0f;
					b -> joystick.pos_x = 0.0f;
					b -> joystick.pos_y = 0.0f;
				}
				else if(s == all_in_range_status)
				{
					if(nres && b -> joystick.base.z < last_nz)
					{
						b -> joystick.base.pressed = GL_FALSE;
						if(f)
						{
							GLfloat cx = b -> joystick.base.x + b -> joystick.base.width / 2;
							GLfloat cy = b -> joystick.base.y + b -> joystick.base.height / 2;
							circle_direction d = UI_GetJoystickDirection(last_x, last_y, cx, cy, b -> joystick.e_ignore_radius, b -> joystick.e_radius, NULL, NULL);
							switch(d)
							{
								case circle_top_direction:
									f(b -> joystick.keys[0], b -> joystick.actions[0], GL_FALSE);
									break;
								case circle_bottom_direction:
									f(b -> joystick.keys[1], b -> joystick.actions[1], GL_FALSE);
									break;
								case circle_right_direction:
									f(b -> joystick.keys[3], b -> joystick.actions[3], GL_FALSE);
									break;
								case circle_left_direction:
									f(b -> joystick.keys[2], b -> joystick.actions[2], GL_FALSE);
									break;
								case circle_lefttop_direction:
									f(b -> joystick.keys[0], b -> joystick.actions[0], GL_FALSE);
									f(b -> joystick.keys[2], b -> joystick.actions[2], GL_FALSE);
									break;
								case circle_leftbottom_direction:
									f(b -> joystick.keys[1], b -> joystick.actions[1], GL_FALSE);
									f(b -> joystick.keys[2], b -> joystick.actions[2], GL_FALSE);
									break;
								case circle_righttop_direction:
									f(b -> joystick.keys[0], b -> joystick.actions[0], GL_FALSE);
									f(b -> joystick.keys[3], b -> joystick.actions[3], GL_FALSE);
									break;
								case circle_rightbottom_direction:
									f(b -> joystick.keys[1], b -> joystick.actions[1], GL_FALSE);
									f(b -> joystick.keys[3], b -> joystick.actions[3], GL_FALSE);
									break;
								default:
									break;
							}
						}
						b -> joystick.angle = -1.0f;
						b -> joystick.percent = 0.0f;
						b -> joystick.pos_x = 0.0f;
						b -> joystick.pos_y = 0.0f;
					}
					else
					{
						last_nz = b -> joystick.base.z;
						GLfloat cx = b -> joystick.base.x + b -> joystick.base.width / 2;
						GLfloat cy = b -> joystick.base.y + b -> joystick.base.height / 2;
						circle_direction ld = UI_GetJoystickDirection(last_x, last_y, cx, cy, b -> joystick.e_ignore_radius, b -> joystick.e_radius, NULL, NULL);
						circle_direction d = UI_GetJoystickDirection(x, y, cx, cy, b -> joystick.e_ignore_radius, b -> joystick.e_radius, &b -> joystick.angle, &b -> joystick.percent);
						if(d != ld)
						{
							if(f)
							{
								GLint mask[4] = {0, 0, 0, 0};
								switch(ld)
								{
									case circle_top_direction:
										mask[0] -= 1;
										break;
									case circle_bottom_direction:
										mask[1] -= 1;
										break;
									case circle_right_direction:
										mask[3] -= 1;
										break;
									case circle_left_direction:
										mask[2] -= 1;
										break;
									case circle_lefttop_direction:
										mask[0] -= 1;
										mask[2] -= 1;
										break;
									case circle_leftbottom_direction:
										mask[1] -= 1;
										mask[2] -= 1;
										break;
									case circle_righttop_direction:
										mask[0] -= 1;
										mask[3] -= 1;
										break;
									case circle_rightbottom_direction:
										mask[1] -= 1;
										mask[3] -= 1;
										break;
									default:
										break;
								}
								switch(d)
								{
									case circle_top_direction:
										mask[0] += 1;
										break;
									case circle_bottom_direction:
										mask[1] += 1;
										break;
									case circle_right_direction:
										mask[3] += 1;
										break;
									case circle_left_direction:
										mask[2] += 1;
										break;
									case circle_lefttop_direction:
										mask[0] += 1;
										mask[2] += 1;
										break;
									case circle_leftbottom_direction:
										mask[1] += 1;
										mask[2] += 1;
										break;
									case circle_righttop_direction:
										mask[0] += 1;
										mask[3] += 1;
										break;
									case circle_rightbottom_direction:
										mask[1] += 1;
										mask[3] += 1;
										break;
									default:
										break;
								}
								if(mask[0] != 0)
								{
									f(b -> joystick.keys[0], b -> joystick.actions[0], mask[0] > 0 ? GL_TRUE : GL_FALSE);
								}
								if(mask[1] != 0)
								{
									f(b -> joystick.keys[1], b -> joystick.actions[1], mask[1] > 0 ? GL_TRUE : GL_FALSE);
								}
								if(mask[2] != 0)
								{
									f(b -> joystick.keys[2], b -> joystick.actions[2], mask[2] > 0 ? GL_TRUE : GL_FALSE);
								}
								if(mask[3] != 0)
								{
									f(b -> joystick.keys[3], b -> joystick.actions[3], mask[3] > 0 ? GL_TRUE : GL_FALSE);
								}
							}
						}
						if(d != circle_outside)
						{
							b -> joystick.pos_x = x - cx;
							b -> joystick.pos_y = y - cy;
						}
						else
						{
							b -> joystick.pos_x = 0;
							b -> joystick.pos_y = 0;
						}
						nres = 1;
					}
				}
			}

			// swipe
			else if(b -> type == vkb_swipe_type)
			{
				if(s == last_out_now_in_range_status)
				{
					if(nres && b -> swipe.base.z < last_nz)
						break;
					last_nz = b -> swipe.base.z;
					b -> swipe.base.pressed = GL_TRUE;
					b -> swipe.distance = 0.0f;
					b -> swipe.angle = -1.0f;
					nres = 1;
				}
				else if(s == last_in_now_out_range_status)
				{
					b -> swipe.base.pressed = GL_FALSE;
					if(b -> swipe.mask[0] > 0)
					{
						if(f)
							f(b -> swipe.keys[0], b -> swipe.actions[0], GL_FALSE);
						b -> swipe.mask[0] = 0;
					}
					if(b -> swipe.mask[1] > 0)
					{
						if(f)
							f(b -> swipe.keys[1], b -> swipe.actions[1], GL_FALSE);
						b -> swipe.mask[1] = 0;
					}
					if(b -> swipe.mask[2] > 0)
					{
						if(f)
							f(b -> swipe.keys[2], b -> swipe.actions[2], GL_FALSE);
						b -> swipe.mask[2] = 0;
					}
					if(b -> swipe.mask[3] > 0)
					{
						if(f)
							f(b -> swipe.keys[3], b -> swipe.actions[3], GL_FALSE);
						b -> swipe.mask[3] = 0;
					}
					b -> swipe.distance = 0.0f;
					b -> swipe.angle = -1.0f;
				}
				else if(s == all_in_range_status)
				{
					if(nres && b -> swipe.base.z < last_nz)
					{
						b -> swipe.base.pressed = GL_FALSE;
						if(b -> swipe.mask[0] > 0)
						{
							if(f)
								f(b -> swipe.keys[0], b -> swipe.actions[0], GL_FALSE);
							b -> swipe.mask[0] = 0;
						}
						if(b -> swipe.mask[1] > 0)
						{
							if(f)
								f(b -> swipe.keys[1], b -> swipe.actions[1], GL_FALSE);
							b -> swipe.mask[1] = 0;
						}
						if(b -> swipe.mask[2] > 0)
						{
							if(f)
								f(b -> swipe.keys[2], b -> swipe.actions[2], GL_FALSE);
							b -> swipe.mask[2] = 0;
						}
						if(b -> swipe.mask[3] > 0)
						{
							if(f)
								f(b -> swipe.keys[3], b -> swipe.actions[3], GL_FALSE);
							b -> swipe.mask[3] = 0;
						}
						b -> swipe.distance = 0.0f;
						b -> swipe.angle = -1.0f;
					}
					else
					{
						last_nz = b -> swipe.base.z;
						b -> swipe.base.pressed = GL_TRUE;
						circle_direction d = UI_GetSwipeDirection(dx, dy, &b -> swipe.angle, &b -> swipe.distance);
						if(d != circle_center)
						{
							if(b -> swipe.distance < b -> swipe.ignore_distance)
								d = circle_center;
						}
						if(f)
						{
							GLuint mask[4] = {0, 0, 0, 0};
							switch(d)
							{
								case circle_top_direction:
									mask[0] += 1;
									break;
								case circle_bottom_direction:
									mask[1] += 1;
									break;
								case circle_right_direction:
									mask[3] += 1;
									break;
								case circle_left_direction:
									mask[2] += 1;
									break;
								case circle_lefttop_direction:
									mask[0] += 1;
									mask[2] += 1;
									break;
								case circle_leftbottom_direction:
									mask[1] += 1;
									mask[2] += 1;
									break;
								case circle_righttop_direction:
									mask[0] += 1;
									mask[3] += 1;
									break;
								case circle_rightbottom_direction:
									mask[1] += 1;
									mask[3] += 1;
									break;
								default:
									break;
							}
							if(b -> swipe.mask[0] != 0 || mask[0] != 0)
							{
								f(b -> swipe.keys[0], b -> swipe.actions[0], mask[0] >= b -> swipe.mask[0] ? GL_TRUE : GL_FALSE);
								b -> swipe.mask[0] = mask[0];
								nres = 1;
							}
							if(b -> swipe.mask[1] != 0 || mask[1] != 0)
							{
								f(b -> swipe.keys[1], b -> swipe.actions[1], mask[1] >= b -> swipe.mask[1] ? GL_TRUE : GL_FALSE);
								b -> swipe.mask[1] = mask[1];
								nres = 1;
							}
							if(b -> swipe.mask[2] != 0 || mask[2] != 0)
							{
								f(b -> swipe.keys[2], b -> swipe.actions[2], mask[2] >= b -> swipe.mask[2] ? GL_TRUE : GL_FALSE);
								b -> swipe.mask[2] = mask[2];
								nres = 1;
							}
							if(b -> swipe.mask[3] != 0 || mask[3] != 0)
							{
								f(b -> swipe.keys[3], b -> swipe.actions[3], mask[3] >= b -> swipe.mask[3] ? GL_TRUE : GL_FALSE);
								b -> swipe.mask[3] = mask[3];
								nres = 1;
							}
						}
					}
				}
			}

			// cursor
			else if(b -> type == vkb_cursor_type)
			{
				if(s == last_in_now_out_range_status)
				{
					b -> cursor.base.pressed = GL_FALSE;
					if(f)
						f(b -> cursor.key, b -> cursor.action, GL_FALSE);
					if(b -> cursor.mask[0] > 0)
					{
						if(f)
							f(b -> cursor.keys[0], b -> cursor.actions[0], GL_FALSE);
						b -> cursor.mask[0] = 0;
					}
					if(b -> cursor.mask[1] > 0)
					{
						if(f)
							f(b -> cursor.keys[1], b -> cursor.actions[1], GL_FALSE);
						b -> cursor.mask[1] = 0;
					}
					if(b -> cursor.mask[2] > 0)
					{
						if(f)
							f(b -> cursor.keys[2], b -> cursor.actions[2], GL_FALSE);
						b -> cursor.mask[2] = 0;
					}
					if(b -> cursor.mask[3] > 0)
					{
						if(f)
							f(b -> cursor.keys[3], b -> cursor.actions[3], GL_FALSE);
						b -> cursor.mask[3] = 0;
					}
					b -> cursor.distance = 0.0f;
					b -> cursor.angle = -1.0f;
					b -> cursor.pos_x = 0;
					b -> cursor.pos_y = 0;
				}
				else if(s == all_in_range_status)
				{
					if(nres && b -> cursor.base.z < last_nz)
					{
						if(b -> cursor.mask[0] > 0)
						{
							if(f)
								f(b -> cursor.keys[0], b -> cursor.actions[0], GL_FALSE);
							b -> cursor.mask[0] = 0;
						}
						if(b -> cursor.mask[1] > 0)
						{
							if(f)
								f(b -> cursor.keys[1], b -> cursor.actions[1], GL_FALSE);
							b -> cursor.mask[1] = 0;
						}
						if(b -> cursor.mask[2] > 0)
						{
							if(f)
								f(b -> cursor.keys[2], b -> cursor.actions[2], GL_FALSE);
							b -> cursor.mask[2] = 0;
						}
						if(b -> cursor.mask[3] > 0)
						{
							if(f)
								f(b -> cursor.keys[3], b -> cursor.actions[3], GL_FALSE);
							b -> cursor.mask[3] = 0;
						}
						b -> cursor.distance = 0.0f;
						b -> cursor.angle = -1.0f;
						b -> cursor.pos_x = 0;
						b -> cursor.pos_y = 0;
						b -> cursor.base.pressed = GL_FALSE;
						if(f)
							f(b -> cursor.key, b -> cursor.action, GL_FALSE);
					}
					else
					{
						if(b -> cursor.base.pressed)
						{
							last_nz = b -> cursor.base.z;
							circle_direction d = UI_GetSwipeDirection(dx, dy, &b -> cursor.angle, &b -> cursor.distance);
							if(d != circle_center)
							{
								if(b -> cursor.distance < b -> cursor.ignore_distance)
									d = circle_center;
							}
							if(f)
							{
								GLuint mask[4] = {0, 0, 0, 0};
								switch(d)
								{
									case circle_top_direction:
										mask[0] += 1;
										break;
									case circle_bottom_direction:
										mask[1] += 1;
										break;
									case circle_right_direction:
										mask[3] += 1;
										break;
									case circle_left_direction:
										mask[2] += 1;
										break;
									case circle_lefttop_direction:
										mask[0] += 1;
										mask[2] += 1;
										break;
									case circle_leftbottom_direction:
										mask[1] += 1;
										mask[2] += 1;
										break;
									case circle_righttop_direction:
										mask[0] += 1;
										mask[3] += 1;
										break;
									case circle_rightbottom_direction:
										mask[1] += 1;
										mask[3] += 1;
										break;
									default:
										break;
								}
								if(b -> cursor.mask[0] != 0 || mask[0] != 0)
								{
									if(f)
										f(b -> cursor.keys[0], b -> cursor.actions[0], mask[0] >= b -> cursor.mask[0] ? GL_TRUE : GL_FALSE);
									b -> cursor.mask[0] = mask[0];
									nres = 1;
								}
								if(b -> cursor.mask[1] != 0 || mask[1] != 0)
								{
									if(f)
										f(b -> cursor.keys[1], b -> cursor.actions[1], mask[1] >= b -> cursor.mask[1] ? GL_TRUE : GL_FALSE);
									b -> cursor.mask[1] = mask[1];
									nres = 1;
								}
								if(b -> cursor.mask[2] != 0 || mask[2] != 0)
								{
									if(f)
										f(b -> cursor.keys[2], b -> cursor.actions[2], mask[2] >= b -> cursor.mask[2] ? GL_TRUE : GL_FALSE);
									b -> cursor.mask[2] = mask[2];
									nres = 1;
								}
								if(b -> cursor.mask[3] != 0 || mask[3] != 0)
								{
									if(f)
										f(b -> cursor.keys[3], b -> cursor.actions[3], mask[3] >= b -> cursor.mask[3] ? GL_TRUE : GL_FALSE);
									b -> cursor.mask[3] = mask[3];
									nres = 1;
								}
							}
							GLfloat cx = b -> cursor.base.x + b -> cursor.base.width / 2;
							GLfloat cy = b -> cursor.base.y + b -> cursor.base.height / 2;
							b -> cursor.pos_x = x - cx;
							b -> cursor.pos_y = y - cy;
						}
					}
				}
			}
		}
		if(nres)
			return 1;
	}
	return 0;
}

int UI_VKBMouseEvent(vkb *v, int b, int p, int x, int y, VKB_Key_Action_Function f)
{
	if(!v)
		return 0;
	int last_z = INT_MIN;
	int res = 0;
	int clicked[TOTAL_VKB_COUNT];
	int count = UI_GetControlItemOnPosition(v, x, y, clicked);
	if(count > 0)
	{
		int i;
		for(i = 0; i < count; i++)
		{
			virtual_control_item *b = v -> vb + clicked[i];
			if(b -> type == vkb_joystick_type)
			{
				GLboolean pr = GL_FALSE;
				if(res && b -> base.z < last_z)
				{
					pr = GL_FALSE;
				}
				else
				{
					pr = p ? GL_TRUE : GL_FALSE;
					last_z = b -> base.z;
					res = 1;
				}
				b -> joystick.base.pressed = pr;
				GLfloat cx = b -> joystick.base.x + b -> joystick.base.width / 2;
				GLfloat cy = b -> joystick.base.y + b -> joystick.base.width / 2;
				circle_direction d = UI_GetJoystickDirection(x, y, cx, cy, b -> joystick.e_ignore_radius, b -> joystick.e_radius, &b -> joystick.angle, &b -> joystick.percent);
				if(f)
				{
					switch(d)
					{
						case circle_top_direction:
							f(b -> joystick.keys[0], b -> joystick.actions[0], b -> joystick.base.pressed);
							break;
						case circle_bottom_direction:
							f(b -> joystick.keys[1], b -> joystick.actions[1], b -> joystick.base.pressed);
							break;
						case circle_right_direction:
							f(b -> joystick.keys[3], b -> joystick.actions[3], b -> joystick.base.pressed);
							break;
						case circle_left_direction:
							f(b -> joystick.keys[2], b -> joystick.actions[2], b -> joystick.base.pressed);
							break;
						case circle_lefttop_direction:
							f(b -> joystick.keys[0], b -> joystick.actions[0], b -> joystick.base.pressed);
							f(b -> joystick.keys[2], b -> joystick.actions[2], b -> joystick.base.pressed);
							break;
						case circle_leftbottom_direction:
							f(b -> joystick.keys[1], b -> joystick.actions[1], b -> joystick.base.pressed);
							f(b -> joystick.keys[2], b -> joystick.actions[2], b -> joystick.base.pressed);
							break;
						case circle_righttop_direction:
							f(b -> joystick.keys[0], b -> joystick.actions[0], b -> joystick.base.pressed);
							f(b -> joystick.keys[3], b -> joystick.actions[3], b -> joystick.base.pressed);
							break;
						case circle_rightbottom_direction:
							f(b -> joystick.keys[1], b -> joystick.actions[1], b -> joystick.base.pressed);
							f(b -> joystick.keys[3], b -> joystick.actions[3], b -> joystick.base.pressed);
							break;
						default:
							break;
					}
				}
				if(!pr)
				{
					b -> joystick.angle = -1.0f;
					b -> joystick.percent = 0.0f;
					b -> joystick.pos_x = 0.0f;
					b -> joystick.pos_y = 0.0f;
				}
				else
				{
					if(d != circle_outside)
					{
						b -> joystick.pos_x = x - cx;
						b -> joystick.pos_y = y - cy;
					}
					else
					{
						b -> joystick.pos_x = 0;
						b -> joystick.pos_y = 0;
					}
				}
			}
			else if(b -> type == vkb_button_type)
			{
				GLboolean pr = GL_FALSE;
				if(res && b -> base.z < last_z)
				{
					pr = GL_FALSE;
				}
				else
				{
					pr = p ? GL_TRUE : GL_FALSE;
					last_z = b -> base.z;
					res = 1;
				}
				b -> button.base.pressed = pr;
				if(f)
					f(b -> button.key, b -> button.action, b -> button.base.pressed);
			}
			else if(b -> type == vkb_swipe_type)
			{
				if(!p)
				{
					GLboolean pr = GL_FALSE;
					res = 1;
					b -> swipe.base.pressed = pr;
					if(b -> swipe.mask[0] > 0)
					{
						if(f)
							f(b -> swipe.keys[0], b -> swipe.actions[0], GL_FALSE);
						b -> swipe.mask[0] = 0;
					}
					if(b -> swipe.mask[1] > 0)
					{
						if(f)
							f(b -> swipe.keys[1], b -> swipe.actions[1], GL_FALSE);
						b -> swipe.mask[1] = 0;
					}
					if(b -> swipe.mask[2] > 0)
					{
						if(f)
							f(b -> swipe.keys[2], b -> swipe.actions[2], GL_FALSE);
						b -> swipe.mask[2] = 0;
					}
					if(b -> swipe.mask[3] > 0)
					{
						if(f)
							f(b -> swipe.keys[3], b -> swipe.actions[3], GL_FALSE);
						b -> swipe.mask[3] = 0;
					}
					b -> swipe.distance = 0.0f;
					b -> swipe.angle = -1.0f;
				}
			}
			else if(b -> type == vkb_cursor_type)
			{
				GLboolean pr = GL_FALSE;
				if(res && b -> base.z < last_z)
				{
					pr = GL_FALSE;
				}
				else
				{
					pr = p ? GL_TRUE : GL_FALSE;
				}
				GLfloat cx = b -> cursor.base.x + b -> cursor.base.width / 2;
				GLfloat cy = b -> cursor.base.y + b -> cursor.base.height / 2;
				circle_direction d = UI_GetJoystickDirection(x, y, cx, cy, 0, b -> cursor.e_radius, NULL, NULL);
				if(!pr)
				{
					if(b -> cursor.mask[0] > 0)
					{
						if(f)
							f(b -> cursor.keys[0], b -> cursor.actions[0], GL_FALSE);
						b -> cursor.mask[0] = 0;
					}
					if(b -> cursor.mask[1] > 0)
					{
						if(f)
							f(b -> cursor.keys[1], b -> cursor.actions[1], GL_FALSE);
						b -> cursor.mask[1] = 0;
					}
					if(b -> cursor.mask[2] > 0)
					{
						if(f)
							f(b -> cursor.keys[2], b -> cursor.actions[2], GL_FALSE);
						b -> cursor.mask[2] = 0;
					}
					if(b -> cursor.mask[3] > 0)
					{
						if(f)
							f(b -> cursor.keys[3], b -> cursor.actions[3], GL_FALSE);
						b -> cursor.mask[3] = 0;
					}
					b -> cursor.distance = 0.0f;
					b -> cursor.angle = -1.0f;
					b -> cursor.pos_x = 0.0f;
					b -> cursor.pos_y = 0.0f;
					b -> cursor.base.pressed = GL_FALSE;
					if(f)
						f(b -> cursor.key, b -> cursor.action, GL_FALSE);
				}
				else
				{
					if(d != circle_outside)
					{
						b -> cursor.base.pressed = GL_TRUE;
						last_z = b -> base.z;
						res = 1;
						if(f)
							f(b -> cursor.key, b -> cursor.action, GL_TRUE);
						b -> cursor.distance = 0.0f;
						b -> cursor.angle = -1.0f;
						b -> cursor.pos_x = x - cx;
						b -> cursor.pos_y = y - cy;
					}
				}
			}
		}
	}
	return res;
}

mouse_motion_button_status UI_ButtonMouseMotion(const virtual_control_item *b, int nx, int ny, int lx, int ly)
{
	if(!b)
		return all_out_range_status;
	int	l = MOUSE_IN_RANGE(b -> base, lx, ly) ? 1 : 0;
	int	n = MOUSE_IN_RANGE(b -> base, nx, ny) ? 1 : 0;
	mouse_motion_button_status s = all_out_range_status;
	if(l)
		s |= last_in_now_out_range_status;
	if(n)
		s |= last_out_now_in_range_status;
	return s;
}

circle_direction UI_GetJoystickDirection(int x, int y, GLfloat cx, GLfloat cy, GLfloat ir, GLfloat or, float *angle, float *percent)
{
	int oh = or / 2;
	int ih = ir / 2;
	int xl = x - cx;
	int yl = y - cy;
	int xls = xl >= 0 ? xl : -xl;
	int yls = yl >= 0 ? yl : -yl;
	if(xls > oh || yls > oh)
	{
		if(angle)
			*angle = -1.0f;
		if(percent)
			*percent = 0.0f;
		return circle_outside;
	}
	else if(xls < ih && yls < ih)
	{
		if(angle)
			*angle = -1.0f;
		if(percent)
			*percent = 0.0f;
		return circle_center;
	}

	double a = (double)(xl);
	double b = (double)(yl);
	//float ra = Algo_FormatAngle(atan2(xl, yl) * (180.0 / M_PI));
	float rb = Algo_FormatAngle(atan2(b, a) * (180.0 / M_PI));
	if(angle)
		*angle = rb;
	if(percent)
	{
		double c = sqrt(a * a + b * b);
		*percent = (float)c / oh;
	}
	//printf("%f - %f\n", ra, rb);
	if(rb >= 60 && rb <= 120)
		return circle_top_direction;
	else if((rb >= 0 && rb <= 30) || (rb >= 330 && rb <= 360))
		return circle_right_direction;
	else if(rb >= 240 && rb <= 300)
		return circle_bottom_direction;
	else if(rb >= 150 && rb <= 210)
		return circle_left_direction;

	else if(rb > 30 && rb < 60)
		return circle_righttop_direction;
	else if(rb > 300 && rb < 330)
		return circle_rightbottom_direction;
	else if(rb > 210 && rb < 240)
		return circle_leftbottom_direction;
	else
		return circle_lefttop_direction;
}

circle_direction UI_GetSwipeDirection(int dx, int dy, float *angle, float *distance)
{
	if(dx == 0 && dy == 0)
	{
		if(distance)
			*distance = 0.0f;
		if(*angle)
			*angle = -1.0f;
		return circle_center;
	}
	double a = (double)(dx);
	double b = (double)(dy);
	double c = sqrt(a * a + b * b);
	if(distance)
		*distance = (float)c;
	//float ra = Algo_FormatAngle(atan2(xl, yl) * (180.0 / M_PI));
	float rb = Algo_FormatAngle(atan2(b, a) * (180.0 / M_PI));
	if(*angle)
		*angle = rb;
	//printf("%f - %f\n", ra, rb);
	if(rb >= 60 && rb <= 120)
		return circle_top_direction;
	else if((rb >= 0 && rb <= 30) || (rb >= 330 && rb <= 360))
		return circle_right_direction;
	else if(rb >= 240 && rb <= 300)
		return circle_bottom_direction;
	else if(rb >= 150 && rb <= 210)
		return circle_left_direction;

	else if(rb > 30 && rb < 60)
		return circle_righttop_direction;
	else if(rb > 300 && rb < 330)
		return circle_rightbottom_direction;
	else if(rb > 210 && rb < 240)
		return circle_leftbottom_direction;
	else
		return circle_lefttop_direction;
}

#define GET_JOY_XY(r, v, s, w, b) \
	switch(b) \
{ \
	case opengl_mf_base : \
	case opengl_s_base : \
											 r = v + (1.0 - s) * w / 2.0; \
	break; \
	case opengl_mb_base : \
	case opengl_e_base : \
											 r = v - (1.0 - s) * w / 2.0; \
	break; \
	default : \
						r = v; \
	break; \
}

#define GET_VB_XY(r, t, v, b) \
	switch(b) \
{ \
	case opengl_mf_base : \
												r = t / 2 + v; \
	break; \
	case opengl_mb_base : \
												r = t / 2 - v; \
	break; \
	case opengl_e_base : \
											 r = t - v; \
	break; \
	case opengl_s_base : \
	default : \
						r = v; \
	break; \
}

#define GET_TEX_S(t, v, w) (GLfloat)(v + w) / (GLfloat)t
#define GET_TEX_T(t, v, h) (GLfloat)(v - h) / (GLfloat)t

void UI_MakeCursor(virtual_control_item *b, struct vkb_cursor *d, unsigned int width, unsigned int height)
{
	if(!b || !d)
		return;
	b -> cursor.base.type = vkb_cursor_type;
	b -> cursor.base.pressed = GL_FALSE;
	b -> cursor.base.enabled = d -> ava;
	b -> cursor.base.tex_index = d -> tex_index;
	b -> cursor.base.z = d -> z;
	b -> cursor.ignore_distance = 1.5f;
	b -> cursor.angle = -1.0f;
	b -> cursor.distance = 0.0f;
	b -> cursor.render_bg = d -> render;
	b -> cursor.pos_x = 0.0f;
	b -> cursor.pos_y = 0.0f;
	b -> cursor.base.visible = d -> ava;
	b -> cursor.actions[0] = d -> action0;
	b -> cursor.actions[1] = d -> action1;
	b -> cursor.actions[2] = d -> action2;
	b -> cursor.actions[3] = d -> action3;
	b -> cursor.action = d -> action;
	b -> cursor.keys[0] = Harmattan_Other_Key;
	b -> cursor.keys[1] = Harmattan_Other_Key;
	b -> cursor.keys[2] = Harmattan_Other_Key;
	b -> cursor.keys[3] = Harmattan_Other_Key;
	b -> cursor.key = Harmattan_Other_Key;
	if(!b -> cursor.base.enabled)
	{
		b -> cursor.actions[0] = Total_Action;
		b -> cursor.actions[1] = Total_Action;
		b -> cursor.actions[2] = Total_Action;
		b -> cursor.actions[3] = Total_Action;
		b -> cursor.action = Total_Action;
		return;
	}

	GET_VB_XY(b -> cursor.base.x, width, d -> x, d -> x_base)
		GET_VB_XY(b -> cursor.base.y, height, d -> y, d -> y_base)
		b -> cursor.base.width = d -> r;
	b -> cursor.base.height = d -> r;
	b -> cursor.e_radius = d -> r * d -> eminr;
	GLfloat ex;
	GLfloat ey;
	GET_JOY_XY(ex, d -> x, d -> emaxr, d -> r, d -> x_base)
		GET_JOY_XY(ey, d -> y, d -> emaxr, d -> r, d -> y_base)
		GET_VB_XY(b -> cursor.base.e_min_x, width, ex, d -> x_base)
		GET_VB_XY(b -> cursor.base.e_min_y, height, ey, d -> y_base)
		b -> cursor.base.e_max_x = b -> cursor.base.e_min_x + d -> r * d -> emaxr;
	b -> cursor.base.e_max_y = b -> cursor.base.e_min_y + d -> r * d -> emaxr;

	GLfloat jw = b -> cursor.base.width * d -> joy_r / 2.0;
	GLfloat jh = b -> cursor.base.height * d -> joy_r / 2.0;
	GLfloat vertex[] = {
		// joy
		-jw, -jh,
		jw, -jh,
		-jw, jh,
		jw, jh,
		// bg
		b -> cursor.base.x, b -> cursor.base.y,
		b -> cursor.base.x + b -> cursor.base.width, b -> cursor.base.y,
		b -> cursor.base.x, b -> cursor.base.y + b -> cursor.base.height,
		b -> cursor.base.x + b -> cursor.base.width, b -> cursor.base.y + b -> cursor.base.height
	};
	GLfloat texcoord[] = {
		// joy
		GET_TEX_S(TEX_FULL_WIDTH, d -> joy_tx, 0), GET_TEX_T(TEX_FULL_HEIGHT, d -> joy_ty, 0),
		GET_TEX_S(TEX_FULL_WIDTH, d -> joy_tx, d -> joy_tw), GET_TEX_T(TEX_FULL_HEIGHT, d -> joy_ty, 0),
		GET_TEX_S(TEX_FULL_WIDTH, d -> joy_tx, 0), GET_TEX_T(TEX_FULL_HEIGHT, d -> joy_ty, d -> joy_tw),
		GET_TEX_S(TEX_FULL_WIDTH, d -> joy_tx, d -> joy_tw), GET_TEX_T(TEX_FULL_HEIGHT, d -> joy_ty, d -> joy_tw),

		// joy pressed
		GET_TEX_S(TEX_FULL_WIDTH, d -> joy_ptx, 0), GET_TEX_T(TEX_FULL_HEIGHT, d -> joy_pty, 0),
		GET_TEX_S(TEX_FULL_WIDTH, d -> joy_ptx, d -> joy_ptw), GET_TEX_T(TEX_FULL_HEIGHT, d -> joy_pty, 0),
		GET_TEX_S(TEX_FULL_WIDTH, d -> joy_ptx, 0), GET_TEX_T(TEX_FULL_HEIGHT, d -> joy_pty, d -> joy_ptw),
		GET_TEX_S(TEX_FULL_WIDTH, d -> joy_ptx, d -> joy_ptw), GET_TEX_T(TEX_FULL_HEIGHT, d -> joy_pty, d -> joy_ptw),

		// bg
		GET_TEX_S(TEX_FULL_WIDTH, d -> tx, 0), GET_TEX_T(TEX_FULL_HEIGHT, d -> ty, 0),
		GET_TEX_S(TEX_FULL_WIDTH, d -> tx, d -> tw), GET_TEX_T(TEX_FULL_HEIGHT, d -> ty, 0),
		GET_TEX_S(TEX_FULL_WIDTH, d -> tx, 0), GET_TEX_T(TEX_FULL_HEIGHT, d -> ty, d -> tw),
		GET_TEX_S(TEX_FULL_WIDTH, d -> tx, d -> tw), GET_TEX_T(TEX_FULL_HEIGHT, d -> ty, d -> tw)
	};
	b -> cursor.base.buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16, vertex, GL_STATIC_DRAW);
	b -> cursor.base.buffers[texcoord_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 24, texcoord, GL_STATIC_DRAW);
}

void UI_MakeJoystick(virtual_control_item *b, struct vkb_joystick *d, unsigned int width, unsigned int height)
{
	if(!b || !d)
		return;
	b -> joystick.base.type = vkb_joystick_type;
	b -> joystick.base.pressed = GL_FALSE;
	b -> joystick.base.enabled = d -> ava;
	b -> joystick.base.tex_index = 1;
	b -> joystick.base.z = d -> z;
	b -> joystick.angle = -1.0f;
	b -> joystick.percent = 0.0f;
	b -> joystick.pos_x = 0.0f;
	b -> joystick.pos_y = 0.0f;
	b -> joystick.base.visible = d -> ava;
	b -> joystick.actions[0] = d -> action0;
	b -> joystick.actions[1] = d -> action1;
	b -> joystick.actions[2] = d -> action2;
	b -> joystick.actions[3] = d -> action3;
	b -> joystick.keys[0] = Harmattan_Other_Key;
	b -> joystick.keys[1] = Harmattan_Other_Key;
	b -> joystick.keys[2] = Harmattan_Other_Key;
	b -> joystick.keys[3] = Harmattan_Other_Key;
	if(!b -> joystick.base.enabled)
	{
		b -> joystick.actions[0] = Total_Action;
		b -> joystick.actions[1] = Total_Action;
		b -> joystick.actions[2] = Total_Action;
		b -> joystick.actions[3] = Total_Action;
		return;
	}

	GET_VB_XY(b -> joystick.base.x, width, d -> x, d -> x_base)
		GET_VB_XY(b -> joystick.base.y, height, d -> y, d -> y_base)
		b -> joystick.base.width = d -> r;
	b -> joystick.base.height = d -> r;
	b -> joystick.e_ignore_radius = d -> r * d -> eminr;
	b -> joystick.e_radius = d -> r * d -> emaxr;
	GLfloat ex;
	GLfloat ey;
	GET_JOY_XY(ex, d -> x, d -> emaxr, d -> r, d -> x_base)
		GET_JOY_XY(ey, d -> y, d -> emaxr, d -> r, d -> y_base)
		GET_VB_XY(b -> joystick.base.e_min_x, width, ex, d -> x_base)
		GET_VB_XY(b -> joystick.base.e_min_y, height, ey, d -> y_base)
		b -> joystick.base.e_max_x = b -> joystick.base.e_min_x + d -> r * d -> emaxr;
	b -> joystick.base.e_max_y = b -> joystick.base.e_min_y + d -> r * d -> emaxr;

	GLfloat jw = b -> joystick.base.width * d -> joy_r / 2.0;
	GLfloat jh = b -> joystick.base.height * d -> joy_r / 2.0;
	GLfloat vertex[] = {
		b -> joystick.base.x, b -> joystick.base.y,
		b -> joystick.base.x + b -> joystick.base.width, b -> joystick.base.y,
		b -> joystick.base.x, b -> joystick.base.y + b -> joystick.base.height,
		b -> joystick.base.x + b -> joystick.base.width, b -> joystick.base.y + b -> joystick.base.height,
		// joy
		-jw, -jh,
		jw, -jh,
		-jw, jh,
		jw, jh
	};
	GLfloat texcoord[] = {
		GET_TEX_S(TEX_FULL_WIDTH, d -> tx, 0), GET_TEX_T(TEX_FULL_HEIGHT, d -> ty, 0),
		GET_TEX_S(TEX_FULL_WIDTH, d -> tx, d -> tw), GET_TEX_T(TEX_FULL_HEIGHT, d -> ty, 0),
		GET_TEX_S(TEX_FULL_WIDTH, d -> tx, 0), GET_TEX_T(TEX_FULL_HEIGHT, d -> ty, d -> tw),
		GET_TEX_S(TEX_FULL_WIDTH, d -> tx, d -> tw), GET_TEX_T(TEX_FULL_HEIGHT, d -> ty, d -> tw),

		// joy
		GET_TEX_S(TEX_FULL_WIDTH, d -> joy_tx, 0), GET_TEX_T(TEX_FULL_HEIGHT, d -> joy_ty, 0),
		GET_TEX_S(TEX_FULL_WIDTH, d -> joy_tx, d -> joy_tw), GET_TEX_T(TEX_FULL_HEIGHT, d -> joy_ty, 0),
		GET_TEX_S(TEX_FULL_WIDTH, d -> joy_tx, 0), GET_TEX_T(TEX_FULL_HEIGHT, d -> joy_ty, d -> joy_tw),
		GET_TEX_S(TEX_FULL_WIDTH, d -> joy_tx, d -> joy_tw), GET_TEX_T(TEX_FULL_HEIGHT, d -> joy_ty, d -> joy_tw),
	};
	b -> joystick.base.buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16, vertex, GL_STATIC_DRAW);
	b -> joystick.base.buffers[texcoord_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16, texcoord, GL_STATIC_DRAW);
}

void UI_MakeSwipe(virtual_control_item *b, struct vkb_swipe *d, unsigned int width, unsigned int height)
{
	if(!b || !d)
		return;
	b -> swipe.base.type = vkb_swipe_type;
	b -> swipe.base.pressed = GL_FALSE;
	b -> swipe.base.tex_index = 1;
	b -> swipe.base.enabled = d -> ava;
	b -> swipe.base.visible = d -> ava;
	b -> swipe.base.z = d -> z;
	b -> swipe.ignore_distance = 2.5f;
	b -> swipe.angle = -1.0f;
	b -> swipe.distance = 0.0f;
	b -> swipe.actions[0] = d -> action0;
	b -> swipe.actions[1] = d -> action1;
	b -> swipe.actions[2] = d -> action2;
	b -> swipe.actions[3] = d -> action3;
	b -> swipe.keys[0] = Harmattan_Other_Key;
	b -> swipe.keys[1] = Harmattan_Other_Key;
	b -> swipe.keys[2] = Harmattan_Other_Key;
	b -> swipe.keys[3] = Harmattan_Other_Key;
	if(!b -> swipe.base.enabled)
	{
		b -> swipe.actions[0] = Total_Action;
		b -> swipe.actions[1] = Total_Action;
		b -> swipe.actions[2] = Total_Action;
		b -> swipe.actions[3] = Total_Action;
		return;
	}

	GET_VB_XY(b -> swipe.base.x, width, d -> x, d -> x_base)
		GET_VB_XY(b -> swipe.base.y, height, d -> y, d -> y_base)
		b -> swipe.base.width = d -> w;
	b -> swipe.base.height = d -> h;
	GET_VB_XY(b -> swipe.base.e_min_x, width, d -> ex, d -> x_base)
		GET_VB_XY(b -> swipe.base.e_min_y, height, d -> ey, d -> y_base)
		b -> swipe.base.e_max_x = b -> swipe.base.e_min_x + d -> ew;
	b -> swipe.base.e_max_y = b -> swipe.base.e_min_y + d -> eh;
	if(d -> render)
	{
		GLfloat vertex[] = {
			b -> swipe.base.x, b -> swipe.base.y,
			b -> swipe.base.x + b -> swipe.base.width, b -> swipe.base.y,
			b -> swipe.base.x, b -> swipe.base.y + b -> swipe.base.height,
			b -> swipe.base.x + b -> swipe.base.width, b -> swipe.base.y + b -> swipe.base.height
		};
		GLfloat texcoord[] = {
			GET_TEX_S(TEX_FULL_WIDTH, d -> tx, 0), GET_TEX_T(TEX_FULL_HEIGHT, d -> ty, 0),
			GET_TEX_S(TEX_FULL_WIDTH, d -> tx, d -> tw), GET_TEX_T(TEX_FULL_HEIGHT, d -> ty, 0),
			GET_TEX_S(TEX_FULL_WIDTH, d -> tx, 0), GET_TEX_T(TEX_FULL_HEIGHT, d -> ty, d -> tw),
			GET_TEX_S(TEX_FULL_WIDTH, d -> tx, d -> tw), GET_TEX_T(TEX_FULL_HEIGHT, d -> ty, d -> tw),
		};
		b -> swipe.base.buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, vertex, GL_STATIC_DRAW);
		b -> swipe.base.buffers[texcoord_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, texcoord, GL_STATIC_DRAW);
	}
}

void UI_MakeButton(virtual_control_item *b, struct vkb_button *d, unsigned int width, unsigned int height)
{
	if(!b || !d)
		return;
	b -> button.base.type = vkb_button_type;
	b -> button.base.pressed = GL_FALSE;
	b -> button.base.enabled = d -> ava;
	b -> button.base.visible = d -> ava;
	b -> button.base.z = d -> z;
	b -> button.base.tex_index = 0;
	b -> button.action = d -> action;
	b -> button.key = Harmattan_Other_Key;
	if(!b -> button.base.enabled)
	{
		b -> button.action = Total_Action;
		return;
	}

	GET_VB_XY(b -> button.base.x, width, d -> x, d -> x_base)
		GET_VB_XY(b -> button.base.y, height, d -> y, d -> y_base)
		b -> button.base.width = d -> w;
	b -> button.base.height = d -> h;
	GET_VB_XY(b -> button.base.e_min_x, width, d -> ex, d -> x_base)
		GET_VB_XY(b -> button.base.e_min_y, height, d -> ey, d -> y_base)
		b -> button.base.e_max_x = b -> button.base.e_min_x + d -> ew;
	b -> button.base.e_max_y = b -> button.base.e_min_y + d -> eh;
	GLfloat vertex[] = {
		b -> button.base.x, b -> button.base.y,
		b -> button.base.x + b -> button.base.width, b -> button.base.y,
		b -> button.base.x, b -> button.base.y + b -> button.base.height,
		b -> button.base.x + b -> button.base.width, b -> button.base.y + b -> button.base.height
	};
	GLfloat texcoord[] = {
		GET_TEX_S(TEX_FULL_WIDTH, d -> tx, 0), GET_TEX_T(TEX_FULL_HEIGHT, d -> ty, 0),
		GET_TEX_S(TEX_FULL_WIDTH, d -> tx, d -> tw), GET_TEX_T(TEX_FULL_HEIGHT, d -> ty, 0),
		GET_TEX_S(TEX_FULL_WIDTH, d -> tx, 0), GET_TEX_T(TEX_FULL_HEIGHT, d -> ty, d -> th),
		GET_TEX_S(TEX_FULL_WIDTH, d -> tx, d -> tw), GET_TEX_T(TEX_FULL_HEIGHT, d -> ty, d -> th),

		GET_TEX_S(TEX_FULL_WIDTH, d -> ptx, 0), GET_TEX_T(TEX_FULL_HEIGHT, d -> pty, 0),
		GET_TEX_S(TEX_FULL_WIDTH, d -> ptx, d -> ptw), GET_TEX_T(TEX_FULL_HEIGHT, d -> pty, 0),
		GET_TEX_S(TEX_FULL_WIDTH, d -> ptx, 0), GET_TEX_T(TEX_FULL_HEIGHT, d -> pty, d -> pth),
		GET_TEX_S(TEX_FULL_WIDTH, d -> ptx, d -> ptw), GET_TEX_T(TEX_FULL_HEIGHT, d -> pty, d -> pth)
	};
	b -> button.base.buffers[vertex_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, vertex, GL_STATIC_DRAW);
	b -> button.base.buffers[texcoord_buffer_type] = new_OpenGL_buffer_object(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16, texcoord, GL_STATIC_DRAW);
}
#undef GET_VB_XY
#undef GET_TEX_S
#undef GET_TEX_T

int UI_GetControlItemOnPosition(const vkb *v, int x, int y, int *r)
{
	if(!v)
		return -1;
	int c = 0;
	int i;
	int count = TOTAL_VKB_COUNT;
	for(i = 0; i < count; i++)
	{
		const virtual_control_item *b = v -> vb + i;
		if(!b -> base.enabled)
			continue;
		if(MOUSE_IN_RANGE(b -> base, x, y))
		{
			if(r)
				r[c] = i;
			c++;
		}
	}
	if(r)
	{
		int j;
		for(j = 0; j < c; j++)
		{
			int k;
			for(k = j + 1; k < c; k++)
			{
				const virtual_control_item *a = v -> vb + r[j];
				const virtual_control_item *b = v -> vb + r[k];
				if(b -> base.z > a -> base.z)
				{
					int t = r[j];
					r[j] = r[k];
					r[k] = t;
				}
			}
		}
	}
	return c;
}

int UI_GetControlItemOnPosition2(const vkb *v, int x, int y, int lx, int ly, int *r, mouse_motion_button_status *s)
{
	if(!v)
		return -1;
	int c = 0;
	int i;
	int count = TOTAL_VKB_COUNT;
	for(i = 0; i < count; i++)
	{
		const virtual_control_item *b = v -> vb + i;
		if(!b -> base.enabled)
			continue;
		mouse_motion_button_status status = UI_ButtonMouseMotion(b, x, y, lx, ly);
		if(status == all_out_range_status)
			continue;
		if(r)
			r[c] = i;
		if(s)
			s[c] = status;
		c++;
	}
	if(r && s)
	{
		int j;
		for(j = 0; j < c; j++)
		{
			int k;
			for(k = j + 1; k < c; k++)
			{
				const virtual_control_item *a = v -> vb + r[j];
				const virtual_control_item *b = v -> vb + r[k];
				if(b -> base.z > a -> base.z)
				{
					int t = r[j];
					r[j] = r[k];
					r[k] = t;
					mouse_motion_button_status tt = s[j];
					s[j] = s[k];
					s[k] = tt;
				}
			}
		}
	}
	return c;
}

void UI_RenderVKBButton(const virtual_button *b, texture * const tex[])
{
	if(!b)
		return;
	if(b -> base.type != vkb_button_type)
		return;
	if(!tex[b -> base.tex_index] || !glIsTexture(tex[b -> base.tex_index] -> texid))
		return;
	if(!b -> base.visible)
		return;
	if(!glIsBuffer(b -> base.buffers[texcoord_buffer_type]) || !glIsBuffer(b -> base.buffers[vertex_buffer_type]))
		return;
	oglBindTexture(GL_TEXTURE_2D, tex[b -> base.tex_index] -> texid);
	glBindBuffer(GL_ARRAY_BUFFER, b -> base.buffers[texcoord_buffer_type]);
	GLvoid *ptr = (b -> base.pressed && b -> base.enabled) ? (GLfloat *)NULL + 8 : NULL;
	glTexCoordPointer(2, GL_FLOAT, 0, ptr);
	glBindBuffer(GL_ARRAY_BUFFER, b -> base.buffers[vertex_buffer_type]);
	glVertexPointer(2, GL_FLOAT, 0, NULL);
	oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	oglBindTexture(GL_TEXTURE_2D, 0);
}

void UI_RenderVKBSwipe(const virtual_swipe *b, texture * const tex[])
{
	if(!b)
		return;
	if(b -> base.type != vkb_swipe_type)
		return;
	if(!tex[b -> base.tex_index] || !glIsTexture(tex[b -> base.tex_index] -> texid))
		return;
	if(!b -> base.visible)
		return;
	if(!glIsBuffer(b -> base.buffers[texcoord_buffer_type]) || !glIsBuffer(b -> base.buffers[vertex_buffer_type]))
		return;
	oglBindTexture(GL_TEXTURE_2D, tex[b -> base.tex_index] -> texid);
	glBindBuffer(GL_ARRAY_BUFFER, b -> base.buffers[texcoord_buffer_type]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, b -> base.buffers[vertex_buffer_type]);
	glVertexPointer(2, GL_FLOAT, 0, NULL);
	oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	oglBindTexture(GL_TEXTURE_2D, 0);
}

void UI_RenderVKBJoystick(const virtual_joystick *b, texture * const tex[])
{
	if(!b)
		return;
	if(b -> base.type != vkb_joystick_type)
		return;
	if(!tex[b -> base.tex_index] || !glIsTexture(tex[b -> base.tex_index] -> texid))
		return;
	if(!b -> base.visible)
		return;
	if(!glIsBuffer(b -> base.buffers[texcoord_buffer_type]) || !glIsBuffer(b -> base.buffers[vertex_buffer_type]))
		return;
	oglBindTexture(GL_TEXTURE_2D, tex[b -> base.tex_index] -> texid);
	glBindBuffer(GL_ARRAY_BUFFER, b -> base.buffers[texcoord_buffer_type]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, b -> base.buffers[vertex_buffer_type]);
	glVertexPointer(2, GL_FLOAT, 0, NULL);
	oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	GLfloat cx = b -> base.x + b -> base.width / 2;
	GLfloat cy = b -> base.y + b -> base.height / 2;
	glPushMatrix();
	{
		glTranslatef(cx + b -> pos_x, cy + b -> pos_y, 0.0f);
		oglDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
	}
	glPopMatrix();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	oglBindTexture(GL_TEXTURE_2D, 0);
}

void UI_RenderVKBCursor(const virtual_cursor *b, texture *const tex[])
{
	if(!b)
		return;
	if(b -> base.type != vkb_cursor_type)
		return;
	if(!tex[b -> base.tex_index] || !glIsTexture(tex[b -> base.tex_index] -> texid))
		return;
	if(!b -> base.visible)
		return;
	if(!glIsBuffer(b -> base.buffers[texcoord_buffer_type]) || !glIsBuffer(b -> base.buffers[vertex_buffer_type]))
		return;
	oglBindTexture(GL_TEXTURE_2D, tex[b -> base.tex_index] -> texid);
	glBindBuffer(GL_ARRAY_BUFFER, b -> base.buffers[texcoord_buffer_type]);
	GLvoid *ptr = (b -> base.pressed && b -> base.enabled) ? (GLfloat *)NULL + 8 : NULL;
	glTexCoordPointer(2, GL_FLOAT, 0, ptr);
	glBindBuffer(GL_ARRAY_BUFFER, b -> base.buffers[vertex_buffer_type]);
	glVertexPointer(2, GL_FLOAT, 0, NULL);

	GLfloat cx = b -> base.x + b -> base.width / 2;
	GLfloat cy = b -> base.y + b -> base.height / 2;
	glPushMatrix();
	{
		glTranslatef(cx + b -> pos_x, cy + b -> pos_y, 0.0f);
		oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	glPopMatrix();

	if(b -> render_bg)
	{
		glBindBuffer(GL_ARRAY_BUFFER, b -> base.buffers[texcoord_buffer_type]);
		glTexCoordPointer(2, GL_FLOAT, 0, (GLfloat *)NULL + 16);
		glBindBuffer(GL_ARRAY_BUFFER, b -> base.buffers[vertex_buffer_type]);
		glVertexPointer(2, GL_FLOAT, 0, (GLfloat *)NULL + 8);

		oglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	oglBindTexture(GL_TEXTURE_2D, 0);
}
