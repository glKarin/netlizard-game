#include "menu.h"
#include "netlizard/netlizard_3d.h"
#include "gl_3d_main.h"
#include "button.h"
#include "label.h"
#include "list_view.h"
#include "action_signal_slot.h"

#define PAGE_NAME "MainMenu"

#define BTN_W 150
#define BTN_H 60
#define ACTION_LIST_VIEW_X 227
#define ACTION_LIST_VIEW_Y 40
#define ACTION_LIST_VIEW_W 400
#define ACTION_LIST_VIEW_H 360
#define ACTION_BUTTON_W 380
#define ACTION_BUTTON_H 50
#define LABEL_H 80

#define IDLE_TIME_DELAY 0.4
#define MAIN_MENU_MUSIC_INDEX -1

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
} Menu_Action[] = {
	{"Start Game", OPEN_GAME_LEVEL_MENU},
	{"Character Model Chooser", OPEN_CHARACTER_MODEL_CHOOSER},
	{"Weapon Chooser", OPEN_WEAPON_CHOOSER},
	{"Key Map Setting", OPEN_KEYMAP_SETTING},
	{"Setting", OPEN_SETTING},
	{"Map Viewer", OPEN_MAP_VIEWER},
	{"MDL Viewer", OPEN_MDL_VIEWER},
	{"Help", OPEN_HELP},
	{"About", OPEN_ABOUT},
	{"Old Main Menu", INIT_OLD_MAIN_MENU},
	{"File Chooser", OPEN_FILE_CHOOSER},
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
static Main3DStoreFunction_f UI_StoreFunc = NULL;
static Main3DRestoreFunction_f UI_RestoreFunc = NULL;

static void Menu_EnterAction(void *args);
static void Menu_ResetMenu(void);
static void Menu_InitListView(void);
static void Menu_EnterSubMenu(void *);
static void Menu_BackAction(void *);
static void Menu_QuitAction(void);
static void Menu_OpenAbout(void);
static void Menu_SetPageSize(GLsizei w, GLsizei h);

static const button_initilizer Btn_Infos[] = {
	{54, 10, BTN_W, BTN_H, "Sure", Menu_EnterSubMenu, NULL},
	{650, 10, BTN_W, BTN_H, "Back", Menu_BackAction, NULL},
};

static button btns[total_action_type];
static button action_btn;
static list_view action_lst;
static label lb;
static int action_index = -1;
static GLsizei page_width = HARMATTAN_FULL_WIDTH;
static GLsizei page_height = HARMATTAN_FULL_HEIGHT;

static bool_t has_init = 0;
static menu_save_state save_state = menu_init_state;
static float action_progress = 0.0;
static list_view_data *action_data = NULL;
static unsigned int action_data_count = 0;
static float idle_time = 0.0f;

void Menu_SetPageSize(GLsizei w, GLsizei h)
{
	if(page_width == w && page_height == h)
		return;
	page_width = w;
	page_height = h;
	if(has_init)
	{
		UI_ResizeButton(&action_btn, ACTION_BUTTON_W, ACTION_BUTTON_H);
		UI_ResetListViewGeometry(&action_lst, ACTION_LIST_VIEW_X, ACTION_LIST_VIEW_Y, ACTION_LIST_VIEW_W, ACTION_LIST_VIEW_H);
		UI_ResetLabelGeometry(&lb, 0.0, page_height - LABEL_H, page_width, LABEL_H);
		int i;
		for(i = 0; i < total_action_type; i++)
			UI_ResetButtonGeometry(btns + i, Btn_Infos[i].x, Btn_Infos[i].y, Btn_Infos[i].w, Btn_Infos[i].h);
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
		UI_MoveListViewCurrentIndex(&action_lst, -1);
	else if(key_state[Harmattan_K_Down] || key_state[Harmattan_K_s] || key_state[Harmattan_K_S])
		UI_MoveListViewCurrentIndex(&action_lst, 1);
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
			glTranslatef(action_lst.base.x, action_lst.base.y, action_lst.base.z);
			UI_RenderListView(&action_lst);
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
	Menu_SetPageSize(w, h);
}

void UI_FreeFunc(void)
{
	if(!has_init)
		return;
	if(save_state == menu_last_state)
	{
		action_index = action_lst.current_index;
		action_progress = action_lst.progress;
	}
	else
	{
		action_index = -1;
		action_progress = 0.0;
	}

	int m;
	for(m = 0; m < total_action_type; m++)
		delete_button(btns + m);
	delete_button(&action_btn);
	delete_label(&lb);
	delete_list_view(&action_lst);
	if(action_data)
	{
		GLuint i;
		for(i = 0; i < action_data_count; i++)
		{
			FREE_PTR(action_data[i].text)
				FREE_PTR(action_data[i].args)
		}
		free(action_data);
		action_data = NULL;
		action_data_count = 0;
	}
	Menu_ResetMenu();
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
		case Harmattan_K_Return:
		case Harmattan_K_KP_Enter:
			if(pressed)
			{
				Menu_EnterSubMenu(NULL);
				return 1;
			}
			break;
		case Harmattan_K_Control_R:
		case Harmattan_K_Control_L:
			if(pressed)
			{
				Menu_BackAction(NULL);
				return 1;
			}
			break;
		case Harmattan_K_BackSpace:
		case Harmattan_K_Escape:
			if(pressed)
			{
				Menu_QuitAction();
				return 1;
			}
			break;
		case Harmattan_K_Up:
		case Harmattan_K_w:
		case Harmattan_K_W:
			if(pressed)
			{
				UI_MoveListViewCurrentIndex(&action_lst, -1);
				idle_time = 0.0f;
			}
			break;
		case Harmattan_K_Down:
		case Harmattan_K_s:
		case Harmattan_K_S:
			if(pressed)
			{
				UI_MoveListViewCurrentIndex(&action_lst, 1);
				idle_time = 0.0f;
			}
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
		int last_x = x - dx;
		int last_gl_y = height - (y - dy);
		int gl_y = height - y;
		if(UI_PointInWidget(&action_lst.base, x, gl_y))
		{
			res |= UI_SlideListView(&action_lst, -dy);
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

void UI_NewMainMenuRegisterFunction(void)
{
	glk_function func;

	if(!has_init)
		return;

	func = REGISTER_RENDER_FUNCTION(UI);
	Main3D_InitRenderPage(PAGE_NAME, &func);

	const void *slot = SignalSlot_GetAction(PLAY_MENU_MUSIC);

	if(slot)
	{
		((void__func__int)slot)(MAIN_MENU_MUSIC_INDEX);
	}
}

void Menu_InitListView(void)
{
	if(!has_init)
		return;
}

void Menu_EnterSubMenu(void *args)
{
	if(!has_init)
		return;
	action_index = action_lst.current_index;
	const void *slot = SignalSlot_GetAction(Menu_Action[action_index].func);
	if(slot)
	{
		((void__func__void)slot)();
	}
}

void Menu_BackAction(void *args)
{
	if(!has_init)
		return;
	// exit
	Menu_QuitAction();
}

int UI_ClickFunc(int button, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	if(UI_PointInWidget(&action_lst.base, x, gl_y))
	{
		UI_ClickListView(&action_lst, x - action_lst.base.x, gl_y - action_lst.base.y);
		return 1;
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

void Menu_QuitAction(void)
{
	const void *slot = SignalSlot_GetAction(QUIT);
	if(slot)
	{
		((void__func__void)slot)();
	}
}

void Menu_OpenAbout(void)
{
	const void *slot = SignalSlot_GetAction(OPEN_ABOUT);
	if(slot)
	{
		((void__func__void)slot)();
	}
}

void UI_InitMainMenu(void)
{
	if(has_init)
		return;
	//Menu_SetPageSize(width, height);
	const void *slot = SignalSlot_GetAction(LOADING_PROGRESS_CALLBACK);
	void__func__int_int_constcharptr loading_progress_func = NULL;
	if(slot)
		loading_progress_func = (void__func__int_int_constcharptr)slot;
	if(loading_progress_func)
		loading_progress_func(0, 10, "Init main menu");
	if(loading_progress_func)
		loading_progress_func(0, 25, "Create menu component");
	new_button(&action_btn, 0.0, 0.0, 0.0, ACTION_BUTTON_W, ACTION_BUTTON_H, 2.0, X11_COLOR(lightskyblue), X11_COLOR(green), X11_COLOR(lightsteelblue), X11_COLOR(skyblue), X11_COLOR(darkgreen), X11_COLOR(steelblue), NULL);
	action_btn.base.clip = GL_FALSE;
	action_btn.fnt = &fnt;
	int m;
	for(m = 0; m < total_action_type; m++)
	{
		new_button(btns + m, Btn_Infos[m].x, Btn_Infos[m].y, 0.3, Btn_Infos[m].w, Btn_Infos[m].h, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(gray), Btn_Infos[m].label);
		btns[m].fnt = &fnt;
	}
	new_list_view(&action_lst, ACTION_LIST_VIEW_X, ACTION_LIST_VIEW_Y, 0.0, ACTION_LIST_VIEW_W, ACTION_LIST_VIEW_H, 10, 20, 15, Color_GetColor(black_color, 0.0), X11_COLOR(lightgreen), X11_COLOR(darkgreen));
	action_lst.delegate.component = &action_btn;
	action_lst.delegate.update_func = UI_ButtonUpdateText;
	action_lst.delegate.render_func = UI_RenderButtonItem;
	action_lst.delegate.get_geometry_func = UI_GetWidgetGeometry;

	if(action_data)
	{
		GLuint i;
		for(i = 0; i < action_data_count; i++)
		{
			FREE_PTR(action_data[i].text)
				FREE_PTR(action_data[i].args)
		}
		free(action_data);
	}
	action_data_count = countof(Menu_Action);
	action_data = NEW_II(list_view_data, action_data_count);
	GLuint i;
	for(i = 0; i < action_data_count; i++)
	{
		action_data[i].text = strdup(Menu_Action[i].text);
		action_data[i].func = Menu_EnterAction;
		action_data[i].args = NULL;
	}
	action_lst.data = action_data;
	action_lst.count = action_data_count;
	action_lst.current_index = 0;
	action_lst.progress = 0.0;

	new_label(&lb, 0.0, page_height - LABEL_H, 0.2, page_width, LABEL_H, 0, Color_GetColor(white_color, 0.4), X11_COLOR(green), Color_GetColor(black_color, 0.0), "NETLizard 3D Game", NULL);
	lb.fnt = &fnt;
	if(loading_progress_func)
		loading_progress_func(0, 75, "Make menu list");
	has_init = 1;
	Menu_InitListView();
	if(save_state == menu_last_state)
	{
		action_lst.current_index = action_index;
		action_lst.progress = action_progress;
	}
	if(loading_progress_func)
		loading_progress_func(0, 100, "Go to main menu");
}

void Menu_ResetMenu(void)
{
	if(save_state == menu_init_state)
	{
		action_index = -1;
	}
	page_width = width;
	page_height = height;
	idle_time = 0.0f;
}

void Menu_EnterAction(void *args)
{
	if(!has_init)
		return;
	const void *slot = SignalSlot_GetAction(Menu_Action[action_lst.current_index].func);
	if(slot)
		((void__func__void)slot)();
}

void UI_SetMainMenuSaveState(menu_save_state s)
{
	//if(has_init)
	save_state = s;
	if(save_state == menu_init_state)
	{
		action_index = -1;
	}
}
