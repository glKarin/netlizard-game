#include "menu.h"
#include "netlizard/netlizard_3d.h"
#include "gl_3d_main.h"
#include "button.h"
#include "label.h"
#include "list_view.h"
#include "action_signal_slot.h"

#define LIST_VIEW_X 0
#define LIST_VIEW_Y 100
#define LIST_VIEW_W 504
#define LIST_VIEW_H 300
#define LIST_BUTTON_W 400
#define LIST_BUTTON_H 50
#define BUTTON_SURE_X 60
#define BUTTON_SURE_Y 10
#define BUTTON_BACK_X 300
#define BUTTON_BACK_Y 10
#define BUTTON_W 200
#define BUTTON_H 60
#define ACTION_LIST_VIEW_X 550
#define ACTION_LIST_VIEW_Y 100
#define ACTION_LIST_VIEW_W 304
#define ACTION_LIST_VIEW_H 300
#define ACTION_BUTTON_W 280
#define ACTION_BUTTON_H 50
#define LABEL_H 80

#define ACTION_MENU_COUNT 7

#define IDLE_TIME_DELAY 0.4

static const struct _game_menu_action
{
	char *text;
	char *func;
} Menu_Action[] = {
	{"Character Model Chooser", OPEN_CHARACTER_MODEL_CHOOSER},
	{"Weapon Chooser", OPEN_WEAPON_CHOOSER},
	{"Key Map Setting", OPEN_KEYMAP_SETTING},
	{"Setting", OPEN_SETTING},
	{"Help", OPEN_HELP},
	{"About", OPEN_ABOUT},
	{"Quit", QUIT}
};

static int Menu_IdleEventFunc(void);
static int Menu_KeyEventFunc(int k, int a, int p, int x, int y);
static int Menu_MouseEventFunc(int b, int p, int x, int y);
static int Menu_MouseClickEventFunc(int b, int x, int y);
static int Menu_MouseMotionEventFunc(int b, int p, int x, int y, int dx, int dy);
static void Menu_DrawFunc(void);
static void Menu_ReshapeFunc(int w, int h);
static void Menu_InitFunc(void);
static void Menu_FreeFunc(void);

static void Menu_EnterAction(void *args);
static void Menu_ResetMenu(void);
static void Menu_MakeListViewData(void);
static void Menu_InitListView(void);
static void Menu_EnterSubMenu(void *);
static void Menu_BackAction(void *);
static void Menu_QuitAction(void);
static void Menu_OpenAbout(void);
static void Menu_SetPageSize(GLsizei w, GLsizei h);

static button btn;
static button sure_btn;
static button back_btn;
static button action_btn;
static list_view lst;
static list_view action_lst;
static label lb;
static GLsizei page_width = HARMATTAN_FULL_WIDTH;
static GLsizei page_height = HARMATTAN_FULL_HEIGHT;

static int menu_level = 0;
static int game = -1;
static int level = -1;
static bool_t has_init = 0;
static menu_save_state save_state = menu_init_state;

static int level_index = -1;
static int action_index = -1;
static float level_progress = 0.0;
static float action_progress = 0.0;

static list_view_data *data = NULL;
static unsigned int data_count = 0;
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
		UI_ResizeButton(&btn, LIST_BUTTON_W, LIST_BUTTON_H);
		UI_ResetButtonGeometry(&sure_btn, BUTTON_SURE_X, BUTTON_SURE_Y, BUTTON_W, BUTTON_H);
		UI_ResetButtonGeometry(&back_btn, BUTTON_BACK_X, BUTTON_BACK_Y, BUTTON_W, BUTTON_H);
		UI_ResizeButton(&action_btn, ACTION_BUTTON_W, ACTION_BUTTON_H);
		UI_ResetListViewGeometry(&lst, LIST_VIEW_X, LIST_VIEW_Y, LIST_VIEW_W, LIST_VIEW_H);
		UI_ResetListViewGeometry(&action_lst, ACTION_LIST_VIEW_X, ACTION_LIST_VIEW_Y, ACTION_LIST_VIEW_W, ACTION_LIST_VIEW_H);
		UI_ResetLabelGeometry(&lb, 0.0, page_height - LABEL_H, page_width, LABEL_H);
	}
}

int Menu_IdleEventFunc(void)
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

void Menu_InitFunc(void)
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

void Menu_DrawFunc(void)
{
	if(!has_init)
		return;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	OpenGL_Render3DOrtho(0.0, width, 0.0, height);
	{
		//glPolygonMode(GL_FRONT, GL_LINE);
		oglEnable(GL_SCISSOR_TEST);
		glScissor(lst.base.x, lst.base.y, lst.base.width, lst.base.height);
		glPushMatrix();
		{
			glTranslatef(lst.base.x, lst.base.y, lst.base.z);
			UI_RenderListView(&lst);
		}
		glPopMatrix();
		glScissor(action_lst.base.x, action_lst.base.y, action_lst.base.width, action_lst.base.height);
		glPushMatrix();
		{
			glTranslatef(action_lst.base.x, action_lst.base.y, action_lst.base.z);
			UI_RenderListView(&action_lst);
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

void Menu_ReshapeFunc(int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	if(!has_init)
		return;
	Menu_SetPageSize(w, h);
}

void Menu_FreeFunc(void)
{
	if(!has_init)
		return;
	if(save_state == menu_last_state)
	{
		level_index = lst.current_index;
		action_index = action_lst.current_index;
		level_progress = lst.progress;
		action_progress = action_lst.progress;
	}
	else
	{
		level_index = -1;
		action_index = -1;
		level_progress = 0.0;
		action_progress = 0.0;
	}

	delete_button(&btn);
	delete_button(&sure_btn);
	delete_button(&back_btn);
	delete_button(&action_btn);
	delete_label(&lb);
	delete_list_view(&lst);
	delete_list_view(&action_lst);
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
}

// for all X event pointer coord y, Using left-down as ori, like OpenGL, and not left-top of X11. so the y coord need to convert by screen height - y, and delta_y is invert.
int Menu_KeyEventFunc(int key, int act, int pressed, int x, int y)
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
	}
	return 0;
}

int Menu_MouseEventFunc(int button, int pressed, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	if(UI_PointInWidget(&sure_btn.base, x, gl_y))
	{
		sure_btn.highlight = pressed ? GL_TRUE : GL_FALSE;
		return 1;
	}
	else if(UI_PointInWidget(&back_btn.base, x, gl_y))
	{
		back_btn.highlight = pressed ? GL_TRUE : GL_FALSE;
		return 1;
	}
	return 0;
}

int Menu_MouseMotionEventFunc(int button, int pressed, int x, int y, int dx, int dy)
{
	if(!has_init)
		return 0;
	int res = 0;
	if(pressed)
	{
		int last_x = x - dx;
		int last_gl_y = height - (y - dy);
		int gl_y = height - y;
		if(UI_PointInWidget(&lst.base, x, gl_y))
		{
			res |= UI_SlideListView(&lst, -dy);
		}
		else if(UI_PointInWidget(&action_lst.base, x, gl_y))
		{
			res |= UI_SlideListView(&action_lst, -dy);
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

void Menu_RegisterFunction(void)
{
	if(!has_init)
		return;
	Main3D_SetInitFunction(Menu_InitFunc);
	Main3D_SetDrawFunction(Menu_DrawFunc);
	Main3D_SetFreeFunction(Menu_FreeFunc);
	Main3D_SetKeyEventFunction(Menu_KeyEventFunc);
	Main3D_SetIdleEventFunction(Menu_IdleEventFunc);
	Main3D_SetReshapeFunction(Menu_ReshapeFunc);
	Main3D_SetMouseEventFunction(Menu_MouseEventFunc);
	Main3D_SetMouseMotionEventFunction(Menu_MouseMotionEventFunc);
	Main3D_SetMouseClickEventFunction(Menu_MouseClickEventFunc);
	const void *slot = SignalSlot_GetAction(PLAY_MENU_MUSIC);
	if(slot)
	{
		((void__func__int)slot)(game);
	}
}

void Menu_MakeListViewData(void)
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
		data = NULL;
		data_count = 0;
	}
	if(menu_level == 0)
	{
		data = NEW_II(list_view_data, Game_Count);
		data_count = Game_Count;
		GLuint i;
		for(i = 0; i < data_count; i++)
		{
			data[i].text = strdup(Game_Names[i]);
			data[i].func = Menu_EnterSubMenu;
			data[i].args = NULL;
		}
	}
	else if(menu_level == 1)
	{
		data = NEW_II(list_view_data, Game_Level[game]);
		data_count = Game_Level[game];
		GLuint i;
		for(i = 0; i < data_count; i++)
		{
			data[i].text = strdup(Game_Level_Name[game][i]);
			data[i].func = Menu_EnterSubMenu;
			data[i].args = NULL;
		}
	}
}

void Menu_InitListView(void)
{
	if(!has_init)
		return;
	lst.data = data;
	lst.count = data_count;
	lst.current_index = 0;
	lst.progress = 0.0;
}

void Menu_EnterSubMenu(void *args)
{
	if(!has_init)
		return;
	if(menu_level == 0)
	{
		menu_level++;
		game = lst.current_index;
		Menu_MakeListViewData();
		Menu_InitListView();
		const void *slot = SignalSlot_GetAction(PLAY_MENU_MUSIC);
		if(slot)
		{
			((void__func__int)slot)(game);
		}
	}
	else if(menu_level == 1)
	{
		level = lst.current_index;
		const void *slot = SignalSlot_GetAction(OPEN_RUN_SETTING);
		if(slot)
		{
			((void__func__int_int)slot)(game, level);
		}
	}
}

void Menu_BackAction(void *args)
{
	if(!has_init)
		return;
	if(menu_level == 1)
	{
		menu_level--;
		game = -1;
		Menu_MakeListViewData();
		Menu_InitListView();
	}
}

int Menu_MouseClickEventFunc(int button, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	if(UI_PointInWidget(&lst.base, x, gl_y))
	{
		UI_ClickListView(&lst, x - lst.base.x, gl_y - lst.base.y);
		return 1;
	}
	else if(UI_PointInWidget(&sure_btn.base, x, gl_y))
	{
		Menu_EnterSubMenu(NULL);
		return 1;
	}
	else if(UI_PointInWidget(&back_btn.base, x, gl_y))
	{
		Menu_BackAction(NULL);
		return 1;
	}
	else if(UI_PointInWidget(&action_lst.base, x, gl_y))
	{
		UI_ClickListView(&action_lst, x - action_lst.base.x, gl_y - action_lst.base.y);
		return 1;
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

void Menu_InitMenu(void)
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
	new_button(&btn, 0.0, 0.0, 0.0, LIST_BUTTON_W, LIST_BUTTON_H, 2.0, X11_COLOR(lightskyblue), X11_COLOR(green), X11_COLOR(lightseagreen), X11_COLOR(pink), X11_COLOR(darkgreen), X11_COLOR(seagreen), NULL);
	new_button(&sure_btn, BUTTON_SURE_X, BUTTON_SURE_Y, 0.3, BUTTON_W, BUTTON_H, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(gray), "Sure");
	new_button(&back_btn, BUTTON_BACK_X, BUTTON_BACK_Y, 0.3, BUTTON_W, BUTTON_H, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(gray), "Back");
	new_button(&action_btn, 0.0, 0.0, 0.0, ACTION_BUTTON_W, ACTION_BUTTON_H, 2.0, X11_COLOR(lightskyblue), X11_COLOR(green), X11_COLOR(lightsteelblue), X11_COLOR(skyblue), X11_COLOR(darkgreen), X11_COLOR(steelblue), NULL);
	btn.fnt = &fnt;
	sure_btn.fnt = &fnt;
	back_btn.fnt = &fnt;
	action_btn.fnt = &fnt;
	new_list_view(&lst, LIST_VIEW_X, LIST_VIEW_Y, 0.0, LIST_VIEW_W, LIST_VIEW_H, 10, 20, 15, Color_GetColor(black_color, 0.0), X11_COLOR(lightgreen), X11_COLOR(darkgreen));
	lst.delegate.component = &btn;
	lst.delegate.update_func = UI_ButtonUpdateText;
	lst.delegate.render_func = UI_RenderButtonItem;
	lst.delegate.get_geometry_func = UI_GetWidgetGeometry;
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
	action_data_count = ACTION_MENU_COUNT;
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
	Menu_MakeListViewData();
	Menu_InitListView();
	if(save_state == menu_last_state)
	{
		lst.current_index = level_index;
		lst.progress = level_progress;
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
		menu_level = 0;
		game = -1;
	}
	level = -1;
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

void Menu_SetMenuSaveState(menu_save_state s)
{
	//if(has_init)
	save_state = s;
	if(save_state == menu_init_state)
	{
		menu_level = 0;
		game = -1;
	}
}
