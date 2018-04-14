#ifndef KARIN_GAME_AI_H
#define KARIN_GAME_AI_H

typedef enum _ai_action
{
	aiaction_no_type = 0,
	aiaction_idle_type = 1,
	aiaction_moveforward_type = 1 << 1,
	aiaction_movebackward_type = 1 << 2,
	aiaction_moveleft_type = 1 << 3,
	aiaction_moveright_type = 1 << 4,
	aiaction_turnleft_type = 1 << 5,
	aiaction_turnright_type = 1 << 6,
	aiaction_turnup_type = 1 << 7,
	aiaction_turndown_type = 1 << 8,
	aiaction_jump_type = 1 << 9,
	aiaction_crouch_type = 1 << 10,
	aiaction_attack_type = 1 << 11,
	aiaction_moveup_type = 1 << 12,
	aiaction_movedown_type = 1 << 13,
	aiaction_stand_type = 1 << 14,
	aiaction_dead_type = 1 << 15,
	aiaction_fight_type = 1 << 16,
	aiaction_path_type = 1 << 17,
	aiaction_reload_type = 1 << 18,
	aiaction_movey_type = aiaction_moveforward_type | aiaction_movebackward_type,
	aiaction_movex_type = aiaction_moveleft_type | aiaction_moveright_type,
	aiaction_movez_type = aiaction_moveup_type | aiaction_movedown_type,
	aiaction_movexy_type = aiaction_movex_type | aiaction_movey_type,
	aiaction_movexyz_type = aiaction_movex_type | aiaction_movey_type | aiaction_movez_type,
	aiaction_turnx_type = aiaction_turnup_type | aiaction_turndown_type,
	aiaction_turny_type = aiaction_turnleft_type | aiaction_turnright_type,
	aiaction_turnxy_type = aiaction_turnx_type | aiaction_turny_type
} ai_action_type;

typedef enum _ai_type
{
	ai_compute_type = 0, // 自动计算
	ai_script_type, // 脚本式移动
	ai_force_type, // 强制位移
	ai_operate_type, // 人工指挥AI
	ai_trigger_type, // 触发，只通过逻辑控制
	ai_player_type // 人工操作
} ai_type;

// 空闲 以时间记录
// 死亡 以时间记录
// 自动移动 以步数记录
// 旋转 以角度记录
// 到达位置 以坐标记录
// 攻击 可移动 旋转 次数计算
typedef struct _game_ai
{
	ai_type type;
	int action;

	long long time;

	int idle_mask;
	long long idle_time;
	long long idle_time_target;

	int dead_mask;
	long long dead_time;

	int move_mask;
	float move_step;
	int move_step_progress;
	int move_step_target;

	int rotation_mask;
	float x_angle_progress;
	float y_angle_progress;
	float x_angle_target;
	float y_angle_target;
	float angle_range;

	int goto_mask;
	float position_progress[3];
	float position_target[3];
	float position_range;

	int attack_mask;
	int attack_count;
	int attack_total_count;

	int fight_mask;
	int fighting;

	int path_mask;
	float *path;
	int path_count;
	int current_path;
	int current_scene;
	int next;

	int force_mask;
	float force_speed;
	float force_start_pos[3];
	float force_pos[3];
	long long force_start_time;
	float force_x_dir;
	float force_y_dir;
	unsigned int force_time_limit;
} game_ai;

void AI_AddForceAction(game_ai *ai, float force_speed, float x, float y, float z, long long force_start_time, float force_x_dir, float force_y_dir, unsigned int limit);
void AI_ProcessAction(game_ai *ai, long long time);
void AI_MakeComputeAction(game_ai *ai, int at, int action);
void AI_ClearAction(game_ai *ai);
void delete_game_ai(game_ai *ai);
void AI_Copy(game_ai *a, const game_ai *b);

#endif
