#ifndef KARIN_GAME_CHARACTER_H
#define KARIN_GAME_CHARACTER_H

#include "lol.h"
#include "nl_gl.h"
#include "game_algo.h"
#include "game_ai.h"
#include "weapon.h"
#include "studio_game.h"

#define CHARACTER_VIEW_FOV 120.0

#define NETLIZARD_ANIMATION_FPS 20
#define CHARACTER_WEAPON_COUNT 4

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

#define NATASHA2_MDL _KARIN_RESOURCE_DIR"resource/model/Girl/natasha2.mdl"
#define CHOIJIYOON_MDL _KARIN_RESOURCE_DIR"resource/model/Girl/choijiyoon.mdl"
#define JESSICA_MDL _KARIN_RESOURCE_DIR"resource/model/Girl/jennifer.mdl"
#define JESSICA2_MDL _KARIN_RESOURCE_DIR"resource/model/Girl/jennifer2.mdl"
#define LUCIA_MDL _KARIN_RESOURCE_DIR"resource/model/Girl/marinegirl.mdl"
#define NATASHA_MDL _KARIN_RESOURCE_DIR"resource/model/Girl/natasha.mdl"
#define CHOIJIYOON2_MDL _KARIN_RESOURCE_DIR"resource/model/Girl/choijiyoon2.mdl"
#define YURI2_MDL _KARIN_RESOURCE_DIR"resource/model/Girl/yuri2.mdl"

#define TR1_TERROR_MDL _KARIN_RESOURCE_DIR"resource/model/TR/terror.mdl"
#define TR2_LEET_MDL _KARIN_RESOURCE_DIR"resource/model/TR/leet.mdl"
#define TR3_ARCTIC_MDL _KARIN_RESOURCE_DIR"resource/model/TR/arctic.mdl"
#define TR4_GUERILLA_MDL _KARIN_RESOURCE_DIR"resource/model/TR/guerilla.mdl"
#define TR5_MILITIA_MDL _KARIN_RESOURCE_DIR"resource/model/TR/militia.mdl"
#define TR2_LEET2_MDL _KARIN_RESOURCE_DIR"resource/model/TR/leet2.mdl"

#define CT1_URBAN_MDL _KARIN_RESOURCE_DIR"resource/model/CT/urban.mdl"
#define CT2_GSG9_MDL _KARIN_RESOURCE_DIR"resource/model/CT/gsg9.mdl"
#define CT3_SAS_MDL _KARIN_RESOURCE_DIR"resource/model/CT/sas.mdl"
#define CT4_GIGN_MDL _KARIN_RESOURCE_DIR"resource/model/CT/gign.mdl"
#define CT5_SPETSNAZ_MDL _KARIN_RESOURCE_DIR"resource/model/CT/spetsnaz.mdl"


#define NATASHA_CHARACTER_SCALE 3.8
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

typedef enum _csol_role_model_type
{
	natasha2 = clone3d_damage_machine,
	choijiyoon,
	jessica,
	jessica2,
	lucia,
	natasha,
	choijiyoon2,
	yuri2,

	TR1_terror,
	TR2_leet,
	TR3_arctic,
	TR4_guerilla,
	TR5_militia,
	TR2_leet2,

	CT1_urban,
	CT2_gsg9,
	CT3_sas,
	CT4_gign,
	CT5_spetsnaz,

	csol_total_model
} csol_role_model_type;

typedef enum _lol_role_model_type
{
	caitlyn_original = csol_total_model,
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
	lol_model_type,
	csol_model_type
} model_source_type;

typedef	struct _character_animation_data
{
	struct character_animation_internal_data {
		int anim;
		int frame;
		int frame_count;
		animation_loop_type anim_loop;
		animation_orientation_type anim_orient;
		int fps;
		float comp;
		int play;
		unsigned status;
	} idata[character_all_part_type];
	float last_play_time;
	unsigned int num;
} character_animation_data;

typedef struct _csol_game_character
{
	model_source_type source;
	float scale;
	float x_offset;
	float y_offset;
	float z_offset;
	GameStudioModel *model;
} csol_game_character;

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
	csol_game_character csol_character;
} game_character_model;

typedef struct _game_character
{
	game_character_model model; // 角色模型数据 模型 动画
	float position[3]; // 位置坐标，脚部坐标，NETLizard地图的场景坐标
	float direction[3]; // 当前方向法线
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
	unsigned current_status; // 当前状态
	game_ai ai; // 简单AI数据，自动计算和人工指挥
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
	struct{
		weapon *wpons;
		unsigned int wp_count;
		unsigned mask;
		int current_weapon;
		float wpon_z_fixed;
	} weapons; // 当前武器
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
game_character * new_csol_game_character(game_character *c, const char *mdlfile, float x, float y, float z, float xr, float yr, float f, float w, float h, float th, float mu, float tu, float speed, int scene);

void delete_game_character(game_character *gamer);

void Game_CharacterPlayAnimation(game_character *gamer, long long time, int fps, float delta);
void Game_RenderGameCharacter(const game_character *gamer);
void Game_UpdateCharacterPositionAndDirection(game_character *gamer, float x, float y, float z, float xr, float yr, unsigned up_wp);
void Game_UpdateCharacterCurrentWeaponPositionAndDirection(game_character *gamer);
game_character * new_game_character(game_character *c, int type, float x, float y, float z, float xr, float yr, int id, const char *name, int scene, const weapon_model_type wt[], unsigned int max);
int Game_MakeGameCharacterModel(game_character_model *game_model, unsigned int type);
void Game_FreeCharacterModel(game_character_model *game_model);
int Game_GetNETLizardAnimationIndex(GL_NETLizard_3D_Animation_Model *model, NETLizard_3D_Animation_Type type);
void Game_GetAnimationNextFrame(character_animation_data *data);
void Game_ComputeAnimationPlayFrameCount(model_source_type source, character_animation_data *animation, int fps, float delta);
int Game_GetWeapon(game_character *gamer, const weapon_model_type types[], unsigned int count);
void Game_FreeCharacterWeapons(game_character *gamer);
weapon * Game_CharacterCurrentWeapon(game_character *gamer);
int Game_PrevWeapon(game_character *gamer, unsigned skip);
int Game_NextWeapon(game_character *gamer, unsigned skip);
int Game_PreferWeapon(game_character *gamer);
int Game_UpdateCharacterStatus(game_character *gamer, unsigned status, animation_orientation_type o);

#endif
