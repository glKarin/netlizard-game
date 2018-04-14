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
#define BUTTON_ADD_X 80
#define BUTTON_ADD_Y 10
#define BUTTON_CLEAR_X 240
#define BUTTON_CLEAR_Y 10
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
#define ACTION_BUTTON_W 120
#define ACTION_BUTTON_H 60
#define BUTTON_SURE_X 550
#define BUTTON_SURE_Y 10
#define BUTTON_BACK_X 700
#define BUTTON_BACK_Y 10
#define LABEL_H 80

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
static void Menu_AddKeyMap(void);
static void Menu_BackAction(void);
static void Menu_UpdateKeyMap(void);
static void Menu_ClearKeyMap(void);
static void Menu_SetKeyMapSettingPageSize(GLsizei w, GLsizei h);

static button btn;
static button add_btn;
static button clear_btn;
static button sure_btn;
static button back_btn;
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

void Menu_SetKeyMapSettingPageSize(GLsizei w, GLsizei h)
{
	if(page_width == w && page_height == h)
		return;
	page_width = w;
	page_height = h;
	if(has_init)
	{
		UI_ResizeButton(&btn, BUTTON_W, BUTTON_H);
		UI_ResetButtonGeometry(&add_btn, BUTTON_ADD_X, BUTTON_ADD_Y, ACTION_BUTTON_W, ACTION_BUTTON_H);
		UI_ResetButtonGeometry(&clear_btn, BUTTON_CLEAR_X, BUTTON_CLEAR_Y, ACTION_BUTTON_W, ACTION_BUTTON_H);
		UI_ResetButtonGeometry(&sure_btn, BUTTON_SURE_X, BUTTON_SURE_Y, ACTION_BUTTON_W, ACTION_BUTTON_H);
		UI_ResetButtonGeometry(&back_btn, BUTTON_BACK_X, BUTTON_BACK_Y, ACTION_BUTTON_W, ACTION_BUTTON_H);
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
		if(key_state[Harmattan_K_Up] || key_state[Harmattan_K_w] || key_state[Harmattan_K_W])
			UI_MoveListViewCurrentIndex(&lst, -1);
		else if(key_state[Harmattan_K_Down] || key_state[Harmattan_K_s] || key_state[Harmattan_K_S])
			UI_MoveListViewCurrentIndex(&lst, 1);
	}
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
}

void Menu_KeyMapSettingDrawFunc(void)
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
		glScissor(tb.base.x, tb.base.y, tb.base.width, tb.base.height);
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
		oglDisable(GL_SCISSOR_TEST);

		if(!scan_mode)
		{
			glPushMatrix();
			{
				glTranslatef(add_btn.base.x, add_btn.base.y, add_btn.base.z);
				UI_RenderButton(&add_btn);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(clear_btn.base.x, clear_btn.base.y, clear_btn.base.z);
				UI_RenderButton(&clear_btn);
			}
			glPopMatrix();
		}
		else
		{
			glPushMatrix();
			{
				glTranslatef(sure_btn.base.x, sure_btn.base.y, sure_btn.base.z);
				UI_RenderButton(&sure_btn);
			}
			glPopMatrix();
		}
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
	delete_button(&add_btn);
	delete_button(&sure_btn);
	delete_button(&back_btn);
	delete_button(&clear_btn);
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
					Menu_BackAction();
					return 1;
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
	if(UI_PointInWidget(&add_btn.base, x, gl_y))
	{
		add_btn.highlight = pressed ? GL_TRUE : GL_FALSE;
		return 1;
	}
	else if(UI_PointInWidget(&clear_btn.base, x, gl_y))
	{
		clear_btn.highlight = pressed ? GL_TRUE : GL_FALSE;
		return 1;
	}
	else if(UI_PointInWidget(&sure_btn.base, x, gl_y))
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
			if(UI_PointInWidget(&add_btn.base, x, gl_y) && !UI_PointInWidget(&add_btn.base, last_x, last_gl_y))
			{
				add_btn.highlight = GL_TRUE;
				res |= 1;
			}
			else if(!UI_PointInWidget(&add_btn.base, x, gl_y) && UI_PointInWidget(&add_btn.base, last_x, last_gl_y))
			{
				add_btn.highlight = GL_FALSE;
				res |= 1;
			}
			if(UI_PointInWidget(&clear_btn.base, x, gl_y) && !UI_PointInWidget(&clear_btn.base, last_x, last_gl_y))
			{
				clear_btn.highlight = GL_TRUE;
				res |= 1;
			}
			else if(!UI_PointInWidget(&clear_btn.base, x, gl_y) && UI_PointInWidget(&clear_btn.base, last_x, last_gl_y))
			{
				clear_btn.highlight = GL_FALSE;
				res |= 1;
			}
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
		strcat(p, info -> desc);
		p += strlen(info -> desc);
		strcat(p, " : ");
		p += 3;
		int has = 0;
		int j;
		for(j = Harmattan_K_Multi_key; j < Harmattan_Total_Key; j++)
		{
			if(key_action[j] == -1)
				continue;
			if((Game_Action)key_action[j] == info -> action)
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
	strcat(p, info -> desc);
	p += strlen(info -> desc);
	strcat(p, " > :\n\n");
	p += 6;
	int index = 0;
	int j;
	for(j = Harmattan_K_Multi_key; j < Harmattan_Total_Key; j++)
	{
		if(key_action[j] == -1)
			continue;
		if((Game_Action)key_action[j] == info -> action)
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

void Menu_AddKeyMap(void)
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

void Menu_BackAction(void)
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
		if(UI_PointInWidget(&sure_btn.base, x, gl_y))
		{
			Menu_UpdateKeyMap();
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
		else if(UI_PointInWidget(&add_btn.base, x, gl_y))
		{
			Menu_AddKeyMap();
			return 1;
		}
		else if(UI_PointInWidget(&clear_btn.base, x, gl_y))
		{
			Menu_ClearKeyMap();
			return 1;
		}
	}
	if(UI_PointInWidget(&back_btn.base, x, gl_y))
	{
		Menu_BackAction();
		return 1;
	}
	return 0;
}

void Menu_InitKeyMapSetting(void)
{
	if(has_init)
		return;
	new_button(&btn, 0.0, 0.0, 0.0, BUTTON_W, BUTTON_H, 2.0, X11_COLOR(lightskyblue), X11_COLOR(green), X11_COLOR(lightseagreen), X11_COLOR(pink), X11_COLOR(darkgreen), X11_COLOR(seagreen), NULL);
	new_button(&add_btn, BUTTON_ADD_X, BUTTON_ADD_Y, 0.3, ACTION_BUTTON_W, ACTION_BUTTON_H, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(gray), "Add");
	new_button(&clear_btn, BUTTON_CLEAR_X, BUTTON_CLEAR_Y, 0.3, ACTION_BUTTON_W, ACTION_BUTTON_H, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(gray), "Clear");
	new_button(&sure_btn, BUTTON_SURE_X, BUTTON_SURE_Y, 0.3, ACTION_BUTTON_W, ACTION_BUTTON_H, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(gray), "Sure");
	new_button(&back_btn, BUTTON_BACK_X, BUTTON_BACK_Y, 0.3, ACTION_BUTTON_W, ACTION_BUTTON_H, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(gray), "Back");
	btn.fnt = &fnt;
	add_btn.fnt = &fnt;
	clear_btn.fnt = &fnt;
	sure_btn.fnt = &fnt;
	back_btn.fnt = &fnt;
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
}

void Menu_UpdateKeyMap(void)
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

void Menu_ClearKeyMap(void)
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
		if((Game_Action)key_action[j] == info -> action)
			key_action[j] = -1;
	}
	key_action[info -> def_key] = info -> action;
	Menu_MakeKeyMapListViewData(1);
	Menu_ViewKeyMap(NULL);
}
