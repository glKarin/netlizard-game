#include "loading.h"

#include "progress_bar.h"
#include "label.h"
#include "gl_3d_main.h"
#include "nl_std.h"
#include "action_signal_slot.h"
#include "game_std.h"

#include <string.h>
#include <stdlib.h>

#define LABEL_SHOW_INTERVAL 0.4

#define LABEL_H 40
#define LABEL_Y 80
#define CONTENT_H 80
#define TITLE_H 120
#define PROGRESS_BAR_Y 40
#define PROGRESS_BAR_W 600
#define PROGRESS_BAR_H 20

static const char *Content_Text[] = {
	"Press Return or click anywhere to continue",
	"Press Return or click anywhere to return"
};

static int Menu_LoadingIdleEventFunc(void);
static void Menu_LoadingDrawFunc(void);
static void Menu_LoadingReshapeFunc(int w, int h);
static void Menu_LoadingInitFunc(void);
static void Menu_LoadingFreeFunc(void);
static int Menu_LoadingKeyEventFunc(int key, int act, int pressed, int x, int y);
static int Menu_LoadingMouseClickEventFunc(int button, int x, int y);
static void Menu_ResetLoading(void);
static void Menu_SetLoadingPageSize(GLsizei w, GLsizei h);

static int loading_progress = 0;
static int loading_successful = 0;
static label lb;
static label content;
static label title;
static progress_bar bar;
static char *loading_finished_action = NULL;
static char *loading_fail_action = NULL;
static float idle_time = 0.0f;
static GLboolean auto_load = GL_FALSE;
static bool_t has_init = 0;
static GLsizei page_width = HARMATTAN_FULL_WIDTH;
static GLsizei page_height = HARMATTAN_FULL_HEIGHT;

void Menu_SetLoadingPageSize(GLsizei w, GLsizei h)
{
	if(page_width == w && page_height == h)
		return;
	page_width = w;
	page_height = h;
	if(has_init)
	{
		UI_ResetLabelGeometry(&lb, 0.0, LABEL_Y, page_width, LABEL_H);
		UI_ResetLabelGeometry(&content, 0.0, height / 2 - CONTENT_H / 2, page_width, CONTENT_H);
		UI_ResetLabelGeometry(&title, 0.0, page_height - TITLE_H, page_width, TITLE_H);
		UI_ResetProgressBarGeometry(&bar, page_width / 2 - PROGRESS_BAR_W / 2, PROGRESS_BAR_Y, PROGRESS_BAR_W, PROGRESS_BAR_H);
	}
}

void Menu_SetLoadingFinishedAction(const char *signal)
{
	SET_TEXT(loading_finished_action, signal)
}

void Menu_SetLoadingFailAction(const char *signal)
{
	SET_TEXT(loading_fail_action, signal)
}

void Menu_LoadingUpdateProgressFunc(int has_err, int p, const char *info)
{
	if(!has_init)
		return;
	if(p < 0 || p > 100)
		return;
	loading_progress = p;
	loading_successful = !has_err;
	bar.progress = (GLfloat)loading_progress / 100.0;
	SET_TEXT(lb.text, info)
	if(loading_progress == 100)
	{
		if(auto_load)
		{
			karinPostDrawGL();
			if(loading_successful)
			{
				if(loading_finished_action)
				{
					const void *slot = SignalSlot_GetAction(loading_finished_action);
					if(slot)
						((void__func__void)slot)();
				}
			}
			else
			{
				if(loading_fail_action)
				{
					const void *slot = SignalSlot_GetAction(loading_fail_action);
					if(slot)
						((void__func__void)slot)();
				}
			}
		}
		else
		{
			if(loading_successful)
				SET_TEXT(content.text, Content_Text[0])
			else
				SET_TEXT(content.text, Content_Text[1])
			karinPostDrawGL();
		}
	}
	else
		karinPostDrawGL();
}

int Menu_LoadingIdleEventFunc(void)
{
	if(!has_init)
		return 0;
	if(loading_progress == 100 && !auto_load)
	{
		idle_time += delta_time;
		if(idle_time < LABEL_SHOW_INTERVAL)
			return 0;
		while(idle_time - LABEL_SHOW_INTERVAL > 0.0f)
			idle_time -= LABEL_SHOW_INTERVAL;
		content.base.visible ^= GL_TRUE;
		return 1;
	}
	return 0;
}

void Menu_LoadingInitFunc(void)
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
	//Menu_SetLoadingPageSize(width, height);
	new_label(&lb, 0.0, LABEL_Y, 0.1, page_width, LABEL_H, 0, Color_GetColor(white_color, 0.0), X11_COLOR(green), Color_GetColor(white_color, 0.0), NULL, NULL);
	new_label(&content, 0.0, page_height / 2 - CONTENT_H / 2, 0.1, page_width, CONTENT_H, 0, Color_GetColor(white_color, 0.0), X11_COLOR(green), Color_GetColor(white_color, 0.0), "Loading...", NULL);
	new_label(&title, 0.0, page_height - TITLE_H, 0.2, page_width, TITLE_H, 0, Color_GetColor(white_color, 0.0), X11_COLOR(green), Color_GetColor(white_color, 0.0), NULL, NULL);
	lb.fnt = &fnt;
	content.fnt = &fnt;
	title.fnt = &fnt;
	new_progress_bar(&bar, page_width / 2 - PROGRESS_BAR_W / 2, PROGRESS_BAR_Y, 0.2, PROGRESS_BAR_W, PROGRESS_BAR_H, 0, 0, Color_GetColor(black_color, 0.0), X11_COLOR(black), X11_COLOR(green));
	has_init = 1;
}

void Menu_LoadingDrawFunc(void)
{
	if(!has_init)
		return;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	OpenGL_Render3DOrtho(0.0, width, 0.0, height);
	{
		//glPolygonMode(GL_FRONT, GL_LINE);
		glPushMatrix();
		{
			glTranslatef(bar.base.x, bar.base.y, bar.base.z);
			UI_RenderProgressBar(&bar);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(lb.base.x, lb.base.y, lb.base.z);
			UI_RenderLabel(&lb);
		}
		glPopMatrix();
		if(loading_progress == 100 && content.base.visible && !auto_load)
		{
			glPushMatrix();
			{
				glTranslatef(content.base.x, content.base.y, content.base.z);
				UI_RenderLabel(&content);
			}
			glPopMatrix();
		}
		glPushMatrix();
		{
			glTranslatef(title.base.x, title.base.y, title.base.z);
			UI_RenderLabel(&title);
		}
		glPopMatrix();
	}
}

void Menu_LoadingReshapeFunc(int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	if(!has_init)
		return;
}

void Menu_LoadingFreeFunc(void)
{
	if(!has_init)
		return;
	delete_label(&lb);
	delete_label(&title);
	delete_label(&content);
	delete_progress_bar(&bar);
	FREE_PTR(loading_finished_action)
		FREE_PTR(loading_fail_action)
	Menu_ResetLoading();
	has_init = 0;
}

void Menu_RegisterLoadingFunction(void)
{
	Main3D_SetInitFunction(Menu_LoadingInitFunc);
	Main3D_SetDrawFunction(Menu_LoadingDrawFunc);
	Main3D_SetFreeFunction(Menu_LoadingFreeFunc);
	Main3D_SetKeyEventFunction(Menu_LoadingKeyEventFunc);
	Main3D_SetIdleEventFunction(Menu_LoadingIdleEventFunc);
	Main3D_SetReshapeFunction(Menu_LoadingReshapeFunc);
	Main3D_SetMouseEventFunction(NULL);
	Main3D_SetMouseMotionEventFunction(NULL);
	Main3D_SetMouseClickEventFunction(Menu_LoadingMouseClickEventFunc);
}

int Menu_LoadingKeyEventFunc(int key, int act, int pressed, int x, int y)
{
	if(!has_init)
		return 0;
	switch(key)
	{
		case Harmattan_K_Return:
		case Harmattan_K_KP_Enter:
			if(pressed)
			{
				if(loading_progress == 100 && !auto_load)
				{
					if(loading_successful)
					{
						if(loading_finished_action)
						{
							const void *slot = SignalSlot_GetAction(loading_finished_action);
							if(slot)
								((void__func__void)slot)();
						}
					}
					else
					{
						if(loading_fail_action)
						{
							const void *slot = SignalSlot_GetAction(loading_fail_action);
							if(slot)
								((void__func__void)slot)();
						}
					}
				}
				return 1;
			}
			break;
	}
	return 0;
}

int Menu_LoadingMouseClickEventFunc(int button, int x, int y)
{
	if(!has_init)
		return 0;
	if(loading_progress == 100 && !auto_load)
	{
		if(loading_successful)
		{
			if(loading_finished_action)
			{
				const void *slot = SignalSlot_GetAction(loading_finished_action);
				if(slot)
					((void__func__void)slot)();
			}
		}
		else
		{
			if(loading_fail_action)
			{
				const void *slot = SignalSlot_GetAction(loading_fail_action);
				if(slot)
					((void__func__void)slot)();
			}
		}
		return 1;
	}
	return 0;
}

void Menu_SetLoadingTitle(const char *str)
{
	if(!has_init)
		return;
	SET_TEXT(title.text, str)
}

void Menu_SetLoadingAuto(GLboolean b)
{
	if(auto_load != b)
		auto_load = b;
}

void Menu_ResetLoading(void)
{
	loading_progress = 0;
	loading_successful = 0;
	idle_time = 0.0f;
	auto_load = GL_FALSE;
	page_width = width;
	page_height = height;
}
