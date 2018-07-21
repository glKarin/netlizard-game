#include "mdl_viewer.h"
#include "gl_3d_main.h"
#include "component/button.h"
#include "component/label.h"
#include "component/list_view.h"
#include "component/text_browser.h"
#include "action_signal_slot.h"
#include "game_std.h"
#include "game_util.h"
#include "game_setting.h"
#include "csol/hlsdk.h"

#define MODEL_LIST_VIEW_X 0
#define MODEL_LIST_VIEW_Y 140
#define MODEL_LIST_VIEW_W 277
#define MODEL_LIST_VIEW_H 260
#define MODEL_BUTTON_W 250
#define MODEL_BUTTON_H 40

#define ANIMATION_LIST_VIEW_X 577
#define ANIMATION_LIST_VIEW_Y 140
#define ANIMATION_LIST_VIEW_W 277
#define ANIMATION_LIST_VIEW_H 260
#define ANIMATION_BUTTON_W 250
#define ANIMATION_BUTTON_H 40

#define NAME_LABEL_X 0
#define NAME_LABEL_Y 400
#define NAME_LABEL_W 854
#define NAME_LABEL_H 20
#define ANIMATION_VIEW_X 277
#define ANIMATION_VIEW_Y 0
#define ANIMATION_VIEW_W 300
#define ANIMATION_VIEW_H 400

#define ACTION_BUTTON_W 120
#define ACTION_BUTTON_H 60
#define BTN_W 60
#define BTN_H 60
#define LABEL_H 80

#define IDLE_TIME_DELAY 0.4
#define MDL_COUNT 16
#define MDL_SCALE 4.0
#define MDL_SCALE_UNIT 2.0
#define MDL_ROTATE_UNIT 90.0
#define MDL_TRANSLATE_UNIT 400.0
#define MDL_SCALE_MIN 0.1
#define MDL_SCALE_MAX 20.0

#define MDL_ROTATE_X -90.0
#define MDL_ROTATE_Y 0.0
#define MDL_ROTATE_Z 0.0
#define MDL_TRANSLATE_X 0.0
#define MDL_TRANSLATE_Y -90.0
#define MDL_TRANSLATE_Z 0.0

typedef enum _menu_action
{
	zoom_out_action = 0,
	zoom_in_action,
	move_forward_action,
	move_backward_action,
	move_left_action,
	move_right_action,
	move_up_action,
	move_down_action,
	turn_up_action,
	turn_down_action,
	turn_left_action,
	turn_right_action,
	back_to_menu_action,
	total_action_type
} menu_action;

typedef struct _mdl_seq_info
{
	int index;
	char *name;
} mdl_seq_info;

static const char *MDL_Names[] = {
	"Natasha (Fashion edition)",
	"ChoiJiYoon",
	"Jessica",
	"Jessica (Soilder edition)",
	"Lucia",

	"Terror",
	"Leet",
	"Arctic",
	"Guerilla",
	"Militia",
	"Leet 2",
	
	"Urban",
	"GSG9",
	"SAS",
	"GIGN",
	"Specnaz",
};

static const char *MDL_Paths[] = {
	_KARIN_RESOURCE_DIR"resource/model/Girl/natasha2.mdl",
	_KARIN_RESOURCE_DIR"resource/model/Girl/choijiyoon.mdl",
	_KARIN_RESOURCE_DIR"resource/model/Girl/jennifer.mdl",
	_KARIN_RESOURCE_DIR"resource/model/Girl/jennifer2.mdl",
	_KARIN_RESOURCE_DIR"resource/model/Girl/marinegirl.mdl",

	_KARIN_RESOURCE_DIR"resource/model/TR/terror.mdl",
	_KARIN_RESOURCE_DIR"resource/model/TR/leet.mdl",
	_KARIN_RESOURCE_DIR"resource/model/TR/arctic.mdl",
	_KARIN_RESOURCE_DIR"resource/model/TR/guerilla.mdl",
	_KARIN_RESOURCE_DIR"resource/model/TR/militia.mdl",
	_KARIN_RESOURCE_DIR"resource/model/TR/leet2.mdl",

	_KARIN_RESOURCE_DIR"resource/model/CT/urban.mdl",
	_KARIN_RESOURCE_DIR"resource/model/CT/gsg9.mdl",
	_KARIN_RESOURCE_DIR"resource/model/CT/sas.mdl",
	_KARIN_RESOURCE_DIR"resource/model/CT/gign.mdl",
	_KARIN_RESOURCE_DIR"resource/model/CT/spetsnaz.mdl",
};

static StudioModel *model_list = NULL; 
static float direction[3] = {0.0, 0.0, -1.0};
static float up[3] = {0.0, 1.0, 0.0};
static float scale = MDL_SCALE;
static unsigned actions[back_to_menu_action] = { 0 };

static void Menu_ResetMdlViewerTransform(void *data);
static void Menu_ComputeDirection(void);
static void Menu_TurnLeft(void *data);
static void Menu_TurnRight(void *data);
static void Menu_TurnUp(void *data);
static void Menu_TurnDown(void *data);
static void Menu_Forward(void *data);
static void Menu_Backward(void *data);
static void Menu_MoveLeft(void *data);
static void Menu_MoveRight(void *data);
static void Menu_MoveUp(void *data);
static void Menu_MoveDown(void *data);
static void Menu_IncrScale(void *data);
static void Menu_DecrScale(void *data);
static void Menu_SetActionState(menu_action action, unsigned state);
static int Menu_MDLViewerIdleEventFunc(void);
static int Menu_MDLViewerKeyEventFunc(int k, int a, int p, int x, int y);
static int Menu_MDLViewerMouseEventFunc(int b, int p, int x, int y);
static int Menu_MDLViewerMouseClickEventFunc(int b, int x, int y);
static int Menu_MDLViewerMouseMotionEventFunc(int b, int p, int x, int y, int dx, int dy);
static void Menu_MDLViewerDrawFunc(void);
static void Menu_MDLViewerReshapeFunc(int w, int h);
static void Menu_MDLViewerInitFunc(void);
static void Menu_MDLViewerFreeFunc(void);

static void Menu_ResetMdlViewer(void);
static void Menu_MakeListViewData(void);
static void Menu_ViewMDL(void *index);
static void Menu_BackAction(void *data);
static void Menu_RenderCharacterModel(void);
static int Menu_SwipeMDL(int x, int y, int dx, int dy);
static void Menu_UpdateAnimation(void *index);
static void Menu_PlayAnimation(float delta);
static void Menu_SetMDLViewerPageSize(GLsizei w, GLsizei h);

static const button_initilizer Btn_Infos[] = {
	{724, 70, BTN_W, BTN_H, "-", Menu_DecrScale, NULL},
	{584, 70, BTN_W, BTN_H, "+", Menu_IncrScale, NULL},
	{100, 70, BTN_W, BTN_H, "W", Menu_Forward, NULL},
	{100, 0, BTN_W, BTN_H, "S", Menu_Backward, NULL},
	{20, 0, BTN_W, BTN_H, "A", Menu_MoveLeft, NULL},
	{180, 0, BTN_W, BTN_H, "D", Menu_MoveRight, NULL},
	{20, 70, BTN_W, BTN_H, "Q", Menu_MoveDown, NULL},
	{180, 70, BTN_W, BTN_H, "E", Menu_MoveUp, NULL},
	{654, 70, BTN_W, BTN_H, "Up", Menu_TurnUp, NULL},
	{654, 0, BTN_W, BTN_H, "Down", Menu_TurnDown, NULL},
	{584, 0, BTN_W, BTN_H, "Left", Menu_TurnLeft, NULL},
	{724, 0, BTN_W, BTN_H, "Right", Menu_TurnRight, NULL},
	{794, 35, BTN_W, BTN_H, "Back", Menu_BackAction, NULL},
};

static button btn;
static button action_btn;

static button btns[total_action_type];

static list_view lst;
static list_view action_lst;
static label lb;
static label name_lb;
static scene_3d model_view;
static const float model_view_unit = 150;

static bool_t has_init = 0;
static int current_mdl = -1;

static list_view_data *data = NULL;
static list_view_data *action_data = NULL;
static unsigned int data_count = 0;
static unsigned int action_data_count = 0;
static GLsizei page_width = HARMATTAN_FULL_WIDTH;
static GLsizei page_height = HARMATTAN_FULL_HEIGHT;
static float idle_time = 0.0f;

void Menu_SetMDLViewerPageSize(GLsizei w, GLsizei h)
{
	if(page_width == w && page_height == h)
		return;
	page_width = w;
	page_height = h;
	if(has_init)
	{
		UI_ResizeButton(&btn, MODEL_BUTTON_W, MODEL_BUTTON_H);
		UI_ResizeButton(&action_btn, ANIMATION_BUTTON_W, ANIMATION_BUTTON_H);
		UI_ResetListViewGeometry(&lst, MODEL_LIST_VIEW_X, MODEL_LIST_VIEW_Y, MODEL_LIST_VIEW_W, MODEL_LIST_VIEW_H);
		UI_ResetListViewGeometry(&action_lst, ANIMATION_LIST_VIEW_X, ANIMATION_LIST_VIEW_Y, ANIMATION_LIST_VIEW_W, ANIMATION_LIST_VIEW_H);
		UI_ResetLabelGeometry(&name_lb, NAME_LABEL_X, NAME_LABEL_Y, NAME_LABEL_W, NAME_LABEL_H);
		UI_ResetLabelGeometry(&lb, 0.0, page_height - LABEL_H, page_width, LABEL_H);
		UI_ResizeScene3D(&model_view, ANIMATION_VIEW_W, ANIMATION_VIEW_H, page_width, page_height);
		int i;
		for(i = 0; i < total_action_type; i++)
			UI_ResetButtonGeometry(btns + i, Btn_Infos[i].x, Btn_Infos[i].y, Btn_Infos[i].w, Btn_Infos[i].h);
	}
}

int Menu_MDLViewerIdleEventFunc(void)
{
	if(!has_init)
		return 0;
	Menu_PlayAnimation(delta_time);
	int i;
	for(i = 0; i < back_to_menu_action; i++)
	{
		if(actions[i] && Btn_Infos[i].func)
		{
			Btn_Infos[i].func(Btn_Infos[i].data);
		}
	}

	idle_time += delta_time;
	if(idle_time < IDLE_TIME_DELAY)
		return 1;
	while(idle_time - IDLE_TIME_DELAY > 0.0f)
		idle_time -= IDLE_TIME_DELAY;
	if(key_state[Harmattan_K_p] || key_state[Harmattan_K_P])
		UI_MoveListViewCurrentIndex(&lst, -1);
	else if(key_state[Harmattan_K_n] || key_state[Harmattan_K_N])
		UI_MoveListViewCurrentIndex(&lst, 1);
	else
		idle_time = 0.0f;
	return 1;
}

void Menu_MDLViewerInitFunc(void)
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

void Menu_MDLViewerDrawFunc(void)
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
		glPushMatrix();
		{
			glTranslatef(name_lb.base.x, name_lb.base.y, name_lb.base.z);
			UI_RenderLabel(&name_lb);
		}
		glPopMatrix();
	}

	UI_RenderScene3D(&model_view);
}

void Menu_MDLViewerReshapeFunc(int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	if(!has_init)
		return;
	Menu_SetMDLViewerPageSize(w, h);
}

void Menu_MDLViewerFreeFunc(void)
{
	if(!has_init)
		return;

	int m;
	for(m = 0; m < total_action_type; m++)
		delete_button(btns + m);
	delete_button(&btn);
	delete_button(&action_btn);
	delete_label(&lb);
	delete_label(&name_lb);
	delete_list_view(&lst);
	delete_list_view(&action_lst);
	delete_scene_3d(&model_view);
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
	if(model_list)
	{
		int i;
		for(i = 0; i < MDL_COUNT; i++)
		{
			FreeModel(model_list + i);
		}
		free(model_list);
		model_list = NULL;
	}
	Menu_ResetMdlViewer();
	has_init = 0;
}

// for all X event pointer coord y, Using left-down as ori, like OpenGL, and not left-top of X11. so the y coord need to convert by screen height - y, and delta_y is invert.
int Menu_MDLViewerKeyEventFunc(int key, int act, int pressed, int x, int y)
{
	if(!has_init)
		return 0;
	switch(key)
	{
		case Harmattan_K_Return:
		case Harmattan_K_KP_Enter:
			if(pressed)
			{
				Menu_ResetMdlViewerTransform(NULL);
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
			Menu_SetActionState(turn_up_action, pressed);
			break;
		case Harmattan_K_Down:
			Menu_SetActionState(turn_down_action, pressed);
			break;
		case Harmattan_K_Left:
			Menu_SetActionState(turn_left_action, pressed);
			break;
		case Harmattan_K_Right:
			Menu_SetActionState(turn_right_action, pressed);
			break;
		case Harmattan_K_w:
		case Harmattan_K_W:
			Menu_SetActionState(move_forward_action, pressed);
			break;
		case Harmattan_K_s:
		case Harmattan_K_S:
			Menu_SetActionState(move_backward_action, pressed);
			break;
		case Harmattan_K_a:
		case Harmattan_K_A:
			Menu_SetActionState(move_left_action, pressed);
			break;
		case Harmattan_K_d:
		case Harmattan_K_D:
			Menu_SetActionState(move_right_action, pressed);
			break;
		case Harmattan_K_q:
		case Harmattan_K_Q:
			Menu_SetActionState(move_up_action, pressed);
			break;
		case Harmattan_K_e:
		case Harmattan_K_E:
			Menu_SetActionState(move_down_action, pressed);
			break;
		case Harmattan_K_i:
		case Harmattan_K_I:
			Menu_SetActionState(zoom_out_action, pressed);
			break;
		case Harmattan_K_o:
		case Harmattan_K_O:
			Menu_SetActionState(zoom_in_action, pressed);
			break;
		case Harmattan_K_p:
		case Harmattan_K_P:
			if(pressed)
			{
				UI_MoveListViewCurrentIndex(&lst, -1);
				idle_time = 0.0f;
			}
			break;
		case Harmattan_K_n:
		case Harmattan_K_N:
			if(pressed)
			{
				UI_MoveListViewCurrentIndex(&lst, 1);
				idle_time = 0.0f;
			}
			break;
	}
	return 0;
}

int Menu_MDLViewerMouseEventFunc(int button, int pressed, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	rect2 r = {model_view.x, model_view.y, model_view.x + model_view.width, model_view.y + model_view.height};

	if(UI_PointInRect2(&r, x, gl_y))
	{
		if(pressed)
		{
			// TODO ???
			return 1;
		}
	}
	int i;
	for(i = 0; i < back_to_menu_action; i++)
	{
		if(UI_PointInWidget(&btns[i].base, x, gl_y))
		{
			btns[i].highlight = pressed ? GL_TRUE : GL_FALSE;
			Menu_SetActionState(i, pressed);
			return 1;
		}
	}
	return 0;
}

int Menu_MDLViewerMouseMotionEventFunc(int button, int pressed, int x, int y, int dx, int dy)
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
		int i;
		for(i = 0; i < total_action_type; i++)
		{
			if(UI_PointInWidget(&btns[i].base, x, gl_y) && !UI_PointInWidget(&btns[i].base, last_x, last_gl_y))
			{
				btns[i].highlight = GL_TRUE;
				//Menu_SetActionState(i, GL_TRUE);
				res |= 1;
			}
			else if(!UI_PointInWidget(&btns[i].base, x, gl_y) && UI_PointInWidget(&btns[i].base, last_x, last_gl_y))
			{
				btns[i].highlight = GL_FALSE;
				//Menu_SetActionState(i, GL_FALSE);
				res |= 1;
			}
		}

		res |= Menu_SwipeMDL(x, gl_y, dx, -dy);
	}

	return res;
}

void Menu_MDLViewerRegisterFunction(void)
{
	if(!has_init)
		return;
	Main3D_SetInitFunction(Menu_MDLViewerInitFunc);
	Main3D_SetDrawFunction(Menu_MDLViewerDrawFunc);
	Main3D_SetFreeFunction(Menu_MDLViewerFreeFunc);
	Main3D_SetKeyEventFunction(Menu_MDLViewerKeyEventFunc);
	Main3D_SetIdleEventFunction(Menu_MDLViewerIdleEventFunc);
	Main3D_SetReshapeFunction(Menu_MDLViewerReshapeFunc);
	Main3D_SetMouseEventFunction(Menu_MDLViewerMouseEventFunc);
	Main3D_SetMouseMotionEventFunction(Menu_MDLViewerMouseMotionEventFunc);
	Main3D_SetMouseClickEventFunction(Menu_MDLViewerMouseClickEventFunc);
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
	data_count = MDL_COUNT;
	data = NEW_II(list_view_data, data_count);
	GLuint i;
	for(i = 0; i < data_count; i++)
	{
		data[i].text = strdup(MDL_Names[i]);
		data[i].func = Menu_ViewMDL;
		int *args = NEW(int);
		*args = i;
		data[i].args = args;
	}
}

void Menu_ViewMDL(void *args)
{
	if(!has_init)
		return;
	if(!args)
		return;
	int *index = (int *)args;
	current_mdl = *index;
	if(!name_lb.text || strcmp(name_lb.text, MDL_Names[current_mdl]))
	{
		SET_TEXT(name_lb.text, MDL_Names[current_mdl]);
	}
	// TODO global
	Menu_ResetMdlViewerTransform(NULL);
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
		action_lst.current_index = -1;
	}
	char **names = NULL;
	unsigned int count = 0;
	names = GetSequenceNames(model_list + current_mdl, &count);
	if(names)
	{
		action_data_count = count;
		action_data = NEW_II(list_view_data, action_data_count);
		unsigned int i;
		for(i = 0; i < count; i++)
		{
			action_data[i].text = names[i];
			action_data[i].func = Menu_UpdateAnimation;
			mdl_seq_info *args = NEW(mdl_seq_info);
			args->index = i;
			args->name = names[i];
			action_data[i].args = args;
		}
		action_lst.data = action_data;
		action_lst.count = action_data_count;
		action_lst.current_index = 0;
		action_lst.progress = 0.0;
		Menu_UpdateAnimation(action_data[0].args);
		free(names);
	}
}

void Menu_BackAction(void *data)
{
	if(!has_init)
		return;
	const void *slot = SignalSlot_GetAction(BACK_MAIN_MENU);
	if(slot)
	{
		((void__func__void)slot)();
	}
}

int Menu_MDLViewerMouseClickEventFunc(int button, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	if(UI_PointInWidget(&lst.base, x, gl_y))
	{
		UI_ClickListView(&lst, x - lst.base.x, gl_y - lst.base.y);
		return 1;
	}
	else if(UI_PointInWidget(&action_lst.base, x, gl_y))
	{
		UI_ClickListView(&action_lst, x - action_lst.base.x, gl_y - action_lst.base.y);
		return 1;
	}
	int i;
	for(i = back_to_menu_action; i < total_action_type; i++)
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

void Menu_InitMDLViewer(void)
{
	if(has_init)
		return;
	model_list = NEW_II(StudioModel, MDL_COUNT);
	int i;
	for(i = 0; i < MDL_COUNT; i++)
		Init(model_list + i, MDL_Paths[i]);

	new_button(&btn, 0.0, 0.0, 0.0, MODEL_BUTTON_W, MODEL_BUTTON_H, 2.0, X11_COLOR(lightskyblue), X11_COLOR(green), X11_COLOR(lightseagreen), X11_COLOR(pink), X11_COLOR(darkgreen), X11_COLOR(seagreen), NULL);
	btn.base.clip = GL_FALSE;
	new_button(&action_btn, 0.0, 0.0, 0.0, ANIMATION_BUTTON_W, ANIMATION_BUTTON_H, 2.0, X11_COLOR(lightskyblue), X11_COLOR(green), X11_COLOR(lightseagreen), X11_COLOR(pink), X11_COLOR(darkgreen), X11_COLOR(seagreen), NULL);
	action_btn.base.clip = GL_FALSE;
	for(i = 0; i < total_action_type; i++)
	{
		new_button(btns + i, Btn_Infos[i].x, Btn_Infos[i].y, 0.3, Btn_Infos[i].w, Btn_Infos[i].h, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(gray), Btn_Infos[i].label);
		btns[i].fnt = &fnt;
	}
	btn.fnt = &fnt;

	action_btn.fnt = &fnt;
	new_list_view(&lst, MODEL_LIST_VIEW_X, MODEL_LIST_VIEW_Y, 0.0, MODEL_LIST_VIEW_W, MODEL_LIST_VIEW_H, 10, 20, 15, Color_GetColor(black_color, 0.0), X11_COLOR(lightgreen), X11_COLOR(darkgreen));
	lst.delegate.component = &btn;
	lst.delegate.update_func = UI_ButtonUpdateText;
	lst.delegate.render_func = UI_RenderButtonItem;
	lst.delegate.get_geometry_func = UI_GetWidgetGeometry;

	new_list_view(&action_lst, ANIMATION_LIST_VIEW_X, ANIMATION_LIST_VIEW_Y, 0.0, ANIMATION_LIST_VIEW_W, ANIMATION_LIST_VIEW_H, 10, 20, 15, Color_GetColor(black_color, 0.0), X11_COLOR(lightgreen), X11_COLOR(darkgreen));
	action_lst.delegate.component = &action_btn;
	action_lst.delegate.update_func = UI_ButtonUpdateText;
	action_lst.delegate.render_func = UI_RenderButtonItem;
	action_lst.delegate.get_geometry_func = UI_GetWidgetGeometry;
	new_scene_3d(&model_view, ANIMATION_VIEW_X, ANIMATION_VIEW_Y, 0.0, ANIMATION_VIEW_W, ANIMATION_VIEW_H, left_bottom_anchor_type, X11_COLOR(white), NULL, 45.0, page_width, page_height, 0.1, 20000.0, Menu_RenderCharacterModel);

	new_label(&lb, 0.0, page_height - LABEL_H, 0.2, page_width, LABEL_H, 0, Color_GetColor(white_color, 0.4), X11_COLOR(green), Color_GetColor(black_color, 0.0), "CSOL MDL Viewer", NULL);
	lb.fnt = &fnt;
	new_label(&name_lb, NAME_LABEL_X, NAME_LABEL_Y, 0.2, NAME_LABEL_W, NAME_LABEL_H, 0, Color_GetColor(white_color, 0.0), X11_COLOR(green), Color_GetColor(black_color, 0.0), NULL, NULL);
	name_lb.fnt = &fnt;
	has_init = 1;
	Menu_MakeListViewData();
	lst.data = data;
	lst.count = data_count;
	lst.current_index = 0;
	lst.progress = 0.0;

	action_lst.data = action_data;
	action_lst.count = action_data_count;
	action_lst.current_index = 0;
	action_lst.progress = 0.0;

	current_mdl = 0;
	Menu_ViewMDL(&current_mdl);
}

void Menu_ResetMdlViewer(void)
{
	current_mdl = -1;
	page_width = width;
	page_height = height;
	idle_time = 0.0f;
}

void Menu_RenderCharacterModel(void)
{
	if(!has_init)
		return;
	if(current_mdl == -1)
		return;
	glPushMatrix();
	{
		glTranslatef(0.0, 0.0, (float)HL_MDL_Z_TRANSLATE);
		glRotatef(90.0, 0.0f, 0.0f, 1.0f);
		glRotatef(180.0, 0.0f, 0.0f, 1.0f);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		{
			DrawModel(model_list + current_mdl);
		}
		glPopAttrib();
	}
	glPopMatrix();
}

int Menu_SwipeMDL(int x, int y, int dx, int dy)
{
	if(!has_init)
		return 0;
	if(current_mdl == -1)
		return 0;

	rect2 r = {model_view.x, model_view.y, model_view.x + model_view.width, model_view.y + model_view.height};
	int last_x = x - dx;
	int last_y = y - dy;
	if(UI_PointInRect2(&r, x, y) && UI_PointInRect2(&r, last_x, last_y))
	{
		model_view.rotate.xr = Algo_FormatAngle(model_view.rotate.xr + -dy);
		model_view.rotate.zr = Algo_FormatAngle(model_view.rotate.zr + dx);
		Menu_ComputeDirection();
		return 1;
	}
	return 0;
}

void Menu_UpdateAnimation(void *args)
{
	if(!has_init)
		return;
	if(!args)
		return;
	int index = ((mdl_seq_info *)args)->index;
	const char *name = ((mdl_seq_info *)args)->name;
	StudioModel *mdl = model_list + current_mdl;
	{
		int anim = -1;
		mstudioseqdesc_t *seq = GetSequence(mdl, name, &anim);
		if(seq)
		{
			char text[201];
			sprintf(text, "(%s - (%d. %s)): Frames->%d, FPS->%d\n", MDL_Names[current_mdl], index, name, seq->numframes, (int)seq->fps);
			SET_TEXT(name_lb.text, text);
			SetSequence(mdl, anim);
		}
	}
}

void Menu_PlayAnimation(float delta)
{
	if(!has_init)
		return;
	AdvanceFrame(model_list + current_mdl, delta);

}

void Menu_SetActionState(menu_action action, unsigned state)
{
	if(!has_init)
		return;
	if(action < back_to_menu_action)
		actions[action] = state;
}

void Menu_IncrScale(void *data)
{
	if(!has_init)
		return;
	scale += MDL_SCALE_UNIT * delta_time;
	if(scale > MDL_SCALE_MAX)
		scale = MDL_SCALE_MAX;
	model_view.scale.xs = scale;
	model_view.scale.ys = scale;
	model_view.scale.zs = scale;
}

void Menu_DecrScale(void *data)
{
	if(!has_init)
		return;
	scale -= MDL_SCALE_UNIT * delta_time;
	if(scale <= 0.0)
		scale = MDL_SCALE_MIN;
	model_view.scale.xs = scale;
	model_view.scale.ys = scale;
	model_view.scale.zs = scale;
}

void Menu_Forward(void *data)
{
	if(!has_init)
		return;
	float dis = MDL_TRANSLATE_UNIT * delta_time;
	nl_vector3_t dir = {direction[0], direction[1], direction[2]};
	dir = Vector3_Scale(&dir, dis);
	model_view.translate.xt += dir.x;
	model_view.translate.yt += dir.y;
	model_view.translate.zt += dir.z;
}

void Menu_Backward(void *data)
{
	if(!has_init)
		return;
	float dis = MDL_TRANSLATE_UNIT * delta_time;
	nl_vector3_t dir = {direction[0], direction[1], direction[2]};
	dir = Vector3_Scale(&dir, dis);
	model_view.translate.xt -= dir.x;
	model_view.translate.yt -= dir.y;
	model_view.translate.zt -= dir.z;
}

void Menu_MoveLeft(void *data)
{
	if(!has_init)
		return;
	float dis = MDL_TRANSLATE_UNIT * delta_time;
	float xr = MDL_ROTATE_X;
	float yr = model_view.rotate.zr;
	nl_vector3_t dir = Algo_ComputeDirection(yr, xr);
	nl_vector3_t updir = {up[0], up[1], up[2]};
	nl_vector3_t left = Vector3_CrossVector3(&updir, &dir);
	dir = Vector3_Scale(&left, dis);
	model_view.translate.xt += dir.x;
	model_view.translate.yt += dir.y;
	model_view.translate.zt += dir.z;
}

void Menu_MoveRight(void *data)
{
	if(!has_init)
		return;
	float dis = MDL_TRANSLATE_UNIT * delta_time;
	float xr = MDL_ROTATE_X;
	float yr = model_view.rotate.zr;
	nl_vector3_t dir = Algo_ComputeDirection(yr, xr);
	nl_vector3_t updir = {up[0], up[1], up[2]};
	nl_vector3_t left = Vector3_CrossVector3(&updir, &dir);
	dir = Vector3_Scale(&left, dis);
	model_view.translate.xt -= dir.x;
	model_view.translate.yt -= dir.y;
	model_view.translate.zt -= dir.z;
}

void Menu_MoveUp(void *data)
{
	if(!has_init)
		return;
	model_view.translate.yt -= MDL_TRANSLATE_UNIT * delta_time;
}

void Menu_MoveDown(void *data)
{
	if(!has_init)
		return;
	model_view.translate.yt += MDL_TRANSLATE_UNIT * delta_time;
}

void Menu_TurnLeft(void *data)
{
	if(!has_init)
		return;
	model_view.rotate.zr = Algo_FormatAngle(model_view.rotate.zr - MDL_ROTATE_UNIT * delta_time);
}

void Menu_TurnRight(void *data)
{
	if(!has_init)
		return;
	model_view.rotate.zr = Algo_FormatAngle(model_view.rotate.zr + MDL_ROTATE_UNIT * delta_time);
}

void Menu_TurnUp(void *data)
{
	if(!has_init)
		return;
		model_view.rotate.xr = Algo_FormatAngle(model_view.rotate.xr - MDL_ROTATE_UNIT * delta_time);
}

void Menu_TurnDown(void *data)
{
	if(!has_init)
		return;
		model_view.rotate.xr = Algo_FormatAngle(model_view.rotate.xr + MDL_ROTATE_UNIT * delta_time);
}

void Menu_ComputeDirection(void)
{
	if(!has_init)
		return;
	//float xr = Algo_FormatAngle(model_view.rotate.xr - MDL_ROTATE_X);
	float xr = model_view.rotate.xr;
	float yr = model_view.rotate.zr;
	nl_vector3_t dir = Algo_ComputeDirection(yr, xr);
	direction[0] = dir.x;
	direction[1] = dir.y;
	direction[2] = dir.z;
}

void Menu_ResetMdlViewerTransform(void *data)
{
	if(!has_init)
		return;
	scale = MDL_SCALE;
	model_view.scale.xs = MDL_SCALE;
	model_view.scale.ys = MDL_SCALE;
	model_view.scale.zs = MDL_SCALE;
	model_view.rotate.xr = MDL_ROTATE_X;
	model_view.rotate.yr = MDL_ROTATE_Y;
	model_view.rotate.zr = MDL_ROTATE_Z;
	model_view.translate.xt = MDL_TRANSLATE_X;
	model_view.translate.yt = MDL_TRANSLATE_Y;
	model_view.translate.zt = MDL_TRANSLATE_Z;
	Menu_ComputeDirection();

}
