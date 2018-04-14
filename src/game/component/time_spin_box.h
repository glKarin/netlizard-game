#ifndef KARIN_GAME_TIMESPINBOX_H
#define KARIN_GAME_TIMESPINBOX_H

#include "widget_base.h"

typedef struct _time_spin_box
{
	base_widget base;
	GLfloat bg_color[4];
	GLfloat digit_color[4];
	GLfloat block_color[4];
	GLfloat text_color[4];
	GLfloat disable_block_color[4];
	GLfloat border_color[4];
	GLfloat min_limit;
	GLfloat sec_limit;
	GLfloat box_width;
	long long min;
	long long max;
	long long time;
	int step;
	int hour;
	char minuts;
	char second;
	char *text;
	const font *fnt;
	GLuint buffers[total_buffer_type];
	rect2 min_top;
	rect2 min_bottom;
	rect2 sec_top;
	rect2 sec_bottom;
} time_spin_box;

time_spin_box * new_time_spin_box(time_spin_box *sb, GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, const GLfloat bg_color[], const GLfloat digit_color[], const GLfloat block_color[], const GLfloat text_color[], const GLfloat disable_block_color[], const GLfloat border_color[], int step, long long min, long long max, long long time, const char *text);
void UI_RenderTimeSpinBox(const time_spin_box *s);
void delete_time_spin_box(time_spin_box *s);
void UI_SetTimeSpinBoxTime(time_spin_box *s, long long t);
int UI_ClickTimeSpinBox(time_spin_box *sb, GLfloat x, GLfloat y);
void UI_ResetTimeSpinBoxPosition(time_spin_box *s, GLfloat x, GLfloat y);
void UI_ResizeTimeSpinBox(time_spin_box *s, GLfloat width, GLfloat height);
void UI_ResetTimeSpinBoxGeometry(time_spin_box *s, GLfloat x, GLfloat y, GLfloat width, GLfloat height);

#endif
