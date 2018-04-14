#include "run_setting.h"
#include "gl_3d_main.h"
#include "flickable.h"
#include "label.h"
#include "button.h"
#include "switcher.h"
#include "spin_box.h"
#include "time_spin_box.h"
#include "game_std.h"
#include "game_setting.h"
#include "action_signal_slot.h"
#include "setting_component.h"

#define SETTING_ITEM_W 360
#define SETTING_ITEM_H 45
#define FLICK_X 150
#define FLICK_Y 100
#define FLICK_W 554
#define FLICK_H 300
#define BUTTON_SURE_X 100
#define BUTTON_SURE_Y 10
#define BUTTON_BACK_X 600
#define BUTTON_BACK_Y 10
#define BUTTON_W 154
#define BUTTON_H 60
#define LABEL_H 80

static int Menu_RunSettingIdleEventFunc(void);
static int Menu_RunSettingKeyEventFunc(int k, int a, int p, int x, int y);
static int Menu_RunSettingMouseEventFunc(int b, int p, int x, int y);
static int Menu_RunSettingMouseClickEventFunc(int b, int x, int y);
static int Menu_RunSettingMouseMotionEventFunc(int b, int p, int x, int y, int dx, int dy);
static void Menu_RunSettingDrawFunc(void);
static void Menu_RunSettingReshapeFunc(int w, int h);
static void Menu_RunSettingInitFunc(void);
static void Menu_RunSettingFreeFunc(void);

static void Menu_ResetRunSetting(void);
static void Menu_SureAction(void);
static void Menu_BackAction(void);
static void Menu_SetRunSettingPageSize(GLsizei w, GLsizei h);

static label lb;
static button sure_btn;
static button back_btn;
static flickable_item *items = NULL;
static int item_count = 0;
static flickable flick;
static int game = -1;
static int level = 0;
static bool_t has_init = 0;
static GLsizei page_width = HARMATTAN_FULL_WIDTH;
static GLsizei page_height = HARMATTAN_FULL_HEIGHT;

void Menu_SetRunSettingPageSize(GLsizei w, GLsizei h)
{
	if(page_width == w && page_height == h)
		return;
	page_width = w;
	page_height = h;
	if(has_init)
	{
		UI_ResetButtonGeometry(&back_btn, BUTTON_BACK_X, BUTTON_BACK_Y, BUTTON_W, BUTTON_H);
		UI_ResetButtonGeometry(&sure_btn, BUTTON_SURE_X, BUTTON_SURE_Y, BUTTON_W, BUTTON_H);
		UI_ResetLabelGeometry(&lb, 0.0, page_height - LABEL_H, page_width, LABEL_H);
		UI_ResetFlickableGeometry(&flick, FLICK_X, FLICK_Y, FLICK_W, FLICK_H);
	}
}

int Menu_RunSettingIdleEventFunc(void)
{
	if(!has_init)
		return 0;
	/*
		 if(key_state[Harmattan_K_Up] || key_state[Harmattan_K_w])
		 UI_MoveTextBrowser(&tb, -1);
		 else if(key_state[Harmattan_K_Down] || key_state[Harmattan_K_s])
		 UI_MoveTextBrowser(&tb, 1);
		 */
	return 1;
}

void Menu_RunSettingInitFunc(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_SMOOTH);
	oglEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	oglEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	oglEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	oglEnable(GL_TEXTURE_2D);
}

void Menu_RunSettingDrawFunc(void)
{
	if(!has_init)
		return;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	OpenGL_Render3DOrtho(0.0, width, 0.0, height);
	{
		//glPolygonMode(GL_FRONT, GL_LINE);
		oglEnable(GL_SCISSOR_TEST);
		glScissor(flick.base.x, flick.base.y, flick.base.width, flick.base.height);
		glPushMatrix();
		{
			glTranslatef(flick.base.x, flick.base.y, flick.base.z);
			UI_RenderFlickable(&flick);
		}
		glPopMatrix();
		oglDisable(GL_SCISSOR_TEST);
		glPushMatrix();
		{
			glTranslatef(sure_btn.base.x, sure_btn.base.y, sure_btn.base.z);
			UI_RenderButton(&sure_btn);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(back_btn.base.x, back_btn.base.y, back_btn.base.z);
			UI_RenderButton(&back_btn);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(lb.base.x, lb.base.y, lb.base.z);
			UI_RenderLabel(&lb);
		}
		glPopMatrix();
	}
}

void Menu_RunSettingReshapeFunc(int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	if(!has_init)
		return;
	Menu_SetRunSettingPageSize(w, h);
}

void Menu_RunSettingFreeFunc(void)
{
	if(!has_init)
		return;
	delete_button(&back_btn);
	delete_button(&sure_btn);
	delete_label(&lb);
	delete_flickable(&flick);
	if(items)
	{
		UI_FreeSettingComponent(items, item_count);
		free(items);
		items = NULL;
		item_count = 0;
	}
	Menu_ResetRunSetting();
	has_init = 0;
}

// for all X event pointer coord y, Using left-down as ori, like OpenGL, and not left-top of X11. so the y coord need to convert by screen height - y, and delta_y is invert.
int Menu_RunSettingKeyEventFunc(int key, int act, int pressed, int x, int y)
{
	if(!has_init)
		return 0;
	switch(key)
	{
		case Harmattan_K_Control_R:
		case Harmattan_K_Control_L:
		case Harmattan_K_BackSpace:
		case Harmattan_K_Escape:
			if(pressed)
			{
				Menu_BackAction();
				return 1;
			}
			break;
		case Harmattan_K_Return:
		case Harmattan_K_KP_Enter:
			if(pressed)
			{
				Menu_SureAction();
				return 1;
			}
			break;
			break;
		default:
			break;
	}
	return 0;
}

int Menu_RunSettingMouseEventFunc(int button, int pressed, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	if(UI_PointInWidget(&back_btn.base, x, gl_y))
	{
		back_btn.highlight = pressed ? GL_TRUE : GL_FALSE;
		return 1;
	}
	else if(UI_PointInWidget(&sure_btn.base, x, gl_y))
	{
		sure_btn.highlight = pressed ? GL_TRUE : GL_FALSE;
		return 1;
	}
	return 0;
}

int Menu_RunSettingMouseMotionEventFunc(int button, int pressed, int x, int y, int dx, int dy)
{
	if(!has_init)
		return 0;
	int res = 0;
	if(pressed)
	{
		int gl_y = height - y;
		int last_x = x - dx;
		int last_gl_y = height - (y - dy);
		if(UI_PointInWidget(&flick.base, x, gl_y))
		{
			res = UI_SlideFlickable(&flick, -dy);
		}
		if(UI_PointInWidget(&back_btn.base, x, gl_y) && !UI_PointInWidget(&back_btn.base, last_x, last_gl_y))
		{
			back_btn.highlight = GL_TRUE;
			res |= 1;
		}
		else if(!UI_PointInWidget(&back_btn.base, x, gl_y) && UI_PointInWidget(&back_btn.base, last_x, last_gl_y))
		{
			back_btn.highlight = GL_FALSE;
			res |= 1;
		}
		if(UI_PointInWidget(&sure_btn.base, x, gl_y) && !UI_PointInWidget(&sure_btn.base, last_x, last_gl_y))
		{
			sure_btn.highlight = GL_TRUE;
			res |= 1;
		}
		else if(!UI_PointInWidget(&sure_btn.base, x, gl_y) && UI_PointInWidget(&sure_btn.base, last_x, last_gl_y))
		{
			sure_btn.highlight = GL_FALSE;
			res |= 1;
		}
	}
	return res;
}

void Menu_RunSettingRegisterFunction(void)
{
	Main3D_SetInitFunction(Menu_RunSettingInitFunc);
	Main3D_SetDrawFunction(Menu_RunSettingDrawFunc);
	Main3D_SetFreeFunction(Menu_RunSettingFreeFunc);
	Main3D_SetKeyEventFunction(Menu_RunSettingKeyEventFunc);
	Main3D_SetIdleEventFunction(Menu_RunSettingIdleEventFunc);
	Main3D_SetReshapeFunction(Menu_RunSettingReshapeFunc);
	Main3D_SetMouseEventFunction(Menu_RunSettingMouseEventFunc);
	Main3D_SetMouseMotionEventFunction(Menu_RunSettingMouseMotionEventFunc);
	Main3D_SetMouseClickEventFunction(Menu_RunSettingMouseClickEventFunc);
}

void Menu_BackAction(void)
{
	const void *slot = SignalSlot_GetAction(BACK_MAIN_MENU);
	if(slot)
	{
		((void__func__void)slot)();
	}
}

void Menu_SureAction(void)
{
	const void *slot = SignalSlot_GetAction(LOAD_GAME);
	if(slot)
	{
		((void__func__int_int)slot)(game, level);
	}
}

int Menu_RunSettingMouseClickEventFunc(int button, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	if(UI_PointInWidget(&back_btn.base, x, gl_y))
	{
		Menu_BackAction();
		return 1;
	}
	else if(UI_PointInWidget(&sure_btn.base, x, gl_y))
	{
		Menu_SureAction();
		return 1;
	}
	else if(UI_PointInWidget(&flick.base, x, gl_y))
	{
		return UI_ClickFlickable(&flick, x - flick.base.x, gl_y - flick.base.y);
	}
	return 0;
}

void Menu_InitRunSetting(int g, int l)
{
	if(has_init)
		return;
	//Menu_SetRunSettingPageSize(width, height);
	new_button(&back_btn, BUTTON_BACK_X, BUTTON_BACK_Y, 0.3, BUTTON_W, BUTTON_H, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(black), "Back");
	new_button(&sure_btn, BUTTON_SURE_X, BUTTON_SURE_Y, 0.3, BUTTON_W, BUTTON_H, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(black), "Sure");
	sure_btn.fnt = &fnt;
	back_btn.fnt = &fnt;
	new_label(&lb, 0.0, page_height - LABEL_H, 0.3, page_width, LABEL_H, 0, Color_GetColor(white_color, 0.4), X11_COLOR(green), Color_GetColor(black_color, 0.0), "Run game", NULL);
	lb.fnt = &fnt;
	new_flickable(&flick, FLICK_X, FLICK_Y, 0.2, FLICK_W, FLICK_H, 10, 15, 15, Color_GetColor(black_color, 0.0), X11_COLOR(lightgreen), X11_COLOR(darkgreen));
	item_count = use_weapon_setting - group_count_setting;
	setting_item_type types[item_count];
	int i;
	for(i = 0; i < item_count; i++)
		types[i] = group_count_setting + i;
	items = UI_MakeSettingItems(types, item_count, SETTING_ITEM_W, SETTING_ITEM_H, &fnt);
	flick.items = items;
	flick.count = item_count;
	game = g;
	level = l;
	has_init = 1;
}

void Menu_ResetRunSetting(void)
{
	page_width = width;
	page_height = height;
}
