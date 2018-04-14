#ifndef KARIN_CROSS_HAIR_H
#define KARIN_CROSS_HAIR_H

#include "gl_util.h"

// 瞄准镜部分
typedef enum _sight_part
{
	sight_optical = 0,
	sight_front
} sight_part;

// 准星类型
typedef enum _cross_hair_type
{
	point_type,
	cross_type,
	ray_type,
	optical_type
} cross_hair_type;

// 瞄准镜
typedef struct _optical_sight_cross_hair
{
	cross_hair_type type;
	GLuint buffers[total_buffer_type];
	GLfloat pos[3];
	GLfloat radius;
	GLuint count;
	GLfloat front_sight_point_width;
	GLfloat front_sight_point_color[4];
	GLfloat front_sight_line_width;
	GLfloat front_sight_line_color[4];
} optical_sight_cross_hair;

// 准星
typedef struct _normal_cross_hair
{
	cross_hair_type type;
	GLfloat color[4];
	GLclampf scale;
	GLfloat step;
	GLfloat width;
	GLfloat height;
	GLfloat pos[3];
} normal_cross_hair;

typedef struct _ray_cross_hair
{
	cross_hair_type type;
	GLfloat start_pos[3];
	GLfloat target_pos[3];
	GLfloat color[4];
	GLfloat line_width;
	GLfloat point_min_width;
	GLfloat point_max_width;
} ray_cross_hair;

typedef union _cross_hair
{
	cross_hair_type type;
	normal_cross_hair normal;
	ray_cross_hair ray;
	optical_sight_cross_hair optical;
} cross_hair;

cross_hair * new_normal_cross_hair(cross_hair *c, cross_hair_type type, const GLfloat color[], GLfloat step, GLfloat width, GLfloat height);
cross_hair * new_ray_cross_hair(cross_hair *c, cross_hair_type type, const GLfloat color[], GLfloat line_width, GLfloat point_min_width, GLfloat point_max_width);
cross_hair * new_optical_sight_cross_hair(cross_hair *cross, GLfloat w, GLfloat p, GLfloat cpw, const GLfloat pc[], GLfloat clw, const GLfloat lc[]);

void UI_RenderCrossHair(const cross_hair *c);
void UI_RenderOpticalSightCrossHair(const optical_sight_cross_hair *c, sight_part p);
void UI_RenderRayCrossHair(const ray_cross_hair *c);
void UI_RenderNormalCrossHair(const normal_cross_hair *c);
void delete_optical_sight(optical_sight_cross_hair *c);

#endif
