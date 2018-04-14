#ifndef KARIN_MENU_BUTTON_H
#define KARIN_MENU_BUTTON_H

#include "widget_base.h"

typedef struct _button
{
	base_widget base;
	GLfloat border_width;
	GLfloat bg_color[4];
	GLfloat text_color[4];
	GLfloat border_color[4];
	GLfloat hl_bg_color[4];
	GLfloat hl_text_color[4];
	GLfloat hl_border_color[4];
	GLuint buffers[total_buffer_type];
	GLuint count;
	GLboolean highlight;
	char *text;
	const font *fnt;
} button;

typedef struct _icon_button
{
	base_widget base;
	GLfloat border_width;
	GLfloat border_color[4];
	GLfloat hl_border_color[4];
	texture *tex;
	GLuint buffers[total_buffer_type];
} icon_button;

button * new_button(button *btn, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat border_width, const GLfloat bg_color[], const GLfloat text_color[], const GLfloat border_color[], const GLfloat hl_bg_color[], const GLfloat hl_text_color[], const GLfloat hl_border_color[], const char *text);
icon_button * new_icon_button(icon_button *btn, const char *file, GLfloat border_width, const GLfloat border_color[], const GLfloat hl_border_color[], GLfloat width, GLfloat height);
void UI_RenderButton(const button *btn);
void UI_RenderIconButton(const icon_button *btn);
void delete_button(button *btn);
void delete_icon_button(icon_button *btn);
void UI_ResizeButton(button *b, GLfloat width, GLfloat height);
void UI_ResetButtonPosition(button *b, GLfloat x, GLfloat y);
void UI_ResetButtonGeometry(button *b, GLfloat x, GLfloat y, GLfloat width, GLfloat height);

#endif
