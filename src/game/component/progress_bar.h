#ifndef KARIN_GAME_PROGRESSBAR_H
#define KARIN_GAME_PROGRESSBAR_H

#include "widget_base.h"

typedef struct _progress_bar
{
	base_widget base;
	GLclampf progress;
	GLfloat spacing;
	GLfloat border_width;
	GLfloat border_color[4];
	GLfloat color[4];
	GLfloat block_color[4];
	GLuint buffers[total_buffer_type];
} progress_bar;

progress_bar * new_progress_bar(progress_bar *bar, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat spacing, GLfloat border_width, const GLfloat border_color[], const GLfloat color[], const GLfloat block_color[]);
void UI_RenderProgressBar(const progress_bar *bar);
void delete_progress_bar(progress_bar *bar);
void UI_ResizeProgressBar(progress_bar *b, GLfloat width, GLfloat height);
void UI_ResetProgressBarPosition(progress_bar *b, GLfloat x, GLfloat y);
void UI_ResetProgressBarGeometry(progress_bar *b, GLfloat x, GLfloat y, GLfloat width, GLfloat height);

#endif
