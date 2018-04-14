#include "gravity.h"
#include "game_util.h"

#include <math.h>

float Physics_GetFalldownDistance(float speed, float g, float time)
{
	return(speed * time + g * time * time * 0.5);
}

float Physics_GetJumpSpeed(float speed, float g, float time)
{
	return(g * time + speed);
}

float Physics_GetGravityPositionH(float speed, const nl_vector3_t *start_pos, const nl_vector3_t *last_pos, float x_dir, float y_dir, long long time, int gravity, nl_vector3_t *new_pos, float *rx, float *ry)
{
	if(!start_pos || !last_pos)
		return -1;
	nl_vector3_t dir = Algo_ComputeDirection(y_dir, x_dir);
	float delta_time = (float)time / 1000.0;
	float distance = speed * delta_time;
	dir = Vector3_Scale(&dir, distance);
	nl_vector3_t pos = {0.0, 0.0, 0.0};
	pos = Vector3_PlusVector3(start_pos, &dir);
	
	float xr = x_dir;
	float yr = y_dir;
	float dis = 0.0;
	nl_vector3_t v = Vector3_SubtractVector3(&pos, last_pos);
	dis = Vector3_Mag(&v);
	if(gravity)
	{
		float ydis = GAME_G * delta_time * delta_time * 0.5;
		pos.z -= ydis;
		v = Vector3_SubtractVector3(&pos, last_pos);
		dis = Vector3_Mag(&v);
		Vector3_Normalize(&v);
		Algo_GetNormalAngle(&v, &yr, &xr);
	}

	if(new_pos)
		*new_pos = pos;
	if(rx)
		*rx = xr;
	if(ry)
		*ry = yr;
	return dis;
}

float Physics_GetGravityPosition(float speed, const nl_vector3_t *start_pos, const nl_vector3_t *last_pos, float x_dir, float y_dir, long long time, int gravity, nl_vector3_t *new_pos, float *rx, float *ry)
{
	if(!start_pos || !last_pos)
		return -1;
	float xr = x_dir;
	float yr = y_dir;
	float dis = 0.0;
	nl_vector3_t v = {0.0, 0.0, 0.0};
	nl_vector3_t pos = {0.0, 0.0, 0.0};
	float delta_time = (float)time / 1000.0;

	if(gravity)
	{
		double r = ator(x_dir);
		float xspeed = speed * cos(r);
		float yspeed = speed * sin(r);
		float xdis = xspeed * delta_time;
		nl_vector3_t xdir = Algo_ComputeDirection(y_dir, 0.0);
		xdir = Vector3_Scale(&xdir, xdis);

		float ydis = -yspeed * delta_time + -GAME_G * delta_time * delta_time * 0.5;
		nl_vector3_t ydir = {0.0, 0.0, 1.0};
		ydir = Vector3_Scale(&ydir, ydis);
		nl_vector3_t dir = Vector3_PlusVector3(&xdir, &ydir);
		pos = Vector3_PlusVector3(start_pos, &dir);
		v = Vector3_SubtractVector3(&pos, last_pos);
		dis = Vector3_Mag(&v);
		Vector3_Normalize(&v);
		Algo_GetNormalAngle(&v, &yr, &xr);
	}
	else
	{
		nl_vector3_t dir = Algo_ComputeDirection(y_dir, x_dir);
		float distance = speed * delta_time;
		dir = Vector3_Scale(&dir, distance);
		pos = Vector3_PlusVector3(start_pos, &dir);
		/*
		v = Vector3_SubtractVector3(&pos, last_pos);
		dis = Vector3_Mag(&v);
		Vector3_Normalize(&v);
		*/
	}

	if(new_pos)
		*new_pos = pos;
	if(rx)
		*rx = xr;
	if(ry)
		*ry = yr;
	return dis;
}
