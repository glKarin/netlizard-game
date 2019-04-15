#include "lightsource.h"
#include "nl_std.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Lighting_glLight(const Light_Source_s *light, GLenum source)
{
#ifdef _HARMATTAN_OPENGLES
	GLfloat pos[4];
	if(!light)
		return;

	pos[0] = VECTOR_X(light->position);
	pos[1] = VECTOR_Y(light->position);
	pos[2] = VECTOR_Z(light->position);
	pos[3] = LIGHT_IS_DIRECTION(light) ? 0 : 1;

	glLightfv(source, GL_POSITION, pos);

	glLightfv(source, GL_AMBIENT, light->ambient);
	glLightfv(source, GL_DIFFUSE, light->diffuse);
	glLightfv(source, GL_SPECULAR, light->specular);

	if(LIGHT_IS_SPOT(light))
	{
		glLightf(source, GL_SPOT_CUTOFF, light->cutoff);
		glLightf(source, GL_SPOT_EXPONENT, light->exponent);
		pos[0] = VECTOR_X(light->direction);
		pos[1] = VECTOR_Y(light->direction);
		pos[2] = VECTOR_Z(light->direction);
		glLightfv(source, GL_SPOT_DIRECTION, pos);
	}

	if(!LIGHT_IS_DIRECTION(light))
	{
		glLightf(source, GL_CONSTANT_ATTENUATION, light->constant_attenuation);
		glLightf(source, GL_LINEAR_ATTENUATION, light->linear_attenuation);
		glLightf(source, GL_QUADRATIC_ATTENUATION, light->quadratic_attenuation);
	}
#endif
}

Light_Source_s * new_point_light_source(Light_Source_s *r, const vector3_s *pos)
{
	if(!pos)
		return NULL;

	RETURN_PTR(light, r, Light_Source_s);
	light->position = *pos;

	light->dirlighting = 0;
	light->cutoff = 0;

	return light;
}

Light_Source_s * new_spot_light_source(Light_Source_s *r, const vector3_s *pos, const vector3_s *dir, float exponent, float cutoff)
{
	if(!pos || !dir)
		return NULL;

	RETURN_PTR(light, r, Light_Source_s);
	light->position = *pos;

	light->dirlighting = 0;

	light->cutoff = cutoff;
	light->direction = *dir;
	light->exponent = exponent;

	return light;
}

Light_Source_s * new_direction_light_source(Light_Source_s *r, const vector3_s *dir)
{
	if(!dir)
		return NULL;

	RETURN_PTR(light, r, Light_Source_s);
	light->position = *dir;
	Vector3_Normalize(&light->position);

	light->dirlighting = 1;

	return light;
}

void Lighting_SetColor(Light_Source_s *light, int type, const float color[4])
{
#define _colorcpy4(d, s) \
	{ \
		d[0] = s[0]; \
		d[1] = s[1]; \
		d[2] = s[2]; \
		d[3] = s[3]; \
	}

	if(!light || !color)
		return;

	if(type & LIGHT_AMBIANT_COLOR)
	{
		_colorcpy4(light->ambient, color);
	}

	if(type & LIGHT_DIFFUSE_COLOR)
	{
		_colorcpy4(light->diffuse, color);
	}

	if(type & LIGHT_SPECULAR_COLOR)
	{
		_colorcpy4(light->specular, color);
	}

#undef _colorcpy4
}
