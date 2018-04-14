#ifndef KARIN_RELOADING_PROGRESS_BAR_H
#define KARIN_RELOADING_PROGRESS_BAR_H

#include "game_mode.h"
#include "font.h"
#include "component/progress_bar.h"

typedef struct _reloading_progress_bar
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat width;
	GLfloat height;
	GLfloat border_width;
	GLfloat bg_color[4];
	GLfloat text_color[4];
	GLfloat border_color[4];
	GLfloat limit;
	const font *fnt;
	GLuint buffers[total_buffer_type];
	progress_bar bar;
	const death_game_mode *game_mode;
} reloading_progress_bar;

reloading_progress_bar * new_reloading_progress_bar(reloading_progress_bar *rb, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat border_width, const GLfloat bg_color[], const GLfloat text_color[], const GLfloat border_color[], const GLfloat block_color[], const GLfloat bar_color[]);
void UI_RenderReloadingProgressBar(reloading_progress_bar *rb);
void delete_reloading_progress_bar(reloading_progress_bar *rb);

#endif
