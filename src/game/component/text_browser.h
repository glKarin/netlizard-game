#ifndef KARIN_GAME_TEXTBROWSER_H
#define KARIN_GAME_TEXTBROWSER_H

#include "widget_base.h"
#include "slider_bar.h"
#include "font.h"

typedef struct _text_browser
{
	base_widget base;
	GLfloat border_width;
	GLfloat border_color[4];
	GLfloat bg_color[4];
	char *text;
	GLfloat text_color[4];
	GLfloat spacing;
	GLclampf progress;
	slider_bar bar;
	const font *fnt;
	GLuint buffers[total_buffer_type];
	GLfloat text_height;
	GLuint line_count;
} text_browser;

text_browser * new_text_browser(text_browser *tb, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, const GLfloat spacing, GLfloat border_width, const GLfloat border_color[], const GLfloat bg_color[], const GLfloat bar_color[], const GLfloat bar_block_color[], const GLfloat text_color[], const char *text);
void UI_RenderTextBrowser(text_browser *tb);
void delete_text_browser(text_browser *tb);
void UI_SetBrowserText(text_browser *tb, const char *text);
int UI_SlideTextBrowser(text_browser *tb, GLfloat dis);
int UI_MoveTextBrowser(text_browser *tb, GLfloat step);
void UI_ResizeTextBrowser(text_browser *t, GLfloat width, GLfloat height);
void UI_ResetTextBrowserPosition(text_browser *t, GLfloat x, GLfloat y);
void UI_ResetTextBrowserGeometry(text_browser *t, GLfloat x, GLfloat y, GLfloat width, GLfloat height);

#endif

