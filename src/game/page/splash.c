#include "splash.h"

#include "gl_3d_main.h"
#include "game_util.h"
#include "label.h"
#include "action_signal_slot.h"
#include "nl_std.h"
#include "game_std.h"

#include <string.h>
#include <stdlib.h>

#define PAGE_NAME "Splash"

#define LABEL_SHOW_INTERVAL 0.4
#define	FADE_OUT_UNIT 0.4
#define	FADE_IN_UNIT 0.8
#define CONTENT_H 80

typedef enum _show_splash_state_type
{
	ready_show_splash_type = 0,
	fade_out_show_splash_type,
	wait_show_splash_type,
	fade_in_show_splash_type,
	finish_show_splash_type
} show_splash_state_type;

static void UI_ResetSplash(void);
static int UI_IdleFunc(void);
static void UI_DrawFunc(void);
static void UI_ReshapeFunc(int w, int h);
static void UI_InitFunc(void);
static void UI_FreeFunc(void);
static int UI_KeyFunc(int key, int act, int pressed, int x, int y);
static int UI_ClickFunc(int button, int x, int y);
static void Splash_SetPageSize(GLsizei w, GLsizei h);

static Main3DStoreFunction_f UI_StoreFunc = NULL;
static Main3DRestoreFunction_f UI_RestoreFunc = NULL;
static Main3DMouseMotionFunction UI_MotionFunc = NULL;
static Main3DMouseFunction UI_MouseFunc = NULL;

static float show_splash_fade_out_unit = FADE_OUT_UNIT;
static float show_splash_fade_in_unit = FADE_IN_UNIT;
static show_splash_state_type show_splash_state = ready_show_splash_type;
static int show_splash_started = 0;
static char *splash_file = NULL;
static char *show_finished_action = NULL;
static scene_2d fg;
static scene_2d bg;
static label content;
static float idle_time = 0.0f;
static float per = 1.0f;
static GLsizei page_width = HARMATTAN_FULL_WIDTH;
static GLsizei page_height = HARMATTAN_FULL_HEIGHT;
static bool_t has_init = 0;

void Splash_SetPageSize(GLsizei w, GLsizei h)
{
	if(page_width == w && page_height == h)
		return;
	page_width = w;
	page_height = h;
	if(has_init)
	{
		UI_ResizeScene2D(&bg, page_width, page_height);
		UI_ResizeScene2D(&fg, page_width, page_height);
		UI_ResetLabelGeometry(&content, 0.0, page_height / 2 - CONTENT_H / 2, page_width, CONTENT_H);
	}
}

void Splash_SetSplashShowFinishedAction(const char *signal)
{
	if(show_splash_started)
		return;
	SET_TEXT(show_finished_action, signal)
}

void Splash_SetSplashImageFile(const char *file)
{
	if(has_init)
		return;
	if(!file)
		return;
	if(show_splash_started)
		return;
	FREE_PTR(splash_file)

		splash_file = strdup(file);
}

void Splash_SetSplashShowTimeInterval(float t1, float t2)
{
	if(has_init)
		return;
	if(show_splash_started)
		return;
	if(t1 > 0)
		show_splash_fade_out_unit = t1;
	if(t2 > 0)
		show_splash_fade_in_unit = t2;
}

int UI_IdleFunc(void)
{
	if(!has_init)
		return 0;
	if(show_splash_state == finish_show_splash_type && show_finished_action)
	{
		per = 1.0f;
		idle_time = 0.0f;
		const void *slot = SignalSlot_GetAction(show_finished_action);
		if(slot)
			((void__func__void)slot)();
		return 1;
	}
	else if(show_splash_state == wait_show_splash_type)
	{
		idle_time += delta_time;
		if(idle_time < LABEL_SHOW_INTERVAL)
			return 0;
		while(idle_time - LABEL_SHOW_INTERVAL > 0.0f)
			idle_time -= LABEL_SHOW_INTERVAL;

		content.base.visible ^= GL_TRUE;
		return 1;
	}
	else if(show_splash_state != fade_in_show_splash_type && show_splash_state != fade_out_show_splash_type)
	{
		per = 1.0f;
		idle_time = 0.0f;
		return 0;
	}

	idle_time = 0.0f;
	if(show_splash_state == fade_out_show_splash_type)
	{
		per -= delta_time * show_splash_fade_out_unit;
		if(per <= 0.0)
		{
			per = 0.0;
			show_splash_state = wait_show_splash_type;
		}
	}
	else
	{
		per += delta_time * show_splash_fade_in_unit;
		if(per >= 1.0)
		{
			per = 1.0;
			show_splash_state = finish_show_splash_type;
		}
	}
	fg.color[3] = (GLfloat)per;
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

	if(has_init)
		return;
	//Splash_SetPageSize(width, height);
	new_scene_2d(&fg, 0.0f, 0.0f, page_width, page_height, 1.0, left_bottom_anchor_type, X11_COLOR(black), NULL);
	new_scene_2d(&bg, 0.0f, 0.0f, page_width, page_height, 1.0, left_bottom_anchor_type, X11_COLOR(white), NULL);
	if(splash_file)
		bg.tex = new_OpenGL_texture_2d(splash_file);
	new_label(&content, 0.0, height / 2 - CONTENT_H / 2, 0.2, page_width, CONTENT_H, 0, Color_GetColor(white_color, 0.0), X11_COLOR(green), Color_GetColor(white_color, 0.0), "Press Return or click anywhere to continue", NULL);
	content.fnt = &fnt;
	has_init = 1;
}

void UI_DrawFunc(void)
{
	if(!has_init)
		return;
	if(show_splash_state == ready_show_splash_type)
	{
		show_splash_state = fade_out_show_splash_type;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	OpenGL_Render3DOrtho(0.0, width, 0.0, height);
	{
		UI_RenderScene2D(&bg);
		UI_RenderScene2D(&fg);
		if(show_splash_state == wait_show_splash_type && content.base.visible)
		{
			glPushMatrix();
			{
				glTranslatef(content.base.x, content.base.y, content.base.z);
				UI_RenderLabel(&content);
			}
			glPopMatrix();
		}
	}
}

void UI_ReshapeFunc(int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	if(!has_init)
		return;
	Splash_SetPageSize(w, h);
}

void UI_FreeFunc(void)
{
	if(!has_init)
		return;
	FREE_PTR(splash_file)
		delete_scene_2d(&fg);
	delete_scene_2d(&bg);
	delete_label(&content);
	FREE_PTR(show_finished_action)
		UI_ResetSplash();
	has_init = 0;

	NL_PAGE_DESTROY_DEBUG(PAGE_NAME)
}

void UI_SplashRegisterFunction(void)
{
	glk_function func;

	func = REGISTER_RENDER_FUNCTION(UI);
	Main3D_InitRenderPage(PAGE_NAME, &func);
	show_splash_started = 1;
}

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
				if(show_splash_state == wait_show_splash_type)
				{
					show_splash_state = fade_in_show_splash_type;
				}
				return 1;
			}
			break;
	}
	return 0;
}

int UI_ClickFunc(int button, int x, int y)
{
	if(!has_init)
		return 0;
	if(show_splash_state == wait_show_splash_type)
	{
		show_splash_state = fade_in_show_splash_type;
		return 1;
	}
	return 0;
}

void UI_ResetSplash(void)
{
	show_splash_fade_out_unit = FADE_OUT_UNIT;
	show_splash_fade_in_unit = FADE_IN_UNIT;
	show_splash_state = ready_show_splash_type;
	show_splash_started = 0;
	//splash_file = NULL;
	page_width = width;
	page_height = height;
	idle_time = 0.0f;
	per = 1.0f;
}

