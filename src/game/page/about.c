#include "about.h"
#include "gl_3d_main.h"
#include "button.h"
#include "label.h"
#include "text_browser.h"
#include "action_signal_slot.h"
#include "game_std.h"

#define PAGE_NAME "About"

#define TEXT_BROWSER_X 150
#define TEXT_BROWSER_Y 80
#define TEXT_BROWSER_W 554
#define TEXT_BROWSER_H 300
#define BUTTON_BACK_X 600
#define BUTTON_BACK_Y 10
#define BUTTON_W 180
#define BUTTON_H 60
#define LABEL_H 80

#define TEXT_MOVE_UNIT 10

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

static void Menu_ResetAbout(void);
static void Menu_BackAction(void);
static void Menu_SetAboutPageSize(GLsizei w, GLsizei h);

static button back_btn;
static text_browser tb;
static label lb;
static bool_t has_init = 0;
static GLsizei page_width = HARMATTAN_FULL_WIDTH;
static GLsizei page_height = HARMATTAN_FULL_HEIGHT;

void Menu_SetAboutPageSize(GLsizei w, GLsizei h)
{
	if(page_width == w && page_height == h)
		return;
	page_width = w;
	page_height = h;
	if(has_init)
	{
		UI_ResetButtonGeometry(&back_btn.base, BUTTON_BACK_X, BUTTON_BACK_Y, BUTTON_W, BUTTON_H);
		UI_ResetTextBrowserGeometry(&tb.base, TEXT_BROWSER_X, TEXT_BROWSER_Y, TEXT_BROWSER_W, TEXT_BROWSER_H);
		UI_ResetLabelGeometry(&lb.base, 0.0, page_height - LABEL_H, page_width, LABEL_H);
	}
}

int UI_IdleFunc(void)
{
	if(!has_init)
		return 0;
	if(key_state[Harmattan_K_Up] || key_state[Harmattan_K_w] || key_state[Harmattan_K_W])
		UI_MoveTextBrowser(&tb, -TEXT_MOVE_UNIT * delta_time);
	else if(key_state[Harmattan_K_Down] || key_state[Harmattan_K_s] || key_state[Harmattan_K_S])
		UI_MoveTextBrowser(&tb, TEXT_MOVE_UNIT * delta_time);
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
			glTranslatef(tb.base.x, tb.base.y, tb.base.z);
			UI_RenderTextBrowser(&tb);
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

void UI_ReshapeFunc(int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	if(!has_init)
		return;
	Menu_SetAboutPageSize(w, h);
}

void UI_FreeFunc(void)
{
	if(!has_init)
		return;
	delete_button(&back_btn);
	delete_label(&lb);
	delete_text_browser(&tb);
	Menu_ResetAbout();
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
		case Harmattan_K_Return:
		case Harmattan_K_KP_Enter:
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
				UI_MoveTextBrowser(&tb, -TEXT_MOVE_UNIT * delta_time);
			}
			break;
		case Harmattan_K_Down:
		case Harmattan_K_s:
		case Harmattan_K_S:
			if(pressed)
			{
				UI_MoveTextBrowser(&tb, TEXT_MOVE_UNIT * delta_time);
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
	if(UI_PointInWidget(&back_btn.base, x, gl_y))
	{
		back_btn.highlight = pressed ? GL_TRUE : GL_FALSE;
		return 1;
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
		int gl_y = height - y;
		int last_x = x - dx;
		int last_gl_y = height - (y - dy);
		if(UI_PointInWidget(&tb.base, x, gl_y))
		{
			res = UI_SlideTextBrowser(&tb, -dy);
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

void UI_AboutRegisterFunction(void)
{
	glk_function func;

	func = REGISTER_RENDER_FUNCTION(UI);
	Main3D_PushRenderPage(PAGE_NAME, &func);
}

void Menu_BackAction(void)
{
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
	if(UI_PointInWidget(&back_btn.base, x, gl_y))
	{
		Menu_BackAction();
		return 1;
	}
	return 0;
}

void Menu_InitAbout(void)
{
	if(has_init)
		return;
	//Menu_SetAboutPageSize(width, height);
	new_button(&back_btn, BUTTON_BACK_X, BUTTON_BACK_Y, 0.3, BUTTON_W, BUTTON_H, 2.0, X11_COLOR(white), X11_COLOR(green), X11_COLOR(black), X11_COLOR(gray), X11_COLOR(darkgreen), X11_COLOR(black), "Back");
	back_btn.fnt = &fnt;
	new_text_browser(&tb, TEXT_BROWSER_X, TEXT_BROWSER_Y, 0.0, TEXT_BROWSER_W, TEXT_BROWSER_H, 4.0, 0.0, X11_COLOR(black), X11_COLOR(black), X11_COLOR(lightgreen), X11_COLOR(darkgreen), X11_COLOR(green), NULL);
	tb.fnt = &fnt;
	new_label(&lb, 0.0, page_height - LABEL_H, 0.3, page_width, LABEL_H, 0, Color_GetColor(white_color, 0.4), X11_COLOR(green), Color_GetColor(black_color, 0.0), NULL, NULL);
	lb.fnt = &fnt;
	has_init = 1;
}

void Menu_ResetAbout(void)
{
	page_width = width;
	page_height = height;
}

void Menu_SetAboutTitleAndContent(const char *title, const char *content)
{
	if(!has_init)
		return;
	if(title)
	{
		FREE_PTR(lb.text)
			lb.text = strdup(title);
	}
	if(content)
	{
		UI_SetBrowserText(&tb, content);
	}
}
