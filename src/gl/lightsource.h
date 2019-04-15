#ifndef KARIN_LIGHT_SPURCE_H
#define KARIN_LIGHT_SPURCE_H

#include "opengl/opengl.h"
#include "math3d/vector.h"

#define LIGHT_AMBIANT_COLOR 1
#define LIGHT_DIFFUSE_COLOR (1 << 1)
#define LIGHT_SPECULAR_COLOR (1 << 2)

#define LIGHT_IS_DIRECTION(x) ((x)->dirlighting)
#define LIGHT_IS_POINT(x) (!(x)->dirlighting && ((x)->cutoff == 0 || (x)->cutoff >= 180))
#define LIGHT_IS_SPOT(x) (!(x)->dirlighting && ((x)->cutoff > 0 && (x)->cutoff <= 90))
#define LIGHT_IS_SPOT_360(x) (!(x)->dirlighting && ((x)->cutoff > 0 && (x)->cutoff < 180))

typedef enum _Light_Source_Type_e
{
	Direction_Light_Source = 0,
	Point_Light_Source,
	Spot_Light_Source,
} Light_Source_Type_e;

typedef struct _Light_Source_s
{
	Light_Source_Type_e type;

	vector3_s position;
	int dirlighting;

	float ambient[4];
	float diffuse[4];
	float specular[4];

	// spot
	vector3_s direction;
	float exponent;
	float cutoff;

	float constant_attenuation;
	float linear_attenuation;
	float quadratic_attenuation;
} Light_Source_s;

void Lighting_glLight(const Light_Source_s *light, GLenum source);
Light_Source_s * new_point_light_source(Light_Source_s *r, const vector3_s *pos);
Light_Source_s * new_spot_light_source(Light_Source_s *r, const vector3_s *pos, const vector3_s *dir, float exponent, float cutoff);
Light_Source_s * new_direction_light_source(Light_Source_s *r, const vector3_s *dir);

void Lighting_SetColor(Light_Source_s *light, int type, const float color[4]);

#endif
