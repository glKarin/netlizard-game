#include "game_over.h"
#include "component/button.h"
#include "component/label.h"
#include "nl_std.h"
#include "game_std.h"
#include "action_signal_slot.h"
#include "score_table.h"
#include "component/text_browser.h"

#define BUTTON_REPLAY_X 700
#define BUTTON_REPLAY_Y 100
#define BUTTON_BACK_X 700
#define BUTTON_BACK_Y 0
#define BUTTON_W 120
#define BUTTON_H 60
#define TABLE_X 0
#define TABLE_Y 0
#define TABLE_W 650
#define TABLE_H 400
#define TEXT_X 654
#define TEXT_Y 200
#define TEXT_W 200
#define TEXT_H 200
#define LABEL_H 80

static int GameMenu_GameOverIdleEventFunc(void);
static int GameMenu_GameOverKeyEventFunc(int k, int a, int p, int x, int y);
static int GameMenu_GameOverMouseEventFunc(int b, int p, int x, int y);
static int GameMenu_GameOverMouseClickEventFunc(int b, int x, int y);
static int GameMenu_GameOverMouseMotionEventFunc(int b, int p, int x, int y, int dx, int dy);
static void GameMenu_GameOverDrawFunc(void);
static void GameMenu_GameOverReshapeFunc(int w, int h);
static void GameMenu_GameOverInitFunc(void);
static void GameMenu_GameOverFreeFunc(void);
static void GameMenu_GameOverEnterAction(const char *func);
static void GameMenu_SetGameOverPageSize(GLsizei w, GLsizei h);
static void GameMenu_ResetGameOver(void);

static button replay_btn;
static button back_btn;
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
		UI_ResetButtonGeometry(&replay_btn, BUTTON_REPLAY_X, BUTTON_REPLAY_Y, BUTTON_W, BUTTON_H);
		UI_ResetButtonGeometry(&back_btn, BUTTON_BACK_X, BUTTON_BACK_Y, BUTTON_W, BUTTON_H);
		//UI_SetWidgetGeometry(&score_tb.base, TABLE_X, TABLE_Y, 0.0, TABLE_W, TABLE_H, geometry_xyzwh_mask);
		UI_ResetLabelGeometry(&lb, 0.0, page_height - LABEL_H, page_width, LABEL_H);
		UI_ResetTextBrowserGeometry(&tb, TEXT_X, TEXT_Y, TEXT_W, TEXT_H);
	}
}

int GameMenu_GameOverIdleEventFunc(void)
{
	if(!has_init)
		return 0;
	return 1;
}

void GameMenu_GameOverInitFunc(void)
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

	if(has_init)
		return;
	new_button(&replay_btn, BUTTON_REPLAY_X, BUTTON_REPLAY_Y, 0.1, BUTTON_W, BUTTON_H,  2.0, Color_GetColor(black_color, 0.4), Color_GetColor(green_color, 0.4), Color_GetColor(black_color, 0.4), Color_GetColor(gray_color, 0.4), Color_GetColor(darkgreen_color, 0.4), Color_GetColor(black_color, 0.4), "Replay");
	new_button(&back_btn, BUTTON_BACK_X, BUTTON_BACK_Y, 0.1, BUTTON_W, BUTTON_H, 2.0, Color_GetColor(black_color, 0.4), Color_GetColor(green_color, 0.4), Color_GetColor(black_color, 0.4), Color_GetColor(gray_color, 0.4), Color_GetColor(darkgreen_color, 0.4), Color_GetColor(black_color, 0.4), "Back");
	replay_btn.fnt = &fnt;
	back_btn.fnt = &fnt;
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

void GameMenu_GameOverDrawFunc(void)
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
		glPushMatrix();
		{
			glTranslatef(replay_btn.base.x, replay_btn.base.y, replay_btn.base.z);
			UI_RenderButton(&replay_btn);
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

void GameMenu_GameOverReshapeFunc(int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	if(!has_init)
		return;
	GameMenu_SetGameOverPageSize(w, h);
}

void GameMenu_GameOverFreeFunc(void)
{
	if(!has_init)
		return;
	if(bg.tex)
	{
		if(glIsTexture(bg.tex -> texid))
			glDeleteTextures(1, &bg.tex -> texid);
		free(bg.tex);
		bg.tex = NULL;
	}
	delete_button(&replay_btn);
	delete_button(&back_btn);
	delete_text_browser(&tb);
	delete_label(&lb);
	delete_score_table(&score_tb);
	delete_scene_2d(&bg);
	delete_scene_2d(&fg);
	game_mode = NULL;
	GameMenu_ResetGameOver();
	has_init = 0;
}

void GameMenu_ResetGameOver(void)
{
	page_width = width;
	page_height = height;
}

// for all X event pointer coord y, Using left-down as ori, like OpenGL, and not left-top of X11. so the y coord need to convert by screen height - y, and delta_y is invert.
int GameMenu_GameOverKeyEventFunc(int key, int act, int pressed, int x, int y)
{
	if(!has_init)
		return 0;
	switch(key)
	{
		case Harmattan_K_Return:
		case Harmattan_K_KP_Enter:
			if(pressed)
			{
				GameMenu_GameOverEnterAction(REPLAY_GAME);
				return 1;
			}
			break;
		case Harmattan_K_BackSpace:
		case Harmattan_K_Escape:
			if(pressed)
			{
				GameMenu_GameOverEnterAction(OPEN_MAIN_MENU);
				return 1;
			}
			break;
		default:
			break;
	}
	return 0;
}

int GameMenu_GameOverMouseEventFunc(int button, int pressed, int x, int gl_y)
{
	if(!has_init)
		return 0;
	if(UI_PointInWidget(&replay_btn.base, x, gl_y))
	{
		replay_btn.highlight = pressed ? GL_TRUE : GL_FALSE;
		return 1;
	}
	else if(UI_PointInWidget(&back_btn.base, x, gl_y))
	{
		back_btn.highlight = pressed ? GL_TRUE : GL_FALSE;
		return 1;
	}
	return 0;
}

int GameMenu_GameOverMouseMotionEventFunc(int button, int pressed, int x, int gl_y, int dx, int dy)
{
	if(!has_init)
		return 0;
	int res = 0;
	if(pressed)
	{
		int last_x = x - dx;
		int last_gl_y = gl_y - dy;
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
		if(UI_PointInWidget(&replay_btn.base, x, gl_y) && !UI_PointInWidget(&replay_btn.base, last_x, last_gl_y))
		{
			replay_btn.highlight = GL_TRUE;
			res |= 1;
		}
		else if(!UI_PointInWidget(&replay_btn.base, x, gl_y) && UI_PointInWidget(&replay_btn.base, last_x, last_gl_y))
		{
			replay_btn.highlight = GL_FALSE;
			res |= 1;
		}
	}

	return res;
}

void GameMenu_GameOverEnterAction(const char *func)
{
	const void *slot = SignalSlot_GetAction(func);
	if(slot)
		((void__func__void)slot)();
}

int GameMenu_GameOverMouseClickEventFunc(int button, int x, int gl_y)
{
	if(!has_init)
		return 0;
	if(UI_PointInWidget(&replay_btn.base, x, gl_y))
	{
		GameMenu_GameOverEnterAction(REPLAY_GAME);
		return 1;
	}
	else if(UI_PointInWidget(&back_btn.base, x, gl_y))
	{
		GameMenu_GameOverEnterAction(OPEN_MAIN_MENU);
		return 1;
	}
	return 0;
}

void GameMenu_OpenGameOver(death_game_mode *m)
{
	if(!has_init)
		return;
	if(bg.tex)
	{
		if(glIsTexture(bg.tex -> texid))
			glDeleteTextures(1, &bg.tex -> texid);
		free(bg.tex);
		bg.tex = NULL;
	}
	bg.tex = new_OpenGL_texture_2d_from_buffer_with_glReadPixels(0, 0, width, height, GL_RGBA);
	game_mode = m;
	score_tb.game_mode = game_mode;
	if(game_mode && game_mode -> state == finish_game_type)
	{
		int *group = NEW_II(int, game_mode -> group_count);
		int *character = NEW_II(int, game_mode -> group_count);
		int i;
		for(i = 0; i < game_mode -> group_count; i++)
		{
			group[i] = -1;
			character[i] = -1;
		}
		int point = 0;
		for(i = 0; i < game_mode -> group_count; i++)
		{
			point = KARIN_MAX(game_mode -> group_point[i], point);
		}
		int index = 0;
		for(i = 0; i < game_mode -> group_count; i++)
		{
			if(game_mode -> group_point[i] == point)
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
			for(j = 0; j < game_mode -> group_person_count[group[i]]; j++)
			{
				kill = KARIN_MAX(game_mode -> group_character[group[i]][j] -> score.kill, kill);
			}
		}
		int index2 = 0;
		for(i = 0; i < index; i++)
		{
			int j;
			for(j = 0; j < game_mode -> group_person_count[group[i]]; j++)
			{
				if(game_mode -> group_character[group[i]][j] -> score.kill == kill)
				{
					character[index2] = game_mode -> group_character[group[i]][j] -> index;
					index2++;
				}
			}
		}
		for(i = 0; i < index2; i++)
		{
			if(death == -1)
				death = game_mode -> characters[character[i]].score.death;
			else
				death = KARIN_MIN(game_mode -> characters[character[i]].score.death, death);
		}
		int index3 = 0;
		for(i = 0; i < index2; i++)
		{
			if(game_mode -> characters[character[i]].score.death != death)
				character[i] = -1;
			else
				index3++;
		}
		char **group_name = NEW_II(char *, index);
		int *character_name = NEW_II(int, index3);
		for(i = 0; i < index; i++)
		{
			group_name[i] = itostr(game_mode -> group_id[group[i]]);
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
			strcat(p, game_mode -> characters[character_name[i]].name);
			p += strlen(game_mode -> characters[character_name[i]].name);
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

glk_function * new_game_over(glk_function *men)
{
	RETURN_PTR(m, men, glk_function)
		m -> init_func = GameMenu_GameOverInitFunc;
	m -> draw_func = GameMenu_GameOverDrawFunc;
	m -> free_func = GameMenu_GameOverFreeFunc;
	m -> idle_func = GameMenu_GameOverIdleEventFunc;
	m -> key_func = GameMenu_GameOverKeyEventFunc;
	m -> motion_func = GameMenu_GameOverMouseMotionEventFunc;
	m -> reshape_func = GameMenu_GameOverReshapeFunc;
	m -> mouse_func = GameMenu_GameOverMouseEventFunc;
	m -> click_func = GameMenu_GameOverMouseClickEventFunc;
	return m;
}

