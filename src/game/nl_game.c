#include "nl_game.h"
#include "nl_algo.h"
#include "gl_util.h"
#include "game_util.h"
#include "game_mode.h"
#include "gl_3d_main.h"
#include "math3d/algo.h"
#include "particle.h"
#include "game_sound.h"
#include "game_setting.h"
#include "physics/gravity.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define SOUND_RANGE 8000
#define BULLET_PER 0.02
#define BOOM_ZERO 0.1
#define BOOM_SPEED 2000.0f

#define RAND_POSITION_PART 10
#define FIGHTING_MOVE_SPEED_PER 0.8
//0.523599))

extern char shared_str[DEBUG_STRING_MAX_LENGTH];

static const human_body_hits Human_Body_Data[human_body_total] = {
	{0.844, 1.0, 1.5},
	{0.600, 0.843, 1.0},
	{0.467, 0.599, 0.8},
	{0.267, 0.466, 0.6},
	{0.067, 0.266, 0.5},
	{0.0, 0.066, 0.2}
};

game_character *characters = NULL;
int character_count = 0;

game_character * Game_InitCharacter(float x, float y, float z, float xr, float yr, int scene, unsigned int gc, unsigned int cc, unsigned int self, unsigned int *count)
{
	character_count = gc * cc;
	characters = NEW_II(game_character, character_count);
	weapon_model_type types[CHARACTER_WEAPON_COUNT];
	unsigned mask = main_weapon_1 | secondary_weapon | fighting_weapon | launch_weapon;
	unsigned int i;
	for(i = 0; i < gc; i++)
	{
		unsigned int j;
		for(j = 0; j < cc; j++)
		{
			unsigned int index = i * cc + j;
			Game_Rand4WeaponTypes(types, countof(types), mask);
			if(index == self)
			{
				int wpi = clone3d_M16;
				Setting_GetSettingInteger(USE_WEAPON_SETTING, &wpi);
				int cmi = natasha2;
				Setting_GetSettingInteger(USE_CHARACTER_MODEL_SETTING, &cmi);
				new_game_character(characters + index, cmi, x, y, z, xr, yr, index, "karin", scene, types, countof(types));
				characters[index].group = i;
				//new_weapon(&characters[i].current_weapon, clone3d_Rocket_Launcher);
			}
			else
			{
				unsigned int ct = TR1_terror + i;
				char name[21];
				memset(name, '\0', sizeof(char) * 21);
				sprintf(name, "%d-%d", i, j);
				new_game_character(characters + index, ct, x, y, z, xr, yr, index, name, scene, types, countof(types));
				characters[index].group = i;
			}
		}
	}
	if(count)
		*count = character_count;
	return characters;
}

void Game_DeleteCharacter(game_character *characters, int count)
{
	if(!characters)
		return;
	int i;
	for(i = 0; i < count; i++)
		delete_game_character(characters + i);
	free(characters);
	characters = NULL;
	character_count = 0;
}

void Game_RenderCharacters(const game_character *characters, int start, int cc, const int *scenes, int sc)
{
	if(!characters || cc == 0)
		return;
	if(scenes && sc != 0)
	{
		int i;
		for(i = start; i < cc; i++)
		{
			int j;
			for(j = 0; j < sc; j++)
			{
				if(scenes[j] == characters[i].scene)
					Game_RenderGameCharacter(characters + i);

			}
		}
	}
	else
	{
		int i;
		for(i = start; i < cc; i++)
		{
			Game_RenderGameCharacter(characters + i);
		}
	}
}

void Game_UpdateAIAnimation(game_character *characters, int start, int count, long long time, int fps, float delta)
{
	if(!characters)
		return;
	int i;
	for(i = start; i < count; i++)
		Game_CharacterPlayAnimation(characters + i, time, fps, delta);
}

void Game_HandleCharacterAction(const GL_NETLizard_3D_Model *map_model, game_character *characters, int start, int count, long long time)
{
	if(!map_model || !characters || count == 0)
		return;

	int i;
	for(i = start; i < count; i++)
	{
		if(Game_HandleForceAI(map_model, characters + i, time))
			continue;
		// 系统随机AI更新
		if(characters[i].ai.type == ai_compute_type)
			Game_HandleComputeAI(map_model, characters + i, time);
		else if(characters[i].ai.type == ai_operate_type)// 人工操作AI更新
			Game_HandleOperateAI(map_model, characters + i, time);
		else if(characters[i].ai.type == ai_trigger_type) // 触发AI更新
			Game_HandleTriggerAI(map_model, characters + i, time);
		else if(characters[i].ai.type == ai_player_type) // 玩家AI更新
			Game_HandlePlayerAI(map_model, characters + i, time);
		else if(characters[i].ai.type == ai_script_type)// 脚本AI更新
			Game_HandleScriptAI(map_model, characters + i, time);
	}
}

void Game_OperateAIMoveToPosition(const GL_NETLizard_3D_Model *map_model, const game_character *gamer, game_character *characters, int start, int count)
{
	if(!map_model || !gamer || !characters)
		return;
	nl_vector3_t dir = Algo_ComputeDirection(gamer->y_angle, gamer->x_angle);
	nl_vector3_t pos = {gamer->position[0], gamer->position[1], gamer->position[2] + gamer->height};
	int i;
	for(i = start; i < count; i++)
	{
		game_character *b = characters + i;
		if(gamer == b)
			continue;
		if(b->health == health_death_type)
			continue;
		if(gamer->group != b->group)
			continue;
		if(!Game_CharacterCanViewCharacter(map_model, gamer, b))
			continue;
		float dis = 0.0;
		nl_vector3_t point = {0.0, 0.0, 0.0};
		// 取得指向位置的坐标
		int r = Algo_RayCollisionTestingInNETLizard3DMap(map_model, &pos, &dir, b->width, NULL, &dis, &point, NULL);
		if(r == 0)
			continue;
		game_ai ai;
		ZERO(&ai, game_ai);
		AI_ClearAction(&ai);
		ai.type = ai_operate_type;
		ai.action = aiaction_no_type;
		// 目标距离小于角色宽度 不操作
		if(dis > b->width)
		{
			ai.goto_mask = 1;
			ai.action |= aiaction_moveforward_type;
			ai.position_progress[0] = b->position[0];
			ai.position_progress[1] = b->position[1];
			ai.position_progress[2] = b->position[2];
			ai.position_target[0] = point.x;
			ai.position_target[1] = point.y;
			ai.position_target[2] = point.z;
			ai.position_range = b->width;
			// 更新角色的操作AI
		}
		// 获取目标位置的角度
		nl_vector3_t vg = {b->position[0], b->position[1], b->position[2] + b->height};
		nl_vector3_t v = Vector3_SubtractVector3(&vg, &point);
		float xl = v.x;
		float yl = v.y;
		float f = Algo_FormatAngle(rtoa(atan2(yl, xl)) - 90.0);
		if(f != b->y_angle)
		{
			// TODO 选取最近角度选择向左或右旋转
			float offset = Algo_FormatAngle(f - b->y_angle);
			if(offset > 0 && offset <= 180.0f)
				ai.action |= aiaction_turnleft_type;
			else
				ai.action |= aiaction_turnright_type;
			ai.rotation_mask = 1;
			ai.y_angle_target = f;
			ai.angle_range = 0.0;
			ai.y_angle_progress = b->y_angle;
			// 更新角色的操作AI
		}
		ai.time = b->ai.time;
		if(ai.action != aiaction_no_type)
			AI_Copy(&b->ai, &ai);
	}
}

void Game_OperateAIBackToMe(const GL_NETLizard_3D_Model *map_model, const game_character *gamer, game_character *characters, int start, int count)
{
	if(!map_model || !gamer || !characters)
		return;
	nl_vector3_t pos = {gamer->position[0], gamer->position[1], gamer->position[2] + gamer->height};
	int i;
	for(i = start; i < count; i++)
	{
		game_character *b = characters + i;
		if(gamer == b)
			continue;
		if(b->health == health_death_type)
			continue;
		if(gamer->group != b->group)
			continue;
		if(!Game_CharacterCanViewCharacter(map_model, gamer, b))
			continue;
		game_ai ai;
		ZERO(&ai, game_ai);
		AI_ClearAction(&ai);
		ai.type = ai_operate_type;
		ai.action = aiaction_no_type;
		nl_vector3_t vg = {b->position[0], b->position[1], b->position[2] + b->height};
		nl_vector3_t dir = Vector3_SubtractVector3(&vg, &pos);
		float dis = Vector3_Mag(&dir);
		// 目标距离小于角色宽度 不操作
		if(dis > b->width)
		{
			ai.goto_mask = 1;
			ai.action |= aiaction_moveforward_type;
			ai.position_progress[0] = b->position[0];
			ai.position_progress[1] = b->position[1];
			ai.position_progress[2] = b->position[2];
			ai.position_target[0] = pos.x;
			ai.position_target[1] = pos.y;
			ai.position_target[2] = pos.z;
			ai.position_range = b->width + gamer->width + CHARACTER_MIN_SPACING;
			// 更新角色的操作AI
		}
		// 获取目标位置的角度
		float xl = dir.x;
		float yl = dir.y;
		float f = Algo_FormatAngle(rtoa(atan2(yl, xl)) - 90.0);
		if(f != b->y_angle)
		{
			// TODO 选取最近角度选择向左或右旋转
			float offset = Algo_FormatAngle(f - b->y_angle);
			if(offset > 0 && offset <= 180.0f)
				ai.action |= aiaction_turnleft_type;
			else
				ai.action |= aiaction_turnright_type;
			ai.rotation_mask = 1;
			ai.y_angle_target = f;
			ai.angle_range = 0.0;
			ai.y_angle_progress = b->y_angle;
			// 更新角色的操作AI
		}
		ai.time = b->ai.time;
		if(ai.action != aiaction_no_type)
			AI_Copy(&b->ai, &ai);
	}
}

void Game_OperateAIStandBy(const GL_NETLizard_3D_Model *map_model, const game_character *gamer, game_character *characters, int start, int count)
{
	if(!map_model || !gamer || !characters)
		return;
	int i;
	for(i = start; i < count; i++)
	{
		game_character *b = characters + i;
		if(gamer == b)
			continue;
		if(b->health == health_death_type)
			continue;
		if(gamer->group != b->group)
			continue;
		if(!Game_CharacterCanViewCharacter(map_model, gamer, b))
			continue;
		AI_ClearAction(&b->ai);
		b->ai.type = ai_operate_type;
		b->ai.action = aiaction_stand_type;
	}
}

void Game_OperateAIGoMe(const GL_NETLizard_3D_Model *map_model, const game_character *gamer, game_character *characters, int start, int count)
{
	if(!map_model || !gamer || !characters)
		return;
	int i;
	for(i = start; i < count; i++)
	{
		game_character *b = characters + i;
		if(gamer == b)
			continue;
		if(b->health == health_death_type)
			continue;
		if(gamer->group != b->group)
			continue;
		if(!Game_CharacterCanViewCharacter(map_model, gamer, b))
			continue;
		b->position[0] = gamer->position[0];
		b->position[1] = gamer->position[1];
		b->position[2] = gamer->position[2];
		AI_MakeComputeAction(&characters[i].ai, 1, 0);
	}
}

int Game_GetRayPointCoord(const GL_NETLizard_3D_Model *map_model, const game_character *character, GLboolean dy, int *scene, nl_vector3_t *cpoint, nl_vector3_t *normal, float *distance)
{
	if(!map_model || !character)
		return 0;
	const weapon *wp = Game_CharacterCurrentWeapon((game_character *)character);
	nl_vector3_t direction;
	if(dy && wp)
		direction = Algo_ComputeDirection(wp->y_angle, wp->x_angle);
	else
		direction = Algo_ComputeDirection(character->y_angle, character->x_angle);
	nl_vector3_t position;
	if(wp)
	{
		position.x = wp->position[0]; 
		position.y = wp->position[1];
		position.z = wp->position[2];
	}
	else
	{
		position.x = character->position[0]; 
		position.y = character->position[1];
		position.z = character->position[2] + character->height;
	}
	float dis = 0.0;
	int s = -1;
	nl_vector3_t point = {0.0, 0.0, 0.0};
	nl_vector3_t nml = {0.0, 0.0, 0.0};
	int r = Algo_RayCollisionTestingInNETLizard3DMap(map_model, &position, &direction, 1, &s, &dis, &point, &nml);
	if(r)
	{
		if(distance)
			*distance = dis;
		if(cpoint)
			*cpoint = point;
		if(normal)
			*normal = nml;
		if(scene)
			*scene = s;
	}
	return r;
}

int Game_CharacterCanViewCharacter(const GL_NETLizard_3D_Model *model, const game_character *c1, const game_character *c2)
{
	if(!c1 || !c2)
		return 0;
	nl_vector3_t v1 = {
		c1->position[0],
		c1->position[1],
		c1->position[2] + c1->height
	};
	nl_vector3_t v2 = {
		c2->position[0],
		c2->position[1],
		c2->position[2] + c2->height
	};
	if(Algo_PointCanViewPointInNETLizard3DMap(model, &v1, &v2, NULL))
	{
		nl_vector3_t dir1 = {
			c1->direction[0],
			c1->direction[1],
			c1->direction[2]
		};
		nl_vector3_t dir2 = Math3D_ComputeTwoPointNormal(&v1, &v2);
		float r = acos(Vector3_DotVector3(&dir2, &dir1));
		r = rtoa(r);
		r = Algo_FormatAngle(r);
		//sprintf(shared_str, "%f", r);
		if(r <= CHARACTER_VIEW_FOV || r >= (360.0 - CHARACTER_VIEW_FOV))
			return 1;
		else
			return 0;
	}
	return 0;
}

int Game_ShotCharacter2D(const GL_NETLizard_3D_Model *model, game_character *gamer, game_character *characters, int start, int count)
{
	if(!model || !gamer || !characters)
		return -1;

	if(gamer->health == health_death_type)
		return -1;
	const weapon *wp = Game_CharacterCurrentWeapon(gamer);
	if(!wp)
		return -1;
	if(gamer->ai.type != ai_trigger_type && gamer->ai.type != ai_player_type)
		return -1;
	if((gamer->ai.action & aiaction_attack_type) == 0)
		return -1;
	if(wp->status != firing_type)
		return -1;
	const nl_vector3_t me = {
		wp->position[0],
		wp->position[1],
		wp->position[2]
	};
	int i;
	for(i = start; i < count; i++)
	{
		game_character *b = characters + i;
		if(gamer == b)
			continue;
		if(b->health == health_death_type)
			continue;
		if(gamer->group == b->group) // kill partner ?
			continue;
		if(!Game_CharacterCanViewCharacter(model, gamer, b))
			continue;
		//计算目标与主角之间的角度
		nl_vector3_t tg = {
			b->position[0],
			b->position[1],
			b->position[2] + b->height
		};
		nl_vector3_t va = Vector3_SubtractVector3(&me, &tg);
		float xl = va.x;
		float yl = va.y;
		float ft = Algo_FormatAngle(rtoa(atan2(yl, xl)) - 90.0);

		// 计算击中目标的最大角度
		vector2_t v2 = {xl, yl};
		float dis = Vector2_Mag(&v2);
		if(dis == 0.0f)
			return i;

		float fd = Algo_FormatAngle(rtoa(atan(characters[i].width / 2 / abs(dis))));
		//printf("%f %f %f %f\n", gamer->y_angle, ft, dis, fd);
		// 目标与主角角度差小于2倍的击中目标的最小角度则击中
		// 2倍是由于视角色为圆柱体
		if(abs(ft - Algo_FormatAngle(wp->y_angle)) <= fd * 2)
		{
			return i;
		}
	}
	return -1;
}

int Algo_ComputeCharacterPositionInNETLizard3DMap(const GL_NETLizard_3D_Model *map_model, game_character *gamer, const nl_vector3_t *new_v, nl_vector3_t *return_v)
{
	if(!map_model || !gamer || !new_v || !return_v)
		return 0;

	nl_vector3_t ori_v = {gamer->position[0], gamer->position[1], gamer->position[2] + gamer->height};
	int r = Algo_LadderItemCollisionFromScene(map_model, &ori_v, new_v, gamer->x_angle, gamer->y_angle, gamer->width, gamer->height, &gamer->scene, &gamer->collision_item, return_v);
	if(!r)
	{
		r = Algo_ComputePositionInNETLizard3DMap(map_model, &ori_v, new_v, gamer->width, gamer->height, return_v, &gamer->scene, &gamer->collision_item);
	}
	gamer->scene_collision_result = r;
	return r;
}

int Algo_ComputeThirdPersonPosition(const GL_NETLizard_3D_Model *map_model, const game_character *gamer, float yr, float xr, float tps_factory, int cross, int free_view, float free_yr, float free_xr, gl_vector3_t *v, float *ryr, float *rxr)
{
	if(!map_model || !gamer || !v)
		return 0;
	float yr_tmp; // left-right view
	float xr_tmp; // up-down view
	if(free_view)
	{
		yr_tmp = free_yr;
		//xr_tmp = 0;
		xr_tmp = free_xr;
	}
	else
	{
		yr_tmp = gamer->y_angle;
		xr_tmp = gamer->x_angle;
	}
	float oyr = Algo_FormatAngle(yr_tmp + yr);
	float oxr = Algo_FormatAngle(xr_tmp + xr);

	nl_vector3_t d = Algo_ComputeDirection(oyr, oxr);
	Vector3_Inverse(&d);
	nl_vector3_t dir = Vector3_Scale(&d, tps_factory);
	if(ryr)
		*ryr = Algo_FormatAngle(- yr_tmp - 180.0);
	if(rxr)
		*rxr = xr_tmp;

	nl_vector3_t new_position = {gamer->position[0] + dir.x, gamer->position[1] + dir.y, gamer->position[2] + gamer->height + dir.z };

	if(cross)
	{
		v->x = -new_position.x;
		v->y = -new_position.z;
		v->z = new_position.y;
		return 1;
	}
	int scene = -1;
	map_collision_testing_result_type res = Algo_NETLizard3DMapCollisionTesting(map_model, &new_position, 0.0, 0.0, &scene);
	if(res == map_only_in_aabb_type)
	{
		const GL_NETLizard_3D_Mesh *mesh = map_model->meshes + scene;
		aabb_t aabb = {
			{mesh->ortho[3], mesh->ortho[4], mesh->ortho[5]},
			{mesh->ortho[0], mesh->ortho[1], mesh->ortho[2]}
		};
		unsigned int j;
		int find = 0;
		int p = -1;
		float distance = FLT_MAX;
		nl_vector3_t dt = {-d.x, -d.y, -d.z};
		line_t l = {new_position, dt};
		nl_vector3_t po = {0.0, 0.0, 0.0};
		nl_vector3_t no = {0.0, 0.0, 0.0};
		for(j = 0; j < mesh->plane_count; j++)
		{
			plane_t plane = {
				{mesh->plane[j].position[0], mesh->plane[j].position[1], mesh->plane[j].position[2]},
				{-mesh->plane[j].normal[0], -mesh->plane[j].normal[1], -mesh->plane[j].normal[2]}
			};
			float dis = 0.0;
			nl_vector3_t n = {0.0, 0.0, 0.0};
			int r = Math3D_LineToPlaneCollision(&l, &plane, &dis, &n);
			if(r != 1)
				continue;
			if(find == 0)
			{
				Math3D_LineToPlaneIntersect(&l, &plane, &po);
				if(!Math3D_PointInAABB(&po, &aabb))
					continue;
				distance = dis;
				find = 1;
				p = j;
				no = n;
			}
			else
			{
				if(dis < distance)
				{
					Math3D_LineToPlaneIntersect(&l, &plane, &po);
					if(!Math3D_PointInAABB(&po, &aabb))
						continue;
					p = j;
					distance = dis;
					no = n;
				}
			}
		}
		if(p != -1)
		{
			float va = Vector3_DotVector3(&no, &dt);
			if(distance > tps_factory && va > 0.0f)
			{
				v->x = -new_position.x;
				v->y = -new_position.z;
				v->z = new_position.y;
			}
			else
			{
				v->x = -po.x - -no.x;
				v->y = -po.z - -no.z;
				v->z = po.y - no.y;
			}
		}
		else
		{
			float bdis = KARIN_MIN(gamer->width, gamer->full_height - gamer->height);
			nl_vector3_t dd = Vector3_Scale(&d,  bdis);
			v->x = -(gamer->position[0] + dd.x);
			v->y = -(gamer->position[2] + gamer->height + dd.z);
			v->z = gamer->position[1] + dd.y;
		}
	}
	else if(res == map_out_aabb_type && gamer->scene_collision_result)
	{
		const GL_NETLizard_3D_Mesh *mesh = map_model->meshes + gamer->scene;
		int *scenes = NEW_II(int, map_model->count);
		scenes[0] = gamer->scene + 1;
		int cur = 1;
		int i;
		for(i = 0; i < (int)mesh->bsp_count; i++)
		{
			GLint prev = map_model->bsp_data[mesh->bsp[i]].prev_scene;
			GLint next = map_model->bsp_data[mesh->bsp[i]].next_scene;
			int j;
			for(j = 0; j < cur; j++)
			{
				if(scenes[j] == prev + 1)
					break;
			}
			if(j == cur)
			{
				scenes[cur] = prev + 1;
				cur++;
			}
			for(j = 0; j < cur; j++)
			{
				if(scenes[j] == next + 1)
					break;
			}
			if(j == cur)
			{
				scenes[cur] = next + 1;
				cur++;
			}
		}
		int find = 0;
		int p = -1;
		int s = -2;
		float distance = FLT_MAX;
		nl_vector3_t dt = {-d.x, -d.y, -d.z};
		line_t l = {new_position, dt};
		nl_vector3_t po = {0.0, 0.0, 0.0};
		nl_vector3_t no = {0.0, 0.0, 0.0};
		for(i = cur - 1; i >= 0; i--)
		{
			if(scenes[i] == 0)
				break;
			mesh = map_model->meshes + (scenes[i] - 1);
			aabb_t aabb = {
				{mesh->ortho[3], mesh->ortho[4], mesh->ortho[5]},
				{mesh->ortho[0], mesh->ortho[1], mesh->ortho[2]}
			};
			unsigned int j;
			for(j = 0; j < mesh->plane_count; j++)
			{
				plane_t plane = {
					{mesh->plane[j].position[0], mesh->plane[j].position[1], mesh->plane[j].position[2]},
					{-mesh->plane[j].normal[0], -mesh->plane[j].normal[1], -mesh->plane[j].normal[2]}
				};
				nl_vector3_t n = {0.0, 0.0, 0.0};
				float dis = 0.0;
				int r = Math3D_LineToPlaneCollision(&l, &plane, &dis, &n);
				if(r != 1)
					continue;
				if(find == 0)
				{
					Math3D_LineToPlaneIntersect(&l, &plane, &po);
					if(!Math3D_PointInAABB(&po, &aabb))
						continue;
					distance = dis;
					find = 1;
					p = j;
					s = scenes[i] - 1;
					no = n;
				}
				else
				{
					if(dis < distance)
					{
						Math3D_LineToPlaneIntersect(&l, &plane, &po);
						if(!Math3D_PointInAABB(&po, &aabb))
							continue;
						p = j;
						distance = dis;
						s = scenes[i] - 1;
						no = n;
					}
				}
			}
		}
		if(p != -1 && s != -2)
		{
			float va = Vector3_DotVector3(&no, &dt);
			if(distance > tps_factory && va > 0.0f)
			{
				v->x = -new_position.x;
				v->y = -new_position.z;
				v->z = new_position.y;
			}
			else
			{
				v->x = -po.x - -no.x;
				v->y = -po.z - -no.z;
				v->z = po.y - no.y;
			}
		}
		else
		{
			float bdis = KARIN_MIN(gamer->width, gamer->full_height - gamer->height);
			nl_vector3_t dd = Vector3_Scale(&d,  bdis);
			v->x = -(gamer->position[0] + dd.x);
			v->y = -(gamer->position[2] + gamer->height + dd.z);
			v->z = gamer->position[1] + dd.y;
		}
		free(scenes);
	}
	else
	{
		v->x = -new_position.x;
		v->y = -new_position.z;
		v->z = new_position.y;
	}
	return 1;
}

void Game_CharacterAttack(const GL_NETLizard_3D_Model *model, game_character *a, game_character *characters, int start, int count)
{
	if(!model || !characters || !a)
		return;
	if(a->health == health_death_type)
		return;
	weapon *wp = Game_CharacterCurrentWeapon(a);
	if(!wp)
		return;
	if(a->ai.type == ai_player_type)
		return;
	if((wp->ammo_total_count == 0) && (a->ai.type == ai_trigger_type && (((a->ai.action & aiaction_attack_type) || (a->ai.action & aiaction_fight_type)))))
	{
		AI_MakeComputeAction(&a->ai, 0, aiaction_movebackward_type);
		return;
	}
	if(wp->ammo_total_count == 0)
		return;
	int attack = 0;
	int state = 0;
	float distance = 0.0;
	int index = 0;
	nl_vector3_t v1 = {a->position[0], a->position[1], a->position[2] + a->height};
	int j;
	for(j = start; j < count; j++)
	{
		game_character *b = characters + j;
		if(a == b)
			continue;
		if(b->health == health_death_type)
			continue;
		if(a->group == b->group)
			continue;
		if(!Game_CharacterCanViewCharacter(model, a, b))
			continue;
		nl_vector3_t v2 = {b->position[0], b->position[1], b->position[2] + b->height};
		nl_vector3_t v = Vector3_SubtractVector3(&v1, &v2);
		float d = Vector3_Mag(&v);
		if(state == 0)
		{
			distance = d;
			index = j;
			state = 1;
		}
		else
		{
			if(d < distance)
			{
				distance = d;
				index = j;
			}
		}
	}
	if(state)
	{
		game_ai ai;
		ZERO(&ai, game_ai);
		AI_ClearAction(&ai);
		ai.time = a->ai.time;
		ai.type = ai_trigger_type;
		if(wp->type <= short_attack_type)
		{
			ai.action |= aiaction_fight_type;
			ai.fight_mask = 1;
			ai.fighting = 0;
		}
		else
		{
			ai.action |= aiaction_attack_type;
			ai.attack_mask = 1;
			ai.attack_count = 0;
			ai.attack_total_count = 20;
		}
		game_character *b = characters + index;
		if(a->ai.type != ai_trigger_type || (((a->ai.action & aiaction_attack_type) == 0) && (a->ai.action & aiaction_fight_type) == 0))
			AI_Copy(&a->ai, &ai);
		attack++;
		nl_vector3_t v2 = {b->position[0], b->position[1], b->position[2] + b->height};
		nl_vector3_t v = Vector3_SubtractVector3(&v1, &v2);
		float yr = 0.0;
		float xr = 0.0;
		Algo_GetNormalAngle(&v, &yr, &xr);
		if(yr != a->y_angle)
		{
			// TODO 选取最近角度选择向左或右旋转
			float offset = Algo_FormatAngle(yr - a->y_angle);
			if(offset > 0 && offset <= 180.0f)
				a->ai.action |= aiaction_turnleft_type;
			else
				a->ai.action |= aiaction_turnright_type;
			a->ai.rotation_mask = 1;
			a->ai.y_angle_target = yr;
			a->ai.angle_range = 0.0;
			a->ai.y_angle_progress = a->y_angle;
			wp->y_angle = a->y_angle;
		}
		wp->x_angle = xr;
		a->x_angle = xr;
		if(wp->type <= short_attack_type)
		{
			nl_vector3_t dir = Vector3_SubtractVector3(&v2, &v1);
			float dis = Vector3_Mag(&dir);
			// 目标距离小于角色宽度 不操作
			if(dis > a->width + b->width)
			{
				a->ai.goto_mask = 1;
				a->ai.action |= aiaction_moveforward_type;
				a->ai.position_progress[0] = a->position[0];
				a->ai.position_progress[1] = a->position[1];
				a->ai.position_progress[2] = a->position[2];
				a->ai.position_target[0] = v2.x;
				a->ai.position_target[1] = v2.y;
				a->ai.position_target[2] = v2.z;
				a->ai.position_range = b->width + a->width + CHARACTER_MIN_SPACING;
			}
		}
		else
		{
			a->ai.position_target[0] = b->position[0];
			a->ai.position_target[1] = b->position[1];
			a->ai.position_target[2] = b->position[2] + b->height;
		}
	}
	else
	{
		// nothing
	}
	if(a->ai.type == ai_trigger_type && (((a->ai.action & aiaction_attack_type) || (a->ai.action & aiaction_fight_type))) && attack == 0)
	{
		a->x_angle = 0.0;
		if(a->ai.action & aiaction_movexy_type)
			AI_MakeComputeAction(&a->ai, 1, 0);
		else
		{
			if(a->health > a->health_full * 0.8)
				AI_MakeComputeAction(&a->ai, 0, aiaction_moveforward_type);
			else if(a->health > a->health_full * 0.7)
				AI_MakeComputeAction(&a->ai, 0, aiaction_idle_type);
			else if(a->health < a->health_full * 0.2)
				AI_MakeComputeAction(&a->ai, 0, aiaction_movebackward_type);
			else
				AI_MakeComputeAction(&a->ai, 1, 0);
		}
		if(Game_ReloadWeapon(wp, a->ai.time))
			a->ai.action |= aiaction_reload_type;
	}
}


// 更新主角的位置
void Game_HandlePlayerAI(const GL_NETLizard_3D_Model *map_model, game_character *player, long long time)
{
	if(!map_model || !player)
		return;
	if(player->ai.type != ai_player_type)
		return;
	// myself player model
	// get position and angle
	double per = (double)(time - player->ai.time) / 1000.0;
	float turn_unit = player->turn_unit * per;
	float move_unit = player->move_unit * per;

	nl_vector3_t ori_v = {player->position[0], player->position[1], player->position[2] + player->height};
	float oxr = player->x_angle;
	float oyr = player->y_angle;

	orientation_type o = center_orientation_type;
	position_type p = center_position_type;
	if(player->ai.action & aiaction_turnup_type)
		o |= up_orientation_type;
	if(player->ai.action & aiaction_turndown_type)
		o |= down_orientation_type;
	if(player->ai.action & aiaction_turnleft_type)
		o |= left_orientation_type;
	if(player->ai.action & aiaction_turnright_type)
		o |= right_orientation_type;

	if(player->ai.action & aiaction_moveforward_type)
		p |= forward_position_type;
	if(player->ai.action & aiaction_movebackward_type)
		p |= backward_position_type;
	if(player->ai.action & aiaction_moveleft_type)
		p |= left_position_type;
	if(player->ai.action & aiaction_moveright_type)
		p |= right_position_type;
	if(is_cross)
	{
		if(player->ai.action & aiaction_moveup_type)
			p |= up_position_type;
		if(player->ai.action & aiaction_movedown_type)
			p |= down_position_type;
	}

	// get return var
	float ryr = 0.0;
	float rxr = 0.0;
	nl_vector3_t rv = ori_v;

	Algo_TransformPositionAndAngle(p, &ori_v, move_unit, &rv, o, oxr, oyr, turn_unit, &rxr, &ryr, is_cross);

	if(o != center_orientation_type)
	{
		player->y_angle = ryr;
		player->x_angle = rxr;
	}

	if(is_cross)
	{
		player->position[0] = rv.x;
		player->position[1] = rv.y;
		player->position[2] = rv.z - player->height;
	}
	else
	{
		// whatever must update position, ex. on the elevator
		// check is jumping or falldown
		if(player->z_moving.state != no_z_type)
		{
			double delta = (double)(time - player->z_moving.start_time) / 1000.0;
			rv.z += -Physics_GetFalldownDistance(player->z_moving.jump_speed, GAME_G, delta);
			player->z_moving.speed = Physics_GetJumpSpeed(player->z_moving.jump_speed, GAME_G, delta);
		}
		// collision testing
		nl_vector3_t v = ori_v;
		nl_vector3_t cv = {0.0, 0.0, 0.0};
		if(Algo_CharacterCollisionTesting(map_model, player, &rv, characters, 0, character_count, NULL, &cv))
		{
			rv.x = cv.x;
			rv.y = cv.y;
		}
		Algo_ComputeCharacterPositionInNETLizard3DMap(map_model, player, &rv, &v);
		if(player->scene_collision_result)
		{
			float d = rv.z - v.z;
			if(player->z_moving.state != no_z_type)
			{
				if(d > 0.0f || player->z_moving.speed < 0.0f)
					v.z = rv.z;
				else
				{
					player->z_moving.speed = 0.0;
					player->z_moving.state = no_z_type;
				}
			}
			else
			{
				if(d > move_unit)
				{
					player->z_moving.state = z_falldown_type;
					player->z_moving.start_z = rv.z;
					player->z_moving.start_time = time;
					player->z_moving.jump_speed = 0.0;
					player->z_moving.speed = 0.0;
					v.z = rv.z;
				}
			}
		}
		else
		{
			if(player->z_moving.state == z_jumping_type)
			{
				player->z_moving.state = z_falldown_type;
				player->z_moving.start_z = ori_v.z;
				player->z_moving.start_time = time;
				player->z_moving.jump_speed = 0.0;
				player->z_moving.speed = 0.0;
			}
			else if(player->z_moving.state == z_falldown_type)
			{
				//player->z_moving.speed = 0.0;
				//player->z_moving.state = no_z_type;
			}
			v.x = ori_v.x;
			v.y = ori_v.y;
			v.z = ori_v.z;
		}
		player->position[0] = v.x;
		player->position[1] = v.y;
		player->position[2] = v.z - player->height;
	}

	unsigned up_wp = 0;
	if((player->ai.action & aiaction_attack_type) == 0 && (player->ai.action & aiaction_fight_type) == 0)
	{
		up_wp = 1;
	}
	if(player->z_moving.state != no_z_type && (player->ai.action & aiaction_jump_type) == 0)
		player->ai.action |= aiaction_jump_type;
	else if(player->z_moving.state == no_z_type && player->ai.action & aiaction_jump_type)
		player->ai.action ^= aiaction_jump_type;
	Game_UpdateCharacterPositionAndDirection(player, player->position[0], player->position[1], player->position[2], player->x_angle, player->y_angle, up_wp);
}

void Game_HandleComputeAI(const GL_NETLizard_3D_Model *map_model, game_character *gamer, long long time)
{
	if(!map_model || !gamer)
		return;
	if(gamer->ai.type != ai_compute_type)
		return;
	double per = (double)(time - gamer->ai.time) / 1000.0;
	float turn_unit = gamer->turn_unit * per;
	float move_unit = gamer->move_unit * per;

	nl_vector3_t ov = {gamer->position[0], gamer->position[1], gamer->position[2] + gamer->height};
	float oxr = gamer->x_angle;
	float oyr = gamer->y_angle;
	float rxr = 0.0;
	float ryr = 0.0;

	nl_vector3_t rv = ov;
	// 旋转
	position_type p = center_position_type;
	orientation_type o = center_orientation_type;

	if(gamer->ai.action & aiaction_turnleft_type)
		o |= left_orientation_type;
	else if(gamer->ai.action & aiaction_turnright_type)
		o |= right_orientation_type;
	if(o != center_orientation_type)
	{
		if(gamer->ai.y_angle_target - gamer->ai.y_angle_progress < turn_unit)
		{
			turn_unit = gamer->ai.y_angle_target - gamer->ai.y_angle_progress;
		}
	}

	// 移动
	if(gamer->ai.action & aiaction_moveforward_type)
		p |= forward_position_type;
	else if(gamer->ai.action & aiaction_movebackward_type)
		p |= backward_position_type;
	if(gamer->ai.action & aiaction_moveleft_type)
		p |= left_position_type;
	else if(gamer->ai.action & aiaction_moveright_type)
		p |= right_position_type;
	if(p != center_position_type)
		gamer->ai.move_step += move_unit / gamer->move_unit;

	// 计算更新后的坐标
	Algo_TransformPositionAndAngle(p, &ov, move_unit, &rv, o, oxr, oyr, turn_unit, &rxr, &ryr, 0);

	// 更新角色数据
	if(o != center_orientation_type)
	{
		gamer->ai.y_angle_progress += turn_unit;
		gamer->y_angle = ryr;
	}
	// 碰撞测试
	// 无碰撞则更新
	// 碰撞则停止AI进度
	if(gamer->z_moving.state != no_z_type)
	{
		double delta = (double)(time - gamer->z_moving.start_time) / 1000.0;
		rv.z += -Physics_GetFalldownDistance(gamer->z_moving.jump_speed, GAME_G, delta);
		gamer->z_moving.speed = Physics_GetJumpSpeed(gamer->z_moving.jump_speed, GAME_G, delta);
	}
	nl_vector3_t v = ov;
	nl_vector3_t cv = {0.0, 0.0, 0.0};
	if(Algo_CharacterCollisionTesting(map_model, gamer, &rv, characters, 0, character_count, NULL, &cv))
	{
		rv.x = cv.x;
		rv.y = cv.y;
	}
	Algo_ComputeCharacterPositionInNETLizard3DMap(map_model, gamer, &rv, &v);	

	if(gamer->scene_collision_result)
	{
		float d = rv.z - v.z;
		if(gamer->z_moving.state != no_z_type)
		{
			if(d > 0.0f || gamer->z_moving.speed < 0.0f)
				v.z = rv.z;
			else
			{
				gamer->z_moving.speed = 0.0;
				gamer->z_moving.state = no_z_type;
			}
		}
		else
		{
			if(d > move_unit)
			{
				gamer->z_moving.state = z_falldown_type;
				gamer->z_moving.start_z = ov.z;
				gamer->z_moving.start_time = time;
				gamer->z_moving.jump_speed = 0.0;
				gamer->z_moving.speed = 0.0;
				v.z = rv.z;
			}
		}
		gamer->position[0] = v.x;
		gamer->position[1] = v.y;
		gamer->position[2] = v.z - gamer->height;
	}
	else
	{
		if(gamer->z_moving.state == z_jumping_type)
		{
			gamer->z_moving.state = z_falldown_type;
			gamer->z_moving.start_z = ov.z;
			gamer->z_moving.start_time = time;
			gamer->z_moving.jump_speed = 0.0;
			gamer->z_moving.speed = 0.0;
		}
		else if(gamer->z_moving.state == z_falldown_type)
		{
			gamer->z_moving.speed = 0.0;
			gamer->z_moving.state = no_z_type;
		}
		v.z = ov.z;
	}

	Game_UpdateCharacterPositionAndDirection(gamer, gamer->position[0], gamer->position[1], gamer->position[2], gamer->x_angle, gamer->y_angle, 1);
}

void Game_HandleOperateAI(const GL_NETLizard_3D_Model *map_model, game_character *gamer, long long time)
{
	if(!map_model || !gamer)
		return;
	if(gamer->ai.type != ai_operate_type)// 人工操作AI更新
		return;
	double per = (double)(time - gamer->ai.time) / 1000.0;
	float turn_unit = gamer->turn_unit * per;
	float move_unit = gamer->move_unit * per;

	nl_vector3_t ov = {gamer->position[0], gamer->position[1], gamer->position[2] + gamer->height};
	nl_vector3_t rv = ov;

	// 重新计算是否需要旋转
	float oxr = gamer->x_angle;
	float oyr = gamer->y_angle;
	float rxr = 0.0;
	float ryr = 0.0;
	position_type p = center_position_type;
	orientation_type o = center_orientation_type;
	nl_vector3_t vg = {
		gamer->position[0],
		gamer->position[1],
		gamer->position[2]
	};
	nl_vector3_t point = {
		gamer->ai.position_target[0],
		gamer->ai.position_target[1],
		gamer->ai.position_target[2]
	};
	nl_vector3_t va = Vector3_SubtractVector3(&vg, &point);
	float xl = va.x;
	float yl = va.y;
	float f = Algo_FormatAngle(rtoa(atan2(yl, xl)) - 90.0);
	float offset = f - Algo_FormatAngle(gamer->y_angle);
	gamer->ai.y_angle_target = f;
	if(abs(offset) <= turn_unit)
	{
		gamer->y_angle = gamer->ai.y_angle_target;
		gamer->ai.y_angle_progress = gamer->ai.y_angle_target;
		oyr = gamer->y_angle;
	}
	else
	{
		if(gamer->ai.action & aiaction_turnleft_type)
			o |= left_orientation_type;
		else if(gamer->ai.action & aiaction_turnright_type)
			o |= right_orientation_type;
	}

	// 前进
	nl_vector2_t vp = {
		gamer->ai.position_progress[0],
		gamer->ai.position_progress[1]
	};
	nl_vector2_t vt = {
		gamer->ai.position_target[0],
		gamer->ai.position_target[1]
	};
	nl_vector2_t v2 = Vector2_SubtractVector2(&vt, &vp);
	float dis = Vector2_Mag(&v2);
	// 位置距离目标位置小于计算宽度 停止动作进度
	if(abs(dis) <= gamer->ai.position_range)
	{
		gamer->position[0] = gamer->ai.position_target[0];
		gamer->position[1] = gamer->ai.position_target[1];
		gamer->ai.position_progress[0] = gamer->ai.position_target[0];
		gamer->ai.position_progress[1] = gamer->ai.position_target[1];
	}
	else
	{
		if(gamer->ai.action & aiaction_moveforward_type)
			p |= forward_position_type;
		else if(gamer->ai.action & aiaction_movebackward_type)
			p |= backward_position_type;
		if(gamer->ai.action & aiaction_moveleft_type)
			p |= left_position_type;
		else if(gamer->ai.action & aiaction_moveright_type)
			p |= right_position_type;
	}

	// 计算新位置坐标 角度
	Algo_TransformPositionAndAngle(p, &ov, move_unit, &rv, o, oxr, oyr, turn_unit, &rxr, &ryr, 0);

	if(o != center_orientation_type)
	{
		gamer->y_angle = ryr;
		gamer->ai.y_angle_progress = ryr;
	}
	// 碰撞测试
	// 碰撞则停止，更新AI为随机计算，状态为空闲
	// 无碰撞则更新进度
	if(gamer->z_moving.state != no_z_type)
	{
		double delta = (double)(time - gamer->z_moving.start_time) / 1000.0;
		rv.z += -Physics_GetFalldownDistance(gamer->z_moving.jump_speed, GAME_G, delta);
		gamer->z_moving.speed = Physics_GetJumpSpeed(gamer->z_moving.jump_speed, GAME_G, delta);
	}
	nl_vector3_t v = ov;
	nl_vector3_t cv = {0.0, 0.0, 0.0};
	if(Algo_CharacterCollisionTesting(map_model, gamer, &rv, characters, 0, character_count, NULL, &cv))
	{
		rv.x = cv.x;
		rv.y = cv.y;
	}
	Algo_ComputeCharacterPositionInNETLizard3DMap(map_model, gamer, &rv, &v);	
	if(gamer->scene_collision_result)
	{
		float d = rv.z - v.z;
		if(gamer->z_moving.state != no_z_type)
		{
			if(d > 0.0f || gamer->z_moving.speed < 0.0f)
				v.z = rv.z;
			else
			{
				gamer->z_moving.speed = 0.0;
				gamer->z_moving.state = no_z_type;
			}
		}
		else
		{
			if(d > move_unit)
			{
				gamer->z_moving.state = z_falldown_type;
				gamer->z_moving.start_z = ov.z;
				gamer->z_moving.start_time = time;
				gamer->z_moving.jump_speed = 0.0;
				gamer->z_moving.speed = 0.0;
				v.z = rv.z;
			}
		}
		gamer->position[0] = v.x;
		gamer->position[1] = v.y;
		gamer->position[2] = v.z - gamer->height;
		gamer->ai.position_progress[0] = gamer->position[0];
		gamer->ai.position_progress[1] = gamer->position[1];
		gamer->ai.position_progress[2] = gamer->position[2];
	}
	else
	{
		if(gamer->z_moving.state == z_jumping_type)
		{
			gamer->z_moving.state = z_falldown_type;
			gamer->z_moving.start_z = ov.z;
			gamer->z_moving.start_time = time;
			gamer->z_moving.jump_speed = 0.0;
			gamer->z_moving.speed = 0.0;
		}
		else if(gamer->z_moving.state == z_falldown_type)
		{
			gamer->z_moving.speed = 0.0;
			gamer->z_moving.state = no_z_type;
		}
		v.z = ov.z;
		gamer->ai.position_progress[0] = gamer->position[0];
		gamer->ai.position_progress[1] = gamer->position[1];
		gamer->ai.position_target[0] = gamer->ai.position_progress[0];
		gamer->ai.position_target[1] = gamer->ai.position_progress[1];
	}
	Game_UpdateCharacterPositionAndDirection(gamer, gamer->position[0], gamer->position[1], gamer->position[2], gamer->x_angle, gamer->y_angle, 1);
}

void Game_HandleTriggerAI(const GL_NETLizard_3D_Model *map_model, game_character *gamer, long long time)
{
	if(!map_model || !gamer)
		return;
	if(gamer->ai.type != ai_trigger_type) // 触发AI更新
		return;
	const weapon *wp = Game_CharacterCurrentWeapon(gamer);
	double per = (double)(time - gamer->ai.time) / 1000.0;
	float turn_unit = gamer->turn_unit * per;
	float move_unit = gamer->move_unit * per;

	nl_vector3_t ov = {gamer->position[0], gamer->position[1], gamer->position[2] + gamer->height};
	nl_vector3_t rv = ov;

	// 重新计算是否需要旋转
	float oxr = gamer->x_angle;
	float oyr = gamer->y_angle;
	float rxr = 0.0;
	float ryr = 0.0;
	position_type p = center_position_type;
	orientation_type o = center_orientation_type;
	nl_vector3_t vg = {
		gamer->position[0],
		gamer->position[1],
		gamer->position[2] + gamer->height
	};
	nl_vector3_t point = {
		gamer->ai.position_target[0],
		gamer->ai.position_target[1],
		gamer->ai.position_target[2]
	};
	nl_vector3_t va = Vector3_SubtractVector3(&vg, &point);
	float xl = va.x;
	float yl = va.y;
	float f = Algo_FormatAngle(rtoa(atan2(yl, xl)) - 90.0);
	float offset = f - Algo_FormatAngle(gamer->y_angle);
	gamer->ai.y_angle_target = f;
	if(abs(offset) <= turn_unit)
	{
		gamer->y_angle = gamer->ai.y_angle_target;
		gamer->ai.y_angle_progress = gamer->ai.y_angle_target;
		oyr = gamer->y_angle;
	}
	else
	{
		if(gamer->ai.action & aiaction_turnleft_type)
			o |= left_orientation_type;
		else if(gamer->ai.action & aiaction_turnright_type)
			o |= right_orientation_type;
	}

	if(gamer->ai.action & aiaction_fight_type)
	{
		nl_vector3_t me = {
			gamer->position[0],
			gamer->position[1],
			gamer->position[2]
		};
		nl_vector3_t tg = {
			gamer->ai.position_target[0],
			gamer->ai.position_target[1],
			gamer->ai.position_target[2]
		};
		nl_vector3_t v2 = Vector3_SubtractVector3(&tg, &me);
		float dis = Vector3_Mag(&v2);
		// 位置距离目标位置小于计算宽度 停止动作进度
		if(wp && wp->type <= short_attack_type && abs(dis) < wp->shot_range) // ?? 20180718 4wps
			gamer->ai.fighting = 1;
		if(abs(dis) < gamer->ai.position_range)
		{
			//gamer->position[0] = gamer->ai.position_target[0];
			//gamer->position[1] = gamer->ai.position_target[1];
			gamer->ai.position_progress[0] = gamer->ai.position_target[0];
			gamer->ai.position_progress[1] = gamer->ai.position_target[1];
		}
		else
		{
			if(gamer->ai.action & aiaction_moveforward_type)
				p |= forward_position_type;
			else if(gamer->ai.action & aiaction_movebackward_type)
				p |= backward_position_type;
			if(gamer->ai.action & aiaction_moveleft_type)
				p |= left_position_type;
			else if(gamer->ai.action & aiaction_moveright_type)
				p |= right_position_type;
		}
	}
	else
	{
		if(gamer->ai.action & aiaction_moveforward_type)
			p |= forward_position_type;
		else if(gamer->ai.action & aiaction_movebackward_type)
			p |= backward_position_type;
		if(gamer->ai.action & aiaction_moveleft_type)
			p |= left_position_type;
		else if(gamer->ai.action & aiaction_moveright_type)
			p |= right_position_type;
		if(p != center_position_type && gamer->ai.action & aiaction_attack_type)
			gamer->ai.move_step += move_unit / gamer->move_unit;
	}

	if(((gamer->ai.action & aiaction_attack_type) && (gamer->ai.action & aiaction_movexyz_type))
			|| ((gamer->ai.action & aiaction_fight_type) && gamer->ai.fighting))
		move_unit *= FIGHTING_MOVE_SPEED_PER;
	// 计算新位置坐标 角度
	Algo_TransformPositionAndAngle(p, &ov, move_unit, &rv, o, oxr, oyr, turn_unit, &rxr, &ryr, 0);

	if(o != center_orientation_type)
	{
		gamer->y_angle = ryr;
		gamer->ai.y_angle_progress = ryr;
	}
	// 碰撞测试
	// 碰撞则停止，更新AI为随机计算，状态为空闲
	// 无碰撞则更新进度
	if(gamer->z_moving.state != no_z_type)
	{
		double delta = (double)(time - gamer->z_moving.start_time) / 1000.0;
		rv.z += -Physics_GetFalldownDistance(gamer->z_moving.jump_speed, GAME_G, delta);
		gamer->z_moving.speed = Physics_GetJumpSpeed(gamer->z_moving.jump_speed, GAME_G, delta);
	}
	nl_vector3_t v = ov;
	nl_vector3_t cv = {0.0, 0.0, 0.0};
	if(Algo_CharacterCollisionTesting(map_model, gamer, &rv, characters, 0, character_count, NULL, &cv))
	{
		rv.x = cv.x;
		rv.y = cv.y;
	}
	Algo_ComputeCharacterPositionInNETLizard3DMap(map_model, gamer, &rv, &v);	
	if(gamer->scene_collision_result)
	{
		float d = rv.z - v.z;
		if(gamer->z_moving.state != no_z_type)
		{
			if(d > 0.0f || gamer->z_moving.speed < 0.0f)
				v.z = rv.z;
			else
			{
				gamer->z_moving.speed = 0.0;
				gamer->z_moving.state = no_z_type;
			}
		}
		else
		{
			if(d > move_unit)
			{
				gamer->z_moving.state = z_falldown_type;
				gamer->z_moving.start_z = ov.z;
				gamer->z_moving.start_time = time;
				gamer->z_moving.jump_speed = 0.0;
				gamer->z_moving.speed = 0.0;
				v.z = rv.z;
			}
		}
		gamer->position[0] = v.x;
		gamer->position[1] = v.y;
		gamer->position[2] = v.z - gamer->height;
		if(gamer->ai.action & aiaction_fight_type)
		{
			gamer->ai.position_progress[0] = gamer->position[0];
			gamer->ai.position_progress[1] = gamer->position[1];
			gamer->ai.position_progress[2] = gamer->position[2];
		}
	}
	else
	{
		if(gamer->z_moving.state == z_jumping_type)
		{
			gamer->z_moving.state = z_falldown_type;
			gamer->z_moving.start_z = ov.z;
			gamer->z_moving.start_time = time;
			gamer->z_moving.jump_speed = 0.0;
			gamer->z_moving.speed = 0.0;
		}
		else if(gamer->z_moving.state == z_falldown_type)
		{
			gamer->z_moving.speed = 0.0;
			gamer->z_moving.state = no_z_type;
		}
		v.z = ov.z;
		if(gamer->ai.action & aiaction_fight_type)
		{
			gamer->ai.position_progress[0] = gamer->position[0];
			gamer->ai.position_progress[1] = gamer->position[1];
			gamer->ai.position_target[0] = gamer->ai.position_progress[0];
			gamer->ai.position_target[1] = gamer->ai.position_progress[1];
		}
	}

	// ??? dont update weapon position
	Game_UpdateCharacterPositionAndDirection(gamer, gamer->position[0], gamer->position[1], gamer->position[2], gamer->x_angle, gamer->y_angle, 0);
}

void Game_AIRelive(const GL_NETLizard_3D_Model *map_model, game_character *characters, int start, int count, long rt, long long game_time)
{
	if(!map_model || !characters)
		return;
	long long t = game_time / 1000;
	int i;
	for(i = start; i < count; i++)
	{
		if((characters[i].ai.type == ai_trigger_type || characters[i].ai.type == ai_player_type) && characters[i].ai.action == aiaction_dead_type)
		{
			if(t - characters[i].ai.dead_time / 1000.0 > rt)
			{
				characters[i].health = characters[i].health_full;
				Game_RandStartPosition(map_model, characters + i, 2);
				if(characters[i].ai.type == ai_player_type)
				{
					characters[i].ai.action ^= aiaction_dead_type;
					characters[i].ai.dead_time = 0;
					characters[i].ai.dead_mask = 0;
				}
				else
					AI_MakeComputeAction(&characters[i].ai, 1, 0);
				characters[i].x_angle = 0.0;
				characters[i].y_angle = (float)(rand() % 360);
				characters[i].z_moving.state = no_z_type;
				characters[i].z_moving.start_z = 0;
				characters[i].z_moving.start_time  = 0;
				characters[i].z_moving.jump_speed = 0;
				characters[i].z_moving.speed = 0;
				const weapon *wp = Game_CharacterCurrentWeapon(characters + i);
				if(wp && wp->weapon_index < egypt3d_Worm_Weapon)
				{
					Game_CharacterRand4Weapons(characters + i);
				}
				Game_UpdateCharacterPositionAndDirection(characters + i, characters[i].position[0], characters[i].position[1], characters[i].position[2], characters[i].x_angle, characters[i].y_angle, 0);
			}
		}
	}
}

void Game_AttackEvent(const GL_NETLizard_3D_Model *map_model, game_character *characters, int current, int start, int count, long long game_time, list_template *list, list_template *bullets, list_template *sound)
{
	if(!map_model || !characters)
		return;
	int j;
	for(j = start; j < count; j++)
		Game_CharacterAttack(map_model, characters + j, characters, start, count);

	int *healths = NEW_II(int, count);
	for(j = start; j < count; j++)
	{
		healths[j] = characters[j].health;
	}
	nl_vector3_t cur_pos = {characters[current].position[0], characters[current].position[1], characters[current].position[2]};
	for(j = start; j < count; j++)
	{
		weapon *wp = Game_CharacterCurrentWeapon(characters + j);
		if(!wp)
			continue;
		Game_UpdateWeapon(characters + j, game_time);
		if(Game_WeaponShot(characters + j, list, bullets))
		{
			if(sound)
			{
				nl_vector3_t wp_pos = {wp->position[0], wp->position[1], wp->position[2]};
				nl_vector3_t direction = Vector3_SubtractVector3(&wp_pos, &cur_pos);
				float distance = Vector3_Mag(&direction);
				if(distance < SOUND_RANGE)
				{
					sound_effect e;
					if(Sound_MakeWeaponFireSound(&e, wp, distance, SOUND_RANGE))
						List_PushBack(sound, &e);
				}
			}
		}
	}

	if(bullets)
	{
		unsigned int k;
		for(k = 0; k < bullets->count; k++)
		{
			bullet *bt = List_GetDataByIndexT(bullets, k, bullet);
			if(!bt)
				continue;
			if(bt->finished == 1)
				continue;
			int index = -1;
			int scene = -1;
			int item = -1;
			human_body_type body = human_body_total;
			int r = 0;
			nl_vector3_t cv = {0.0, 0.0, 0.0};
			nl_vector3_t cn = {0.0, 0.0, 0.0};

			nl_vector3_t c_pos1 = {0.0, 0.0, 0.0};
			nl_vector3_t c_nml1 = {0.0, 0.0, 0.0};
			float dis1 = 0.0;
			nl_vector3_t c_pos2 = {0.0, 0.0, 0.0};
			nl_vector3_t c_nml2 = {0.0, 0.0, 0.0};
			float dis2 = 0.0;
			int cr = Game_BulletCharacterCollisionTesting(bt, characters, start, count, &index, &dis1, &body, &c_pos1, &c_nml1);
			int mr = Game_BulletMapCollisionTesting(map_model, bt, &dis2, &scene, &item, &c_pos2, &c_nml2);
			if(cr && mr)
			{
				if(dis1 <= dis2)
				{
					r = 1;
					cv = c_pos1;
					cn = c_nml1;
					bt->position[0] = cv.x;
					bt->position[1] = cv.y;
					bt->position[2] = cv.z;
					bt->finished = 1;
				}
				else
				{
					r = 2;
					cv = c_pos2;
					cn = c_nml2;
					bt->position[0] = cv.x;
					bt->position[1] = cv.y;
					bt->position[2] = cv.z;
					bt->finished = 1;
				}
			}
			else if(cr && !mr)
			{
				r = 1;
				cv = c_pos1;
				cn = c_nml1;
				bt->position[0] = cv.x;
				bt->position[1] = cv.y;
				bt->position[2] = cv.z;
				bt->finished = 1;
			}
			else if(!cr && mr)
			{
				r = 2;
				cv = c_pos2;
				cn = c_nml2;
				bt->position[0] = cv.x;
				bt->position[1] = cv.y;
				bt->position[2] = cv.z;
				bt->finished = 1;
			}
			else
			{
				Game_UpdateBullet(bt, game_time);
			}

			// 碰撞角色
			if(r == 1)
			{
				if(body == human_body_total)
					body = human_body_a_type;
				if(index != -1)
				{
					if(list)
					{
						float yr = 0.0;
						float xr = 0.0;
						Algo_GetNormalAngle(&cn, &yr, &xr);
						if(bt->type != shell_bullet_type && bt->type != grenade_bullet_type)
						{
							// 流血血迹
							particle p = Particle_MakeParticle(blood_block_particle_type, parabola_particle_type, cv.x + cn.x, cv.y + cn.y, cv.z + cn.z, xr, yr, xr, yr, bt->speed * BULLET_PER, game_time, 5000, GL_TRUE);
							List_PushBack(list, &p);
							// 伤口血迹
							p = Particle_MakeParticle(blood_spot_particle_type, fixed_particle_type, cv.x + cn.x, cv.y + cn.y, cv.z + cn.z, xr, yr, 0.0, 0.0, 0.0, game_time, 300, GL_FALSE);
							List_PushBack(list, &p);
						}
						else
						{
							particle p = Particle_MakeParticle(boom_particle_type, fixed_particle_type, cv.x + cn.x, cv.y + cn.y, cv.z + cn.z, xr, yr, 0.0, 0.0, 0.0, game_time, 300, GL_FALSE);
							List_PushBack(list, &p);
						}
					}

					if(bt->type != shell_bullet_type && bt->type != grenade_bullet_type)
					{
						if(healths[index] > health_death_type)
						{
							healths[index] = KARIN_MAX(healths[index] - bt->damage * Human_Body_Data[body].damage_factory, 0);
							if(healths[index] == health_death_type)
							{
								Game_CharacterDeath(characters + bt->character, characters + index);
								characters[bt->character].score.kill++;
								characters[index].score.death++;
								characters[bt->character].score.kill_character = index;
								characters[index].score.killed_character = bt->character;
								if(list)
								{
									// 死亡血迹
									particle p = Particle_MakeParticle(blood_particle_type, fixed_particle_type, characters[index].position[0], characters[index].position[1], characters[index].position[2] + 1, characters[index].x_angle, characters[index].y_angle, 0.0, 0.0, 0.0, game_time, 6000, GL_FALSE);
									List_PushBack(list, &p);
								}
							}
							else // 转向子弹方向
							{
								if(characters[index].ai.type == ai_compute_type || characters[index].ai.type == ai_operate_type)
								{
									nl_vector3_t btdir = Algo_ComputeDirection(bt->y_angle, bt->x_angle);
									Vector3_Inverse(&btdir);
									Game_LookatCharacter(map_model, characters + index, &btdir);
								}
							}
						}
					}
					else
					{
						int l;
						for(l = start; l < count; l++)
						{
							/*
							// kill self?
							if(characters[l].index == bt->character)
							continue;
							*/
							// kill partner?
							if(bt->group == characters[l].group && bt->character != characters[l].index)
								continue;
							float dis = 0.0;
							nl_vector3_t b_pos = {0.0, 0.0, 0.0};
							nl_vector3_t b_nml = {0.0, 0.0, 0.0};
							human_body_type body = human_body_total;
							nl_vector3_t boom = Vector3_PlusVector3(&cv, &cn);
							int br = Game_BoomAttack(map_model, &boom, characters + l, &dis, &b_pos, &b_nml, &body);
							if(!br)
								continue;
							int damage = Game_GetBulletBoomDamage(bt, dis);
							if(characters[l].index == bt->character)
								damage /= 2;
							if(damage > 0)
							{
								float yr2 = 0.0;
								float xr2 = 0.0;
								Algo_GetNormalAngle(&b_nml, &yr2, &xr2);
								if(list)
								{
									// 流血血迹
									particle p = Particle_MakeParticle(blood_block_particle_type, parabola_particle_type, b_pos.x + b_nml.x, b_pos.y + b_nml.y, b_pos.z + b_nml.z, xr2, yr2, xr2, yr2, bt->speed * BULLET_PER, game_time, 5000, GL_TRUE);
									List_PushBack(list, &p);
									// 伤口血迹
									p = Particle_MakeParticle(blood_spot_particle_type, fixed_particle_type, b_pos.x + b_nml.x, b_pos.y + b_nml.y, b_pos.z + b_nml.z, xr2, yr2, 0.0, 0.0, 0.0, game_time, 300, GL_FALSE);
									List_PushBack(list, &p);
								}

								if(healths[l] > health_death_type)
								{
									healths[l] = KARIN_MAX(healths[l] - damage * Human_Body_Data[body].damage_factory, health_death_type);
									if(healths[l] == health_death_type)
									{
										Game_CharacterDeath(characters + bt->character, characters + l);
										if(bt->character != l)
											characters[bt->character].score.kill++;
										characters[l].score.death++;
										characters[bt->character].score.kill_character = l;
										characters[l].score.killed_character = bt->character;
										if(list)
										{
											// 死亡血迹
											particle p = Particle_MakeParticle(blood_particle_type, fixed_particle_type, characters[l].position[0], characters[l].position[1], characters[l].position[2] + 1, characters[l].x_angle, characters[l].y_angle, 0.0, 0.0, 0.0, game_time, 6000, GL_FALSE);
											List_PushBack(list, &p);
										}
									}
									else // 转向子弹方向不会生效
									{
										if(characters[l].ai.type == ai_compute_type || characters[l].ai.type == ai_operate_type)
										{
											nl_vector3_t btdir = Algo_ComputeDirection(bt->y_angle, bt->x_angle);
											Vector3_Inverse(&btdir);
											Game_LookatCharacter(map_model, characters + l, &btdir);
										}
									}
								}
								nl_vector3_t nb_nml = b_nml;
								if(nb_nml.z > -BOOM_ZERO && nb_nml.z < BOOM_ZERO)
								{
									float dp = (float)damage / (float)bt->damage * 1000.0;
									AI_AddForceAction(&characters[l].ai, (float)damage * BOOM_SPEED / (float)bt->damage, characters[l].position[0], characters[l].position[1], characters[l].position[2] + 1, game_time, xr2, yr2, (unsigned int)dp);
								}
								else
								{
									if(nb_nml.z > 0)
										nb_nml.z = -nb_nml.z;
									Algo_GetNormalAngle(&nb_nml, &yr2, &xr2);
									AI_AddForceAction(&characters[l].ai, (float)damage * BOOM_SPEED / (float)bt->damage, characters[l].position[0], characters[l].position[1], characters[l].position[2], game_time, xr2, yr2, 0);
								}
							}
						}
					}
				}
			}
			// 碰撞地形
			else if(r == 2)
			{
				if(list)
				{
					float yr = 0.0;
					float xr = 0.0;
					Algo_GetNormalAngle(&cn, &yr, &xr);
					// 弹孔/爆炸痕迹
					particle p = Particle_MakeParticle(bt->type <= normal_bullet_type ? trace_particle_type : boom_particle_type, fixed_particle_type, cv.x + cn.x, cv.y + cn.y, cv.z + cn.z, bt->x_angle, bt->y_angle, 0.0, 0.0, 0.0, game_time, 300, GL_FALSE);
					List_PushBack(list, &p);
				}
				// boom
				if(bt->type == shell_bullet_type || bt->type == grenade_bullet_type)
				{
					int l;
					for(l = start; l < count; l++)
					{
						/*
						// kill self?
						if(characters[l].index == bt->character)
						continue;
						*/
						// kill partner?
						if(bt->group == characters[l].group && bt->character != characters[l].index)
							continue;
						float dis = 0.0;
						nl_vector3_t b_pos = {0.0, 0.0, 0.0};
						nl_vector3_t b_nml = {0.0, 0.0, 0.0};
						human_body_type body = human_body_total;
						nl_vector3_t boom = Vector3_PlusVector3(&cv, &cn);
						int br = Game_BoomAttack(map_model, &boom, characters + l, &dis, &b_pos, &b_nml, &body);
						if(!br)
							continue;
						int damage = Game_GetBulletBoomDamage(bt, dis);
						if(characters[l].index == bt->character)
							damage /= 2;
						if(damage > 0)
						{
							float yr2 = 0.0;
							float xr2 = 0.0;
							Algo_GetNormalAngle(&b_nml, &yr2, &xr2);
							if(list)
							{
								// 流血血迹
								particle p = Particle_MakeParticle(blood_block_particle_type, parabola_particle_type, b_pos.x + b_nml.x, b_pos.y + b_nml.y, b_pos.z + b_nml.z, xr2, yr2, xr2, yr2, bt->speed * BULLET_PER, game_time, 5000, GL_TRUE);
								List_PushBack(list, &p);
								// 伤口血迹
								p = Particle_MakeParticle(blood_spot_particle_type, fixed_particle_type, b_pos.x + b_nml.x, b_pos.y + b_nml.y, b_pos.z + b_nml.z, xr2, yr2, 0.0, 0.0, 0.0, game_time, 300, GL_FALSE);
								List_PushBack(list, &p);
							}

							if(healths[l] > health_death_type)
							{
								healths[l] = KARIN_MAX(healths[l] - damage * Human_Body_Data[body].damage_factory, health_death_type);
								if(healths[l] == health_death_type)
								{
									Game_CharacterDeath(characters + bt->character, characters + l);
									if(bt->character != l)
										characters[bt->character].score.kill++;
									characters[l].score.death++;
									characters[bt->character].score.kill_character = l;
									characters[l].score.killed_character = bt->character;
									if(list)
									{
										// 死亡血迹
										particle p = Particle_MakeParticle(blood_particle_type, fixed_particle_type, characters[l].position[0], characters[l].position[1], characters[l].position[2] + 1, characters[l].x_angle, characters[l].y_angle, 0.0, 0.0, 0.0, game_time, 6000, GL_FALSE);
										List_PushBack(list, &p);
									}
								}
							}
							nl_vector3_t nb_nml = b_nml;
							if(nb_nml.z > -BOOM_ZERO && nb_nml.z < BOOM_ZERO)
							{
								float dp = (float)damage / (float)bt->damage * 1000.0;
								AI_AddForceAction(&characters[l].ai, (float)damage * BOOM_SPEED / (float)bt->damage, characters[l].position[0], characters[l].position[1], characters[l].position[2] + 1, game_time, xr2, yr2, (unsigned int)dp);
							}
							else
							{
								if(nb_nml.z > 0)
									nb_nml.z = -nb_nml.z;
								Algo_GetNormalAngle(&nb_nml, &yr2, &xr2);
								AI_AddForceAction(&characters[l].ai, (float)damage * BOOM_SPEED / (float)bt->damage, characters[l].position[0], characters[l].position[1], characters[l].position[2], game_time, xr2, yr2, 0);
							}
						}
					}
				}
			}
		} // end for list
	}

	for(j = start; j < count; j++)
	{
		if(characters[j].ai.action == aiaction_dead_type)
			continue;
		characters[j].health = healths[j];
		if(characters[j].health == health_death_type)
		{
			ai_action_type type = characters[j].ai.type;
			AI_ClearAction(&characters[j].ai);
			if(type == ai_player_type)
				characters[j].ai.type = ai_player_type;
			else
				characters[j].ai.type = ai_trigger_type;
			characters[j].ai.action = aiaction_dead_type;
			characters[j].ai.dead_mask = 1;
			characters[j].ai.dead_time = game_time;
		}
	}

	free(healths);
}

void Game_UpdateWeapon(game_character *gamer, long long game_time)
{
	if(!gamer)
		return;
	weapon *wp = Game_CharacterCurrentWeapon(gamer);
	if(!wp)
		return;
	if(wp->type <= short_attack_type)
	{
		if((gamer->ai.action & aiaction_fight_type) == 0)
		{
			if(wp->status == firing_type || wp->status == fired_type)
			{
				double wt = 1000.0 / wp->firing_rate;
				int r = (game_time - wp->time > wt) ? 1 : 0;
				if(r)
				{
					wp->status = ready_type;
					wp->time = game_time;
				}
				else
				{
					double d = game_time - wp->time;
					if(wp->firing_progress != 0.0f)
					{
						wp->firing_progress -= d / (1000.0 / wp->firing_rate) * wp->hit_rate / 10.0;
						if(wp->firing_progress < 0.0f)
							wp->firing_progress = 0.0;
					}
				}
			}
			else if(wp->status == ready_type)
			{
				if(wp->firing_progress != 0.0f)
				{
					double d = game_time - wp->time;
					wp->firing_progress -= d / (1000.0 / wp->firing_rate) * wp->hit_rate;
					if(wp->firing_progress < 0.0f)
						wp->firing_progress = 0.0;
					wp->x_angle = gamer->x_angle;
					wp->y_angle = gamer->y_angle;
				}
			}
		}
		else
		{
			if(wp->status == fired_type)
			{
				double wt = 1000.0 / wp->firing_rate;
				int r = (game_time - wp->time > wt) ? 1 : 0;
				if(r)
				{
					wp->status = firing_type;
					wp->time = game_time;
					if(wp->firing_progress > 0.0f)
					{
						float f = SHORT_ANGLE_MAX_OFFSET / 2.0 * wp->firing_progress;
						float offset = rand_f(-f, f, 100);
						wp->x_angle = Algo_FormatAngle(gamer->x_angle + offset);
						offset = rand_f(-f, f, 100);
						wp->y_angle = Algo_FormatAngle(gamer->y_angle + offset);
					}
					if(wp->firing_progress != 1.0f)
					{
						wp->firing_progress += wp->hit_rate;
						if(wp->firing_progress > 1.0f)
							wp->firing_progress = 1.0;
					}
				}
				else
				{
					double d = game_time - wp->time;
					if(wp->firing_progress != 0.0f)
					{
						wp->firing_progress -= d / (1000.0 / wp->firing_rate) * wp->hit_rate / 10.0;
						if(wp->firing_progress < 0.0f)
							wp->firing_progress = 0.0;
					}
				}
			}
			else if(wp->status == firing_type)
			{
				wp->status = fired_type;
				//gamer->current_weapon.time = game_time;
			}
			else if(wp->status == ready_type)
			{
				wp->status = firing_type;
				wp->time = game_time;
				if(wp->firing_progress > 0.0f)
				{
					float f = SHORT_ANGLE_MAX_OFFSET / 2.0 * wp->firing_progress;
					float offset = rand_f(-f, f, 100);
					wp->x_angle = Algo_FormatAngle(gamer->x_angle + offset);
					offset = rand_f(-f, f, 100);
					wp->y_angle = Algo_FormatAngle(gamer->y_angle + offset);
				}
				if(wp->firing_progress != 1.0f)
				{
					wp->firing_progress += wp->hit_rate;
					if(wp->firing_progress > 1.0f)
						wp->firing_progress = 1.0;
				}
			}
		}
	}

	else
	{
		if((gamer->ai.action & aiaction_attack_type) == 0)
		{
			if(wp->status == firing_type || wp->status == fired_type)
			{
				if(wp->ammo_total_count != -1 && wp->ammo_total_count == 0)
				{
					wp->status = outofammo_type;
					wp->time = game_time;
					Game_PreferWeapon(gamer);
				}
				else if(wp->ammo_count != -1 && (wp->ammo_total_count > 0 || wp->ammo_total_count == -1) && wp->ammo == 0)
				{
					if(Game_ReloadWeapon(wp, game_time))
						gamer->ai.action |= aiaction_reload_type;
				}
				else
				{
					double wt = 1000.0 / wp->firing_rate;
					int r = (game_time - wp->time > wt) ? 1 : 0;
					if(r)
					{
						wp->status = ready_type;
						wp->time = game_time;
					}
					else
					{
						double d = game_time - wp->time;
						if(wp->firing_progress != 0.0f)
						{
							wp->firing_progress -= d / (1000.0 / wp->firing_rate) * wp->hit_rate / 10.0;
							if(wp->firing_progress < 0.0f)
								wp->firing_progress = 0.0;
						}
					}
				}
			}
			else if(wp->status == ready_type)
			{
				if(wp->firing_progress != 0.0f)
				{
					double d = game_time - wp->time;
					wp->firing_progress -= d / (1000.0 / wp->firing_rate) * wp->hit_rate;
					if(wp->firing_progress < 0.0f)
						wp->firing_progress = 0.0;
					wp->x_angle = gamer->x_angle;
					wp->y_angle = gamer->y_angle;
				}
			}
			else if(wp->status == outofammo_type)
			{
				if(wp->firing_progress != 0.0f)
				{
					double d = game_time - wp->time;
					wp->firing_progress -= d / (1000.0 / wp->firing_rate) * wp->hit_rate;
					if(wp->firing_progress < 0.0f)
						wp->firing_progress = 0.0;
					wp->x_angle = gamer->x_angle;
					wp->y_angle = gamer->y_angle;
				}
			}
			else if(wp->status == reload_type)
			{
				double d = game_time - wp->time;
				if(wp->firing_progress != 0.0f)
				{
					wp->firing_progress -= d / (1000.0 / wp->firing_rate) * wp->hit_rate;
					if(wp->firing_progress < 0.0f)
						wp->firing_progress = 0.0;
					wp->x_angle = gamer->x_angle;
					wp->y_angle = gamer->y_angle;
				}
				if(d >= (double)wp->reload_time * 1000.0)
				{
					wp->status = ready_type;
					wp->time = game_time;
					if(gamer->ai.action & aiaction_reload_type)
						gamer->ai.action ^= aiaction_reload_type;
					if(wp->ammo_total_count > 0)
						wp->ammo = KARIN_MIN(wp->ammo_count, wp->ammo_total_count);
					else if(wp->ammo_total_count == -1)
						wp->ammo = wp->ammo_count;
				}
			}
		}
		else
		{
			if(wp->status == fired_type)
			{
				if(wp->ammo > 0 || wp->ammo_count == -1)
				{
					double wt = 1000.0 / wp->firing_rate;
					int r = (game_time - wp->time > wt) ? 1 : 0;
					if(r)
					{
						if(wp->ammo_count != -1)
							wp->ammo--;
						if(wp->ammo_total_count != -1)
							wp->ammo_total_count--;
						wp->status = firing_type;
						wp->time = game_time;
						if(wp->firing_progress > 0.0f)
						{
							float f = LONG_ANGLE_MAX_OFFSET / 2.0 * wp->firing_progress;
							float offset = rand_f(-f, f, 100);
							wp->x_angle = Algo_FormatAngle(gamer->x_angle + offset);
							offset = rand_f(-f, f, 100);
							wp->y_angle = Algo_FormatAngle(gamer->y_angle + offset);
						}
						if(wp->firing_progress != 1.0f)
						{
							wp->firing_progress += wp->hit_rate;
							if(wp->firing_progress > 1.0f)
								wp->firing_progress = 1.0;
						}
					}
					else
					{
						double d = game_time - wp->time;
						if(wp->firing_progress != 0.0f)
						{
							wp->firing_progress -= d / (1000.0 / wp->firing_rate) * wp->hit_rate / 10.0;
							if(wp->firing_progress < 0.0f)
								wp->firing_progress = 0.0;
						}
					}
				}
				else if(wp->ammo_total_count != -1 && wp->ammo_total_count == 0)
				{
					wp->status = outofammo_type;
					wp->time = game_time;
					Game_PreferWeapon(gamer);
				}
				else if(wp->ammo_count != -1 && (wp->ammo_total_count > 0 || wp->ammo_total_count == -1) && wp->ammo == 0)
				{
					if(Game_ReloadWeapon(wp, game_time))
						gamer->ai.action |= aiaction_reload_type;
				}
			}
			else if(wp->status == firing_type)
			{
				wp->status = fired_type;
				//wp->time = game_time;
			}
			else if(wp->status == reload_type)
			{
				double d = game_time - wp->time;
				if(wp->firing_progress != 0.0f)
				{
					wp->firing_progress -= d / (1000.0 / wp->firing_rate) * wp->hit_rate;
					if(wp->firing_progress < 0.0f)
						wp->firing_progress = 0.0;
					wp->x_angle = gamer->x_angle;
					wp->y_angle = gamer->y_angle;
				}
				if(d >= (double)wp->reload_time * 1000.0)
				{
					if(wp->ammo_total_count > 0)
						wp->ammo = KARIN_MIN(wp->ammo_count, wp->ammo_total_count);
					else if(wp->ammo_total_count == -1)
						wp->ammo = wp->ammo_count;
					wp->status = ready_type;
					wp->time = game_time;
					if(gamer->ai.action & aiaction_reload_type)
						gamer->ai.action ^= aiaction_reload_type;
				}
			}
			else if(wp->status == ready_type)
			{
				wp->status = firing_type;
				wp->time = game_time;
				if(wp->firing_progress > 0.0f)
				{
					float f = LONG_ANGLE_MAX_OFFSET / 2.0 * wp->firing_progress;
					float offset = rand_f(-f, f, 100);
					wp->x_angle = Algo_FormatAngle(gamer->x_angle + offset);
					offset = rand_f(-f, f, 100);
					wp->y_angle = Algo_FormatAngle(gamer->y_angle + offset);
				}
				if(wp->firing_progress != 1.0f)
				{
					wp->firing_progress += wp->hit_rate;
					if(wp->firing_progress > 1.0f)
						wp->firing_progress = 1.0;
				}
				if(wp->ammo_count != -1)
					wp->ammo--;
				if(wp->ammo_total_count != -1)
					wp->ammo_total_count--;
			}
			else if(wp->status == outofammo_type)
			{
				if(wp->firing_progress != 0.0f)
				{
					double d = game_time - wp->time;
					wp->firing_progress -= d / (1000.0 / wp->firing_rate) * wp->hit_rate;
					if(wp->firing_progress < 0.0f)
						wp->firing_progress = 0.0;
					wp->x_angle = gamer->x_angle;
					wp->y_angle = gamer->y_angle;
				}
			}
		}
	}
}

int Game_RandStartPosition(const GL_NETLizard_3D_Model *model, game_character *gamer, int max)
{
	if(!model || !gamer)
		return 0;

	int i = 0;
	while(1)
	{
		if(max > 0 && i >= max)
			break;
		int s = rand() % model->count;
		GL_NETLizard_3D_Mesh *mesh = model->meshes + s;
		float x = rand_f(mesh->ortho[3] + gamer->width * 2, mesh->ortho[0] - gamer->width * 2, 1);
		float y = rand_f(mesh->ortho[4] + gamer->width * 2, mesh->ortho[1] - gamer->width * 2, 1);
		float z = rand_f(mesh->ortho[5] + 1, mesh->ortho[2] - 1, 1);
		nl_vector3_t pos = {x, y, z};
		nl_vector3_t rv = pos;
		int ci = -1;
		int r = Algo_ComputePositionInNETLizard3DMap(model, &pos, &pos, gamer->width, gamer->height, &rv, &s, &ci);
		if(r)
		{
			gamer->position[0] = rv.x;
			gamer->position[1] = rv.y;
			gamer->position[2] = rv.z - gamer->height;
			gamer->scene = s;
			gamer->collision_item = ci;
			gamer->scene_collision_result = r;
			return 1;
		}
		i++;
	}
	return 0;
}

int Game_ShotCharacter(const GL_NETLizard_3D_Model *model, game_character *gamer, game_character *characters, int start, int count, human_body_type *type, nl_vector3_t *c, nl_vector3_t *n)
{
	if(!model || !gamer || !characters)
		return -1;

	if(gamer->health == health_death_type)
		return -1;
	const weapon *wp = Game_CharacterCurrentWeapon(gamer);
	if(!wp)
		return -1;
	if(gamer->ai.type != ai_trigger_type && gamer->ai.type != ai_player_type)
		return -1;
	if((gamer->ai.action & aiaction_attack_type) == 0 && (gamer->ai.action & aiaction_fight_type) == 0)
		return -1;
	if(wp->status != firing_type)
		return -1;
	if(gamer->ai.type == ai_trigger_type &&
			gamer->ai.action & aiaction_attack_type &&
			(gamer->ai.action & aiaction_movexy_type) == 0)
		gamer->ai.attack_count++;
	const nl_vector3_t me = {
		wp->position[0],
		wp->position[1],
		wp->position[2]
	};
	human_body_type t = human_body_total;
	int index = -1;
	int res = 0;
	float distance = 0.0;
	nl_vector3_t d = Algo_ComputeDirection(wp->y_angle, wp->x_angle);
	nl_vector3_t glc_pos = {0.0, 0.0, 0.0};
	nl_vector3_t glc_nml = {0.0, 0.0, 0.0};
	line_t line = {me, d};
	int i;
	for(i = start; i < count; i++)
	{
		game_character *b = characters + i;
		if(gamer == b)
			continue;
		if(b->health == health_death_type)
			continue;
		if(gamer->group == b->group) // kill partner ?
			continue;
		/*
			 if(!Game_CharacterCanViewCharacter(model, gamer, b))
			 continue;
			 */
		nl_vector3_t tg = {
			b->position[0],
			b->position[1],
			b->position[2]
		};
		if(gamer->ai.action & aiaction_fight_type)
		{
			nl_vector3_t dis = Vector3_SubtractVector3(&tg, &me);
			if(Vector3_Mag(&dis) > (gamer->width + b->width + CHARACTER_MIN_SPACING + wp->shot_range) / cos(ator(wp->x_angle)))
				continue;
		}
		float lamda = 0.0;
		vector3_t c_pos = {0.0, 0.0, 0.0};
		vector3_t c_nml = {0.0, 0.0, 0.0};
		cylinder_t cylinder = {
			tg, 
			{0.0, 0.0, 1.0},
			b->width
		};
		int r = Math3D_LineToCylinderCollision(&line, &cylinder, &lamda, &c_nml, &c_pos);
		if(r && (c_pos.z >= b->position[2] && c_pos.z <= b->position[2] + b->full_height))
		{
			float pos_z = c_pos.z - b->position[2];
			float per = pos_z / b->full_height;
			human_body_type tp = human_body_total;
			int j;
			for(j = human_head_type; j < human_body_total; j++)
			{
				if(per >= Human_Body_Data[j].bottom_per && per <= Human_Body_Data[j].top_per)
				{
					tp = j;
					break;
				}
			}
			if(res == 0)
			{
				distance = lamda;
				index = i;
				t = tp;
				res = 1;
				glc_pos = c_pos;
				glc_nml = c_nml;
			}
			else
			{
				if(lamda < distance)
				{
					index = i;
					t = tp;
					distance = lamda;
					glc_pos = c_pos;
					glc_nml = c_nml;
				}
			}
		}
	}
	if(res)
	{
		unsigned int k;
		for(k = 0; k < model->item_count; k++)
		{
			const GL_NETLizard_3D_Item_Mesh *im = model->item_meshes + k;
			if(im->item_type & Item_Weapon_Type || im->item_type & Item_Tiny_Type)
			{
				continue;
			}
			aabb_t aabb = {
				{im->item_mesh.ortho[3] + im->pos[0], im->item_mesh.ortho[4] + im->pos[1], im->item_mesh.ortho[5] + im->pos[2]},
				{im->item_mesh.ortho[0] + im->pos[0], im->item_mesh.ortho[1] + im->pos[1], im->item_mesh.ortho[2] + im->pos[2]}
			};
			if(im->item_mesh.plane_count > 0)
			{
				const GL_NETLizard_3D_Plane *planes = im->item_mesh.plane;
				unsigned int j;
				for(j = 0; j < im->item_mesh.plane_count; j++)
				{
					plane_t plane = {
						{planes[j].position[0] + im->pos[0], planes[j].position[1] + im->pos[1], planes[j].position[2] + im->pos[2]},
						{planes[j].normal[0], planes[j].normal[1], planes[j].normal[2]}
					};
					float lamda = 0.0;
					nl_vector3_t point = {0.0, 0.0, 0.0};
					int r;
					r = Math3D_LineToPlaneIntersect(&line, &plane, &point);
					if(r && Math3D_PointInAABB(&point, &aabb))
					{
						r = Math3D_LineToPlaneCollision(&line, &plane, &lamda, NULL);
						if(lamda < distance)
						{
							res = 0;
							break;
						}
					}
				}
			}
		}
	}
	if(res)
	{
		if(c)
			*c = glc_pos;
		if(n)
			*n = glc_nml;
		if(type)
			*type = t;
		return index;
	}
	else
	{
		if(Game_GetRayPointCoord(model, gamer, GL_TRUE, NULL, c, n, NULL))
			index = -2;
		else
			index = -3;
		return index;
	}
}

int Algo_RayCharacterCollisionTesting(const game_character *gamer, const game_character *characters, int start, int count, GLboolean dy, int *scene, float *dis, nl_vector3_t *pos)
{
	if(!characters || !gamer)
		return 0;
	const weapon *wp = Game_CharacterCurrentWeapon((game_character *)gamer);
	nl_vector3_t me = {0.0, 0.0, 0.0};
	if(wp)
	{
		me.x = wp->position[0];
		me.y = wp->position[1];
		me.z = wp->position[2];
	}
	else
	{
		me.x = gamer->position[0];
		me.y = gamer->position[1];
		me.z = gamer->position[2] + gamer->height;
	}
	nl_vector3_t d;
	if(wp && dy)
		d = Algo_ComputeDirection(wp->y_angle, wp->x_angle);
	else
		d = Algo_ComputeDirection(gamer->y_angle, gamer->x_angle);
	line_t line = {me, d};
	int state = 0;
	int s = -1;
	float distance = 0.0;
	nl_vector3_t point = {0.0, 0.0, 0.0};
	int j;
	for(j = start; j < count; j++)
	{
		const game_character *b = characters + j;
		if(gamer == b)
			continue;
		if(b->health == health_death_type)
			continue;
		/*
			 if(!Game_CharacterCanViewCharacter(model, a, b))
			 continue;
			 */
		nl_vector3_t tg = {
			b->position[0],
			b->position[1],
			b->position[2] + b->height
		};
		float lamda = 0.0;
		vector3_t c_pos = {0.0, 0.0, 0.0};
		cylinder_t cylinder = {
			tg, 
			{0.0, 0.0, 1.0},
			b->width
		};
		int r = Math3D_LineToCylinderCollision(&line, &cylinder, &lamda, NULL, &c_pos);
		if(r && (c_pos.z >= b->position[2] && c_pos.z <= b->position[2] + b->full_height))
		{
			if(state == 0)
			{
				distance = lamda;
				state = 1;
				point = c_pos;
				s = b->scene;
			}
			else
			{
				if(lamda < distance)
				{
					distance = lamda;
					point = c_pos;
					s = b->scene;
				}
			}
		}
	}
	if(state)
	{
		if(pos)
		{
			pos->x = point.x;
			pos->y = point.y;
			pos->z = point.z;
		}
		if(dis)
			*dis = distance;
		if(scene)
			*scene = s;
		return 1;
	}
	return 0;
}

int Algo_CharacterCollisionTesting(const GL_NETLizard_3D_Model *map_model, const game_character *gamer, const nl_vector3_t *new_v, const game_character *characters, int start, int count, int *character_index, nl_vector3_t *rv)
{
	if(!map_model || !characters || !gamer || !new_v)
		return 0;
	const GL_NETLizard_3D_Mesh *mesh = map_model->meshes + gamer->scene;
	int *scenes = NEW_II(int, map_model->count);
	scenes[0] = gamer->scene + 1;
	int cur = 1;
	if(map_model->bsp_data)
	{
		int i;
		for(i = 0; i < (int)mesh->bsp_count; i++)
		{
			GLint prev = map_model->bsp_data[mesh->bsp[i]].prev_scene;
			GLint next = map_model->bsp_data[mesh->bsp[i]].next_scene;
			int j;
			for(j = 0; j < cur; j++)
			{
				if(scenes[j] == prev + 1)
					break;
			}
			if(j == cur)
			{
				scenes[cur] = prev + 1;
				cur++;
			}
			for(j = 0; j < cur; j++)
			{
				if(scenes[j] == next + 1)
					break;
			}
			if(j == cur)
			{
				scenes[cur] = next + 1;
				cur++;
			}
		}
	}

	nl_vector3_t me = {
		gamer->position[0],
		gamer->position[1],
		gamer->position[2] + gamer->height
	};
	nl_vector3_t direction = Vector3_SubtractVector3(new_v, &me);
	me.z -= gamer->height;
	Vector3_Normalize(&direction);
	line_t line = {me, direction};
	int res = 0;
	int index = -1;
	float distance = 0.0;
	nl_vector3_t point = {0.0, 0.0, 0.0};
	int j;
	for(j = start; j < count; j++)
	{
		const game_character *b = characters + j;
		if(gamer == b)
			continue;
		int find = 0;
		int k;
		for(k = 0; k < cur; k++)
		{
			if(b->scene == scenes[k] - 1)
			{
				find = 1;
				break;
			}
			if(scenes[k] == 0)
				break;
		}
		if(find == 0)
			continue;
		if(b->health == health_death_type)
			continue;
		/*
			 if(!Game_CharacterCanViewCharacter(model, a, b))
			 continue;
			 */
		nl_vector3_t tg = {
			b->position[0],
			b->position[1],
			b->position[2]
		};
		float lamda = 0.0;
		vector3_t c_pos = {0.0, 0.0, 0.0};
		float radius = gamer->width + b->width;
		cylinder_t cylinder = {
			tg, 
			{0.0, 0.0, 1.0},
			radius
		};
		int r = Math3D_LineToCylinderCollision(&line, &cylinder, &lamda, NULL, &c_pos);
		if(r && (c_pos.z >= b->position[2] && c_pos.z <= b->position[2] + b->full_height))
		{
			if(lamda < radius)
			{
				if(res == 0)
				{
					distance = lamda;
					res = 1;
					index = j;
					point = c_pos;
				}
				else
				{
					if(lamda < distance)
					{
						distance = lamda;
						index = j;
						point = c_pos;
					}
				}
			}
		}
	}
	free(scenes);
	if(res)
	{
		if(character_index)
			*character_index = index;
		if(rv)
		{
			nl_vector3_t c = {
				characters[index].position[0],
				characters[index].position[1],
				characters[index].position[2] + characters[index].height
			};
			nl_vector3_t dir = Vector3_SubtractVector3(&point, &c);
			Vector3_Normalize(&dir);
			dir = Vector3_Scale(&dir, CHARACTER_MIN_SPACING);
			nl_vector3_t p = Vector3_PlusVector3(&point, &dir);
			rv->x = p.x;
			rv->y = p.y;
			rv->z = p.z;
		}
		return 1;
	}
	return 0;
}

int Game_WeaponShot(game_character *gamer, list_template *particle_list, list_template *bullets)
{
	if(!gamer || !bullets)
		return 0;

	if(gamer->health == health_death_type)
		return 0;
	const weapon *wp = Game_CharacterCurrentWeapon(gamer);
	if(!wp)
		return 0;
	if(gamer->ai.type != ai_trigger_type && gamer->ai.type != ai_player_type)
		return 0;
	if((gamer->ai.action & aiaction_attack_type) == 0 && (gamer->ai.action & aiaction_fight_type) == 0)
		return 0;
	if(wp->status != firing_type)
		return 0;

	if(gamer->ai.type == ai_player_type)
	{
		unsigned int sc = 0;
		bullet *b = Game_WeaponFire(NULL, wp, gamer->width, gamer->index, gamer->group, &sc);
		if(b)
		{
			unsigned int k;
			for(k = 0; k < sc; k++)
			{
				List_PushBack(bullets, b + k);
			}
			if(particle_list && b->type != no_bullet_type)
			{
				particle p = Particle_MakeParticle(gunfire_particle_type, fixed_particle_type, b->start_pos[0], b->start_pos[1], b->start_pos[2], b->x_angle, b->y_angle, b->x_dir, b->y_dir, 0.0, wp->time, 1000, GL_FALSE);
				p.finished = GL_TRUE;
				List_PushBack(particle_list, &p);
			}
			free(b);
			return(sc > 0 ? 1 : 0);
		}
	}
	else
	{
		if(gamer->ai.type == ai_trigger_type &&
				gamer->ai.action & aiaction_attack_type &&
				(gamer->ai.action & aiaction_movexy_type) == 0)
			gamer->ai.attack_count++;
		nl_vector3_t vg = {
			gamer->position[0],
			gamer->position[1],
			gamer->position[2] + gamer->height
		};
		nl_vector3_t point = {
			gamer->ai.position_target[0],
			gamer->ai.position_target[1],
			gamer->ai.position_target[2]
		};
		nl_vector3_t va = Vector3_SubtractVector3(&vg, &point);
		float xl = va.x;
		float yl = va.y;
		float f = Algo_FormatAngle(rtoa(atan2(yl, xl)) - 90.0);
		float offset = f - Algo_FormatAngle(gamer->y_angle);
		if(abs(offset) <= 0)
		{
			unsigned int sc = 0;
			bullet *b = Game_WeaponFire(NULL, wp, gamer->width, gamer->index, gamer->group, &sc);
			if(b)
			{
				unsigned int k;
				for(k = 0; k < sc; k++)
				{
					List_PushBack(bullets, b + k);
				}
				if(particle_list && b->type != no_bullet_type && b->type != grenade_bullet_type)
				{
					particle p = Particle_MakeParticle(gunfire_particle_type, fixed_particle_type, b->start_pos[0], b->start_pos[1], b->start_pos[2], b->x_angle, b->y_angle, b->x_dir, b->y_dir, 0.0, wp->time, 1000, GL_FALSE);
					p.finished = GL_TRUE;
					List_PushBack(particle_list, &p);
				}
				free(b);
				return(sc > 0 ? 1 : 0);
			}
		}
	}
	return 0;
}

// 子弹与角色碰撞
// 1 碰撞 0 未碰撞
// 返回 击中角色索引，距离，击中身体部位， 击中点坐标 击中点反射法线 
int Game_BulletCharacterCollisionTesting(bullet *bt, game_character *characters, int start, int count, int *c_index, float *c_dis, human_body_type *type, nl_vector3_t *c, nl_vector3_t *n)
{
	if(!bt || !characters)
		return 0;

	const nl_vector3_t me = {
		bt->last_pos[0],
		bt->last_pos[1],
		bt->last_pos[2]
	};
	const nl_vector3_t new_me = {
		bt->position[0],
		bt->position[1],
		bt->position[2]
	};
	nl_vector3_t bullet_sport_v = Vector3_SubtractVector3(&new_me, &me);
	const float bullet_sport_dis = Vector3_Mag(&bullet_sport_v);

	human_body_type t = human_body_total;
	int index = -1;
	int res = 0;
	float distance = 0.0;
	//nl_vector3_t d = Algo_ComputeDirection(bt->y_angle, bt->x_angle);
	Vector3_Normalize(&bullet_sport_v);
	nl_vector3_t glc_pos = {0.0, 0.0, 0.0};
	nl_vector3_t glc_nml = {0.0, 0.0, 0.0};
	line_t line = {me, bullet_sport_v};
	int i;
	for(i = start; i < count; i++)
	{
		game_character *b = characters + i;
		if(bt->character == b->index)
			continue;
		if(b->health == health_death_type)
			continue;
		if(bt->group == b->group) // kill partner ?
			continue;
		nl_vector3_t tg = {
			b->position[0],
			b->position[1],
			b->position[2]
		};
		/*
			 if(bt->type == no_bullet_type)
			 {
			 nl_vector3_t dis = Vector3_SubtractVector3(&tg, &new_me);
			 if(Vector3_Mag(&dis) > (b->width + CHARACTER_MIN_SPACING + bt->range) / cos(ator(bt->x_angle)))
			 continue;
			 }
			 */
		float lamda = 0.0;
		vector3_t c_pos = {0.0, 0.0, 0.0};
		vector3_t c_nml = {0.0, 0.0, 0.0};
		cylinder_t cylinder = {
			tg, 
			{0.0, 0.0, 1.0},
			b->width
		};
		int r = Math3D_LineToCylinderCollision(&line, &cylinder, &lamda, &c_nml, &c_pos);
		if(r && (c_pos.z >= b->position[2] && c_pos.z <= b->position[2] + b->full_height) && lamda <= bullet_sport_dis)
		{
			float pos_z = c_pos.z - b->position[2];
			float per = pos_z / b->full_height;
			human_body_type tp = human_body_total;
			int j;
			for(j = human_head_type; j < human_body_total; j++)
			{
				if(per >= Human_Body_Data[j].bottom_per && per <= Human_Body_Data[j].top_per)
				{
					tp = j;
					break;
				}
			}
			if(res == 0)
			{
				distance = lamda;
				index = i;
				t = tp;
				res = 1;
				glc_pos = c_pos;
				glc_nml = c_nml;
			}
			else
			{
				if(lamda < distance)
				{
					index = i;
					t = tp;
					distance = lamda;
					glc_pos = c_pos;
					glc_nml = c_nml;
				}
			}
		}
	}
	if(res)
	{
		if(c)
			*c = glc_pos;
		if(n)
			*n = glc_nml;
		if(type)
			*type = t;
		if(c_index)
			*c_index = index;
		if(c_dis)
			*c_dis = distance;
		return 1;
	}
	return 0;
}

// 子弹与地形碰撞
// 1 碰撞 0 未碰撞
// 返回 距离, 场景索引，碰撞物品索引，击中点坐标 击中点反射法线 
int Game_BulletMapCollisionTesting(const GL_NETLizard_3D_Model *model, bullet *bt, float *c_dis, int *c_scene, int *c_item, nl_vector3_t *c, nl_vector3_t *n)
{
	if(!model || !bt)
		return 0;

	const nl_vector3_t me = {
		bt->last_pos[0],
		bt->last_pos[1],
		bt->last_pos[2]
	};
	const nl_vector3_t new_me = {
		bt->position[0],
		bt->position[1],
		bt->position[2]
	};
	nl_vector3_t bullet_sport_v = Vector3_SubtractVector3(&new_me, &me);
	const float bullet_sport_dis = Vector3_Mag(&bullet_sport_v);

	Vector3_Normalize(&bullet_sport_v);
	//nl_vector3_t d = Algo_ComputeDirection(bt->y_dir, bt->x_dir);
	nl_vector3_t glc_pos = {0.0, 0.0, 0.0};
	nl_vector3_t glc_nml = {0.0, 0.0, 0.0};
	int scene = -1;
	float distance = 0.0;
	int item = -1;
	int r = Algo_RayCollisionTestingInNETLizard3DMap(model, &me, &bullet_sport_v, 0, &scene, &distance, &glc_pos, &glc_nml);
	if(r && distance <= bullet_sport_dis)
	{
		if(c)
			*c = glc_pos;
		if(n)
			*n = glc_nml;
		if(c_item)
			*c_item = item;
		if(c_dis)
			*c_dis = distance;
		if(c_scene)
			*c_scene = scene;
		return 1;
	}
	return 0;
}

int Game_BoomAttack(const GL_NETLizard_3D_Model *model, const nl_vector3_t *boom_pos, const game_character *gamer, float *dis, nl_vector3_t *cv, nl_vector3_t *cn, human_body_type *type)
{
	if(!model || !boom_pos || !gamer)
		return 0;
	int res = 0;
	nl_vector3_t v2 = {
		gamer->position[0],
		gamer->position[1],
		gamer->position[2] + gamer->height
	};
	res = Algo_PointCanViewPointInNETLizard3DMap(model, boom_pos, &v2, NULL);

	if(res == 0)
		return 0;

	float z = boom_pos->z;
	human_body_type tp = human_body_total;
	if(boom_pos->z > gamer->position[2] + gamer->full_height)
	{
		tp = human_head_type;
		z = gamer->position[2] + gamer->full_height;
	}
	else if(boom_pos->z < gamer->position[2])
	{
		tp = human_foot_type;
		z = gamer->position[2];
	}
	else
	{
		float pos_z = boom_pos->z - gamer->position[2];
		float per = pos_z / gamer->full_height;
		int j;
		for(j = human_head_type; j < human_body_total; j++)
		{
			if(per >= Human_Body_Data[j].bottom_per && per <= Human_Body_Data[j].top_per)
			{
				tp = j;
				break;
			}
		}
	}
	float lamda = 0.0;
	vector3_t c_pos = {0.0, 0.0, 0.0};
	vector3_t c_nml = {0.0, 0.0, 0.0};
	res = 0;

	nl_vector3_t pos = {gamer->position[0], gamer->position[1], z};
	nl_vector3_t wpos = {gamer->position[0], gamer->position[1], gamer->position[2] + gamer->height};
	nl_vector3_t dir = Vector3_SubtractVector3(&wpos, boom_pos);
	Vector3_Normalize(&dir);
	if(dir.z == -1)
	{
		c_nml.z = 1;
		c_pos.x = gamer->position[0];
		c_pos.y = gamer->position[1];
		c_pos.z = KARIN_MAX(gamer->position[2] + gamer->full_height, 0);
		lamda = boom_pos->z - (gamer->position[2] + gamer->full_height);
		res = 1;
	}
	else if(dir.z == 1 || Vector3_EqualsVector3(&wpos, boom_pos))
	{
		c_nml.z = -1;
		c_pos.x = gamer->position[0];
		c_pos.y = gamer->position[1];
		c_pos.z = gamer->position[2];
		lamda = KARIN_MAX(gamer->position[2] - boom_pos->z, 0);
		res = 1;
	}
	else
	{
		line_t line = {*boom_pos, dir};
		cylinder_t cylinder = {
			pos, 
			{0.0, 0.0, 1.0},
			gamer->width
		};
		int r = Math3D_LineToCylinderCollision(&line, &cylinder, &lamda, NULL, &c_pos);
		if(r)
		{
			if(c_pos.z > gamer->position[2] + gamer->full_height)
			{
				c_pos.z = gamer->position[2] + gamer->full_height;
				nl_vector3_t v = Vector3_SubtractVector3(&c_pos, boom_pos);
				lamda = Vector3_Mag(&v);
			}
			else if(c_pos.z < gamer->position[2])
			{
				c_pos.z = gamer->position[2];
				nl_vector3_t v = Vector3_SubtractVector3(&c_pos, boom_pos);
				lamda = Vector3_Mag(&v);
			}
			c_nml = dir;
			Vector3_Inverse(&c_nml);
			res = 1;
		}
	}
	if(res)
	{
		if(cv)
			*cv = c_pos;
		if(cn)
			*cn = c_nml;
		if(dis)
			*dis = lamda;
		if(type)
			*type = tp;
		return 1;
	}
	return 0;
}

void Game_ComputeCharacterAndCharacterAngle(const game_character *a, const game_character *b, float *y_angle, float *x_angle)
{
	if(!a || !b || (!x_angle && !y_angle))
		return;
	nl_vector3_t v1 = {a->position[0], a->position[1], a->position[2] + a->height};
	nl_vector3_t v2 = {b->position[0], b->position[1], b->position[2] + b->height};
	nl_vector3_t v = Vector3_SubtractVector3(&v1, &v2);
	float yr = 0.0;
	float xr = 0.0;
	Algo_GetNormalAngle(&v, &yr, &xr);
	if(x_angle)
		*x_angle = xr;
	if(y_angle)
		*y_angle = yr;
}

void Game_CharacterDeath(game_character *killer, game_character *death)
{
	if(!killer || !death)
		return;
	if(killer == death)
		return;
	float xr = 0.0;
	float yr = 0.0;
	Game_ComputeCharacterAndCharacterAngle(death, killer, &yr, &xr);
	death->x_angle = xr;
	death->y_angle = yr;
	weapon *wp = Game_CharacterCurrentWeapon(death);
	if(wp)
	{
		wp->x_angle = death->x_angle;
		wp->y_angle = death->y_angle;
	}
}

int Game_MakeScriptAI(const GL_NETLizard_3D_Model *model, game_character *gamer, long long time)
{
	if(!model || !gamer)
		return 0;
	if(gamer->ai.type != ai_script_type)
		return 0;
	if(gamer->ai.path_mask)
		return 0;
	if(model->count <= 1)
		return 0;
	GLint count = 0;
	GLint end;
	do
	{
		end = rand() % model->count;
		if(end != gamer->scene)
			break;
	}while(1);
	GLuint *bsps = Algo_GetMapPathSceneAndBSP(model, gamer->scene, end, &count);
	if(!bsps)
		return 0;
	int len = (count - 1) / 2;
	GLfloat *path = NEW_II(GLfloat, len * 4);
	int i;
	for(i = 0; i < len; i++)
	{
		GLfloat x = 0.0;
		GLfloat y = 0.0;
		GLfloat z = 0.0;
		int j;
		for(j = 0; j < 4; j++)
		{
			x += model->bsp_data[bsps[i * 2 + 1]].plane[j][0];
			y += model->bsp_data[bsps[i * 2 + 1]].plane[j][1];
			z += model->bsp_data[bsps[i * 2 + 1]].plane[j][2];
		}
		x /= 4;
		y /= 4;
		z /= 4;
		path[i * 4] = x;
		path[i * 4 + 1] = y;
		path[i * 4 + 2] = z;
		path[i * 4 + 3] = bsps[i * 2 + 2];
	}
	gamer->ai.path_mask = 1;
	gamer->ai.path = path;
	gamer->ai.path_count = len;
	gamer->ai.current_path = 0;
	gamer->ai.time = time;
	gamer->ai.action |= aiaction_path_type;
	gamer->ai.next = 1;
	/*
		 for(i = 0; i < len; i++)
		 {
		 printf("%d %f\n", i, path[i * 4 + 3] );
		 }
		 printfi(gamer->scene);
		 printfi(end);
		 printfi(gamer->ai.path_count);
		 */
	free(bsps);
	return 1;
}

void Game_HandleScriptAI(const GL_NETLizard_3D_Model *map_model, game_character *gamer, long long time)
{
	if(!map_model || !gamer)
		return;
	if(gamer->ai.type != ai_script_type)// 脚本操作AI更新
		return;
	if(gamer->ai.path_mask == 0)
	{
		if(!Game_MakeScriptAI(map_model, gamer, time))
			AI_MakeComputeAction(&gamer->ai, 1, 0);
		return;
	}

	if(gamer->ai.current_path >= gamer->ai.path_count)
		return;

	double per = (double)(time - gamer->ai.time) / 1000.0;
	float turn_unit = gamer->turn_unit * per;
	float move_unit = gamer->move_unit * per;
	nl_vector3_t ov = {gamer->position[0], gamer->position[1], gamer->position[2] + gamer->height};
	nl_vector3_t rv = ov;

	// 重新计算是否需要旋转
	float oxr = gamer->x_angle;
	float oyr = gamer->y_angle;
	float rxr = 0.0;
	float ryr = 0.0;
	position_type p = center_position_type;
	orientation_type o = center_orientation_type;
	nl_vector3_t vg = {
		gamer->position[0],
		gamer->position[1],
		gamer->position[2]
	};
	nl_vector3_t point = {
		gamer->ai.path[gamer->ai.current_path * 4],
		gamer->ai.path[gamer->ai.current_path * 4 + 1],
		gamer->ai.path[gamer->ai.current_path * 4 + 2]
	};
	nl_vector3_t va = Vector3_SubtractVector3(&vg, &point);
	float xl = va.x;
	float yl = va.y;
	float f = Algo_FormatAngle(rtoa(atan2(yl, xl)) - 90.0);
	float offset = f - Algo_FormatAngle(gamer->y_angle);
	gamer->ai.y_angle_target = f;

	if(gamer->ai.next)
	{
		if(gamer->ai.rotation_mask == 0)
		{
			// TODO 选取最近角度选择向左或右旋转
			if(offset > 0 && offset <= 180.0f)
				gamer->ai.action |= aiaction_turnleft_type;
			else
				gamer->ai.action |= aiaction_turnright_type;
			gamer->ai.rotation_mask = 1;
			gamer->ai.y_angle_target = f;
			gamer->ai.angle_range = 0.0;
			gamer->ai.y_angle_progress = gamer->y_angle;
		}
		if(gamer->ai.goto_mask == 0)
		{
			gamer->ai.goto_mask = 1;
			gamer->ai.action |= aiaction_moveforward_type;
			gamer->ai.position_progress[0] = gamer->position[0];
			gamer->ai.position_progress[1] = gamer->position[1];
			gamer->ai.position_progress[2] = gamer->position[2];
			gamer->ai.position_range = gamer->width;
		}
		gamer->ai.next = 0;
	}

	if(abs(offset) <= turn_unit)
	{
		gamer->y_angle = gamer->ai.y_angle_target;
		gamer->ai.y_angle_progress = gamer->ai.y_angle_target;
		oyr = gamer->y_angle;
	}
	else
	{
		if(gamer->ai.action & aiaction_turnleft_type)
			o |= left_orientation_type;
		else if(gamer->ai.action & aiaction_turnright_type)
			o |= right_orientation_type;
	}

	// 前进
	nl_vector2_t vp = {
		gamer->ai.position_progress[0],
		gamer->ai.position_progress[1]
	};
	nl_vector2_t vt = {
		gamer->ai.path[gamer->ai.current_path * 4],
		gamer->ai.path[gamer->ai.current_path * 4 + 1],
	};
	nl_vector2_t v2 = Vector2_SubtractVector2(&vt, &vp);
	float dis = Vector2_Mag(&v2);
	// 位置距离目标位置小于计算宽度 停止动作进度
	if(abs(dis) <= gamer->ai.position_range)
	{
		gamer->position[0] = gamer->ai.path[gamer->ai.current_path * 4];
		gamer->position[1] = gamer->ai.path[gamer->ai.current_path * 4 + 1];
	}
	else
	{
		if(gamer->ai.action & aiaction_moveforward_type)
			p |= forward_position_type;
		else if(gamer->ai.action & aiaction_movebackward_type)
			p |= backward_position_type;
		if(gamer->ai.action & aiaction_moveleft_type)
			p |= left_position_type;
		else if(gamer->ai.action & aiaction_moveright_type)
			p |= right_position_type;
	}

	// 计算新位置坐标 角度
	Algo_TransformPositionAndAngle(p, &ov, move_unit, &rv, o, oxr, oyr, turn_unit, &rxr, &ryr, 0);

	if(o != center_orientation_type)
	{
		gamer->y_angle = ryr;
		gamer->ai.y_angle_progress = ryr;
	}
	// 碰撞测试
	// 碰撞则停止，更新AI为随机计算，状态为空闲
	// 无碰撞则更新进度
	if(gamer->z_moving.state != no_z_type)
	{
		double delta = (double)(time - gamer->z_moving.start_time) / 1000.0;
		rv.z += -Physics_GetFalldownDistance(gamer->z_moving.jump_speed, GAME_G, delta);
		gamer->z_moving.speed = Physics_GetJumpSpeed(gamer->z_moving.jump_speed, GAME_G, delta);
	}
	nl_vector3_t v = ov;
	nl_vector3_t cv = {0.0, 0.0, 0.0};
	if(Algo_CharacterCollisionTesting(map_model, gamer, &rv, characters, 0, character_count, NULL, &cv))
	{
		rv.x = cv.x;
		rv.y = cv.y;
	}
	Algo_ComputeCharacterPositionInNETLizard3DMap(map_model, gamer, &rv, &v);	
	if(gamer->scene_collision_result)
	{
		float d = rv.z - v.z;
		if(gamer->z_moving.state != no_z_type)
		{
			if(d > 0.0f || gamer->z_moving.speed < 0.0f)
				v.z = rv.z;
			else
			{
				gamer->z_moving.speed = 0.0;
				gamer->z_moving.state = no_z_type;
			}
		}
		else
		{
			if(d > move_unit)
			{
				gamer->z_moving.state = z_falldown_type;
				gamer->z_moving.start_z = ov.z;
				gamer->z_moving.start_time = time;
				gamer->z_moving.jump_speed = 0.0;
				gamer->z_moving.speed = 0.0;
				v.z = rv.z;
			}
		}
		gamer->position[0] = v.x;
		gamer->position[1] = v.y;
		gamer->position[2] = v.z - gamer->height;
		gamer->ai.position_progress[0] = gamer->position[0];
		gamer->ai.position_progress[1] = gamer->position[1];
		gamer->ai.position_progress[2] = gamer->position[2];
	}
	else
	{
		if(gamer->z_moving.state == z_jumping_type)
		{
			gamer->z_moving.state = z_falldown_type;
			gamer->z_moving.start_z = ov.z;
			gamer->z_moving.start_time = time;
			gamer->z_moving.jump_speed = 0.0;
			gamer->z_moving.speed = 0.0;
		}
		else if(gamer->z_moving.state == z_falldown_type)
		{
			gamer->z_moving.speed = 0.0;
			gamer->z_moving.state = no_z_type;
		}
		v.z = ov.z;
		gamer->ai.position_progress[0] = gamer->ai.path[gamer->ai.current_path * 4];
		gamer->ai.position_progress[1] = gamer->ai.path[gamer->ai.current_path * 4 + 1];
	}
	//printf("%d %d | %d %f\n", gamer->ai.current_path, gamer->ai.path_count, gamer->scene, gamer->ai.path[gamer->ai.current_path * 4 + 3]);
	Game_UpdateCharacterPositionAndDirection(gamer, gamer->position[0], gamer->position[1], gamer->position[2], gamer->x_angle, gamer->y_angle, 1);

	gamer->ai.current_scene = gamer->scene;
}

int Game_ReloadWeapon(weapon *w, long long game_time)
{
	if(!w)
		return 0;
	if(w->type <= short_attack_type)
		return 0;
	if(w->status == reload_type)
		return 0;
	if(w->ammo_count == -1)
		return 0;
	if(w->ammo == -1)
		return 0;
	if(w->ammo_total_count - w->ammo == 0)
		return 0;
	if(w->ammo == w->ammo_count)
		return 0;
	w->status = reload_type;
	w->time = game_time;
	return 1;
}

int Game_HandleForceAI(const GL_NETLizard_3D_Model *map_model, game_character *gamer, long long time)
{
	if(!map_model || !gamer)
		return 0;
	if(gamer->ai.force_mask == 0)
		return 0;
	if(gamer->ai.force_time_limit > 0 && time - gamer->ai.force_start_time >= gamer->ai.force_time_limit)
	{
		gamer->ai.force_speed = 0;
		gamer->ai.force_start_pos[0] = 0;
		gamer->ai.force_start_pos[1] = 0;
		gamer->ai.force_start_pos[2] = 0;
		gamer->ai.force_pos[0] = 0;
		gamer->ai.force_pos[1] = 0;
		gamer->ai.force_pos[2] = 0;
		gamer->ai.force_start_time = 0;
		gamer->ai.force_x_dir = 0;
		gamer->ai.force_y_dir = 0;
		gamer->ai.force_time_limit = 0;
		gamer->ai.force_mask = 0;
		return 0;
	}

	nl_vector3_t start_pos = {gamer->ai.force_start_pos[0], gamer->ai.force_start_pos[1], gamer->ai.force_start_pos[2]};
	nl_vector3_t last_pos = {gamer->ai.force_pos[0], gamer->ai.force_pos[1], gamer->ai.force_pos[2]};
	nl_vector3_t pos = {0.0, 0.0, 0.0};
	Physics_GetGravityPosition(gamer->ai.force_speed, &start_pos, &last_pos, gamer->ai.force_x_dir, gamer->ai.force_y_dir, time - gamer->ai.force_start_time, gamer->ai.force_time_limit == 0 ? 1 : 0, &pos, NULL, NULL);
	gamer->ai.force_pos[0] = pos.x;
	gamer->ai.force_pos[1] = pos.y;
	gamer->ai.force_pos[2] = pos.z;

	nl_vector3_t rv = pos;
	rv.z += gamer->height;
	gamer->scene_collision_result = Algo_PointIsCollisionInScene(map_model, &rv, gamer->width, gamer->height, &gamer->scene, &gamer->collision_item);
	/*
		 if(Algo_CharacterCollisionTesting(map_model, gamer, &rv, characters, 0, character_count, NULL, &cv))
		 {
		 rv.x = cv.x;
		 rv.y = cv.y;
		 }
		 */
	if(gamer->scene_collision_result)
	{
		nl_vector3_t v = rv;
		Algo_ComputeCharacterPositionInNETLizard3DMap(map_model, gamer, &rv, &v);
		if(!(rv.z < v.z))
			v.z = rv.z;
		gamer->position[0] = v.x;
		gamer->position[1] = v.y;
		gamer->position[2] = v.z - gamer->height;
		Game_UpdateCharacterPositionAndDirection(gamer, gamer->position[0], gamer->position[1], gamer->position[2], gamer->x_angle, gamer->y_angle, 1);
		return 1;
	}
	else
	{
		gamer->ai.force_speed = 0;
		gamer->ai.force_start_pos[0] = 0;
		gamer->ai.force_start_pos[1] = 0;
		gamer->ai.force_start_pos[2] = 0;
		gamer->ai.force_pos[0] = 0;
		gamer->ai.force_pos[1] = 0;
		gamer->ai.force_pos[2] = 0;
		gamer->ai.force_start_time = 0;
		gamer->ai.force_x_dir = 0;
		gamer->ai.force_y_dir = 0;
		gamer->ai.force_time_limit = 0;
		gamer->ai.force_mask = 0;
		return 0;
	}
}

void Game_LookatCharacter(const GL_NETLizard_3D_Model *map_model, game_character *gamer, const nl_vector3_t *dir)
{
	if(!map_model || !gamer || !dir)
		return;
	/*
	float xr = 0.0;
	float yr = 0.0;
	Algo_GetNormalAngle(&direction, &yr, &xr);
	*/
	game_ai ai;
	ZERO(&ai, game_ai);
	AI_ClearAction(&ai);
	ai.type = ai_operate_type;
	ai.action = aiaction_no_type;
	// 获取目标位置的角度
	float xl = dir->x;
	float yl = dir->y;
	float f = Algo_FormatAngle(rtoa(atan2(yl, xl)) - 90.0);
	if(f != gamer->y_angle)
	{
		// TODO 选取最近角度选择向左或右旋转
		float offset = Algo_FormatAngle(f - gamer->y_angle);
		if(offset > 0 && offset <= 180.0f)
			ai.action |= aiaction_turnleft_type;
		else
			ai.action |= aiaction_turnright_type;
		ai.rotation_mask = 1;
		ai.y_angle_target = f;
		ai.angle_range = 0.0;
		ai.y_angle_progress = gamer->y_angle;
		// 更新角色的操作AI
	}
	ai.time = gamer->ai.time;
	if(ai.action != aiaction_no_type)
		AI_Copy(&gamer->ai, &ai);
}

void Game_CharacterRand4Weapons(game_character *gamer)
{
	if(!gamer)
		return;
	weapon_model_type types[CHARACTER_WEAPON_COUNT];
	unsigned mask = main_weapon_1 | secondary_weapon | fighting_weapon | launch_weapon;
	Game_Rand4WeaponTypes(types, countof(types), mask);
	Game_GetWeapon(gamer, types, CHARACTER_WEAPON_COUNT);
}
