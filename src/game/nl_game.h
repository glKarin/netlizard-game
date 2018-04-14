#ifndef KARIN_NL_GAME_H
#define KARIN_NL_GAME_H

#include "nl_gl.h"
#include "nl_std.h"
#include "game/character.h"
#include "game_util.h"
#include "template/list_template.h"

typedef enum _human_body_position_type
{
	human_head_type = 0,
	human_body_a_type,
	human_body_b_type,
	human_leg_a_type,
	human_leg_b_type,
	human_foot_type,
	human_body_total
} human_body_type;

typedef struct human_body_hits
{
	float bottom_per;
	float top_per;
	float damage_factory;
} human_body_hits;

extern game_character *characters;
extern int character_count;

// 初始化角色数组
game_character * Game_InitCharacter(float x, float y, float z, float xr, float yr, int scene, unsigned int gc, unsigned int cc, unsigned int self, unsigned int *count);
// 清理角色数组
void Game_DeleteCharacter(game_character *characters, int count);
// 绘制角色
void Game_RenderCharacters(const game_character *characters, int start, int cc, const int *scenes, int sc);
// 空闲时调用
// 执行角色AI行为，或人工操作行为
void Game_HandleCharacterAction(const GL_NETLizard_3D_Model *model, game_character *characters, int start, int count, long long time);
// 人工指挥操作 - 向前移动指令
// 位置移动和选择同步
void Game_OperateAIMoveToPosition(const GL_NETLizard_3D_Model *map_model, const game_character *gamer, game_character *characters, int start, int count);
// 人工指挥操作 - 回到身边指令
// 位置移动和选择同步
void Game_OperateAIBackToMe(const GL_NETLizard_3D_Model *map_model, const game_character *gamer, game_character *characters, int start, int count);
// 人工指挥操作 - 瞬移到主角位置
void Game_OperateAIGoMe(const GL_NETLizard_3D_Model *map_model, const game_character *gamer, game_character *characters, int start, int count);
// 人工指挥操作 - 停止待命指令
void Game_OperateAIStandBy(const GL_NETLizard_3D_Model *map_model, const game_character *gamer, game_character *characters, int start, int count);
// 计算角色红色圆点准心坐标
int Game_GetRayPointCoord(const GL_NETLizard_3D_Model *map_model, const game_character *character, GLboolean dy, int *scene, nl_vector3_t *cpoint, nl_vector3_t *normal, float *distance);
// 一角色是否可见另一角色
int Game_CharacterCanViewCharacter(const GL_NETLizard_3D_Model *model, const game_character *c1, const game_character *c2);
// 一角色射击另一角色
// 2D 版本 只判断y轴旋转
int Game_ShotCharacter2D(const GL_NETLizard_3D_Model *model, game_character *gamer, game_character *characters, int start, int count);
// 3D版本 线圆柱体碰撞测试
int Game_ShotCharacter(const GL_NETLizard_3D_Model *model, game_character *gamer, game_character *characters, int start, int count, human_body_type *type, nl_vector3_t *c, nl_vector3_t *n);
// 更新角色数组的动作
void Game_UpdateAIAnimation(game_character *characters, int start, int count, long long time, int fps);
// 计算角色在地图中的位置
int Algo_ComputeCharacterPositionInNETLizard3DMap(const GL_NETLizard_3D_Model *map_model, game_character *gamer, const nl_vector3_t *new_v, nl_vector3_t *return_v);
// 计算角色的第三人称视角坐标
int Algo_ComputeThirdPersonPosition(const GL_NETLizard_3D_Model *map_model, const game_character *gamer, float yr, float xr, float tps_factory, int cross, int free_view, float free_yr, float free_xr, gl_vector3_t *v, float *ryr, float *rxr);
// 检测是否进入战斗
void Game_CharacterAttack(const GL_NETLizard_3D_Model *model, game_character *gamer, game_character *characters, int start, int count);
// 复活角色
void Game_AIRelive(const GL_NETLizard_3D_Model *map_model, game_character *characters, int start, int count, long rt, long long game_time);
// 攻击事件
void Game_AttackEvent(const GL_NETLizard_3D_Model *map_model, game_character *characters, int current, int start, int count, long long game_time, list_template *list, list_template *bullets, list_template *sound);
// 随机出生地
int Game_RandStartPosition(const GL_NETLizard_3D_Model *model, game_character *gamer, int max);
// 更新操控角色的动作影响
void Game_HandlePlayerAI(const GL_NETLizard_3D_Model *map_model, game_character *caitlyn, long long time);
// 更新自动AI角色的动作影响
void Game_HandleComputeAI(const GL_NETLizard_3D_Model *map_model, game_character *gamer, long long time);
// 更新指挥AI角色的动作影响
void Game_HandleOperateAI(const GL_NETLizard_3D_Model *map_model, game_character *gamer, long long time);
// 更新触发型AI角色的动作影响
void Game_HandleTriggerAI(const GL_NETLizard_3D_Model *map_model, game_character *gamer, long long time);
// 检测武器的状态
void Game_UpdateWeapon(game_character *gamer, long long game_time);
// 射线与角色碰撞检测
int Algo_RayCharacterCollisionTesting(const game_character *gamer, const game_character *characters, int start, int count, GLboolean dy, int *scene, float *dis, nl_vector3_t *pos);
// 角色之间碰撞检测
int Algo_CharacterCollisionTesting(const GL_NETLizard_3D_Model *model, const game_character *gamer, const nl_vector3_t *new_v, const game_character *characters, int start, int count, int *character_index, nl_vector3_t *rv);
// 射击 生成子弹对象到链表
int Game_WeaponShot(game_character *gamer, list_template *particle_list, list_template *bullets);
// 子弹与角色碰撞测试
int Game_BulletMapCollisionTesting(const GL_NETLizard_3D_Model *model, bullet *bt, float *c_dis, int *c_scene, int *c_item, nl_vector3_t *c, nl_vector3_t *n);
// 子弹与地图碰撞测试
int Game_BulletCharacterCollisionTesting(bullet *bt, game_character *characters, int start, int count, int *c_index, float *c_dis, human_body_type *type, nl_vector3_t *c, nl_vector3_t *n);
// 获取爆炸中与角色的碰撞点和距离以及法线
int Game_BoomAttack(const GL_NETLizard_3D_Model *model, const nl_vector3_t *boom_pos, const game_character *gamer, float *dis, nl_vector3_t *cv, nl_vector3_t *cn, human_body_type *type);
// 计算b在a角色的视角角度
void Game_ComputeCharacterAndCharacterAngle(const game_character *a, const game_character *b, float *y_angle, float *x_angle);
// 角色死亡
void Game_CharacterDeath(game_character *killer, game_character *death);
// 生成一个路线脚本式AI
int Game_MakeScriptAI(const GL_NETLizard_3D_Model *model, game_character *gamer, long long time);
// 处理路线AI
void Game_HandleScriptAI(const GL_NETLizard_3D_Model *map_model, game_character *gamer, long long time);
// 强制移动AI
int Game_HandleForceAI(const GL_NETLizard_3D_Model *map_model, game_character *gamer, long long time);
// 换弹
int Game_ReloadWeapon(weapon *w, long long game_time);

#endif
