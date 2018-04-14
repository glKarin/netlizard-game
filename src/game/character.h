#ifndef KARIN_GAME_CHARACTER_H
#define KARIN_GAME_CHARACTER_H

#include "lol.h"
#include "nl_gl.h"
#include "game_algo.h"
#include "game_ai.h"
#include "weapon.h"

#define NETLIZARD_ANIMATION_FPS 12

/*
#define CAITLYN_ARCTIC_WARFARE_ANIM _KARIN_RESOURCE_DIR"resource/model/caitlyn_arctic_warfare.lanim"
#define CAITLYN_ARCTIC_WARFARE_MESH _KARIN_RESOURCE_DIR"resource/model/caitlyn_arctic_warfare.lmesh"
#define CAITLYN_ARCTIC_WARFARE_PNG _KARIN_RESOURCE_DIR"resource/model/caitlyn_arctic_warfare.png"
#define CAITLYN_OFFICER_ANIM _KARIN_RESOURCE_DIR"resource/model/caitlyn_officer.lanim"
#define CAITLYN_OFFICER_MESH _KARIN_RESOURCE_DIR"resource/model/caitlyn_officer.lmesh"
#define CAITLYN_OFFICER_PNG _KARIN_RESOURCE_DIR"resource/model/caitlyn_officer.png"
#define CAITLYN_SAFARI_ANIM _KARIN_RESOURCE_DIR"resource/model/caitlyn_safari.lanim"
#define CAITLYN_SAFARI_MESH _KARIN_RESOURCE_DIR"resource/model/caitlyn_safari.lmesh"
#define CAITLYN_SAFARI_PNG _KARIN_RESOURCE_DIR"resource/model/caitlyn_safari.png"
*/
#define CAITLYN_ORIGINAL_ANIM _KARIN_RESOURCE_DIR"resource/model/caitlyn_original.lanim"
#define CAITLYN_ORIGINAL_MESH _KARIN_RESOURCE_DIR"resource/model/caitlyn_original.lmesh"
#define CAITLYN_ORIGINAL_PNG _KARIN_RESOURCE_DIR"resource/model/caitlyn_original.png"

#define JINX_ORIGINAL_ANIM _KARIN_RESOURCE_DIR"resource/model/jinx_original.lanim"
#define JINX_ORIGINAL_MESH _KARIN_RESOURCE_DIR"resource/model/jinx_original.lmesh"
#define JINX_ORIGINAL_PNG _KARIN_RESOURCE_DIR"resource/model/jinx_original.png"

#define CAITLYN_CHARACTER_SCALE 1.9
#define JINX_CHARACTER_SCALE 1.3
#define NETLIZARD_CHARACTER_SCALE 1
#define CHARACTER_MIN_SPACING 10

typedef enum _netlizard_role_model_type
{
	egypt3d_worm = 0,
	egypt3d_scorpion,
	egypt3d_fly_fish,
	egypt3d_anubis,
	egypt3d_tentacle,
	egypt3d_machine_monster,
	egypt3d_fly_machine,
	clone3d_human_cloning,
	clone3d_soldier,
	clone3d_human_cloning_old,
	clone3d_soldier2,
	clone3d_bio_soldier,
	clone3d_machine,
	clone3d_damage_machine
} netlizard_role_model_type;

typedef enum _lol_role_model_type
{
	caitlyn_original = clone3d_damage_machine,
	jinx_original,
	lol_total_model
} lol_role_model_type;

typedef enum _z_moving_type
{
	no_z_type = 0,
	z_falldown_type = 1,
	z_jumping_type = 2
} z_moving_type;

typedef enum _model_source_type
{
	unavailable_model_type = 0,
	netlizard_model_type,
	lol_model_type
} model_source_type;

typedef	struct _character_animation_data
{
	int anim;
	int frame;
	int frame_count;
	animation_loop_type anim_loop;
	animation_orientation_type anim_orient;
	long long last_play_time;
	int fps;
} character_animation_data;

typedef struct _lol_game_character
{
	model_source_type source;
	float scale;
	float x_offset;
	float y_offset;
	float z_offset;
	LOL_Model *model;
	int anim_list[LOL_Total_Type];
} lol_game_character;

typedef struct _netlizard_game_character
{
	model_source_type source;
	float scale;
	float x_offset;
	float y_offset;
	float z_offset;
	GL_NETLizard_3D_Animation_Model *model;
} netlizard_game_character;

typedef union _game_character_model
{
	model_source_type source;
	lol_game_character lol_character;
	netlizard_game_character netlizard_character;
} game_character_model;

typedef struct _game_character
{
	game_character_model model; // 角色模型数据 模型 动画
	float position[3]; // 位置坐标，脚部坐标，NETLizard地图的场景坐标
	float direction[3]; // 当前方向法线，暂不使用
	float x_angle; // X轴旋转角度 0 - 180
	float y_angle; // 竖直z轴旋转角度 0 - 360
	float move_unit; // 单位移动距离
	float turn_unit; // 单位旋转角度
	float z_jump_speed; // 跳跃速度
	struct {
		z_moving_type state; // z轴移动状态，1 下落 2 跳跃
		float start_z; // 跳跃起始高度 暂不使用
		long long start_time; // 跳跃起始时间
		float jump_speed; // 0 自由落体 < 0 向上跳跃 > 0 向下坠落
		float speed; // 当前速度
	} z_moving;
	float width; // 角色宽度，用于碰撞检测
	float height; // 角色视角高度，用于碰撞检测
	float full_height; // 角色总高度
	int scene; // 当前位置所在场景
	int scene_collision_result; // 最后一次碰撞检测的结果，用于计算第三人称视角坐标
	int collision_item; // 当前碰撞的物品
	int health; // 生命值
	int health_full; // 生命值
	character_animation_data animation; // 动画数据
	character_status_type status; // 当前状态
	game_ai ai; // 简单人工智能数据，自动计算和人工指挥
	int group; // 所属阵营
	int index;
	char *name;
	struct{
		int kill;
		int death;
		int assist;
		int killed_character;
		int kill_character;
	}score;
	weapon current_weapon; // 当前武器
	//weapon *weapons; // 所有武器
	//int weapon_count; // 武器数量
	//int current_weapon_index; // 当前武器索引
} game_character;
// should extends this struct with c-style OOP
// struct my_game_character
// {
//	game_character gamer;
//	...;
// }

extern const char *Character_Model_Name[lol_total_model];

game_character * new_lol_game_character(game_character *c, const char *meshf, const char *ddsf[], int count, const char *animf, float x, float y, float z, float xr, float yr, float f, float w, float h, float th, float mu, float tu, float speed, int scene);
game_character * new_netlizard_game_character(game_character *c, const char *game, const char *file, int index, float x, float y, float z, float xr, float yr, float f, float w, float h, float th, float mu, float tu, float speed, int scene);

void delete_game_character(game_character *gamer);

void Game_CharacterPlayAnimation(game_character *gamer, long long time, int fps);
void Game_RenderGameCharacter(const game_character *gamer);
void Game_UpdateCharacterPositionAndDirection(game_character *gamer, float x, float y, float z, float xr, float yr);
game_character * new_game_character(game_character *c, int type, float x, float y, float z, float xr, float yr, int id, const char *name, int scene, weapon_model_type wt);
int Game_MakeGameCharacterModel(game_character_model *game_model, unsigned int type);
void Game_FreeCharacterModel(game_character_model *game_model);
int Game_GetNETLizardAnimationIndex(GL_NETLizard_3D_Animation_Model *model, NETLizard_3D_Animation_Type type);
int Game_GetAnimationNextFrame(const character_animation_data *data, int f);
int Game_ComputeAnimationPlayFrameCount(model_source_type type, character_animation_data *animation, int fps, long long time);

#endif
