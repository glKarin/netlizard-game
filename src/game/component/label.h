#ifndef KARIN_GAME_LABEL_H
#define KARIN_GAME_LABEL_H

#include "widget_base.h"

typedef struct _label
{
	base_widget base;
	GLfloat border_width;
	GLfloat bg_color[4];
	GLfloat text_color[4];
	GLfloat border_color[4];
	char *text;
	texture *tex;
	const font *fnt;
	GLuint buffers[total_buffer_type];
} label;

label * new_label(label *lb, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat border_width, const GLfloat bg_color[], const GLfloat text_color[], const GLfloat border_color[], const char *text, const char *tex);
void UI_RenderLabel(const label *l);
void delete_label(label *l);
void UI_ResetLabelPosition(label *l, GLfloat x, GLfloat y);
void UI_ResizeLabel(label *l, GLfloat width, GLfloat height);
void UI_ResetLabelGeometry(label *l, GLfloat x, GLfloat y, GLfloat width, GLfloat height);

#endif
