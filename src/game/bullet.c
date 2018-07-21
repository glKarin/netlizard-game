#include "bullet.h"
#include "nl_std.h"
#include "game_util.h"
#include "nl_algo.h"
#include "math3d/vector3.h"
#include "physics/gravity.h"

#include <string.h>

#define DAMAGE_ATTENUATION_DISTANCE_UNIT 10000

bullet * new_bullet(bullet *bt, float x, float y, float z, float dirx, float diry, long long time, float speed, int damage, float damage_attenuation, float boom_range, float boom_damage_attenuation, float range, int gravity, bullet_type at, int c, int group, float len)
{
	RETURN_PTR(b, bt, bullet)

	b->position[0] = x;
	b->position[1] = y;
	b->position[2] = z;
	b->start_pos[0] = x;
	b->start_pos[1] = y;
	b->start_pos[2] = z;
	b->last_pos[0] = x;
	b->last_pos[1] = y;
	b->last_pos[2] = z;
	b->x_dir = dirx;
	b->y_dir = diry;
	b->x_angle = dirx;
	b->y_angle = diry;
	b->time = time;
	b->speed = speed;
	b->damage = damage;
	b->start_damage = damage;
	b->damage_attenuation = damage_attenuation;
	b->gravity = gravity;
	b->group = group;
	b->character = c;
	b->type = at;
	b->range = range;
	b->distance = 0;
	b->boom_range = boom_range;
	b->boom_damage_attenuation = boom_damage_attenuation;
	b->weapon_length = len;

	b->finished = -1;
	return b;
}

void Game_UpdateBullet(bullet *b, long long game_time)
{
	if(!b)
		return;
	if(b->finished == 1)
		return;
	else if(b->finished == -1)
	{
		if(b->weapon_length == -1)
			b->finished = 0;
		else
		{
			if(b->distance > b->weapon_length)
				b->finished = 0;
		}
	}
	else
	{
		if(b->range != -1 && b->distance >= b->range)
		{
			b->finished = 1;
			return;
		}
	}

	nl_vector3_t start_pos = {b->start_pos[0], b->start_pos[1], b->start_pos[2]};
	nl_vector3_t last_pos = {b->last_pos[0], b->last_pos[1], b->last_pos[2]};
	nl_vector3_t pos = {0.0, 0.0, 0.0};
	/*
	float rx = 0.0;
	float ry = 0.0;
	*/
	float dis = Physics_GetGravityPosition(b->speed, &start_pos, &last_pos, b->x_dir, b->y_dir, game_time - b->time, b->gravity, &pos, &b->x_angle, &b->y_angle);
	b->distance += dis;
	if(b->range != -1 && b->distance >= b->range)
	{
		b->distance = b->range;
	}

	b->last_pos[0] = b->position[0];
	b->last_pos[1] = b->position[1];
	b->last_pos[2] = b->position[2];
	b->position[0] = pos.x;
	b->position[1] = pos.y;
	b->position[2] = pos.z;

	if(b->damage_attenuation != 0.0 && b->type == normal_bullet_type)
	{
		float dis = Vector3_Mag(&pos);
		float per = dis / DAMAGE_ATTENUATION_DISTANCE_UNIT;
		float damage = b->start_damage;
		b->damage = (int)(damage - per * b->damage_attenuation);
	}
}

int Game_GetBulletBoomDamage(bullet *bt, float dis)
{
	if(!bt)
		return -1;
	if(bt->type != shell_bullet_type && bt->type != grenade_bullet_type)
		return -1;
	if(dis < 0.0)
		return -1;
	if(dis > bt->boom_range)
		return 0;
	float per = 1.0 - dis / bt->boom_range;
	float damage = (float)bt->damage;
	if(per > 0.000001)
		return (int)(damage * per);
	else
		return 0;
}
