#ifndef KARIN_NL_ALGO_H
#define KARIN_NL_ALGO_H

#include "nl_std.h"
#include "nl_gl.h"
#include "math3d/graph.h"

typedef enum _map_collision_testing_result_type
{
	map_out_aabb_type = 0,
	map_only_in_aabb_type,
	map_in_all_planes_and_in_aabb_type,
	map_in_aabb_and_scene_no_planes_type,
	map_in_all_planes_and_in_aabb_but_less_than_collision_distance_type
} map_collision_testing_result_type;

typedef enum _item_collision_testing_result_type
{
	item_in_all_planes_and_in_aabb_type = 0,
	item_only_in_aabb_type,
	item_out_aabb_type,
	item_in_aabb_and_item_no_planes_type,
	item_in_all_planes_and_in_aabb_but_less_than_collision_distance_type,
	item_not_need_collision_testing_type
} item_collision_testing_result_type;

// 取得位于当前模型视图投影矩阵中的场景
int * Algo_GetNETLizard3DMapRenderScenes(const GL_NETLizard_3D_Model *netlizard_3d_model, unsigned int *count, GLfloat frustum[][4]);
// 计算当前坐标与场景地板的交点
int Algo_ComputeFloorCoord(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_s *v, int *scene, float *rglz);
// 地图场景中碰撞测试
// 返回结果场景 -1 表示不在任何场景
// 返回0 不在任何场景 1 只在AABB盒子内 2 不仅在AABB盒子内，还在各个场景碰撞面内
map_collision_testing_result_type Algo_NETLizard3DMapCollisionTesting(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_s *n_xyz, float width, float height, int *scene);
// 场景中物品的碰撞测试
item_collision_testing_result_type Algo_NETLizard3DItemCollisionTesting(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_s *xyz, const nl_vector3_s *n_xyz, float width, float height, int scene, nl_vector3_s *c_normal, int *index);
// 获取物品的顶面坐标
int Algo_GetItemTopCoord(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_s *n_xyz, int scene, float width, float *rglz, int *index, float *height);
// 获取物品的顶面坐标，无场景的情况下
int Algo_GetItemTopCoordForAll(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_s *n_xyz, float *rglz, int *index);
// 点是否在场景盒子内
int Algo_PointInAABBInNETLizard3DMap(const nl_vector3_s *p, const GL_NETLizard_3D_Model *map_model, GLuint scene);
// 不再使用，向上寻找当前位置的的地板坐标，模拟电梯
int Algo_ComputeTopFloorCoord(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_s *n_xyz, int *scene, float *rglz);
void Algo_GetNETLizard3DMapRange(const GL_NETLizard_3D_Model *model, int *scenes, unsigned int count, nl_vector3_s *min, nl_vector3_s *max);
// 射线碰撞测试 绘制准星红点
int Algo_RayCollisionTestingInNETLizard3DMap(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_s *pos, const nl_vector3_s *dir, float width, int *scene, float *distance, nl_vector3_s *c_point, nl_vector3_s *c_normal);
// 两点之间是否彼此可见，模拟射击是否击中
int Algo_PointCanViewPointInNETLizard3DMap(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_s *pos, const nl_vector3_s *pos2, float *distance);
// 地图碰撞测试主函数
int Algo_ComputePositionInNETLizard3DMap(const GL_NETLizard_3D_Model *map_model, const nl_vector3_s *ori_v, const nl_vector3_s *new_v, float cwidth, float cheight, nl_vector3_s *return_v, int *cs, int *ci);
int Algo_GetPointInAABBInNETLizard3DMap(const nl_vector3_s *p, const GL_NETLizard_3D_Model *map_model);
int Algo_UpdateThirdPersonPosition(const GL_NETLizard_3D_Model *map_model, float *xt, float *yt, float *zt, float xp, float yp, float zp, float oxr, float oyr, float yr, float xr, float tps_factory, int scene, int available);
// 计算从start场景到end场景需要经过的场景集合，暂时只计算固定的一条路线
GLuint * Algo_GetMapPathScene(const GL_NETLizard_3D_Model *map_model, GLuint start, GLuint end, GLint *count);
// 计算从start场景到end场景需要经过的BSP面集合，暂时只计算固定的一条路线
GLuint * Algo_GetMapPathBSP(const GL_NETLizard_3D_Model *map_model, GLuint start, GLuint end, GLint *count);
// 计算从start场景到end场景需要经过的场景和BSP面集合，暂时只计算固定的一条路线（场景，bsp，场景，bsp …… 场景）
GLuint * Algo_GetMapPathSceneAndBSP(const GL_NETLizard_3D_Model *map_model, GLuint start, GLuint end, GLint *count);
int Algo_LadderItemCollision(const GL_NETLizard_3D_Model *model, const nl_vector3_s *pos, const nl_vector3_s *new_pos, float width, float height, int index, nl_vector3_s *rpos);
int Algo_LadderItemCollisionFromScene(const GL_NETLizard_3D_Model *model, const nl_vector3_s *pos, const nl_vector3_s *new_pos, float x_a, float y_a, float width, float height, int *scene, int *index, nl_vector3_s *rpos);
int Algo_ComputePositionInNETLizard3DMapNotGravity(const GL_NETLizard_3D_Model *map_model, const nl_vector3_s *ori_v, const nl_vector3_s *new_v, float cwidth, float cheight, nl_vector3_s *return_v, int *cs, int *ci);
int Algo_GetItemOfScene(const GL_NETLizard_3D_Model *model, GLuint item, GLint *r);
int Algo_PointIsCollisionInScene(const GL_NETLizard_3D_Model *model, const nl_vector3_s *pos, float cwidth, float cheight, int *scene, int *item);


int * Algo_GetRE3DMapRenderScenes(const GL_RE3D_Model *netlizard_3d_model, unsigned int *c, GLfloat frustum[][4]);

#endif
