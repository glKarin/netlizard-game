#include "splash.h"

#include "gl_3d_main.h"
#include "game_util.h"
#include "label.h"
#include "action_signal_slot.h"
#include "nl_std.h"
#include "game_std.h"

#include <string.h>
#include <stdlib.h>

#define LABEL_SHOW_INTERVAL 400
#define CONTENT_H 80

typedef enum _show_splash_state_type
{
	ready_show_splash_type = 0,
	fade_out_show_splash_type,
	wait_show_splash_type,
	fade_in_show_splash_type,
	finish_show_splash_type
} show_splash_state_type;

static void Splash_ResetSplash(void);
static int Splash_IdleEventFunc(void);
static void Splash_DrawFunc(void);
static void Splash_ReshapeFunc(int w, int h);
static void Splash_InitFunc(void);
static void Splash_FreeFunc(void);
static int Splash_KeyEventFunc(int key, int act, int pressed, int x, int y);
static int Splash_MouseClickEventFunc(int button, int x, int y);
static void Splash_SetPageSize(GLsizei w, GLsizei h);

static long long show_splash_fade_out_interval = 3000;
static long long show_splash_fade_in_interval = 2000;
static long long show_splash_start_time = 0;
static show_splash_state_type show_splash_state = ready_show_splash_type;
static int show_splash_started = 0;
static char *splash_file = NULL;
static char *show_finished_action = NULL;
static scene_2d fg;
static scene_2d bg;
static label content;
static GLuint label_blink_count = 0;
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

void Splash_SetSplashShowTimeInterval(long long t1, long long t2)
{
	if(has_init)
		return;
	if(show_splash_started)
		return;
	if(t1 > 0)
		show_splash_fade_out_interval = t1;
	if(t2 > 0)
		show_splash_fade_in_interval = t2;
}

int Splash_IdleEventFunc(void)
{
	if(!has_init)
		return 0;
	if(show_splash_state == finish_show_splash_type && show_finished_action)
	{
		const void *slot = SignalSlot_GetAction(show_finished_action);
		if(slot)
			((void__func__void)slot)();
		return 1;
	}
	else if(show_splash_state == wait_show_splash_type)
	{
		if(show_splash_start_time != 0)
		{
			long long time = Game_GetGameTime();
			long long i = (time - show_splash_start_time) / LABEL_SHOW_INTERVAL;
			if(i != label_blink_count)
			{
				label_blink_count = i;
				content.base.visible ^= GL_TRUE;
			}
			return 1;
		}
		return 0;
	}
	else if(show_splash_state != fade_in_show_splash_type && show_splash_state != fade_out_show_splash_type)
		return 0;

	if(show_splash_start_time != 0)
	{
		long long time = Game_GetGameTime();
		double per = 0.0;
		if(show_splash_state == fade_out_show_splash_type)
		{
			per = (double)(time - show_splash_start_time) / (double)show_splash_fade_out_interval;
			per = 1.0 - per;
			if(per <= 0.0)
			{
				per = 0.0;
				show_splash_state = wait_show_splash_type;
			}
		}
		else
		{
			per = (double)(time - show_splash_start_time) / (double)show_splash_fade_in_interval;
			if(per >= 1.0)
			{
				per = 1.0;
				show_splash_state = finish_show_splash_type;
			}
		}
		fg.color[3] = (GLfloat)per;
		return 1;
	}
	return 0;
}

void Splash_InitFunc(void)
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

void Splash_DrawFunc(void)
{
	if(!has_init)
		return;
	if(show_splash_state == ready_show_splash_type)
	{
		show_splash_start_time = Game_GetGameTime();
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

void Splash_ReshapeFunc(int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	if(!has_init)
		return;
	Splash_SetPageSize(w, h);
}

void Splash_FreeFunc(void)
{
	if(!has_init)
		return;
	FREE_PTR(splash_file)
		delete_scene_2d(&fg);
	delete_scene_2d(&bg);
	delete_label(&content);
	FREE_PTR(show_finished_action)
	Splash_ResetSplash();
	has_init = 0;
}

void Splash_RegisterFunction(void)
{
	Main3D_SetInitFunction(Splash_InitFunc);
	Main3D_SetDrawFunction(Splash_DrawFunc);
	Main3D_SetFreeFunction(Splash_FreeFunc);
	Main3D_SetKeyEventFunction(Splash_KeyEventFunc);
	Main3D_SetIdleEventFunction(Splash_IdleEventFunc);
	Main3D_SetReshapeFunction(Splash_ReshapeFunc);
	Main3D_SetMouseEventFunction(NULL);
	Main3D_SetMouseMotionEventFunction(NULL);
	Main3D_SetMouseClickEventFunction(Splash_MouseClickEventFunc);
	show_splash_started = 1;
}

int Splash_KeyEventFunc(int key, int act, int pressed, int x, int y)
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
					show_splash_start_time = Game_GetGameTime();
				}
				return 1;
			}
			break;
	}
	return 0;
}

int Splash_MouseClickEventFunc(int button, int x, int y)
{
	if(!has_init)
		return;
	if(show_splash_state == wait_show_splash_type)
	{
		show_splash_state = fade_in_show_splash_type;
		show_splash_start_time = Game_GetGameTime();
		return 1;
	}
	return 0;
}

void Splash_ResetSplash(void)
{
	show_splash_fade_out_interval = 3000;
	show_splash_fade_in_interval = 2000;
	show_splash_start_time = 0;
	show_splash_state = ready_show_splash_type;
	show_splash_started = 0;
	//splash_file = NULL;
	label_blink_count = 0;
	page_width = width;
	page_height = height;
}
