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

#define PAGE_NAME "RunSetting"

#define SETTING_ITEM_W 360
#define SETTING_ITEM_H 45
#define FLICK_X 150
#define FLICK_Y 100
#define FLICK_W 554
#define FLICK_H 300
#define BTN_W 154
#define BTN_H 60
#define LABEL_H 80

#define FLICK_MOVE_UNIT 100

typedef enum _menu_action
{
	enter_action = 0,
	back_action,
	total_action_type
} menu_action;

static int UI_IdleFunc(void);
static int UI_KeyFunc(int k, int a, int p, int x, int y);
static int UI_MouseFunc(int b, int p, int x, int y);
static int UI_ClickFunc(int b, int x, int y);
static int UI_MotionFunc(int b, int p, int x, int y, int dx, int dy);
static void UI_DrawFunc(void);
static void UI_ReshapeFunc(int w, int h);
static void UI_InitFunc(void);
static void UI_FreeFunc(void);
static Main3DStoreFunction_f UI_StoreFunc = NULL;
static Main3DRestoreFunction_f UI_RestoreFunc = NULL;

static void Menu_ResetRunSetting(void);
static void Menu_SureAction(void *data);
static void Menu_BackAction(void *data);
static void Menu_SetRunSettingPageSize(GLsizei w, GLsizei h);

static const button_initilizer Btn_Infos[] = {
	{100, 10, BTN_W, BTN_H, "Sure", Menu_SureAction, NULL},
	{600, 10, BTN_W, BTN_H, "Back", Menu_BackAction, NULL},
};

static label lb;
static button btns[total_action_type];
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
		UI_ResetLabelGeometry(&lb, 0.0, page_height - LABEL_H, page_width, LABEL_H);
		UI_ResetFlickableGeometry(&flick, FLICK_X, FLICK_Y, FLICK_W, FLICK_H);
		int i;
		for(i = 0; i < total_action_type; i++)
			UI_ResetButtonGeometry(btns + i, Btn_Infos[i].x, Btn_Infos[i].y, Btn_Infos[i].w, Btn_Infos[i].h);
	}
}

int UI_IdleFunc(void)
{
	if(!has_init)
		return 0;
	if(key_state[Harmattan_K_Up] || key_state[Harmattan_K_w])
		UI_SlideFlickable(&flick, delta_time * -FLICK_MOVE_UNIT);
	else if(key_state[Harmattan_K_Down] || key_state[Harmattan_K_s])
		UI_SlideFlickable(&flick, delta_time * FLICK_MOVE_UNIT);
	return 1;
}

void UI_InitFunc(void)
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
#ifndef _HARMATTAN_OPENGLES2
	oglDisable(GL_LIGHTING);
#endif
	oglDisable(GL_FOG);
}

void UI_DrawFunc(void)
{
	if(!has_init)
		return;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	OpenGL_Render3DOrtho(0.0, width, 0.0, height);
	{
		//glPolygonMode(GL_FRONT, GL_LINE);
		glPushMatrix();
		{
			glTranslatef(flick.base.x, flick.base.y, flick.base.z);
			UI_RenderFlickable(&flick);
		}
		glPopMatrix();
		int i;
		for(i = 0; i < total_action_type; i++)
		{
			glPushMatrix();
			{
				glTranslatef(btns[i].base.x, btns[i].base.y, btns[i].base.z);
				UI_RenderButton(btns + i);
			}
			glPopMatrix();
		}
		glPushMatrix();
		{
			glTranslatef(lb.base.x, lb.base.y, lb.base.z);
			UI_RenderLabel(&lb);
		}
		glPopMatrix();
	}
}

void UI_ReshapeFunc(int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	if(!has_init)
		return;
	Menu_SetRunSettingPageSize(w, h);
}

void UI_FreeFunc(void)
{
	if(!has_init)
		return;
	int m;
	for(m = 0; m < total_action_type; m++)
		delete_button(btns + m);
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

	NL_PAGE_DESTROY_DEBUG(PAGE_NAME)
}

// for all X event pointer coord y, Using left-down as ori, like OpenGL, and not left-top of X11. so the y coord need to convert by screen height - y, and delta_y is invert.
int UI_KeyFunc(int key, int act, int pressed, int x, int y)
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
				Menu_BackAction(NULL);
				return 1;
			}
			break;
		case Harmattan_K_Return:
		case Harmattan_K_KP_Enter:
			if(pressed)
			{
				Menu_SureAction(NULL);
				return 1;
			}
			break;
		case Harmattan_K_Up:
		case Harmattan_K_w:
		case Harmattan_K_W:
			if(pressed)
			{
				UI_SlideFlickable(&flick, delta_time * -FLICK_MOVE_UNIT);
			}
			break;
		case Harmattan_K_Down:
		case Harmattan_K_s:
		case Harmattan_K_S:
			if(pressed)
			{
				UI_SlideFlickable(&flick, delta_time * FLICK_MOVE_UNIT);
			}
			break;
		default:
			break;
	}
	return 0;
}

int UI_MouseFunc(int button, int pressed, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	int i;
	for(i = 0; i < total_action_type; i++)
	{
		if(UI_PointInWidget(&btns[i].base, x, gl_y))
		{
			btns[i].highlight = pressed ? GL_TRUE : GL_FALSE;
			return 1;
		}
	}
	return 0;
}

int UI_MotionFunc(int button, int pressed, int x, int y, int dx, int dy)
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
		int i;
		for(i = 0; i < total_action_type; i++)
		{
			if(UI_PointInWidget(&btns[i].base, x, gl_y) && !UI_PointInWidget(&btns[i].base, last_x, last_gl_y))
			{
				btns[i].highlight = GL_TRUE;
				res |= 1;
			}
			else if(!UI_PointInWidget(&btns[i].base, x, gl_y) && UI_PointInWidget(&btns[i].base, last_x, last_gl_y))
			{
				btns[i].highlight = GL_FALSE;
				res |= 1;
			}
		}
	}
	return res;
}

void UI_RunSettingRegisterFunction(void)
{
	glk_function func;

	func = REGISTER_RENDER_FUNCTION(UI);
	Main3D_PushRenderPage(PAGE_NAME, &func);
}

void Menu_BackAction(void *data)
{
	const void *slot = SignalSlot_GetAction(BACK_MAIN_MENU);
	if(slot)
	{
		((void__func__void)slot)();
	}
}

void Menu_SureAction(void *data)
{
	const void *slot = SignalSlot_GetAction(LOAD_GAME);
	if(slot)
	{
		((void__func__int_int)slot)(game, level);
	}
}

int UI_ClickFunc(int button, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	if(UI_PointInWidget(&flick.base, x, gl_y))
	{
		return UI_ClickFlickable(&flick, x - flick.base.x, gl_y - flick.base.y);
	}
	int i;
	for(i = 0; i < total_action_type; i++)
	{
		if(UI_PointInWidget(&btns[i].base, x, gl_y))
		{
			if(Btn_Infos[i].func)
			{
				Btn_Infos[i].func(Btn_Infos[i].data);
			}
			return 1;
		}
	}
	return 0;
}

void Menu_InitRunSetting(int g, int l)
{
	if(has_init)
		return;
	//Menu_SetRunSettingPageSize(width, height);
	int m;
	for(m = 0; m < total_action_type; m++)
	{
		new_button(btns + m, Btn_Infos[m].x, Btn_Infos[m].y, 0.3, Btn_Infos[m].w, Btn_Infos[m].h, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(gray), Btn_Infos[m].label);
		btns[m].fnt = &fnt;
	}
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

