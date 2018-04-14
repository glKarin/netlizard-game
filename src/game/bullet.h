#ifndef _KARIN_BULLET_H
#define _KARIN_BULLET_H

typedef enum _bullet_type
{
	no_bullet_type = 0, // 无弹道 近身武器
	normal_bullet_type, // 普通子弹
	shell_bullet_type, // 大号榴弹
	grenade_bullet_type // 手榴弹
} bullet_type;

typedef struct _bullet
{
	bullet_type type; // 0 - 近战 1 远程 2 流弹 3 手雷
	float position[3]; // 当前位置
	float x_dir; // 初始方向
	float y_dir; // 初始方向
	float x_angle; // 当前方向
	float y_angle; // 当前方向
	long long time; // 发射时间
	float speed; // 速度
	int damage; // 伤害
	int start_damage; // 初始伤害
	float damage_attenuation; // 伤害距离衰减 10000单位
	float start_pos[3]; // 起始位置
	float last_pos[3]; // 上次位置
	int gravity; // 是否计算重力加速度

	float distance; // 范围 -1 无限
	float range; // 范围 -1 无限
	float boom_range; // 爆炸范围
	float boom_damage_attenuation; // 爆炸范围伤害衰减
	int group; // 子弹阵营
	int character; // 发射子弹的角色
	float weapon_length;
	int finished;
} bullet;

bullet * new_bullet(bullet *bt, float x, float y, float z, float dirx, float diry, long long time, float speed, int damage, float damage_attenuation, float boom_range, float boom_damage_attenuation, float range, int gravity, bullet_type at, int c, int group, float len);
void Game_UpdateBullet(bullet *b, long long time);
int Game_GetBulletBoomDamage(bullet *bt, float dis);

#endif
