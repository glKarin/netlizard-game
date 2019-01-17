#include "game_over.h"
#include "component/button.h"
#include "component/label.h"
#include "nl_std.h"
#include "game_std.h"
#include "action_signal_slot.h"
#include "score_table.h"
#include "component/text_browser.h"
#include "component/comp_util.h"

#define PAGE_NAME GAME_OVER_PAGE_NAME

#define BTN_W 120
#define BTN_H 60
#define TABLE_X 0
#define TABLE_Y 0
#define TABLE_W 650
#define TABLE_H 400
#define TEXT_X 654
#define TEXT_Y 200
#define TEXT_W 200
#define TEXT_H 200
#define LABEL_H 80

typedef enum _menu_action
{
	replay_action = 0,
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

static void UI_EnterAction(void *func);
static void GameMenu_SetGameOverPageSize(GLsizei w, GLsizei h);
static void GameMenu_ResetGameOver(void);

static const button_initilizer Btn_Infos[] = {
	{700, 100, BTN_W, BTN_H, "Replay", UI_EnterAction, REPLAY_GAME},
	{700, 0, BTN_W, BTN_H, "Back", UI_EnterAction, INIT_MAIN_MENU},
};

static button btns[total_action_type];
static label lb;
static text_browser tb;
static scene_2d bg;
static scene_2d fg;
static score_table score_tb;
static death_game_mode *game_mode = NULL;
static bool_t has_init = 0;
static GLsizei page_width = HARMATTAN_FULL_WIDTH;
static GLsizei page_height = HARMATTAN_FULL_HEIGHT;

void GameMenu_SetGameOverPageSize(GLsizei w, GLsizei h)
{
	if(page_width == w && page_height == h)
		return;
	page_width = w;
	page_height = h;
	if(has_init)
	{
		UI_ResizeScene2D(&bg, page_width, page_height);
		UI_ResizeScene2D(&fg, page_width, page_height);
		int i;
		for(i = 0; i < total_action_type; i++)
			UI_ResetButtonGeometry(btns + i, Btn_Infos[i].x, Btn_Infos[i].y, Btn_Infos[i].w, Btn_Infos[i].h);
		//UI_SetWidgetGeometry(&score_tb.base, TABLE_X, TABLE_Y, 0.0, TABLE_W, TABLE_H, geometry_xyzwh_mask);
		UI_ResetLabelGeometry(&lb, 0.0, page_height - LABEL_H, page_width, LABEL_H);
		UI_ResetTextBrowserGeometry(&tb, TEXT_X, TEXT_Y, TEXT_W, TEXT_H);
	}
}

int UI_IdleFunc(void)
{
	if(!has_init)
		return 0;
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
	int m;
	for(m = 0; m < total_action_type; m++)
	{
		new_button(btns + m, Btn_Infos[m].x, Btn_Infos[m].y, 0.3, Btn_Infos[m].w, Btn_Infos[m].h, 2.0, Color_GetColor(black_color, 0.4), Color_GetColor(green_color, 0.4), Color_GetColor(black_color, 0.4), Color_GetColor(gray_color, 0.4), Color_GetColor(darkgreen_color, 0.4), Color_GetColor(black_color, 0.4), Btn_Infos[m].label);
		btns[m].fnt = &fnt;
	}
	new_label(&lb, 0.0, page_height - LABEL_H, 0.2, page_width, LABEL_H, 0, Color_GetColor(white_color, 0.4), Color_GetColor(green_color, 0.4), Color_GetColor(white_color, 0.0), "Game Over", NULL);
	new_scene_2d(&bg, 0.0f, 0.0f, page_width, page_height, 1.0, left_bottom_anchor_type, Color_GetColor(white_color, 0.0), NULL);
	new_scene_2d(&fg, 0.0f, 0.0f, page_width, page_height, 1.0, left_orientation_type | down_orientation_type, Color_GetColor(black_color, 0.1), NULL);
	lb.fnt = &fnt;
	new_score_table(&score_tb, TABLE_X, TABLE_Y, 0.05, TABLE_W, TABLE_H, 400, 20, 1, Color_GetColor(purple_color, 0.4), Color_GetColor(black_color, 0.4), Color_GetColor(orange_color, 0.4), Color_GetColor(green_color, 0.4));
	score_tb.fnt = &fnt;
	score_tb.game_mode = game_mode;
	new_text_browser(&tb, TEXT_X, TEXT_Y, 0.0, TEXT_W, TEXT_H, 4.0, 0.0, Color_GetColor(white_color, 0.0), Color_GetColor(black_color, 0.2), Color_GetColor(lightgreen_color, 0.2), Color_GetColor(darkgreen_color, 0.2), Color_GetColor(green_color, 0.4), NULL);
	tb.fnt = &fnt;
	has_init = 1;
}

void UI_DrawFunc(void)
{
	if(!has_init)
		return;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	OpenGL_Render3DOrtho(0.0, width, 0.0, height);
	{
		//glPolygonMode(GL_FRONT, GL_LINE);
		UI_RenderScene2D(&bg);
		UI_RenderScene2D(&fg);
		glPushMatrix();
		{
			glTranslatef(score_tb.x, score_tb.y, score_tb.z);
			UI_RenderScoreTable(&score_tb);
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
}

void UI_ReshapeFunc(int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	if(!has_init)
		return;
	GameMenu_SetGameOverPageSize(w, h);
}

void UI_FreeFunc(void)
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
	int m;
	for(m = 0; m < total_action_type; m++)
		delete_button(btns + m);
	delete_text_browser(&tb);
	delete_label(&lb);
	delete_score_table(&score_tb);
	delete_scene_2d(&bg);
	delete_scene_2d(&fg);
	game_mode = NULL;
	GameMenu_ResetGameOver();
	has_init = 0;

	NL_PAGE_DESTROY_DEBUG(PAGE_NAME)
}

void GameMenu_ResetGameOver(void)
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
				UI_EnterAction(REPLAY_GAME);
				return 1;
			}
			break;
		case Harmattan_K_BackSpace:
		case Harmattan_K_Escape:
			if(pressed)
			{
				UI_EnterAction(OPEN_MAIN_MENU);
				return 1;
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

void UI_EnterAction(void *data)
{
	if(!data)
		return;
	const char *func = (const char *)data;
	const void *slot = SignalSlot_GetAction(func);
	if(slot)
		((void__func__void)slot)();
}

int UI_ClickFunc(int button, int x, int y)
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
			if(Btn_Infos[i].func)
			{
				Btn_Infos[i].func(Btn_Infos[i].data);
			}
			return 1;
		}
	}
	return 0;
}

void UI_OpenGameOver(death_game_mode *m)
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
	game_mode = m;
	score_tb.game_mode = game_mode;
	if(game_mode && game_mode->state == finish_game_type)
	{
		int *group = NEW_II(int, game_mode->group_count);
		int *character = NEW_II(int, game_mode->group_count);
		int i;
		for(i = 0; i < game_mode->group_count; i++)
		{
			group[i] = -1;
			character[i] = -1;
		}
		int point = 0;
		for(i = 0; i < game_mode->group_count; i++)
		{
			point = KARIN_MAX(game_mode->group_point[i], point);
		}
		int index = 0;
		for(i = 0; i < game_mode->group_count; i++)
		{
			if(game_mode->group_point[i] == point)
			{
				group[index] = i;
				index++;
			}
		}
		int kill = 0;
		int death = -1;
		for(i = 0; i < index; i++)
		{
			int j;
			for(j = 0; j < game_mode->group_person_count[group[i]]; j++)
			{
				kill = KARIN_MAX(game_mode->group_character[group[i]][j]->score.kill, kill);
			}
		}
		int index2 = 0;
		for(i = 0; i < index; i++)
		{
			int j;
			for(j = 0; j < game_mode->group_person_count[group[i]]; j++)
			{
				if(game_mode->group_character[group[i]][j]->score.kill == kill)
				{
					character[index2] = game_mode->group_character[group[i]][j]->index;
					index2++;
				}
			}
		}
		for(i = 0; i < index2; i++)
		{
			if(death == -1)
				death = game_mode->characters[character[i]].score.death;
			else
				death = KARIN_MIN(game_mode->characters[character[i]].score.death, death);
		}
		int index3 = 0;
		for(i = 0; i < index2; i++)
		{
			if(game_mode->characters[character[i]].score.death != death)
				character[i] = -1;
			else
				index3++;
		}
		char **group_name = NEW_II(char *, index);
		int *character_name = NEW_II(int, index3);
		for(i = 0; i < index; i++)
		{
			group_name[i] = itostr(game_mode->group_id[group[i]]);
		}
		int index4 = 0;
		for(i = 0; i < index2; i++)
		{
			if(character[i] != -1)
			{
				character_name[index4] = character[i];
				index4++;
			}
		}
		char str[200];
		memset(str, '\0', 200);
		char *p = str;
		strcat(p, "Winner group : \n");
		p += strlen("Winner group : \n");
		for(i = 0; i < index; i++)
		{
			strcat(p, "Group-");
			p += strlen("Group-");
			strcat(p, group_name[i]);
			p += strlen(group_name[i]);
			strcat(p, "\n");
			p += 1;
		}
		strcat(p, "\n");
		p += 1;
		strcat(p, "MVP : \n");
		p += strlen("MVP : \n");
		for(i = 0; i < index4; i++)
		{
			strcat(p, game_mode->characters[character_name[i]].name);
			p += strlen(game_mode->characters[character_name[i]].name);
			strcat(p, "\n");
			p += 1;
		}

		UI_SetBrowserText(&tb, str);
		for(i = 0; i < index; i++)
		{
			free(group_name[i]);
		}
		free(group_name);
		free(character_name);
		free(group);
		free(character);
	}
}

void UI_GameOverRegisterFunction(void)
{
	glk_function func;

	func = REGISTER_RENDER_FUNCTION(UI);
	Main3D_SetCurRenderPage(PAGE_NAME, &func);
}
