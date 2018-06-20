#include "weapon_chooser.h"
#include "weapon.h"
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

#define TYPE_LIST_VIEW_X 0
#define TYPE_LIST_VIEW_Y 0
#define TYPE_LIST_VIEW_W 220
#define TYPE_LIST_VIEW_H 400
#define TYPE_BUTTON_W 200
#define TYPE_BUTTON_H 40

#define WEAPON_LIST_VIEW_X 240
#define WEAPON_LIST_VIEW_Y 0
#define WEAPON_LIST_VIEW_W 300
#define WEAPON_LIST_VIEW_H 400
#define WEAPON_BUTTON_W 280
#define WEAPON_BUTTON_H 40

#define TEXT_VIEW_X 540
#define TEXT_VIEW_Y 200
#define TEXT_VIEW_W 300
#define TEXT_VIEW_H 200
#define WEAPON_VIEW_X 540
#define WEAPON_VIEW_Y 80
#define WEAPON_VIEW_W 300
#define WEAPON_VIEW_H 120

#define ACTION_BUTTON_W 120
#define ACTION_BUTTON_H 60
#define BUTTON_SURE_X 550
#define BUTTON_SURE_Y 10
#define BUTTON_BACK_X 700
#define BUTTON_BACK_Y 10
#define LABEL_H 80

#define IDLE_TIME_DELAY 0.4

#define WEAPON_TYPE_COUNT 9

static const weapon_attack_type Weapon_Type_List[WEAPON_TYPE_COUNT] = {
	pistol_gun_type,
	shot_gun_type,
	mini_submachine_gun_type,
	automatic_rifle_type,
	sniper_rifle_type,
	machine_gun_type,
	launcher1_gun_type,
	dagger_type,
	grenades_type
};
static weapon *weapon_list = NULL;

static int Menu_WeaponChooserIdleEventFunc(void);
static int Menu_WeaponChooserKeyEventFunc(int k, int a, int p, int x, int y);
static int Menu_WeaponChooserMouseEventFunc(int b, int p, int x, int y);
static int Menu_WeaponChooserMouseClickEventFunc(int b, int x, int y);
static int Menu_WeaponChooserMouseMotionEventFunc(int b, int p, int x, int y, int dx, int dy);
static void Menu_WeaponChooserDrawFunc(void);
static void Menu_WeaponChooserReshapeFunc(int w, int h);
static void Menu_WeaponChooserInitFunc(void);
static void Menu_WeaponChooserFreeFunc(void);

static void Menu_ResetWeaponChooser(void);
static void Menu_MakeWeaponListViewData(void *type);
static void Menu_ViewWeapon(void *index);
static void Menu_BackAction(void);
static void Menu_ChooseWeapon(void);
static void Menu_RenderWeapon(void);
static int Menu_SwipeWeapon(int x, int y, int dx, int dy);
static void Menu_SetWeaponChooserPageSize(GLsizei w, GLsizei h);

static button btn;
static button wp_btn;

static button sure_btn;
static button back_btn;

static list_view lst;
static list_view wp_lst;
static label lb;
static text_browser tb;
static scene_3d weapon_view;
static const float weapon_view_unit = 150;
static bool_t auto_rotate = 1;

static bool_t has_init = 0;
static int current_weapon = -1;

static list_view_data *data = NULL;
static list_view_data *wp_data = NULL;
static unsigned int data_count = 0;
static unsigned int wp_data_count = 0;
static GLsizei page_width = HARMATTAN_FULL_WIDTH;
static GLsizei page_height = HARMATTAN_FULL_HEIGHT;
static float idle_time = 0.0f;

void Menu_SetWeaponChooserPageSize(GLsizei w, GLsizei h)
{
	if(page_width == w && page_height == h)
		return;
	page_width = w;
	page_height = h;
	if(has_init)
	{
		UI_ResizeButton(&btn, TYPE_BUTTON_W, TYPE_BUTTON_H);
		UI_ResizeButton(&wp_btn, WEAPON_BUTTON_W, WEAPON_BUTTON_H);
		UI_ResetButtonGeometry(&sure_btn, BUTTON_SURE_X, BUTTON_SURE_Y, ACTION_BUTTON_W, ACTION_BUTTON_H);
		UI_ResetButtonGeometry(&back_btn, BUTTON_BACK_X, BUTTON_BACK_Y, ACTION_BUTTON_W, ACTION_BUTTON_H);
		UI_ResetListViewGeometry(&lst, TYPE_LIST_VIEW_X, TYPE_LIST_VIEW_Y, TYPE_LIST_VIEW_W, TYPE_LIST_VIEW_H);
		UI_ResetListViewGeometry(&wp_lst, WEAPON_LIST_VIEW_X, WEAPON_LIST_VIEW_Y, WEAPON_LIST_VIEW_W, WEAPON_LIST_VIEW_H);
		UI_ResetTextBrowserGeometry(&tb, TEXT_VIEW_X, TEXT_VIEW_Y, TEXT_VIEW_W, TEXT_VIEW_H);
		UI_ResetLabelGeometry(&lb, 0.0, page_height - LABEL_H, page_width, LABEL_H);
		UI_ResizeScene3D(&weapon_view, WEAPON_VIEW_W, WEAPON_VIEW_H, page_width, page_height);
	}
}

int Menu_WeaponChooserIdleEventFunc(void)
{
	if(!has_init)
		return 0;
	if(auto_rotate)
	{
		if(current_weapon != -1)
		{
			const weapon *wp = weapon_list + current_weapon;
			if(wp -> model && wp -> model -> tp_model)
			{
				weapon_view.rotate.zr += delta_time * weapon_view_unit;
			}
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

void Menu_WeaponChooserInitFunc(void)
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

void Menu_WeaponChooserDrawFunc(void)
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
		glScissor(wp_lst.base.x, wp_lst.base.y, wp_lst.base.width, wp_lst.base.height);
		glPushMatrix();
		{
			glTranslatef(wp_lst.base.x, wp_lst.base.y, wp_lst.base.z);
			UI_RenderListView(&wp_lst);
		}
		glPopMatrix();
		glScissor(tb.base.x, tb.base.y, tb.base.width, tb.base.height);
		glPushMatrix();
		{
			glTranslatef(tb.base.x, tb.base.y, tb.base.z);
			UI_RenderTextBrowser(&tb);
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

	UI_RenderScene3D(&weapon_view);
}

void Menu_WeaponChooserReshapeFunc(int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	if(!has_init)
		return;
	Menu_SetWeaponChooserPageSize(w, h);
}

void Menu_WeaponChooserFreeFunc(void)
{
	if(!has_init)
		return;

	delete_button(&btn);
	delete_button(&wp_btn);
	delete_button(&sure_btn);
	delete_button(&back_btn);
	delete_label(&lb);
	delete_list_view(&lst);
	delete_list_view(&wp_lst);
	delete_text_browser(&tb);
	delete_scene_3d(&weapon_view);
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
	if(wp_data)
	{
		GLuint i;
		for(i = 0; i < wp_data_count; i++)
		{
			FREE_PTR(wp_data[i].text)
				FREE_PTR(wp_data[i].args)
		}
		free(wp_data);
		wp_data = NULL;
		wp_data_count = 0;
	}
	if(weapon_list)
	{
		int i;
		for(i = ct3d_Dagger; i < total_weapon_model_type; i++)
			delete_weapon(weapon_list + i);
		free(weapon_list);
		weapon_list = NULL;
	}
	Game_FreeWeaponModel();
	Menu_ResetWeaponChooser();
	has_init = 0;
}

// for all X event pointer coord y, Using left-down as ori, like OpenGL, and not left-top of X11. so the y coord need to convert by screen height - y, and delta_y is invert.
int Menu_WeaponChooserKeyEventFunc(int key, int act, int pressed, int x, int y)
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
				Menu_BackAction();
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

int Menu_WeaponChooserMouseEventFunc(int button, int pressed, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	rect2 r = {weapon_view.x, weapon_view.y, weapon_view.x + weapon_view.width, weapon_view.y + weapon_view.height};

	if(UI_PointInRect2(&r, x, gl_y))
	{
		if(pressed)
		{
			auto_rotate = 0;
			return 1;
		}
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

int Menu_WeaponChooserMouseMotionEventFunc(int button, int pressed, int x, int y, int dx, int dy)
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
		else if(UI_PointInWidget(&wp_lst.base, x, gl_y))
		{
			res |= UI_SlideListView(&wp_lst, -dy);
		}
		else if(UI_PointInWidget(&tb.base, x, gl_y))
		{
			res |= UI_SlideTextBrowser(&tb, -dy);
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

		res |= Menu_SwipeWeapon(x, gl_y, dx, -dy);
	}

	return res;
}

void Menu_WeaponChooserRegisterFunction(void)
{
	if(!has_init)
		return;
	Main3D_SetInitFunction(Menu_WeaponChooserInitFunc);
	Main3D_SetDrawFunction(Menu_WeaponChooserDrawFunc);
	Main3D_SetFreeFunction(Menu_WeaponChooserFreeFunc);
	Main3D_SetKeyEventFunction(Menu_WeaponChooserKeyEventFunc);
	Main3D_SetIdleEventFunction(Menu_WeaponChooserIdleEventFunc);
	Main3D_SetReshapeFunction(Menu_WeaponChooserReshapeFunc);
	Main3D_SetMouseEventFunction(Menu_WeaponChooserMouseEventFunc);
	Main3D_SetMouseMotionEventFunction(Menu_WeaponChooserMouseMotionEventFunc);
	Main3D_SetMouseClickEventFunction(Menu_WeaponChooserMouseClickEventFunc);
}

void Menu_MakeWeaponListViewData(void *args)
{
	if(!has_init)
		return;
	if(!args)
		return;
	int *iarg = (int *)args;
	int type = *iarg;
	if(type == -1)
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
		data_count = WEAPON_TYPE_COUNT;
		data = NEW_II(list_view_data, data_count);
		GLuint i;
		for(i = 0; i < data_count; i++)
		{
			data[i].text = strdup(Weapon_Type_Name[Weapon_Type_List[i]]);
			data[i].func = Menu_MakeWeaponListViewData;
			int *args = NEW(int);
			*args = Weapon_Type_List[i];
			data[i].args = args;
		}
	}
	else
	{
		if(wp_data)
		{
			GLuint i;
			for(i = 0; i < wp_data_count; i++)
			{
				FREE_PTR(wp_data[i].text)
					FREE_PTR(wp_data[i].args)
			}
			free(wp_data);
			wp_data = NULL;
			wp_data_count = 0;
		}
		if(type >= long_attack_type || type == short_attack_type || type == launcher2_gun_type)
			return;
		list_template list;
		new_list_template(&list, sizeof(int));
		GLuint i;
		for(i = ct3d_Dagger; i < total_weapon_model_type; i++)
		{
			int index = -1;
			if(type == launcher1_gun_type && (weapon_list[i].type == launcher1_gun_type || weapon_list[i].type == launcher2_gun_type))
				index = i;
			else if(type == grenades_type && (weapon_list[i].type == grenades_type || weapon_list[i].type == flash_flares_type || weapon_list[i].type == smoke_bomb_type))
				index = i;
			else if((weapon_model_type)type == weapon_list[i].type)
				index = i;
			else
				continue;
			List_PushBack(&list, &index);
		}

		wp_data_count = list.count;
		wp_data = NEW_II(list_view_data, wp_data_count);
		for(i = 0; i < wp_data_count; i++)
		{
			const int *index =	List_GetConstDataByIndexT(&list, i, int);
			if(index)
			{
				wp_data[i].text = strdup(Weapon_Name[*index]);
				wp_data[i].func = Menu_ViewWeapon;
				int *args = NEW(int);
				*args = *index;
				wp_data[i].args = args;
			}
		}
		List_DeleteAll(&list);
		wp_lst.data = wp_data;
		wp_lst.count = wp_data_count;
		wp_lst.current_index = 0;
		wp_lst.progress = 0.0;
	}
}

void Menu_ViewWeapon(void *args)
{
	if(!has_init)
		return;
	if(!args)
		return;
	int *index = (int *)args;
	current_weapon = *index;
	const weapon *wp = weapon_list + current_weapon;
	char str[300];
	memset(str, '\0', 300 * sizeof(char));
	sprintf(str, "< %s >\n\n"
			"Type: %s\n"
			"Firing rate: %.1f\n"
			"Shot range: %.0f\n"
			"Damage: %d\n"
			"Ammo count: %d\n"
			"Ammo total count: %d\n"
			"Reload time: %.1fs\n"
			"Bullet speed: %.0f/s\n"
			, Weapon_Name[wp -> weapon_index], Weapon_Type_Name[wp -> type], wp -> firing_rate, wp -> shot_range, wp -> damage * wp -> shell_count, wp -> ammo_count, wp -> ammo_total_count_limit, wp -> reload_time, wp -> speed);

	if(!tb.text || strcmp(tb.text, str))
		UI_SetBrowserText(&tb, str);
	weapon_view.rotate.xr = -90.0;
	weapon_view.rotate.yr = 0.0;
	weapon_view.rotate.zr = 0.0;
	auto_rotate = 1;
}

void Menu_ChooseWeapon(void)
{
	if(!has_init)
		return;
	if(current_weapon == -1)
		return;
	Setting_SetSettingInteger(USE_WEAPON_SETTING, current_weapon);
}

void Menu_BackAction(void)
{
	if(!has_init)
		return;
	const void *slot = SignalSlot_GetAction(BACK_MAIN_MENU);
	if(slot)
	{
		((void__func__void)slot)();
	}
}

int Menu_WeaponChooserMouseClickEventFunc(int button, int x, int y)
{
	if(!has_init)
		return 0;
	int gl_y = height - y;
	if(UI_PointInWidget(&lst.base, x, gl_y))
	{
		UI_ClickListView(&lst, x - lst.base.x, gl_y - lst.base.y);
		return 1;
	}
	else if(UI_PointInWidget(&wp_lst.base, x, gl_y))
	{
		UI_ClickListView(&wp_lst, x - wp_lst.base.x, gl_y - wp_lst.base.y);
		return 1;
	}
	else if(UI_PointInWidget(&sure_btn.base, x, gl_y))
	{
		Menu_ChooseWeapon();
		return 1;
	}
	else if(UI_PointInWidget(&back_btn.base, x, gl_y))
	{
		Menu_BackAction();
		return 1;
	}
	return 0;
}

void Menu_InitWeaponChooser(void)
{
	if(has_init)
		return;
	Game_LoadWeaponModel();
	weapon_list = NEW_II(weapon, total_weapon_model_type);
	int i;
	for(i = ct3d_Dagger; i < total_weapon_model_type; i++)
		new_weapon(weapon_list + i, i);

	new_button(&btn, 0.0, 0.0, 0.0, TYPE_BUTTON_W, TYPE_BUTTON_H, 2.0, X11_COLOR(lightskyblue), X11_COLOR(green), X11_COLOR(lightseagreen), X11_COLOR(pink), X11_COLOR(darkgreen), X11_COLOR(seagreen), NULL);
	new_button(&wp_btn, 0.0, 0.0, 0.0, WEAPON_BUTTON_W, WEAPON_BUTTON_H, 2.0, X11_COLOR(lightskyblue), X11_COLOR(green), X11_COLOR(lightseagreen), X11_COLOR(pink), X11_COLOR(darkgreen), X11_COLOR(seagreen), NULL);
	new_button(&sure_btn, BUTTON_SURE_X, BUTTON_SURE_Y, 0.3, ACTION_BUTTON_W, ACTION_BUTTON_H, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(gray), "Sure");
	new_button(&back_btn, BUTTON_BACK_X, BUTTON_BACK_Y, 0.3, ACTION_BUTTON_W, ACTION_BUTTON_H, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(gray), "Back");
	btn.fnt = &fnt;
	wp_btn.fnt = &fnt;
	sure_btn.fnt = &fnt;
	back_btn.fnt = &fnt;
	new_list_view(&lst, TYPE_LIST_VIEW_X, TYPE_LIST_VIEW_Y, 0.0, TYPE_LIST_VIEW_W, TYPE_LIST_VIEW_H, 10, 20, 15, Color_GetColor(black_color, 0.0), X11_COLOR(lightgreen), X11_COLOR(darkgreen));
	lst.delegate.component = &btn;
	lst.delegate.update_func = UI_ButtonUpdateText;
	lst.delegate.render_func = UI_RenderButtonItem;
	lst.delegate.get_geometry_func = UI_GetWidgetGeometry;

	new_list_view(&wp_lst, WEAPON_LIST_VIEW_X, WEAPON_LIST_VIEW_Y, 0.0, WEAPON_LIST_VIEW_W, WEAPON_LIST_VIEW_H, 10, 20, 15, Color_GetColor(black_color, 0.0), X11_COLOR(lightgreen), X11_COLOR(darkgreen));
	wp_lst.delegate.component = &wp_btn;
	wp_lst.delegate.update_func = UI_ButtonUpdateText;
	wp_lst.delegate.render_func = UI_RenderButtonItem;
	wp_lst.delegate.get_geometry_func = UI_GetWidgetGeometry;
	new_text_browser(&tb, TEXT_VIEW_X, TEXT_VIEW_Y, 0.0, TEXT_VIEW_W, TEXT_VIEW_H, 4.0, 2.0, X11_COLOR(orange), X11_COLOR(black), X11_COLOR(lightgreen), X11_COLOR(darkgreen), X11_COLOR(green), NULL);
	tb.fnt = &fnt;
	new_scene_3d(&weapon_view, WEAPON_VIEW_X, WEAPON_VIEW_Y, 0.0, WEAPON_VIEW_W, WEAPON_VIEW_H, left_bottom_anchor_type, X11_COLOR(black), NULL, 45.0, width, height, 0.1, 2000.0, Menu_RenderWeapon);

	new_label(&lb, 0.0, page_height - LABEL_H, 0.2, page_width, LABEL_H, 0, Color_GetColor(white_color, 0.4), X11_COLOR(green), Color_GetColor(black_color, 0.0), "Weapon Chooser", NULL);
	lb.fnt = &fnt;
	has_init = 1;
	int type = -1;
	Menu_MakeWeaponListViewData(&type);
	lst.data = data;
	lst.count = data_count;
	lst.current_index = 0;
	lst.progress = 0.0;
}

void Menu_ResetWeaponChooser(void)
{
	page_width = width;
	page_height = height;
	auto_rotate = 1;
	current_weapon = -1;
	idle_time = 0.0f;
}

void Menu_RenderWeapon(void)
{
	if(!has_init)
		return;
	if(current_weapon == -1)
		return;
	const weapon *wp = weapon_list + current_weapon;
	if(!wp -> model || !wp -> model -> tp_model)
		return;
	glPushAttrib(GL_POLYGON_BIT);
	{
		oglDisable(GL_CULL_FACE);
		glRotatef(wp -> model -> tp_model -> item_meshes[0].angle[0], 1.0f, 0.0f, 0.0f);
		glRotatef(wp -> model -> tp_model -> item_meshes[0].angle[1], 0.0f, 0.0f, 1.0f);
		if(wp -> model -> scale != 1.0)
			glScalef(wp -> model -> scale, wp -> model -> scale, wp -> model -> scale);
		NETLizard_RenderGL3DMesh(&(wp -> model -> tp_model -> item_meshes[0].item_mesh), wp -> model -> tp_model -> texes);
	}
	glPopAttrib();
}

int Menu_SwipeWeapon(int x, int y, int dx, int dy)
{
	if(!has_init)
		return 0;
	if(current_weapon == -1)
		return 0;
	const weapon *wp = weapon_list + current_weapon;
	if(!wp -> model || !wp -> model -> tp_model)
		return 0;
	rect2 r = {weapon_view.x, weapon_view.y, weapon_view.x + weapon_view.width, weapon_view.y + weapon_view.height};
	int last_x = x - dx;
	int last_y = y - dy;
	if(UI_PointInRect2(&r, x, y) && UI_PointInRect2(&r, last_x, last_y))
	{
		auto_rotate = 0;
		weapon_view.rotate.xr += -dy;
		weapon_view.rotate.zr += dx;
		return 1;
	}
	return 0;
}
