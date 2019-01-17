#include "game_menu.h"
#include "button.h"
#include "label.h"
#include "list_view.h"
#include "nl_std.h"
#include "game_std.h"
#include "action_signal_slot.h"

#define PAGE_NAME GAME_MENU_PAGE_NAME

#define LIST_VIEW_X 150
#define LIST_VIEW_Y 100
#define LIST_VIEW_W 554
#define LIST_VIEW_H 300
#define LIST_BUTTON_W 400
#define LIST_BUTTON_H 50
#define BTN_W 200
#define BTN_H 60
#define LABEL_H 80

#define IDLE_TIME_DELAY 0.4

typedef enum _menu_action
{
	enter_action = 0,
	back_action,
	total_action_type
} menu_action;

static const struct _game_menu_action
{
	char *text;
	char *func;
} Game_Menu_Action[] = {
	{"Continue", CLOSE_GAME_MENU},
	{"Back to menu", INIT_MAIN_MENU},
	{"Quit", QUIT}
};

static int UI_IdleFunc(void);
static int UI_KeyFunc(int k, int a, int p, int x, int y);
static int UI_MouseFunc(int b, int p, int x, int y);
static int UI_ClickFunc(int b, int x, int y);
static int UI_MotionFunc(int b, int p, int x, int y, int dx, int dy);
static void UI_DrawFunc(void);
static void UI_ReshapeFunc(int w, int h);
static void UI_InitFunc(void);
static void UI_FreeFunc(void);
static void UI_StoreFunc(void);
static void UI_RestoreFunc(void);

static void UI_ResetGameMenu(void);
static void UI_MakeListViewData(void);
static void UI_InitListView(void);
static void UI_EnterAction(void *data);
static void UI_BackAction(void *data);
static void UI_SetPageSize(GLsizei w, GLsizei h);

static const button_initilizer Btn_Infos[] = {
	{100, 40, BTN_W, BTN_H, "Sure", UI_EnterAction, NULL},
	{555, 40, BTN_W, BTN_H, "Back", UI_BackAction, NULL},
};

static button btn;
static button btns[total_action_type];
static list_view lst;
static label lb;
static scene_2d bg;
static scene_2d fg;
static bool_t has_init = 0;

static list_view_data *data = NULL;
static unsigned int data_count = 0;
static int menu_level = 0;
static GLsizei page_width = HARMATTAN_FULL_WIDTH;
static GLsizei page_height = HARMATTAN_FULL_HEIGHT;
static float idle_time = 0.0f;

void UI_SetPageSize(GLsizei w, GLsizei h)
{
	if(page_width == w && page_height == h)
		return;
	page_width = w;
	page_height = h;
	if(has_init)
	{
		UI_ResizeScene2D(&bg, page_width, page_height);
		UI_ResizeScene2D(&fg, page_width, page_height);
		UI_ResizeButton(&btn, LIST_BUTTON_W, LIST_BUTTON_H);
		int i;
		for(i = 0; i < total_action_type; i++)
			UI_ResetButtonGeometry(btns + i, Btn_Infos[i].x, Btn_Infos[i].y, Btn_Infos[i].w, Btn_Infos[i].h);
		UI_ResetListViewGeometry(&lst, LIST_VIEW_X, LIST_VIEW_Y, LIST_VIEW_W, LIST_VIEW_H);
		UI_ResetLabelGeometry(&lb, 0.0, page_height - LABEL_H, page_width, LABEL_H);
	}
}

int UI_IdleFunc(void)
{
	if(!has_init)
		return 0;
	idle_time += delta_time;
	if(idle_time < IDLE_TIME_DELAY)
		return 0;
	while(idle_time - IDLE_TIME_DELAY > 0.0f)
		idle_time -= IDLE_TIME_DELAY;
	if(key_state[Harmattan_K_Up] || key_state[Harmattan_K_w] || key_state[Harmattan_K_W])
		UI_MoveListViewCurrentIndex(&lst, -1);
	else if(key_state[Harmattan_K_Down] || key_state[Harmattan_K_s] || key_state[Harmattan_K_S])
		UI_MoveListViewCurrentIndex(&lst, 1);
	else
		idle_time = 0.0f;
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
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	oglEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	oglEnable(GL_TEXTURE_2D);
#ifndef _HARMATTAN_OPENGLES2
	oglDisable(GL_LIGHTING);
#endif
	oglDisable(GL_FOG);

	if(has_init)
		return;
	new_button(&btn, 0.0, 0.0, 0.0, LIST_BUTTON_W, LIST_BUTTON_H, 2.0, Color_GetColor(lightskyblue_color, 0.4), Color_GetColor(green_color, 0.4), Color_GetColor(lightseagreen_color, 0.4), Color_GetColor(skyblue_color, 0.4), Color_GetColor(darkgreen_color, 0.4), Color_GetColor(seagreen_color, 0.4), NULL);
	btn.base.clip = GL_FALSE;
	int m;
	for(m = 0; m < total_action_type; m++)
	{
		new_button(btns + m, Btn_Infos[m].x, Btn_Infos[m].y, 0.3, Btn_Infos[m].w, Btn_Infos[m].h, 2.0, Color_GetColor(black_color, 0.4), Color_GetColor(green_color, 0.4), Color_GetColor(black_color, 0.4), Color_GetColor(gray_color, 0.4), Color_GetColor(darkgreen_color, 0.4), Color_GetColor(black_color, 0.4), Btn_Infos[m].label);
		btns[m].fnt = &fnt;
	}
	btn.fnt = &fnt;
	new_list_view(&lst, LIST_VIEW_X, LIST_VIEW_Y, 0.0, LIST_VIEW_W, LIST_VIEW_H, 10, 20, 15, Color_GetColor(black_color, 0.2), Color_GetColor(lightgreen_color, 0.4), Color_GetColor(darkgreen_color, 0.4));
	lst.delegate.component = &btn;
	lst.delegate.update_func = UI_ButtonUpdateText;
	lst.delegate.render_func = UI_RenderButtonItem;
	lst.delegate.get_geometry_func = UI_GetWidgetGeometry;
	new_label(&lb, 0.0, page_height - LABEL_H, 0.2, page_width, LABEL_H, 0, Color_GetColor(white_color, 0.4), Color_GetColor(green_color, 0.4), Color_GetColor(white_color, 0.0), "NETLizard 3D Game", NULL);
	new_scene_2d(&bg, 0.0f, 0.0f, page_width, page_height, 1.0, left_bottom_anchor_type, Color_GetColor(white_color, 0.0), NULL);
	new_scene_2d(&fg, 0.0f, 0.0f, page_width, page_height, 1.0, left_orientation_type | down_orientation_type, Color_GetColor(black_color, 0.1), NULL);
	lb.fnt = &fnt;
	has_init = 1;
	menu_level = 0;
	UI_MakeListViewData();
	UI_InitListView();

	UI_RestoreFunc();
}

void UI_DrawFunc(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(!has_init)
		return;

	OpenGL_Render3DOrtho(0.0, width, 0.0, height);
	{
		//glPolygonMode(GL_FRONT, GL_LINE);
		UI_RenderScene2D(&bg);
		UI_RenderScene2D(&fg);
		glPushMatrix();
		{
			glTranslatef(lst.base.x, lst.base.y, lst.base.z);
			UI_RenderListView(&lst);
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
	UI_SetPageSize(w, h);
}

void UI_FreeFunc(void)
{
	if(!has_init)
		return;
	delete_button(&btn);
	int m;
	for(m = 0; m < total_action_type; m++)
		delete_button(btns + m);
	delete_label(&lb);
	delete_list_view(&lst);
	if(data)
	{
		GLuint i;
		for(i = 0; i < data_count; i++)
		{
			FREE_PTR(data[i].text)
				FREE_PTR(data[i].args)
		}
		free(data);
		data = NULL;
		data_count = 0;
	}
	delete_scene_2d(&bg);
	delete_scene_2d(&fg);
	menu_level = 0;
	UI_ResetGameMenu();
	has_init = 0;

	NL_PAGE_DESTROY_DEBUG(PAGE_NAME)
}

void UI_ResetGameMenu(void)
{
	page_width = width;
	page_height = height;
}

// for all X event pointer coord y, Using left-down as ori, like OpenGL, and not left-top of X11. so the y coord need to convert by screen height - y, and delta_y is invert.
int UI_KeyFunc(int key, int act, int pressed, int x, int y)
{
	if(!has_init)
		return 0;
	switch(key)
	{
		case Harmattan_K_Return:
		case Harmattan_K_KP_Enter:
			if(pressed)
			{
				UI_EnterAction(NULL);
				return 1;
			}
			break;
		case Harmattan_K_BackSpace:
		case Harmattan_K_Escape:
			if(pressed)
			{
				UI_BackAction(NULL);
				return 1;
			}
			break;
		case Harmattan_K_Up:
		case Harmattan_K_w:
		case Harmattan_K_W:
			if(pressed)
			{
				UI_MoveListViewCurrentIndex(&lst, -1);
				idle_time = 0.0f;
			}
			break;
		case Harmattan_K_Down:
		case Harmattan_K_s:
		case Harmattan_K_S:
			if(pressed)
			{
				UI_MoveListViewCurrentIndex(&lst, 1);
				idle_time = 0.0f;
			}
			break;
		default:
			break;
	}
	return 0;
}

int UI_MouseFunc(int button, int pressed, int x, int y)
{
	int gl_y;
	int i;

	if(!has_init)
		return 0;

	gl_y = height - y;

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
	int gl_y;
	int gl_dy;
	int res;
	int i;
	int last_x;
	int last_gl_y;

	if(!has_init)
		return 0;

	res = 0;
	gl_y = height - y;
	gl_dy = -dy;

	if(pressed)
	{
		last_x = x - dx;
		last_gl_y = gl_y - gl_dy;

		if(UI_PointInWidget(&lst.base, x, gl_y))
		{
			res = UI_SlideListView(&lst, gl_dy);
		}
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

void UI_MakeListViewData(void)
{
	if(!has_init)
		return;
	if(data)
	{
		GLuint i;
		for(i = 0; i < data_count; i++)
		{
			FREE_PTR(data[i].text)
				FREE_PTR(data[i].args)
		}
		free(data);
	}
	if(menu_level == 0)
	{
		data_count = 3;
		data = NEW_II(list_view_data, data_count);
		GLuint i;
		for(i = 0; i < data_count; i++)
		{
			data[i].text = strdup(Game_Menu_Action[i].text);
			data[i].func = UI_EnterAction;
			data[i].args = NULL;
		}
	}
}

void UI_InitListView(void)
{
	if(!has_init)
		return;
	lst.data = data;
	lst.count = data_count;
	lst.current_index = 0;
	lst.progress = 0.0;
}

void UI_EnterAction(void *args)
{
	if(!has_init)
		return;
	if(menu_level == 0)
	{
		const void *slot = SignalSlot_GetAction(Game_Menu_Action[lst.current_index].func);
		if(slot)
			((void__func__void)slot)();
	}
}

void UI_BackAction(void *data)
{
	if(!has_init)
		return;
	if(menu_level == 0)
	{
		const void *slot = SignalSlot_GetAction(CLOSE_GAME_MENU);
		if(slot)
			((void__func__void)slot)();
	}
}

int UI_ClickFunc(int button, int x, int y)
{
	int gl_y;
	int i;

	if(!has_init)
		return 0;

	gl_y = height - y;

	if(UI_PointInWidget(&lst.base, x, gl_y))
	{
		UI_ClickListView(&lst, x - lst.base.x, gl_y - lst.base.y);
		return 1;
	}
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

void UI_GameMenuRegisterFunction(void)
{
	glk_function func;

	func = REGISTER_RENDER_FUNCTION(UI);
	Main3D_SetCurRenderPage(PAGE_NAME, &func);
}

void UI_StoreFunc(void)
{
	if(!has_init)
		return;

	if(bg.tex)
	{
		if(glIsTexture(bg.tex->texid))
			glDeleteTextures(1, &bg.tex->texid);
		free(bg.tex);
		bg.tex = NULL;
	}
}

void UI_RestoreFunc(void)
{
	if(!has_init)
		return;
	if(bg.tex)
	{
		if(glIsTexture(bg.tex->texid))
			glDeleteTextures(1, &bg.tex->texid);
		free(bg.tex);
		bg.tex = NULL;
	}
	bg.tex = new_OpenGL_texture_2d_from_buffer_with_glReadPixels(0, 0, width, height, GL_RGBA);
}

