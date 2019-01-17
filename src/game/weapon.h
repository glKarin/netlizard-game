#ifndef _KARIN_WEAPON_H
#define _KARIN_WEAPON_H

#include "nl_gl.h"
#include "bullet.h"

#define LONG_ANGLE_MAX_OFFSET 4.0f
#define SHORT_ANGLE_MAX_OFFSET 1.0f
#define SHOTGUN_ANGLE_MAX_OFFSET 3.0f
#define SHOTGUN_ANGLE_MIN_OFFSET 0.2f

#define IS_LONG_WEAPON(wp) ((wp).type == shot_gun_type || (wp).type == mini_submachine_gun_type || (wp).type == automatic_rifle_type || (wp).type == sniper_rifle_type || (wp).type == machine_gun_type)
#define IS_GRENADE_WEAPON(wp) ((wp).type == grenades_type || (wp).type == flash_flares_type || (wp).type == smoke_bomb_type)   
#define IS_RIFLE_WEAPON(wp) ((wp).type == automatic_rifle_type || (wp).type == sniper_rifle_type)
#define IS_NEAR_WEAPON(wp) ((wp).type == pistol_gun_type || (wp).type == dagger_type)   
#define IS_LAUNCHER_WEAPON(wp) ((wp).type == launcher1_gun_type || (wp).type == launcher2_gun_type)

#define OTHER_WEAPON_INDEX 0
#define FIGHTING_WEAPON_INDEX 0
#define SECONDARY_WEAPON_INDEX 1
#define MAIN_WEAPON_1_INDEX 2
#define LAUNCH_WEAPON_INDEX 3
#define MAIN_WEAPON_2_INDEX 4

typedef enum _weapon_position_type
{
	other_weapon = 1,
	fighting_weapon = 1 << 1,
	secondary_weapon = 1 << 2,
	main_weapon_1 = 1 << 3,
	launch_weapon = 1 << 4,
	main_weapon_2 = 1 << 5,
} weapon_position_type;

typedef enum _weapon_usage_type
{
	weapon_on_floor_type = 0,
	weapon_use_type,
	weapon_back_type
} weapon_usage_type;

typedef enum _weapon_attack_type
{
	dagger_type = 0,
	short_attack_type,

	pistol_gun_type,
	shot_gun_type,
	mini_submachine_gun_type,
	automatic_rifle_type,
	//semi_automatic_sniper_rifle_type,
	sniper_rifle_type,
	machine_gun_type,

	launcher1_gun_type,
	launcher2_gun_type,
	grenades_type,
	flash_flares_type,
	smoke_bomb_type,

	long_attack_type
} weapon_attack_type;

typedef enum _weapon_model_type
{
	ct3d_Dagger = 0,
	ct3d_USP,
	ct3d_Python,
	ct3d_Desert_Eagle,
	ct3d_MP5,
	ct3d_M4a1,
	ct3d_AK47,
	ct3d_D3AU1,
	ct3d_AWP,
	ct3d_Flash_Grenade,
	ct3d_Fragmentation_Grenade,
	specnaz3d_Dagger,
	specnaz3d_Desert_Eagle,
	specnaz3d_MP5,
	specnaz3d_M4a1,
	specnaz3d_AK47,
	specnaz3d_M32,
	specnaz3d_Fragmentation_Grenade,
	egypt3d_Dagger,
	egypt3d_Colt_Walker,
	egypt3d_MP40,
	egypt3d_Mosin_Nagant,
	egypt3d_AK47,
	egypt3d_Plasma_Gun,
	egypt3d_The_Sword_of_Osiris,
	clone3d_Colt_Walker,
	clone3d_SPAS12, 
	clone3d_M16,
	clone3d_Rocket_Launcher,
	egypt3d_Worm_Weapon,
	egypt3d_Scorpion_Weapon,
	egypt3d_Fly_Fish_Weapon,
	egypt3d_Anubis_Weapon,
	egypt3d_Tentacle_Weapon,
	egypt3d_Machine_Monster_Weapon,
	egypt3d_Fly_Machine_Weapon,
	clone3d_Machine_Weapon,
	total_weapon_model_type
} weapon_model_type;

typedef enum _fire_status_type
{
	ready_type = 0,
	firing_type,
	fired_type,
	reload_type,
	outofammo_type
} fire_status_type;

typedef struct _game_weapon_model
{
	float scale;
	float x_offset;
	float y_offset;
	float z_offset;
	float position[3];
	GL_NETLizard_3D_Model *tp_model;
	texture *fp_tex;
} game_weapon_model;

typedef struct _weapon
{
	weapon_attack_type type; // 近身 / 远程
	weapon_model_type weapon_index;
	game_weapon_model *model; // 武器模型
	float firing_rate; // 射速
	int damage; // 伤害
	float shot_range; // 射程
	fire_status_type status; // 状态
	float hit_rate; // 后座率
	long long time; // 开始射击时间 毫秒
	int ammo; // 当前子弹发射数量
	int ammo_count; // 弹夹容量
	int ammo_total_count; // 总备弹
	int ammo_total_count_limit; // 总备弹限制
	float reload_time; // 填弹时间
	float firing_progress; // 射击持续进度
	float x_angle; // x轴角度
	float y_angle; // y轴角度
	float render_position[3]; // 渲染位置
	float position[3]; // 子弹发射位置
	float speed; // 子弹速度
	float boom_range; // 子弹爆炸范围
	float boom_damage_attenuation; // 子弹爆炸范围伤害衰减
	float damage_attenuation; // 子弹距离伤害衰减
	float length; // 武器长度
	unsigned int shell_count; // 弹丸数量
} weapon;

extern const char *Weapon_Name[total_weapon_model_type];
extern const char *Weapon_Type_Name[long_attack_type];

weapon * new_weapon(weapon *w, weapon_model_type type); 
void delete_weapon(weapon *wp);
bullet * Game_WeaponFire(bullet bt[], const weapon *wp, float w, int character_index, int group, unsigned int *count);

void Game_LoadWeaponModel(void);
void Game_FreeWeaponModel(void);
weapon_model_type Game_RandLongWeapon(void);
weapon_model_type Game_RandHeavyWeapon(void);
weapon_model_type Game_RandLightWeapon(void);
weapon_model_type Game_RandKnifeWeapon(void);
weapon_model_type Game_RandPistolWeapon(void);
weapon_model_type Game_RandGrenadeWeapon(void);
int Game_Rand4WeaponTypes(weapon_model_type wps[], unsigned int max, unsigned mask);
int Game_GetWeaponPosition(weapon_model_type type);

#endif
