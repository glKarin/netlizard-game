#include "keymap_setting.h"
#include "gl_3d_main.h"
#include "button.h"
#include "label.h"
#include "list_view.h"
#include "text_browser.h"
#include "action_signal_slot.h"
#include "game_std.h"
#include "game_util.h"

#define LIST_VIEW_X 0
#define LIST_VIEW_Y 100
#define LIST_VIEW_W 554
#define LIST_VIEW_H 300
#define BUTTON_W 400
#define BUTTON_H 40
#define TEXT_VIEW_X 600
#define TEXT_VIEW_Y 200
#define TEXT_VIEW_W 254
#define TEXT_VIEW_H 200
#define SCAN_TEXT_VIEW_X 600
#define SCAN_TEXT_VIEW_Y 100
#define SCAN_TEXT_VIEW_W 254
#define SCAN_TEXT_VIEW_H 100
#define BTN_W 120
#define BTN_H 60
#define LABEL_H 80

#define IDLE_TIME_DELAY 0.4

typedef enum _menu_action
{
	enter_action = 0,
	edit_action,
	clear_action,
	back_action,
	total_action_type
} menu_action;

static const char Scan_Label[] = "Press a key: \n";

static int Menu_KeyMapSettingIdleEventFunc(void);
static int Menu_KeyMapSettingKeyEventFunc(int k, int a, int p, int x, int y);
static int Menu_KeyMapSettingMouseEventFunc(int b, int p, int x, int y);
static int Menu_KeyMapSettingMouseClickEventFunc(int b, int x, int y);
static int Menu_KeyMapSettingMouseMotionEventFunc(int b, int p, int x, int y, int dx, int dy);
static void Menu_KeyMapSettingDrawFunc(void);
static void Menu_KeyMapSettingReshapeFunc(int w, int h);
static void Menu_KeyMapSettingInitFunc(void);
static void Menu_KeyMapSettingFreeFunc(void);

static void Menu_ResetKeyMapSetting(void);
static void Menu_MakeKeyMapListViewData(int update);
static void Menu_ViewKeyMap(void *);
static void Menu_AddKeyMap(void *data);
static void Menu_BackAction(void *data);
static void Menu_UpdateKeyMap(void *data);
static void Menu_ClearKeyMap(void *data);
static void Menu_SetKeyMapSettingPageSize(GLsizei w, GLsizei h);

static const button_initilizer Btn_Infos[] = {
	{550, 10, BTN_W, BTN_H, "Sure", Menu_UpdateKeyMap, NULL},
	{80, 10, BTN_W, BTN_H, "Edit", Menu_AddKeyMap, NULL},
	{240, 10, BTN_W, BTN_H, "Clear", Menu_ClearKeyMap, NULL},
	{700, 10, BTN_W, BTN_H, "Back", Menu_BackAction, NULL},
};

static button btn;
static button btns[total_action_type];
static list_view lst;
static label lb;
static text_browser tb;
static text_browser scan_tb;

static bool_t has_init = 0;
static bool_t scan_mode = 0;
static Game_Action scan_action = Total_Action;
static Harmattan_Key scan_key = Harmattan_Other_Key;

static list_view_data *data = NULL;
static unsigned int data_count = 0;
static GLsizei page_width = HARMATTAN_FULL_WIDTH;
static GLsizei page_height = HARMATTAN_FULL_HEIGHT;
static float idle_time = 0.0f;

void Menu_SetKeyMapSettingPageSize(GLsizei w, GLsizei h)
{
	if(page_width == w && page_height == h)
		return;
	page_width = w;
	page_height = h;
	if(has_init)
	{
		UI_ResizeButton(&btn, BUTTON_W, BUTTON_H);
		int i;
		for(i = 0; i < total_action_type; i++)
			UI_ResetButtonGeometry(btns + i, Btn_Infos[i].x, Btn_Infos[i].y, Btn_Infos[i].w, Btn_Infos[i].h);
		UI_ResetListViewGeometry(&lst, LIST_VIEW_X, LIST_VIEW_Y, LIST_VIEW_W, LIST_VIEW_H);
		UI_ResetTextBrowserGeometry(&tb, TEXT_VIEW_X, TEXT_VIEW_Y, TEXT_VIEW_W, TEXT_VIEW_H);
		UI_ResetTextBrowserGeometry(&scan_tb, SCAN_TEXT_VIEW_X, SCAN_TEXT_VIEW_Y, SCAN_TEXT_VIEW_W, SCAN_TEXT_VIEW_H);
		UI_ResetLabelGeometry(&lb, 0.0, page_height - LABEL_H, page_width, LABEL_H);
	}
}

int Menu_KeyMapSettingIdleEventFunc(void)
{
	if(!has_init)
		return 0;
	if(!scan_mode)
	{
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
	}
	else
		idle_time = 0.0f;
	return 1;
}

void Menu_KeyMapSettingInitFunc(void)
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

void Menu_KeyMapSettingDrawFunc(void)
{
	if(!has_init)
		return;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	OpenGL_Render3DOrtho(0.0, width, 0.0, height);
	{
		//glPolygonMode(GL_FRONT, GL_LINE);
		glPushMatrix();
		{
			glTranslatef(lst.base.x, lst.base.y, lst.base.z);
			UI_RenderListView(&lst);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(tb.base.x, tb.base.y, tb.base.z);
			UI_RenderTextBrowser(&tb);
		}
		glPopMatrix();
		if(scan_mode)
		{
			glScissor(scan_tb.base.x, scan_tb.base.y, scan_tb.base.width, scan_tb.base.height);
			glPushMatrix();
			{
				glTranslatef(scan_tb.base.x, scan_tb.base.y, scan_tb.base.z);
				UI_RenderTextBrowser(&scan_tb);
			}
			glPopMatrix();
		}

		if(!scan_mode)
		{
			int i;
			for(i = edit_action; i <= clear_action; i++)
			{
				glPushMatrix();
				{
					glTranslatef(btns[i].base.x, btns[i].base.y, btns[i].base.z);
					UI_RenderButton(btns + i);
				}
				glPopMatrix();
			}
		}
		else
		{
			glPushMatrix();
			{
				glTranslatef(btns[enter_action].base.x, btns[enter_action].base.y, btns[enter_action].base.z);
				UI_RenderButton(btns + enter_action);
			}
			glPopMatrix();
		}
		glPushMatrix();
		{
			glTranslatef(btns[back_action].base.x, btns[back_action].base.y, btns[back_action].base.z);
			UI_RenderButton(btns + back_action);
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

void Menu_KeyMapSettingReshapeFunc(int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	if(!has_init)
		return;
	Menu_SetKeyMapSettingPageSize(w, h);
}

void Menu_KeyMapSettingFreeFunc(void)
{
	if(!has_init)
		return;

	delete_button(&btn);
	int m;
	for(m = 0; m < total_action_type; m++)
		delete_button(btns + m);
	delete_label(&lb);
	delete_list_view(&lst);
	delete_text_browser(&tb);
	delete_text_browser(&scan_tb);
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
	Menu_ResetKeyMapSetting();
	page_width = width;
	page_height = height;
	has_init = 0;
}

// for all X event pointer coord y, Using left-down as ori, like OpenGL, and not left-top of X11. so the y coord need to convert by screen height - y, and delta_y is invert.
int Menu_KeyMapSettingKeyEventFunc(int key, int act, int pressed, int x, int y)
{
	if(!has_init)
		return 0;
	if(scan_mode)
	{
		if(pressed)
		{
			size_t len = strlen(Key_Infos[key].symbol);
			size_t llen = strlen(Scan_Label);
			char *str = NEW_II(char, llen + len + 1);
			memset(str, '\0', sizeof(char) * (llen + len + 1));
			sprintf(str, "%s%s", Scan_Label, Key_Infos[key].symbol);
			if(!scan_tb.text || strcmp(scan_tb.text, str))
				UI_SetBrowserText(&scan_tb, str);
			free(str);
			scan_key = key;
			return 1;
		}
	}
	else
	{
		switch(key)
		{
			case Harmattan_K_Return:
			case Harmattan_K_KP_Enter:
				if(pressed)
				{
					Menu_ViewKeyMap(NULL);
					return 1;
				}
				break;
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
	}
	return 0;
}

int Menu_KeyMapSettingMouseEventFunc(int button, int pressed, int x, int y)
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

int Menu_KeyMapSettingMouseMotionEventFunc(int button, int pressed, int x, int y, int dx, int dy)
{
	if(!has_init)
		return 0;
	int res = 0;
	if(pressed)
	{
		int last_x = x - dx;
		int last_gl_y = height - (y - dy);
		int gl_y = height - y;
		if(scan_mode)
		{
			if(UI_PointInWidget(&scan_tb.base, x, gl_y))
			{
				res |= UI_SlideTextBrowser(&scan_tb, -dy);
			}
			if(UI_PointInWidget(&btns[enter_action].base, x, gl_y) && !UI_PointInWidget(&btns[enter_action].base, last_x, last_gl_y))
			{
				btns[enter_action].highlight = GL_TRUE;
				res |= 1;
			}
			else if(!UI_PointInWidget(&btns[enter_action].base, x, gl_y) && UI_PointInWidget(&btns[enter_action].base, last_x, last_gl_y))
			{
				btns[enter_action].highlight = GL_FALSE;
				res |= 1;
			}
		}
		else
		{
			if(UI_PointInWidget(&lst.base, x, gl_y))
			{
				res |= UI_SlideListView(&lst, -dy);
			}
			else if(UI_PointInWidget(&tb.base, x, gl_y))
			{
				res |= UI_SlideTextBrowser(&tb, -dy);
			}
			int i;
			for(i = edit_action; i <= clear_action; i++)
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
		if(UI_PointInWidget(&btns[back_action].base, x, gl_y) && !UI_PointInWidget(&btns[back_action].base, last_x, last_gl_y))
		{
			btns[back_action].highlight = GL_TRUE;
			res |= 1;
		}
		else if(!UI_PointInWidget(&btns[back_action].base, x, gl_y) && UI_PointInWidget(&btns[back_action].base, last_x, last_gl_y))
		{
			btns[back_action].highlight = GL_FALSE;
			res |= 1;
		}
	}

	return res;
}

void Menu_KeyMapSettingRegisterFunction(void)
{
	Main3D_SetInitFunction(Menu_KeyMapSettingInitFunc);
	Main3D_SetDrawFunction(Menu_KeyMapSettingDrawFunc);
	Main3D_SetFreeFunction(Menu_KeyMapSettingFreeFunc);
	Main3D_SetKeyEventFunction(Menu_KeyMapSettingKeyEventFunc);
	Main3D_SetIdleEventFunction(Menu_KeyMapSettingIdleEventFunc);
	Main3D_SetReshapeFunction(Menu_KeyMapSettingReshapeFunc);
	Main3D_SetMouseEventFunction(Menu_KeyMapSettingMouseEventFunc);
	Main3D_SetMouseMotionEventFunction(Menu_KeyMapSettingMouseMotionEventFunc);
	Main3D_SetMouseClickEventFunction(Menu_KeyMapSettingMouseClickEventFunc);
}

void Menu_MakeKeyMapListViewData(int update)
{
	if(!has_init)
		return;
	if(update == 0)
	{
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
	}
	if(!data)
	{
		data = NEW_II(list_view_data, Total_Action);
		data_count = Total_Action;
	}
	GLuint i;
	for(i = 0; i < data_count; i++)
	{
		const action_info *info = Action_Infos + i;
		char str[200];
		memset(str, '\0', 200 * sizeof(char));
		char *p = str;
		strcat(p, info->desc);
		p += strlen(info->desc);
		strcat(p, " : ");
		p += 3;
		int has = 0;
		int j;
		for(j = Harmattan_K_Multi_key; j < Harmattan_Total_Key; j++)
		{
			if(key_action[j] == -1)
				continue;
			if((Game_Action)key_action[j] == info->action)
			{
				if(has)
				{
					strcat(p, ", ");
					p += 2;
				}
				strcat(p, Key_Infos[j].symbol);
				p += strlen(Key_Infos[j].symbol);
				has = 1;
			}
		}
		data[i].text = strdup(str);
		data[i].func = Menu_ViewKeyMap;
		data[i].args = NULL;
	}
}

void Menu_ViewKeyMap(void *args)
{
	if(!has_init)
		return;
	if(lst.current_index == -1)
		return;
	const action_info *info = Action_Infos + lst.current_index;
	char str[200];
	memset(str, '\0', 200 * sizeof(char));
	char *p = str;
	strcat(p, "< ");
	p += 2;
	strcat(p, info->desc);
	p += strlen(info->desc);
	strcat(p, " > :\n\n");
	p += 6;
	int index = 0;
	int j;
	for(j = Harmattan_K_Multi_key; j < Harmattan_Total_Key; j++)
	{
		if(key_action[j] == -1)
			continue;
		if((Game_Action)key_action[j] == info->action)
		{
			char *n = itostr(index);
			strcat(p, n);
			p += strlen(n);
			free(n);
			strcat(p, " : ");
			p += 3;
			strcat(p, Key_Infos[j].symbol);
			p += strlen(Key_Infos[j].symbol);
			strcat(p, "\n");
			p += 1;
			index++;
		}
	}

	UI_SetBrowserText(&tb, str);
}

void Menu_AddKeyMap(void *data)
{
	if(!has_init)
		return;
	if(scan_mode)
		return;
	if(lst.current_index == -1)
		return;
	scan_mode = 1;
	scan_action = Action_Infos[lst.current_index].action;
	scan_key = Harmattan_Other_Key;
	if(!scan_tb.text || strcmp(scan_tb.text, Scan_Label))
		UI_SetBrowserText(&scan_tb, Scan_Label);
	scan_tb.base.visible = GL_TRUE;
}

void Menu_BackAction(void *data)
{
	if(!has_init)
		return;
	if(scan_mode)
	{
		Menu_ResetKeyMapSetting();
		scan_tb.base.visible = GL_FALSE;
	}
	else
	{
		const void *slot = SignalSlot_GetAction(BACK_MAIN_MENU);
		if(slot)
		{
			((void__func__void)slot)();
		}
	}
}

int Menu_KeyMapSettingMouseClickEventFunc(int button, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	if(scan_mode)
	{
		if(UI_PointInWidget(&btns[enter_action].base, x, gl_y))
		{
			if(Btn_Infos[enter_action].func)
			{
				Btn_Infos[enter_action].func(Btn_Infos[enter_action].data);
			}
			return 1;
		}
	}
	else
	{
		if(UI_PointInWidget(&lst.base, x, gl_y))
		{
			UI_ClickListView(&lst, x - lst.base.x, gl_y - lst.base.y);
			return 1;
		}
		int i;
		for(i = edit_action; i <= clear_action; i++)
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
	}
	if(UI_PointInWidget(&btns[back_action].base, x, gl_y))
	{
		if(Btn_Infos[back_action].func)
		{
			Btn_Infos[back_action].func(Btn_Infos[back_action].data);
		}
		return 1;
	}
	return 0;
}

void Menu_InitKeyMapSetting(void)
{
	if(has_init)
		return;
	new_button(&btn, 0.0, 0.0, 0.0, BUTTON_W, BUTTON_H, 2.0, X11_COLOR(lightskyblue), X11_COLOR(green), X11_COLOR(lightseagreen), X11_COLOR(pink), X11_COLOR(darkgreen), X11_COLOR(seagreen), NULL);
	btn.base.clip = GL_FALSE;
	int m;
	for(m = 0; m < total_action_type; m++)
	{
		new_button(btns + m, Btn_Infos[m].x, Btn_Infos[m].y, 0.3, Btn_Infos[m].w, Btn_Infos[m].h, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(gray), Btn_Infos[m].label);
		btns[m].fnt = &fnt;
	}
	btn.fnt = &fnt;
	new_list_view(&lst, LIST_VIEW_X, LIST_VIEW_Y, 0.0, LIST_VIEW_W, LIST_VIEW_H, 10, 20, 15, Color_GetColor(black_color, 0.0), X11_COLOR(lightgreen), X11_COLOR(darkgreen));
	lst.delegate.component = &btn;
	lst.delegate.update_func = UI_ButtonUpdateText;
	lst.delegate.render_func = UI_RenderButtonItem;
	lst.delegate.get_geometry_func = UI_GetWidgetGeometry;
	new_text_browser(&tb, TEXT_VIEW_X, TEXT_VIEW_Y, 0.0, TEXT_VIEW_W, TEXT_VIEW_H, 4.0, 0.0, X11_COLOR(black), X11_COLOR(black), X11_COLOR(lightgreen), X11_COLOR(darkgreen), X11_COLOR(green), NULL);
	tb.fnt = &fnt;
	new_text_browser(&scan_tb, SCAN_TEXT_VIEW_X, SCAN_TEXT_VIEW_Y, 0.0, SCAN_TEXT_VIEW_W, SCAN_TEXT_VIEW_H, 4.0, 1.0, X11_COLOR(darkred), X11_COLOR(black), X11_COLOR(white), X11_COLOR(gray), X11_COLOR(red), NULL);
	scan_tb.fnt = &fnt;
	scan_tb.base.visible = GL_FALSE;

	new_label(&lb, 0.0, page_height - LABEL_H, 0.2, page_width, LABEL_H, 0, Color_GetColor(white_color, 0.4), X11_COLOR(green), Color_GetColor(black_color, 0.0), "Key Map Setting", NULL);
	lb.fnt = &fnt;
	has_init = 1;
	Menu_MakeKeyMapListViewData(0);
	lst.data = data;
	lst.count = data_count;
	lst.current_index = 0;
	lst.progress = 0.0;
}

void Menu_ResetKeyMapSetting(void)
{
	scan_mode = 0;
	scan_action = Total_Action;
	scan_key = Harmattan_Other_Key;
	idle_time = 0.0f;
}

void Menu_UpdateKeyMap(void *data)
{
	if(!has_init)
		return;
	if(!scan_mode)
		return;
	if(scan_action == Total_Action)
		return;
	if(scan_key == Harmattan_Other_Key)
		return;
	key_action[scan_key] = scan_action;
	Menu_MakeKeyMapListViewData(1);
	Menu_ResetKeyMapSetting();
	Menu_ViewKeyMap(NULL);
}

void Menu_ClearKeyMap(void *data)
{
	if(!has_init)
		return;
	if(scan_mode)
		return;
	if(lst.current_index == -1)
		return;
	const action_info *info = Action_Infos + lst.current_index;
	int j;
	for(j = Harmattan_K_Multi_key; j < Harmattan_Total_Key; j++)
	{
		if(key_action[j] == -1)
			continue;
		if((Game_Action)key_action[j] == info->action)
			key_action[j] = -1;
	}
	key_action[info->def_key] = info->action;
	Menu_MakeKeyMapListViewData(1);
	Menu_ViewKeyMap(NULL);
}
