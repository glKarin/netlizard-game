#ifndef KARIN_GAME_SWITCHER_H
#define KARIN_GAME_SWITCHER_H

#include "widget_base.h"

typedef struct _switcher
{
	base_widget base;
	GLfloat bg_color[4];
	GLfloat text_color[4];
	GLfloat block_color[4];
	GLfloat close_bg_color[4];
	GLfloat close_text_color[4];
	GLfloat close_block_color[4];
	GLfloat border_color[4];
	char *text;
	const font *fnt;
	GLuint buffers[total_buffer_type];
	GLboolean open;
	rect2 btn;
} switcher;

switcher * new_switcher(switcher *lb, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, const GLfloat bg_color[], const GLfloat text_color[], const GLfloat block_color[], const GLfloat close_bg_color[], const GLfloat close_text_color[], const GLfloat close_block_color[], const GLfloat border_color[], const char *text);
void UI_RenderSwitcher(const switcher *s);
void delete_switcher(switcher *s);
void UI_ResetSwitcherPosition(switcher *s, GLfloat x, GLfloat y);
void UI_ResizeSwitcher(switcher *s, GLfloat width, GLfloat height);
void UI_ResetSwitcherGeometry(switcher *s, GLfloat x, GLfloat y, GLfloat width, GLfloat height);

#endif

