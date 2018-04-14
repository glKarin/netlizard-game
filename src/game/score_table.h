#ifndef KARIN_GAME_SCORE_TABLE_H
#define KARIN_GAME_SCORE_TABLE_H

#include "font.h"
#include "game_mode.h"
#include "gl_util.h"

typedef struct _score_table
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat width;
	GLfloat height;
	GLboolean visible;
	GLfloat cell_width;
	GLfloat cell_height;
	GLfloat line_width;
	GLfloat line_color[4];
	GLfloat bg_color[4];
	GLfloat hl_color[4];
	GLfloat text_color[4];
	GLuint buffers[total_buffer_type];
	const font *fnt;
	const death_game_mode *game_mode;
} score_table;

score_table * new_score_table(score_table *st, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat cell_w, GLfloat cell_h, GLfloat line_width, const GLfloat line_color[], const GLfloat bg_color[], const GLfloat hl_color[], const GLfloat text_color[]);
void UI_RenderScoreTable(const score_table *t);
void delete_score_table(score_table *t);

#endif
