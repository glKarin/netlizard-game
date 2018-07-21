#include "game_ai.h"
#include "nl_std.h"
#include "math3d/vector2.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define AI_MAX_IDLE 6
#define AI_MIN_IDLE 2
#define AI_MAX_MOVE 20
#define AI_MIN_MOVE 5
#define AI_MAX_ROTATION 270
#define AI_MIN_ROTATION 90
#define AI_MAX_ATTACK 20
#define AI_MIN_ATTACK 10

#define RAND_MIN_MAX(r, min, max) (r) % ((max) - (min)) + (min)

static void AI_PrintAction(ai_action_type t);

void AI_ClearAction(game_ai *ai)
{
	if(!ai)
		return;
	if(ai->type == ai_script_type && ai->action & aiaction_path_type && ai->path_mask)
	{
		if(ai->path)
			free(ai->path);
	}
	ai->type = ai_compute_type;
	ai->action = aiaction_no_type;
	ai->idle_mask = 0;
	ai->idle_time = 0;
	ai->idle_time_target = 0;
	ai->dead_mask = 0;
	ai->dead_time = 0;
	ai->move_mask = 0;
	ai->move_step_progress = 0;
	ai->move_step = 0.0;
	ai->move_step_target = -1;
	ai->rotation_mask = 0;
	ai->x_angle_progress = 0;
	ai->y_angle_progress = 0;
	ai->x_angle_target = 0;
	ai->y_angle_target = 0;
	ai->goto_mask = 0;
	ai->position_progress[0] = 0;
	ai->position_progress[1] = 0;
	ai->position_progress[2] = 0;
	ai->position_target[0] = 0;
	ai->position_target[1] = 0;
	ai->position_target[2] = 0;
	ai->angle_range = 0;
	ai->position_range = 0;
	ai->attack_mask = 0;
	ai->attack_count = 0;
	ai->attack_total_count = -1;
	ai->fight_mask = 0;
	ai->fighting = 0;
	ai->path_mask = 0;
	ai->path = NULL;
	ai->path_count = 0;
	ai->current_path = 0;
	ai->next = 0;
	ai->current_scene = -1;
}
// 生成自动AI指定动作终止条件
int AI_RandActionTarget(ai_action_type a)
{
	int r = rand();
	if(a == aiaction_idle_type)
		return RAND_MIN_MAX(r, AI_MIN_IDLE, AI_MAX_IDLE);
	else if(a & aiaction_turnxy_type)
		return RAND_MIN_MAX(r, AI_MIN_ROTATION, AI_MAX_ROTATION);
	else if(a & aiaction_movexy_type)
		return RAND_MIN_MAX(r, AI_MIN_MOVE, AI_MAX_MOVE);
	else if(a == aiaction_attack_type)
		return RAND_MIN_MAX(r, AI_MIN_ATTACK, AI_MAX_ATTACK);
	return -1;
}

// 生成一个自动的AI类型
ai_action_type AI_RandAction(void)
{
	return aiaction_path_type; ////// for test
	int r = rand() % 3;
	if(r == 0)
		return aiaction_idle_type;
	else if(r == 1)
	{
		ai_action_type a = aiaction_no_type;
		r = rand() % 6;
		if(r == 0)
			a |= aiaction_turnleft_type;
		else if(r == 1)
			a |= aiaction_turnright_type;
		else if(r == 2)
			return a;
		r = rand() % 2;
		if(r != 0)
			a |= aiaction_moveforward_type;
		return a;
	}
	else
		return aiaction_path_type;
}

// 处理AI
void AI_ProcessAction(game_ai *ai, long long time)
{
	if(!ai)
		return;
	if(ai->type == ai_compute_type)
	{
		if(ai->idle_mask && ai->action == aiaction_idle_type)
		{
			ai->idle_time += time - ai->time;
			if(ai->idle_time >= ai->idle_time_target)
			{
				ai->idle_mask = 0;
				ai->idle_time = 0;
				ai->idle_time_target = 0;
				ai->action ^= aiaction_idle_type;
			}
		}
		else
		{
			if(ai->rotation_mask && (ai->action & aiaction_turny_type))
			{
				if(ai->y_angle_target - ai->y_angle_progress <= ai->angle_range)
				{
					ai->rotation_mask = 0;
					ai->y_angle_progress = 1;
					ai->y_angle_target = 0;
					ai->angle_range = 0;
					if(ai->action & aiaction_turnleft_type)
						ai->action ^= aiaction_turnleft_type;
					else if(ai->action & aiaction_turnright_type)
						ai->action ^= aiaction_turnright_type;
				}
			}
			if(ai->move_mask && (ai->action & aiaction_movexy_type))
			{
				if(ai->move_step_progress >= ai->move_step_target)
				{
					ai->move_mask = 0;
					ai->move_step_progress = -1;
					ai->move_step_target = 0;
					ai->move_step = 0.0;
					ai->action ^= aiaction_moveforward_type;
				}
				else
				{
					if(ai->move_step >= 1.0)
					{
						ai->move_step_progress ++;
						ai->move_step -= 1.0;
					}
				}
			}
		}
	}
	else if(ai->type == ai_operate_type)
	{
		if(ai->rotation_mask && (ai->action & aiaction_turnleft_type || ai->action & aiaction_turnright_type))
		{
			if(ai->y_angle_target == ai->y_angle_progress)
			{
				ai->rotation_mask = 0;
				ai->y_angle_progress = 1;
				ai->y_angle_target = 0;
				ai->angle_range = 0;
				if(ai->action & aiaction_turnleft_type)
					ai->action ^= aiaction_turnleft_type;
				else if(ai->action & aiaction_turnright_type)
					ai->action ^= aiaction_turnright_type;
			}
		}
		if(ai->goto_mask && (ai->action & aiaction_moveforward_type))
		{
			nl_vector2_t vp = {
				ai->position_progress[0],
				ai->position_progress[1]
			};
			nl_vector2_t vt = {
				ai->position_target[0],
				ai->position_target[1]
			};
			nl_vector2_t v = Vector2_SubtractVector2(&vt, &vp);
			float dis = Vector2_Mag(&v);
			if(abs(dis) <= ai->position_range)
			{
				ai->goto_mask = 0;
				ai->position_progress[0] = 0;
				ai->position_progress[1] = 0;
				ai->position_progress[2] = 0;
				ai->position_target[0] = 0;
				ai->position_target[1] = 0;
				ai->position_target[2] = 0;
				ai->position_range = -1;
				ai->action ^= aiaction_moveforward_type;
			}
		}
	}
	else if(ai->type == ai_trigger_type)
	{
		if(ai->attack_mask && (ai->action & aiaction_attack_type))
		{
			if(ai->attack_count >= ai->attack_total_count)
			{
				if(ai->move_mask && ((ai->action & aiaction_moveforward_type) || (ai->action & aiaction_moveleft_type) || (ai->action & aiaction_moveright_type) || (ai->action & aiaction_movebackward_type)))
				{
					if(ai->move_step_progress >= ai->move_step_target)
					{
						ai->move_mask = 0;
						ai->move_step_progress = -1;
						ai->move_step_target = 0;
						ai->move_step = 0.0;
						if(ai->action & aiaction_moveforward_type)
							ai->action ^= aiaction_moveforward_type;
						else if(ai->action & aiaction_movebackward_type)
							ai->action ^= aiaction_movebackward_type;
						if(ai->action & aiaction_moveleft_type)
							ai->action ^= aiaction_moveleft_type;
						else if(ai->action & aiaction_moveright_type)
							ai->action ^= aiaction_moveright_type;
						ai->attack_count = 0;
						ai->attack_total_count = AI_RandActionTarget(aiaction_attack_type);
					}
					else
					{
						if(ai->move_step >= 1.0)
						{
							ai->move_step_progress ++;
							ai->move_step -= 1.0;
						}
					}
				}
				else
				{
					int r = rand() % 12;
					if(r == 0)
						ai->action |= aiaction_moveforward_type;
					else if(r == 1)
						ai->action |= aiaction_movebackward_type;
					else if(r >= 2 || r <= 4)
						ai->action |= aiaction_moveleft_type;
					else if(r >= 5 || r == 7)
						ai->action |= aiaction_moveright_type;
					if(r <= 7)
					{
						ai->move_mask = 1;
						ai->move_step_progress = 0;
						ai->move_step = 0.0;
						ai->move_step_target = AI_MIN_MOVE;
					}
				}
			}
			else
			{
				//ai->attack_count++;
			}

			if(ai->rotation_mask && (ai->action & aiaction_turnleft_type || ai->action & aiaction_turnright_type))
			{
				if(ai->y_angle_target == ai->y_angle_progress)
				{
					ai->rotation_mask = 0;
					ai->y_angle_progress = 1;
					ai->y_angle_target = 0;
					ai->angle_range = 0;
					if(ai->action & aiaction_turnleft_type)
						ai->action ^= aiaction_turnleft_type;
					else if(ai->action & aiaction_turnright_type)
						ai->action ^= aiaction_turnright_type;
				}
			}
		}
		else if(ai->fight_mask && (ai->action & aiaction_fight_type))
		{
			if(ai->rotation_mask && (ai->action & aiaction_turnleft_type || ai->action & aiaction_turnright_type))
			{
				if(ai->y_angle_target == ai->y_angle_progress)
				{
					ai->rotation_mask = 0;
					ai->y_angle_progress = 1;
					ai->y_angle_target = 0;
					ai->angle_range = 0;
					if(ai->action & aiaction_turnleft_type)
						ai->action ^= aiaction_turnleft_type;
					else if(ai->action & aiaction_turnright_type)
						ai->action ^= aiaction_turnright_type;
				}
			}
			if(ai->goto_mask && (ai->action & aiaction_moveforward_type))
			{
				nl_vector2_t vp = {
					ai->position_progress[0],
					ai->position_progress[1]
				};
				nl_vector2_t vt = {
					ai->position_target[0],
					ai->position_target[1]
				};
				nl_vector2_t v = Vector2_SubtractVector2(&vt, &vp);
				float dis = Vector2_Mag(&v);
				if(abs(dis) <= ai->position_range)
				{
					ai->goto_mask = 0;
					ai->position_progress[0] = 0;
					ai->position_progress[1] = 0;
					ai->position_progress[2] = 0;
					ai->position_target[0] = 0;
					ai->position_target[1] = 0;
					ai->position_target[2] = 0;
					ai->position_range = -1;
					ai->action ^= aiaction_moveforward_type;
					ai->fighting = 1;
				}
				else
					ai->fighting = 0;
			}
		}
	}
	else if(ai->type == ai_script_type)
	{
		if(ai->path_mask)
		{
			if(ai->rotation_mask && (ai->action & aiaction_turnleft_type || ai->action & aiaction_turnright_type))
			{
				if(ai->y_angle_target == ai->y_angle_progress)
				{
					ai->rotation_mask = 0;
					ai->y_angle_progress = 1;
					ai->y_angle_target = 0;
					ai->angle_range = 0;
					if(ai->action & aiaction_turnleft_type)
						ai->action ^= aiaction_turnleft_type;
					else if(ai->action & aiaction_turnright_type)
						ai->action ^= aiaction_turnright_type;
				}
			}
			if(ai->goto_mask && (ai->action & aiaction_moveforward_type))
			{
				nl_vector2_t vp = {
					ai->position_progress[0],
					ai->position_progress[1]
				};
				nl_vector2_t vt = {
					ai->path[ai->current_path * 4],
					ai->path[ai->current_path * 4 + 1]
				};
				nl_vector2_t v = Vector2_SubtractVector2(&vt, &vp);
				float dis = Vector2_Mag(&v);
				if(abs(dis) <= ai->position_range || ai->current_scene == (int)(ai->path[ai->current_path * 4 + 3]))
				{
					ai->goto_mask = 0;
					ai->position_progress[0] = 0;
					ai->position_progress[1] = 0;
					ai->position_progress[2] = 0;
					ai->position_range = -1;
					ai->action ^= aiaction_moveforward_type;
					//if(ai->current_path >= ai->path_count - 1)
					ai->rotation_mask = 0;
					ai->y_angle_progress = 1;
					ai->y_angle_target = 0;
					ai->angle_range = 0;
					if(ai->action & aiaction_turnleft_type)
						ai->action ^= aiaction_turnleft_type;
					else if(ai->action & aiaction_turnright_type)
						ai->action ^= aiaction_turnright_type;
					ai->current_path++;
					ai->next = 1;
				}
			}
			if(ai->current_path >= ai->path_count)
			{
				if(ai->path)
					free(ai->path);
				ai->path = NULL;
				ai->current_path = 0;
				ai->next = 0;
				ai->current_scene = -1;
				ai->path_count = 0;
				ai->path_mask = 0;
				ai->action ^= aiaction_path_type;
			}
		}
	}
	if(ai->action == aiaction_no_type)
		AI_MakeComputeAction(ai, 1, 0);
	//AI_PrintAction(ai->action);
	ai->time = time;
}

// 生成一个自动AI 空闲 或 旋转移动
void AI_MakeComputeAction(game_ai *ai, int at, int action)
{
	if(!ai)
		return;
	AI_ClearAction(ai);
	/*
		 if(ai->action != aiaction_no_type)
		 return;
		 */

	ai_action_type a;
	if(at)
		a = AI_RandAction();
	else
		a = action;
	/*
		 if(ai->action == a)
		 a = aiaction_idle_type;
		 */
	ai->type = ai_compute_type;
	ai->action = a;
	if(ai->action == aiaction_idle_type)
	{
		int target = AI_RandActionTarget(aiaction_idle_type);
		ai->idle_mask = 1;
		ai->idle_time_target = target * 1000;
		ai->idle_time = 0; 
	}
	else if(ai->action == aiaction_path_type)
	{
		ai->type = ai_script_type;
	}
	else
	{
		if(ai->action & aiaction_turny_type)
		{
			int target = AI_RandActionTarget(aiaction_turnxy_type);
			ai->idle_mask = 0;
			ai->rotation_mask = 1;
			ai->y_angle_progress = 0;
			ai->y_angle_target = target;
		}
		if(ai->action & aiaction_movexy_type)
		{
			int target = AI_RandActionTarget(aiaction_movexy_type);
			ai->idle_mask = 0;
			ai->move_mask = 1;
			ai->move_step_progress = 0;
			ai->move_step = 0.0;
			ai->move_step_target = target;
		}
	}
}

void AI_PrintAction(ai_action_type t)
{
#define AND_TYPE_PRINTF_STRING(t, type) \
	if(t & type) \
	printf("%s ", #type);

	printf("( ");
	AND_TYPE_PRINTF_STRING(t, aiaction_no_type)
		AND_TYPE_PRINTF_STRING(t, aiaction_idle_type)
		AND_TYPE_PRINTF_STRING(t, aiaction_moveforward_type)
		AND_TYPE_PRINTF_STRING(t, aiaction_movebackward_type)
		AND_TYPE_PRINTF_STRING(t, aiaction_moveleft_type)
		AND_TYPE_PRINTF_STRING(t, aiaction_moveright_type)
		AND_TYPE_PRINTF_STRING(t, aiaction_turnleft_type)
		AND_TYPE_PRINTF_STRING(t, aiaction_turnright_type)
		AND_TYPE_PRINTF_STRING(t, aiaction_turnup_type)
		AND_TYPE_PRINTF_STRING(t, aiaction_turndown_type)
		AND_TYPE_PRINTF_STRING(t, aiaction_jump_type)
		AND_TYPE_PRINTF_STRING(t, aiaction_crouch_type)
		AND_TYPE_PRINTF_STRING(t, aiaction_attack_type)
		AND_TYPE_PRINTF_STRING(t, aiaction_moveup_type)
		AND_TYPE_PRINTF_STRING(t, aiaction_movedown_type)
		AND_TYPE_PRINTF_STRING(t, aiaction_stand_type)

		printf(")\n");
}

void delete_game_ai(game_ai *ai)
{
	if(!ai)
		return;
	if(ai->type == ai_script_type && ai->action & aiaction_path_type && ai->path_mask)
	{
		if(ai->path)
		{
			free(ai->path);
			ai->path = NULL;
		}
	}
}

void AI_Copy(game_ai *a, const game_ai *b)
{
	if(!a || !b)
		return;
	delete_game_ai(a);
	memcpy(a, b, sizeof(game_ai));
}

void AI_AddForceAction(game_ai *ai, float force_speed, float x, float y, float z, long long force_start_time, float force_x_dir, float force_y_dir, unsigned int limit)
{
	if(!ai)
		return;
	ai->force_start_pos[0] = x;
	ai->force_start_pos[1] = y;
	ai->force_start_pos[2] = z;
	ai->force_pos[0] = x;
	ai->force_pos[1] = y;
	ai->force_pos[2] = z;
	ai->force_start_time = force_start_time;
	ai->force_speed = force_speed;
	ai->force_x_dir = force_x_dir;
	ai->force_y_dir = force_y_dir;
	ai->force_time_limit = limit;

	ai->force_mask = 1;
}
