#ifndef KARIN_CHARACTER_STATUS_H
#define KARIN_CHARACTER_STATUS_H

#include "game_mode.h"
#include "font.h"

typedef struct _character_status_bar
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat width;
	GLfloat height;
	GLfloat border_width;
	GLfloat bg_color[4];
	GLfloat icon_color[4];
	GLfloat text_color[4];
	GLfloat border_color[4];
	const font *fnt;
	GLuint buffers[total_buffer_type];
	GLuint health_buffers[total_buffer_type];
	GLuint clock_buffers[total_buffer_type];
	GLuint ammo_buffers[total_buffer_type];
	const death_game_mode *game_mode;
} character_status_bar;

character_status_bar * new_character_status_bar(character_status_bar *sb, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat border_width, const GLfloat bg_color[], const GLfloat text_color[], const GLfloat border_color[], const GLfloat icon_color[]);
void UI_RenderCharacterStatusBar(const character_status_bar *sb);
void delete_character_status_bar(character_status_bar *sb);

#endif

