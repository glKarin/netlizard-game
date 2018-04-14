#ifndef KARIN_GAME_SPINBOX_H
#define KARIN_GAME_SPINBOX_H

#include "widget_base.h"

typedef struct _spin_box
{
	base_widget base;
	GLfloat bg_color[4];
	GLfloat digit_color[4];
	GLfloat block_color[4];
	GLfloat text_color[4];
	GLfloat disable_block_color[4];
	GLfloat border_color[4];
	int value;
	int step;
	int min;
	int max;
	GLfloat limit;
	char *text;
	const font *fnt;
	GLuint buffers[total_buffer_type];
	rect2 left;
	rect2 right;
} spin_box;

spin_box * new_spin_box(spin_box *sb, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, const GLfloat bg_color[], const GLfloat digit_color[], const GLfloat block_color[], const GLfloat text_color[], const GLfloat disable_block_color[], const GLfloat border_color[], int num, int min, int max, int step, const char *text);
void UI_RenderSpinBox(const spin_box *s);
void delete_spin_box(spin_box *s);
int UI_ClickSpinBox(spin_box *s, GLfloat x, GLfloat y);
void UI_ResetSpinBoxPosition(spin_box *s, GLfloat x, GLfloat y);
void UI_ResizeSpinBox(spin_box *s, GLfloat width, GLfloat height);
void UI_ResetSpinBoxGeometry(spin_box *s, GLfloat x, GLfloat y, GLfloat width, GLfloat height);

#endif
