#include "character_model_chooser.h"
#include "gl_3d_main.h"
#include "component/button.h"
#include "component/label.h"
#include "component/list_view.h"
#include "component/text_browser.h"
#include "action_signal_slot.h"
#include "game_std.h"
#include "game_util.h"
#include "game_setting.h"
#include "character.h"

#define PAGE_NAME "CharacterChooser"

#define CHARACTER_MODEL_LIST_VIEW_X 0
#define CHARACTER_MODEL_LIST_VIEW_Y 0
#define CHARACTER_MODEL_LIST_VIEW_W 277
#define CHARACTER_MODEL_LIST_VIEW_H 400
#define CHARACTER_MODEL_BUTTON_W 250
#define CHARACTER_MODEL_BUTTON_H 40

#define ANIMATION_LIST_VIEW_X 577
#define ANIMATION_LIST_VIEW_Y 0
#define ANIMATION_LIST_VIEW_W 277
#define ANIMATION_LIST_VIEW_H 400
#define ANIMATION_BUTTON_W 250
#define ANIMATION_BUTTON_H 40

#define NAME_LABEL_X 277
#define NAME_LABEL_Y 360
#define NAME_LABEL_W 300
#define NAME_LABEL_H 40
#define ANIMATION_VIEW_X 277
#define ANIMATION_VIEW_Y 80
#define ANIMATION_VIEW_W 300
#define ANIMATION_VIEW_H 280

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

static const character_status_type Animation_List[] = {
	idle_status_type,
	run_status_type,
	attack_status_type,
	reload_status_type,
	death_status_type
};

static game_character_model *model_list = NULL;

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

static void Menu_ResetCharacterModelChooser(void);
static void Menu_MakeListViewData(void);
static void Menu_ViewCharacterModel(void *index);
static void Menu_BackAction(void *data);
static void Menu_ChooseCharacterModel(void *data);
static void Menu_RenderCharacterModel(void);
static int Menu_SwipeCharacterModel(int x, int y, int dx, int dy);
static void Menu_UpdateAnimation(void *index);
static void Menu_PlayAnimation(float delta);
static void Menu_SetCharacterModelChooserPageSize(GLsizei w, GLsizei h);

static const button_initilizer Btn_Infos[] = {
	{280, 10, BTN_W, BTN_H, "Sure", Menu_ChooseCharacterModel, NULL},
	{420, 10, BTN_W, BTN_H, "Back", Menu_BackAction, NULL},
};

static button btn;
static button action_btn;
static button btns[total_action_type];
static list_view lst;
static list_view action_lst;
static label lb;
static label name_lb;
static scene_3d model_view;
static character_animation_data animation;
static const float model_view_unit = 150;

static bool_t has_init = 0;
static int current_character = -1;

static list_view_data *data = NULL;
static list_view_data *action_data = NULL;
static unsigned int data_count = 0;
static unsigned int action_data_count = 0;
static GLsizei page_width = HARMATTAN_FULL_WIDTH;
static GLsizei page_height = HARMATTAN_FULL_HEIGHT;
static float idle_time = 0.0f;

void Menu_SetCharacterModelChooserPageSize(GLsizei w, GLsizei h)
{
	if(page_width == w && page_height == h)
		return;
	page_width = w;
	page_height = h;
	if(has_init)
	{
		UI_ResizeButton(&btn, CHARACTER_MODEL_BUTTON_W, CHARACTER_MODEL_BUTTON_H);
		UI_ResizeButton(&action_btn, ANIMATION_BUTTON_W, ANIMATION_BUTTON_H);
		UI_ResetListViewGeometry(&lst, CHARACTER_MODEL_LIST_VIEW_X, CHARACTER_MODEL_LIST_VIEW_Y, CHARACTER_MODEL_LIST_VIEW_W, CHARACTER_MODEL_LIST_VIEW_H);
		UI_ResetListViewGeometry(&action_lst, ANIMATION_LIST_VIEW_X, ANIMATION_LIST_VIEW_Y, ANIMATION_LIST_VIEW_W, ANIMATION_LIST_VIEW_H);
		UI_ResetLabelGeometry(&name_lb, NAME_LABEL_X, NAME_LABEL_Y, NAME_LABEL_W, NAME_LABEL_H);
		UI_ResetLabelGeometry(&lb, 0.0, page_height - LABEL_H, page_width, LABEL_H);
		UI_ResizeScene3D(&model_view, ANIMATION_VIEW_W, ANIMATION_VIEW_H, page_width, page_height);
		int i;
		for(i = 0; i < total_action_type; i++)
			UI_ResetButtonGeometry(btns + i, Btn_Infos[i].x, Btn_Infos[i].y, Btn_Infos[i].w, Btn_Infos[i].h);
	}
}

int UI_IdleFunc(void)
{
	if(!has_init)
		return 0;
	Menu_PlayAnimation(delta_time);

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

void UI_ReshapeFunc(int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	if(!has_init)
		return;
	Menu_SetCharacterModelChooserPageSize(w, h);
}

void UI_FreeFunc(void)
{
	if(!has_init)
		return;

	delete_button(&btn);
	delete_button(&action_btn);
	int m;
	for(m = 0; m < total_action_type; m++)
		delete_button(btns + m);
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
		for(i = egypt3d_worm; i < lol_total_model; i++)
		{
			Game_FreeCharacterModel(model_list + i);
		}
		free(model_list);
		model_list = NULL;
	}
	Menu_ResetCharacterModelChooser();
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
			 Menu_ViewWeapon(NULL);
			 return 1;
			 }
			 break;
			 */
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
	rect2 r = {model_view.x, model_view.y, model_view.x + model_view.width, model_view.y + model_view.height};

	if(UI_PointInRect2(&r, x, gl_y))
	{
		if(pressed)
		{
			// TODO ???
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
				res |= 1;
			}
			else if(!UI_PointInWidget(&btns[i].base, x, gl_y) && UI_PointInWidget(&btns[i].base, last_x, last_gl_y))
			{
				btns[i].highlight = GL_FALSE;
				res |= 1;
			}
		}

		res |= Menu_SwipeCharacterModel(x, gl_y, dx, -dy);
	}

	return res;
}

void UI_CharacterChooserRegisterFunction(void)
{
	glk_function func;
	if(!has_init)
		return;

	func = REGISTER_RENDER_FUNCTION(UI);
	Main3D_PushRenderPage(PAGE_NAME, &func);
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
	data_count = lol_total_model;
	data = NEW_II(list_view_data, data_count);
	GLuint i;
	for(i = 0; i < data_count; i++)
	{
		data[i].text = strdup(Character_Model_Name[i]);
		data[i].func = Menu_ViewCharacterModel;
		int *args = NEW(int);
		*args = i;
		data[i].args = args;
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
	action_data_count = countof(Animation_List);
	action_data = NEW_II(list_view_data, action_data_count);
	for(i = 0; i < action_data_count; i++)
	{
		action_data[i].text = strdup(Character_Status_Name[i]);
		action_data[i].func = Menu_UpdateAnimation;
		int *args = NEW(int);
		*args = Animation_List[i];
		action_data[i].args = args;
	}
}

void Menu_ViewCharacterModel(void *args)
{
	if(!has_init)
		return;
	if(!args)
		return;
	int *index = (int *)args;
	current_character = *index;
	if(!name_lb.text || strcmp(name_lb.text, Character_Model_Name[current_character]))
	{
		SET_TEXT(name_lb.text, Character_Model_Name[current_character]);
	}
	// TODO global
	model_view.rotate.xr = -90.0;
	model_view.rotate.yr = 0.0;
	model_view.rotate.zr = 0.0;
	model_view.translate.yt = -ANIMATION_VIEW_H / 2;
	action_lst.current_index = 0;
	character_status_type status = Animation_List[action_lst.current_index];
	Menu_UpdateAnimation(&status);
}

void Menu_ChooseCharacterModel(void *data)
{
	if(!has_init)
		return;
	if(current_character == -1)
		return;
	if(current_character >= clone3d_human_cloning && current_character <= jinx_original)
		Setting_SetSettingInteger(USE_CHARACTER_MODEL_SETTING, current_character);
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
	else if(UI_PointInWidget(&action_lst.base, x, gl_y))
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

void Menu_InitCharacterModelChooser(void)
{
	if(has_init)
		return;
	model_list = NEW_II(game_character_model, lol_total_model);
	int i;
	for(i = egypt3d_worm; i < lol_total_model; i++)
		Game_MakeGameCharacterModel(model_list + i, i);

	new_button(&btn, 0.0, 0.0, 0.0, CHARACTER_MODEL_BUTTON_W, CHARACTER_MODEL_BUTTON_H, 2.0, X11_COLOR(lightskyblue), X11_COLOR(green), X11_COLOR(lightseagreen), X11_COLOR(pink), X11_COLOR(darkgreen), X11_COLOR(seagreen), NULL);
	btn.base.clip = GL_FALSE;
	new_button(&action_btn, 0.0, 0.0, 0.0, ANIMATION_BUTTON_W, ANIMATION_BUTTON_H, 2.0, X11_COLOR(lightskyblue), X11_COLOR(green), X11_COLOR(lightseagreen), X11_COLOR(pink), X11_COLOR(darkgreen), X11_COLOR(seagreen), NULL);
	action_btn.base.clip = GL_FALSE;
	int m;
	for(m = 0; m < total_action_type; m++)
	{
		new_button(btns + m, Btn_Infos[m].x, Btn_Infos[m].y, 0.3, Btn_Infos[m].w, Btn_Infos[m].h, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(gray), Btn_Infos[m].label);
		btns[m].fnt = &fnt;
	}
	btn.fnt = &fnt;
	action_btn.fnt = &fnt;
	new_list_view(&lst, CHARACTER_MODEL_LIST_VIEW_X, CHARACTER_MODEL_LIST_VIEW_Y, 0.0, CHARACTER_MODEL_LIST_VIEW_W, CHARACTER_MODEL_LIST_VIEW_H, 10, 20, 15, Color_GetColor(black_color, 0.0), X11_COLOR(lightgreen), X11_COLOR(darkgreen));
	lst.delegate.component = &btn;
	lst.delegate.update_func = UI_ButtonUpdateText;
	lst.delegate.render_func = UI_RenderButtonItem;
	lst.delegate.get_geometry_func = UI_GetWidgetGeometry;

	new_list_view(&action_lst, ANIMATION_LIST_VIEW_X, ANIMATION_LIST_VIEW_Y, 0.0, ANIMATION_LIST_VIEW_W, ANIMATION_LIST_VIEW_H, 10, 20, 15, Color_GetColor(black_color, 0.0), X11_COLOR(lightgreen), X11_COLOR(darkgreen));
	action_lst.delegate.component = &action_btn;
	action_lst.delegate.update_func = UI_ButtonUpdateText;
	action_lst.delegate.render_func = UI_RenderButtonItem;
	action_lst.delegate.get_geometry_func = UI_GetWidgetGeometry;
	new_scene_3d(&model_view, ANIMATION_VIEW_X, ANIMATION_VIEW_Y, 0.0, ANIMATION_VIEW_W, ANIMATION_VIEW_H, left_bottom_anchor_type, X11_COLOR(black), NULL, 45.0, page_width, page_height, 0.1, 2000.0, Menu_RenderCharacterModel);

	new_label(&lb, 0.0, page_height - LABEL_H, 0.2, page_width, LABEL_H, 0, Color_GetColor(white_color, 0.4), X11_COLOR(green), Color_GetColor(black_color, 0.0), "Character Model Chooser", NULL);
	lb.fnt = &fnt;
	new_label(&name_lb,NAME_LABEL_X, NAME_LABEL_Y, 0.2, NAME_LABEL_W, NAME_LABEL_H, 0, Color_GetColor(white_color, 0.0), X11_COLOR(green), Color_GetColor(black_color, 0.0), NULL, NULL);
	name_lb.fnt = &fnt;
	has_init = 1;
	Menu_MakeListViewData();
	lst.data = data;
	lst.count = data_count;
	lst.progress = 0.0;

	action_lst.data = action_data;
	action_lst.count = action_data_count;
	action_lst.current_index = 0;
	action_lst.progress = 0.0;

	current_character = natasha2;
	Setting_GetSettingInteger(USE_CHARACTER_MODEL_SETTING, &current_character);
	UI_SetListCurrentIndex(&lst, current_character);
	Menu_ViewCharacterModel(&current_character);
}

void Menu_ResetCharacterModelChooser(void)
{
	memset(&animation, 0, sizeof(character_animation_data));
	current_character = -1;
	page_width = width;
	page_height = height;
	idle_time = 0.0f;
}

void Menu_RenderCharacterModel(void)
{
	if(!has_init)
		return;
	if(current_character == -1)
		return;
	const game_character_model *cm = model_list + current_character;
	if(cm->source == lol_model_type)
	{
		if(!cm->lol_character.model)
			return;
		glPushMatrix();
		{
			glRotatef(cm->lol_character.x_offset, 1.0, 0.0, 0.0);

			if(cm->lol_character.scale != 1.0)
				glScalef(cm->lol_character.scale, cm->lol_character.scale, cm->lol_character.scale);
			LOL_RenderModel(cm->lol_character.model, 1, animation.idata[0].anim, animation.idata[0].frame);
		}
		glPopMatrix();
	}

	else if(cm->source == netlizard_model_type)
	{
		if(!cm->netlizard_character.model)
			return;
		glPushMatrix();
		{
			glRotatef(cm->netlizard_character.z_offset, 0.0f, 0.0f, 1.0f);
			if(cm->netlizard_character.scale != 1.0)
				glScalef(cm->netlizard_character.scale, cm->netlizard_character.scale, cm->netlizard_character.scale);
			NETLizard_RenderGL3DAnimationModel(cm->netlizard_character.model, animation.idata[0].anim, animation.idata[0].frame);
		}
		glPopMatrix();
	}

	else if(cm->source == csol_model_type)
	{
		if(!cm->csol_character.model)
			return;
		glPushMatrix();
		{
			glTranslatef(0.0, 0.0, (float)HL_MDL_Z_TRANSLATE * cm->csol_character.scale);
			glRotatef(cm->csol_character.z_offset, 0.0f, 0.0f, 1.0f);
			glRotatef(cm->csol_character.y_offset, 0.0f, 0.0f, 1.0f);
			if(cm->csol_character.scale != 1.0)
				glScalef(cm->csol_character.scale, cm->csol_character.scale, cm->csol_character.scale);
			glPushAttrib(GL_ALL_ATTRIB_BITS);
			{
			CSOL_DrawModel(cm->csol_character.model);
			}
			glPopAttrib();
		}
		glPopMatrix();
	}
}

int Menu_SwipeCharacterModel(int x, int y, int dx, int dy)
{
	if(!has_init)
		return 0;
	if(current_character == -1)
		return 0;
	const game_character_model *cm = model_list + current_character;
	if(cm->source == lol_model_type)
	{
		if(!cm->lol_character.model)
			return 0;
	}
	else if(cm->source == netlizard_model_type)
	{
		if(!cm->netlizard_character.model)
			return 0;
	}
	else if(cm->source == csol_model_type)
	{
		if(!cm->csol_character.model)
			return 0;
	}
	else
		return 0;

	rect2 r = {model_view.x, model_view.y, model_view.x + model_view.width, model_view.y + model_view.height};
	int last_x = x - dx;
	int last_y = y - dy;
	if(UI_PointInRect2(&r, x, y) && UI_PointInRect2(&r, last_x, last_y))
	{
		//model_view.rotate.xr += -dy;
		model_view.rotate.zr = Algo_FormatAngle(model_view.rotate.zr + dx);
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
	character_status_type status = (character_status_type)(*((int *)args));
	game_character_model *gmodel = model_list + current_character;
	if(gmodel->source == lol_model_type)
	{
		if(!gmodel->lol_character.model->anim)
			return;

		int anim = -1;
		int frame_count = -1;
		if(status == death_status_type)
		{
			anim = gmodel->lol_character.anim_list[LOL_Death_Type];
		}
		else if(status == reload_status_type)
		{
			anim = gmodel->lol_character.anim_list[LOL_Idle3_Type];
			frame_count = 83; // idle 3 160 / 340
		}
		else if(status == run_status_type)
		{
			anim = gmodel->lol_character.anim_list[LOL_Run1_Type];
		}
		else if(status == attack_status_type)
		{
			anim = gmodel->lol_character.anim_list[LOL_Attack1_Type];
		}
		else
		{
			int ran = rand() % 3;
			anim = ran == 0 ? gmodel->lol_character.anim_list[LOL_Idle1_Type] : (ran == 1 ? gmodel->lol_character.anim_list[LOL_Idle2_Type] : gmodel->lol_character.anim_list[LOL_Idle2_Type]); //Idle1 for test
		}
		if(anim != -1)
		{
			animation.idata[0].frame = 0;
			animation.idata[0].anim = anim;
			animation.idata[0].frame_count = frame_count == -1 ? (int)gmodel->lol_character.model->anim->animation[animation.idata[0].anim].animation_bone[0].frame_count : frame_count;
			animation.idata[0].anim_loop = one_animation_loop_type;
			animation.idata[0].fps = gmodel->lol_character.model->anim->animation[anim].fps;
			animation.idata[0].anim_orient = forward_play_type;
			animation.idata[0].play = 0;
			animation.idata[0].comp = 0;
			animation.idata[0].status = status;
			animation.num = 1;
		}
		else
			return;
	}
	else if(gmodel->source == netlizard_model_type)
	{
		if(!gmodel->netlizard_character.model)
			return;

		int anim = -1;
		if(status == death_status_type)
		{
			int a1 = Game_GetNETLizardAnimationIndex(gmodel->netlizard_character.model, Animation_Dead1_Type);
			int a2 = Game_GetNETLizardAnimationIndex(gmodel->netlizard_character.model, Animation_Dead2_Type);
			if(a1 != -1 && a2 != -1)
				anim = rand() % 2 == 0 ? a1 : a2;
			else if(a1 != -1)
				anim = a1;
			else if(a2 != -1)
				anim = a2;
			else
				anim = -1;
		}
		else if(status == run_status_type)
		{
			anim = Game_GetNETLizardAnimationIndex(gmodel->netlizard_character.model, Animation_Run_Type);
		}
		else if(status == attack_status_type || status == reload_status_type)
		{
			int a1 = Game_GetNETLizardAnimationIndex(gmodel->netlizard_character.model, Animation_Attack1_Type);
			int a2 = Game_GetNETLizardAnimationIndex(gmodel->netlizard_character.model, Animation_Attack2_Type);
			if(a1 != -1 && a2 != -1)
				anim = rand() % 2 == 0 ? a1 : a2;
			else if(a1 != -1)
				anim = a1;
			else if(a2 != -1)
				anim = a2;
			else
				anim = -1;
		}
		else
		{
			anim = Game_GetNETLizardAnimationIndex(gmodel->netlizard_character.model, Animation_Idle_Type);
		}
		if(anim != -1)
		{
			animation.idata[0].frame = 0;
			animation.idata[0].anim = anim;
			animation.idata[0].frame_count = gmodel->netlizard_character.model->animations[animation.idata[0].anim].end - gmodel->netlizard_character.model->animations[animation.idata[0].anim].begin + 1;
			animation.idata[0].anim_loop = one_animation_loop_type;
			animation.idata[0].fps = NETLIZARD_ANIMATION_FPS;
			animation.idata[0].anim_orient = forward_play_type;
			animation.idata[0].play = 0;
			animation.idata[0].comp = 0;
			animation.idata[0].status = status;
			animation.num = 1;
		}
		else
			return;
	}
	else if(gmodel->source == csol_model_type)
	{
		int anim = -1;
		mstudioseqdesc_t *seq = NULL;

		if(status == death_status_type)
		{
			const char *deaths[] = {
				"death1",
				"death2",
				"death3",
				"head",
				"gutshot",
				"left",
				"back",
				"right",
				"forward",
				"crouch_die"
			};
			seq = CSOL_GetSequence(gmodel->csol_character.model, deaths[rand() % (countof(deaths))], &anim);
		}
		else if(status == reload_status_type)
		{
			seq = CSOL_GetSequence(gmodel->csol_character.model, "ref_reload_ak47", &anim);
		}
		else if(status == run_status_type)
		{
			seq = CSOL_GetSequence(gmodel->csol_character.model, "run", &anim);
		}
		else if(status == attack_status_type)
		{
			seq = CSOL_GetSequence(gmodel->csol_character.model, "idle", &anim);
		}
		else
		{
			seq = CSOL_GetSequence(gmodel->csol_character.model, "idle1", &anim);
		}
		if(seq)
		{
			animation.idata[0].frame = 0;
			animation.idata[0].anim = anim;
			animation.idata[0].frame_count = seq->numframes;
			animation.idata[0].anim_loop = one_animation_loop_type;
			animation.idata[0].fps = seq->fps;
			animation.idata[0].play = 0;
			animation.idata[0].comp = 0;
			animation.idata[0].status = status;
			animation.num = 1;
			CSOL_SetSequence(gmodel->csol_character.model, ALL_PART, anim);
		}
		else
			return;
	}
	else
		return;
}

void Menu_PlayAnimation(float delta)
{
	if(!has_init)
		return;
	if(model_list[current_character].source == unavailable_model_type)
		return;
	Game_ComputeAnimationPlayFrameCount(model_list[current_character].source, &animation, fps, delta);

	Game_GetAnimationNextFrame(&animation);
	if(animation.idata[0].play >= 0)
	{
		animation.idata[0].frame = animation.idata[0].play;
		if(model_list[current_character].source == csol_model_type)
		{
			animation.idata[0].frame = (int)CSOL_SetFrame(model_list[current_character].csol_character.model, ALL_PART, animation.idata[0].play);
		}
	}
	//animation.last_play_time = time;
}
