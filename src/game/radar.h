#ifndef KARIN_RADAR_H
#define KARIN_RADAR_H

#include "gl_util.h"

// 雷达
typedef struct _radar
{
	GLuint buffers[total_buffer_type];
	GLfloat pos[3];
	GLfloat radius;
	GLuint count;
	GLfloat range;
	GLfloat rotation;
	GLfloat view_angle;
	GLfloat point_width;
	GLfloat line_width;
	GLfloat parner_point_color[4];
	GLfloat vip_point_color[4];
	GLfloat enemy_point_color[4];
	GLfloat line_color[4];
	GLfloat bg_color[4];
	GLfloat *point_pos;
	GLuint point_count;
} radar;

radar * new_radar(radar *ra, GLfloat radius, GLfloat angle, GLfloat range, GLfloat p, GLfloat cpw, const GLfloat ppc[], const GLfloat epc[], const GLfloat vpc[], GLfloat clw, const GLfloat lc[], const GLfloat bgc[]);
void delete_radar(radar *r);
void UI_RenderRadar(const radar *r);

#endif
