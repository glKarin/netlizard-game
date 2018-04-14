#ifndef KARIN_GAME_SLIDERBAR_H
#define KARIN_GAME_SLIDERBAR_H

#include "widget_base.h"

typedef struct _slider_bar
{
	base_widget base;
	GLfloat bar_width;
	GLfloat block_width;
	GLfloat map_height;
	GLfloat map_total_height;
	GLclampf progress;
	GLfloat color[4];
	GLfloat block_color[4];
	GLuint buffers[total_buffer_type];
} slider_bar;

slider_bar * new_slider_bar(slider_bar *bar, GLfloat x, GLfloat y, GLfloat z, GLfloat bar_width, GLfloat block_width, GLfloat height, GLfloat map_height, GLfloat map_total_height, const GLfloat color[], const GLfloat block_color[]);
void UI_RenderSliderBar(const slider_bar *bar);
void delete_slider_bar(slider_bar *bar);
void UI_ResetSliderBarPosition(slider_bar *b, GLfloat x, GLfloat y);
void UI_ResizeSliderBar(slider_bar *b, GLfloat width, GLfloat height);
void UI_ResetSliderBarGeometry(slider_bar *b, GLfloat x, GLfloat y, GLfloat width, GLfloat height);

#endif

