#include "map_viewer.h"
#include "gl_3d_main.h"
#include "component/button.h"
#include "component/label.h"
#include "component/list_view.h"
#include "component/text_browser.h"
#include "action_signal_slot.h"
#include "game_std.h"
#include "game_util.h"
#include "game_setting.h"
#include "template/list_template.h"

#define PAGE_NAME "MapViewer"

#define FRUSTUM_NEAR 0.1
#define FRUSTUM_FAR 4000.0

#define MAP_LIST_VIEW_X 0
#define MAP_LIST_VIEW_Y 0
#define MAP_LIST_VIEW_W 360
#define MAP_LIST_VIEW_H 400
#define MAP_BUTTON_W 340
#define MAP_BUTTON_H 50

#define LEVEL_LIST_VIEW_X 360
#define LEVEL_LIST_VIEW_Y 0
#define LEVEL_LIST_VIEW_W 180
#define LEVEL_LIST_VIEW_H 400
#define LEVEL_BUTTON_W 160
#define LEVEL_BUTTON_H 40

#define TEXT_VIEW_X 540
#define TEXT_VIEW_Y 300
#define TEXT_VIEW_W 300
#define TEXT_VIEW_H 100
#define VIEWER_X 540
#define VIEWER_Y 80
#define VIEWER_W 300
#define VIEWER_H 220

#define BTN_W 120
#define BTN_H 60
#define LABEL_H 80

#define IDLE_TIME_DELAY 0.4

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

static void UI_ResetPage(void);
static void UI_MakeListData(void *type);
static void UI_OpenViewer(void *index);
static void UI_BackAction(void *data);
static void UI_OpenPage(void *data);
static void UI_RenderMap(void);
static int UI_SwipeViewer(int x, int y, int dx, int dy);
static void UI_SetPageSize(GLsizei w, GLsizei h);
static int UI_LoadNETLizard3DMap(void);

static const button_initilizer Btn_Infos[] = {
	{560, 10, BTN_W, BTN_H, "Sure", UI_OpenPage, NULL},
	{720, 10, BTN_W, BTN_H, "Back", UI_BackAction, NULL},
};

static MapViewerEnterAction_f enter_action_func;
static GL_NETLizard_3D_Model *map_model;
static button btn;
static button level_btn;
static button btns[total_action_type];
static list_view lst;
static list_view level_lst;
static label lb;
static text_browser tb;
static scene_3d viewer;
static const float viewer_unit = 150;
static bool_t auto_rotate = 0;

static bool_t has_init = 0;

static list_view_data *data = NULL;
static list_view_data *level_data = NULL;
static unsigned int data_count = 0;
static unsigned int level_data_count = 0;
static GLsizei page_width = HARMATTAN_FULL_WIDTH;
static GLsizei page_height = HARMATTAN_FULL_HEIGHT;
static float idle_time = 0.0f;

static int game = -1;
static int level = -1;
static int level_index = -1;
static int action_index = -1;
static float level_progress = 0.0;
static float action_progress = 0.0;

void UI_SetPageSize(GLsizei w, GLsizei h)
{
	if(page_width == w && page_height == h)
		return;
	page_width = w;
	page_height = h;
	if(has_init)
	{
		UI_ResizeButton(&btn, MAP_BUTTON_W, MAP_BUTTON_H);
		UI_ResizeButton(&level_btn, LEVEL_BUTTON_W, LEVEL_BUTTON_H);
		UI_ResetListViewGeometry(&lst, MAP_LIST_VIEW_X, MAP_LIST_VIEW_Y, MAP_LIST_VIEW_W, MAP_LIST_VIEW_H);
		UI_ResetListViewGeometry(&level_lst, LEVEL_LIST_VIEW_X, LEVEL_LIST_VIEW_Y, LEVEL_LIST_VIEW_W, LEVEL_LIST_VIEW_H);
		UI_ResetTextBrowserGeometry(&tb, TEXT_VIEW_X, TEXT_VIEW_Y, TEXT_VIEW_W, TEXT_VIEW_H);
		UI_ResetLabelGeometry(&lb, 0.0, page_height - LABEL_H, page_width, LABEL_H);
		UI_ResizeScene3D(&viewer, VIEWER_W, VIEWER_H, page_width, page_height);
		int i;
		for(i = 0; i < total_action_type; i++)
			UI_ResetButtonGeometry(btns + i, Btn_Infos[i].x, Btn_Infos[i].y, Btn_Infos[i].w, Btn_Infos[i].h);
	}
}

int UI_IdleFunc(void)
{
	if(!has_init)
		return 0;
	if(auto_rotate)
	{
		if(map_model)
		{
				viewer.rotate.zr += delta_time * viewer_unit;
		}
	}

	idle_time += delta_time;
	if(idle_time < IDLE_TIME_DELAY)
		return 1;
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
			glTranslatef(lst.base.x, lst.base.y, lst.base.z);
			UI_RenderListView(&lst);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(level_lst.base.x, level_lst.base.y, level_lst.base.z);
			UI_RenderListView(&level_lst);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(tb.base.x, tb.base.y, tb.base.z);
			UI_RenderTextBrowser(&tb);
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

	UI_RenderScene3D(&viewer);
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
	delete_button(&level_btn);
	int m;
	for(m = 0; m < total_action_type; m++)
		delete_button(btns + m);
	delete_label(&lb);
	delete_list_view(&lst);
	delete_list_view(&level_lst);
	delete_text_browser(&tb);
	delete_scene_3d(&viewer);
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
	if(level_data)
	{
		GLuint i;
		for(i = 0; i < level_data_count; i++)
		{
			FREE_PTR(level_data[i].text)
				FREE_PTR(level_data[i].args)
		}
		free(level_data);
		level_data = NULL;
		level_data_count = 0;
	}
	if(map_model)
	{
		delete_GL_NETLizard_3D_Model(map_model);
		free(map_model);
		map_model = NULL;
	}
	UI_ResetPage();
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
		/*
			 case Harmattan_K_Return:
			 case Harmattan_K_KP_Enter:
			 if(pressed)
			 {
			 UI_OpenViewer(NULL);
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
			 */
		case Harmattan_K_Control_R:
		case Harmattan_K_Control_L:
		case Harmattan_K_BackSpace:
		case Harmattan_K_Escape:
			if(pressed)
			{
				UI_BackAction(NULL);
				return 1;
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
	rect2 r = {viewer.x, viewer.y, viewer.x + viewer.width, viewer.y + viewer.height};

	if(UI_PointInRect2(&r, x, gl_y))
	{
		if(pressed)
		{
			auto_rotate = 0;
			return 1;
		}
	}
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
		if(UI_PointInWidget(&lst.base, x, gl_y))
		{
			res |= UI_SlideListView(&lst, -dy);
		}
		else if(UI_PointInWidget(&level_lst.base, x, gl_y))
		{
			res |= UI_SlideListView(&level_lst, -dy);
		}
		else if(UI_PointInWidget(&tb.base, x, gl_y))
		{
			res |= UI_SlideTextBrowser(&tb, -dy);
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

		res |= UI_SwipeViewer(x, gl_y, dx, -dy);
	}

	return res;
}

void UI_MapViewerRegisterFunction(void)
{
	glk_function func;
	if(!has_init)
		return;

	func = REGISTER_RENDER_FUNCTION(UI);
	Main3D_PushRenderPage(PAGE_NAME, &func);
}

void UI_MakeListData(void *args)
{
	GLuint i;
	int *iarg;
	int type;

	if(!has_init)
		return;
	if(!args)
		return;
	iarg = (int *)args;
	type = *iarg;
	if(type == -1)
	{
		if(data)
		{
			for(i = 0; i < data_count; i++)
			{
				FREE_PTR(data[i].text)
					FREE_PTR(data[i].args)
			}
			free(data);
			data = NULL;
			data_count = 0;
		}
		data_count = Game_Count;
		data = NEW_II(list_view_data, data_count);
		for(i = 0; i < data_count; i++)
		{
			data[i].text = strdup(Game_Names[i]);
			data[i].func = UI_MakeListData;
			int *args = NEW(int);
			*args = i;
			data[i].args = args;
		}
	}
	else
	{
		if(level_data)
		{
			for(i = 0; i < level_data_count; i++)
			{
				FREE_PTR(level_data[i].text)
					FREE_PTR(level_data[i].args)
			}
			free(level_data);
			level_data = NULL;
			level_data_count = 0;
		}
		game = lst.current_index;

		level_data_count = Game_Level[game];
		level_data = NEW_II(list_view_data, level_data_count);
		for(i = 0; i < level_data_count; i++)
		{
			level_data[i].text = strdup(Game_Level_Name[game][i]);
			level_data[i].func = UI_OpenViewer;
			int *args = NEW(int);
			*args = i;
			level_data[i].args = args;
		}
		level_lst.data = level_data;
		level_lst.count = level_data_count;
		level_lst.current_index = 0;
		level_lst.progress = 0.0;
	}
}

void UI_OpenViewer(void *args)
{
	int *index;
	char str[256];

	if(!has_init)
		return;
	if(!args)
		return;

	viewer.rotate.xr = -90.0;
	viewer.rotate.yr = 0.0;
	viewer.rotate.zr = 0.0;
	viewer.translate.xt = 0.0;
	viewer.translate.yt = 0.0;
	viewer.translate.zt = 0.0;
	auto_rotate = 0;
	UI_SetBrowserText(&tb, NULL);
	if(map_model)
	{
		delete_GL_NETLizard_3D_Model(map_model);
		free(map_model);
		map_model = NULL;
	}

	index = (int *)args;
	level = *index;
	UI_LoadNETLizard3DMap();

	memset(str, '\0', 256 * sizeof(char));
	if(map_model)
	{
		sprintf(str, "< %s - %s >\n"
				"Start postion: %.0f, %.0f, %.0f\n"
				"Start angle: %.0f, %.0f"
				, Game_Names[game], Game_Level_Name[game][level], map_model->start_pos[0], map_model->start_pos[1], map_model->start_pos[2], map_model->start_angle[0], map_model->start_angle[1]);

		if(!tb.text || strcmp(tb.text, str))
			UI_SetBrowserText(&tb, str);
	}
}

void UI_OpenPage(void *data)
{
	if(!has_init)
		return;
	if(game == -1 || level == -1)
		return;

	auto_rotate = 0;
	UI_SetBrowserText(&tb, NULL);
	if(map_model)
	{
		delete_GL_NETLizard_3D_Model(map_model);
		free(map_model);
		map_model = NULL;
	}

	if(enter_action_func)
		enter_action_func(game, level);
}

void UI_BackAction(void *data)
{
	if(!has_init)
		return;
	const void *slot = SignalSlot_GetAction(BACK_MAIN_MENU);
	if(slot)
	{
		((void__func__void)slot)();
	}
}

int UI_ClickFunc(int button, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	if(UI_PointInWidget(&lst.base, x, gl_y))
	{
		UI_ClickListView(&lst, x - lst.base.x, gl_y - lst.base.y);
		return 1;
	}
	else if(UI_PointInWidget(&level_lst.base, x, gl_y))
	{
		UI_ClickListView(&level_lst, x - level_lst.base.x, gl_y - level_lst.base.y);
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

void UI_InitMapViewer(void)
{
	if(has_init)
		return;

	new_button(&btn, 0.0, 0.0, 0.0, MAP_BUTTON_W, MAP_BUTTON_H, 2.0, X11_COLOR(lightskyblue), X11_COLOR(green), X11_COLOR(lightseagreen), X11_COLOR(pink), X11_COLOR(darkgreen), X11_COLOR(seagreen), NULL);
	btn.base.clip = GL_FALSE;
	new_button(&level_btn, 0.0, 0.0, 0.0, LEVEL_BUTTON_W, LEVEL_BUTTON_H, 2.0, X11_COLOR(lightskyblue), X11_COLOR(green), X11_COLOR(lightseagreen), X11_COLOR(pink), X11_COLOR(darkgreen), X11_COLOR(seagreen), NULL);
	level_btn.base.clip = GL_FALSE;
	int m;
	for(m = 0; m < total_action_type; m++)
	{
		new_button(btns + m, Btn_Infos[m].x, Btn_Infos[m].y, 0.3, Btn_Infos[m].w, Btn_Infos[m].h, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(gray), Btn_Infos[m].label);
		btns[m].fnt = &fnt;
	}
	btn.fnt = &fnt;
	level_btn.fnt = &fnt;
	new_list_view(&lst, MAP_LIST_VIEW_X, MAP_LIST_VIEW_Y, 0.0, MAP_LIST_VIEW_W, MAP_LIST_VIEW_H, 10, 20, 15, Color_GetColor(black_color, 0.0), X11_COLOR(lightgreen), X11_COLOR(darkgreen));
	lst.delegate.component = &btn;
	lst.delegate.update_func = UI_ButtonUpdateText;
	lst.delegate.render_func = UI_RenderButtonItem;
	lst.delegate.get_geometry_func = UI_GetWidgetGeometry;

	new_list_view(&level_lst, LEVEL_LIST_VIEW_X, LEVEL_LIST_VIEW_Y, 0.0, LEVEL_LIST_VIEW_W, LEVEL_LIST_VIEW_H, 10, 20, 15, Color_GetColor(black_color, 0.0), X11_COLOR(lightgreen), X11_COLOR(darkgreen));
	level_lst.delegate.component = &level_btn;
	level_lst.delegate.update_func = UI_ButtonUpdateText;
	level_lst.delegate.render_func = UI_RenderButtonItem;
	level_lst.delegate.get_geometry_func = UI_GetWidgetGeometry;
	new_text_browser(&tb, TEXT_VIEW_X, TEXT_VIEW_Y, 0.0, TEXT_VIEW_W, TEXT_VIEW_H, 4.0, 2.0, X11_COLOR(orange), X11_COLOR(black), X11_COLOR(lightgreen), X11_COLOR(darkgreen), X11_COLOR(green), NULL);
	tb.fnt = &fnt;
	new_scene_3d(&viewer, VIEWER_X, VIEWER_Y, 0.0, VIEWER_W, VIEWER_H, left_bottom_anchor_type, X11_COLOR(black), NULL, 45.0, width, height, FRUSTUM_NEAR, FRUSTUM_FAR, UI_RenderMap);

	new_label(&lb, 0.0, page_height - LABEL_H, 0.2, page_width, LABEL_H, 0, Color_GetColor(white_color, 0.4), X11_COLOR(green), Color_GetColor(black_color, 0.0), "Map Viewer", NULL);
	lb.fnt = &fnt;
	has_init = 1;
	game = -1;
	UI_MakeListData(&game);
	lst.data = data;
	lst.count = data_count;
	lst.current_index = 0;
	lst.progress = 0.0;
	map_model = NULL;
}

void UI_ResetPage(void)
{
	page_width = width;
	page_height = height;
	auto_rotate = 0;
	game = -1;
	level = -1;
	idle_time = 0.0f;
}

void UI_RenderMap(void)
{
	if(!has_init)
		return;
	if(!map_model)
		return;

	glPushMatrix();
	{
		NETLizard_RenderGL3DModel(map_model);
	}
	glPopMatrix();
}

int UI_SwipeViewer(int x, int y, int dx, int dy)
{
	if(!has_init)
		return 0;
	if(!map_model)
		return;

	rect2 r = {viewer.x, viewer.y, viewer.x + viewer.width, viewer.y + viewer.height};
	int last_x = x - dx;
	int last_y = y - dy;
	if(UI_PointInRect2(&r, x, y) && UI_PointInRect2(&r, last_x, last_y))
	{
		auto_rotate = 0;
		viewer.rotate.xr = Algo_FormatAngle(viewer.rotate.xr + -dy);
		viewer.rotate.zr = Algo_FormatAngle(viewer.rotate.zr + dx);
		return 1;
	}
	return 0;
}

int UI_LoadNETLizard3DMap(void)
{
	char *g;
	char *lvl;
	int lv;
	size_t len;

	if(game == -1 || level == -1)
		return 0;

	g = NULL;
	lvl = NULL;
	lv = -1;
	
	switch(game)
	{
		case nl_racing_evolution_3d:
			//g = strdup("re3d");
			break;
		case nl_contr_terrorism_3d:
			g = strdup("ct3d");
			break;
		case nl_army_ranger_3d:
			g = strdup("specnaz3d");
			break;
		case nl_contr_terrorism_3d_episode_2:
			g = strdup("ct3dep2");
			break;
		case nl_shadow_of_egypt_3d:
			g = strdup("egypt3d");
			break;
		case nl_clone_3d:
			g = strdup("clone3d");
			break;
		case nl_contr_terrorism_3d_episode_3:
			g = strdup("ct3dep3");
			break;
		default:
			break;
	}
	if(!g)
		return;
	len = strlen(g) + 1 + 3 + 2 + 4 + 1 + strlen(_KARIN_GAME_DIR) + 1;
	lvl = NEW_II(char, len);
	memset(lvl, '\0', sizeof(char) * len);
	if(game == 4)
	{
		lv = level;
		if(level <= 17)
			sprintf(lvl, "%s/%s/lvl%d.png", _KARIN_GAME_DIR, g, lv);
		else
			sprintf(lvl, "%s/%s/%s.png", _KARIN_GAME_DIR, g, "dm1");
	}
	else
	{
		lv = level + 1;
		sprintf(lvl, "%s/%s/lvl%d.png", _KARIN_GAME_DIR, g, lv);
	}
	char *str = NEW_II(char, strlen(Game_Names[game]) + 3 + 2 + 1 + 1 + strlen(Game_Level_Name[game][level]) + 1);
	sprintf(str, "%s - %d. %s", Game_Names[game], lv, Game_Level_Name[game][level]);
	free(str);

	switch(game)
	{
		case nl_contr_terrorism_3d:
			map_model = NETLizard_ReadGLCT3DMapModelFile(lvl, level);
			break;
		case nl_army_ranger_3d:
			map_model = NETLizard_ReadGLSpecnaz3DMapModelFile(lvl, level);
			break;
		case nl_contr_terrorism_3d_episode_2:
			map_model = NETLizard_ReadGLCT3DEp2MapModelFile(lvl, level);
			break;
		case nl_shadow_of_egypt_3d:
			map_model = NETLizard_ReadGLEgpyt3DMapModelFile(lvl);
			break;
		case nl_clone_3d:
			map_model = NETLizard_ReadGLClone3DMapModelFile(lvl);
			break;
		case nl_contr_terrorism_3d_episode_3:
			map_model = NETLizard_ReadGLCT3DEp3MapModelFile(lvl, level);
			break;
		default:
			break;
	}
	if(map_model)
	{
		NETLizard_MakeGL23DModel(map_model);
		//bg.tex = map_model->bg_tex;
		//Viewer_LoadNETLizard3DMapEvent();

		viewer.translate.xt = -map_model->start_pos[0];
		viewer.translate.yt = -map_model->start_pos[2];
		viewer.translate.zt = map_model->start_pos[1];
		viewer.rotate.yr = Algo_FormatAngle(map_model->start_angle[1] - 180.0);
		viewer.rotate.zr = -90;
		viewer.far = FRUSTUM_FAR;
		nl_vector3_t min = {0.0, 0.0, 0.0};
		nl_vector3_t max = {0.0, 0.0, 0.0};
		Algo_GetNETLizard3DMapRange(map_model, NULL, 0, &min, &max);
#ifndef _HARMATTAN_OPENGL
		viewer.far = KARIN_MAX(max.y - min.y, (KARIN_MAX(max.x - min.x, max.z - min.z)));
#endif
	}

	free(lvl);
	free(g);
	return 1;
}

void UI_SetMapViewerEnterActionFunction(MapViewerEnterAction_f f)
{
	enter_action_func = f;
}
