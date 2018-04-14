#include "nl_algo.h"
#include "game_util.h"
#include "math3d/algo.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>

#define UP_NORMAL_LIMIT 0.866025

static int Algo_GetPositionCoordIfCollatedMapWall(const GL_NETLizard_3D_Model *model, float limit, const nl_vector3_t *last_position, const nl_vector3_t *new_position, int scene2, nl_vector3_t *rv, int *rs);
static int Algo_GetTopScene(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_t *new_pos, int *scene, float *rglz);
static int Algo_GetScenePath(const GL_NETLizard_3D_Model *model, GLuint start, GLuint end, int index, GLint *path, GLint *count);
static int Algo_GetSceneAndBSPPath(const GL_NETLizard_3D_Model *model, GLuint start, GLuint end, int index, int bsp_index, GLint *path, GLint *count);

int * Algo_GetNETLizard3DMapRenderScenes(const GL_NETLizard_3D_Model *netlizard_3d_model, unsigned int *c, GLfloat frustum[][4])
{
	if(!netlizard_3d_model)
		return NULL;
	int *scenes = NULL;
	unsigned int i;
	unsigned int count = 0;
	for(i = 0; i < netlizard_3d_model -> count; i++)
	{
		const GL_NETLizard_3D_Mesh *mesh = netlizard_3d_model -> meshes + i;
		int r = Algo_AABBInFrustum(frustum, mesh -> ortho[3], mesh -> ortho[4], mesh -> ortho[5], mesh -> ortho[0], mesh -> ortho[1], mesh -> ortho[2]);
		if(r)
		{
			if(!scenes)
			{
				scenes = NEW_II(unsigned int, netlizard_3d_model -> count);
			}
			scenes[count] = i;
			count++;
		}
	}
	if(c)
		*c = count;
	int *s = NEW_II(int, count);
	memcpy(s, scenes, sizeof(unsigned int) * count);
	free(scenes);
	return s;
}

int Algo_ComputeFloorCoord(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_t *new_pos, int *scene, float *rglz)
{
	if(!netlizard_3d_model || !scene || !new_pos)
		return 0;
	const GL_NETLizard_3D_Mesh *mesh = netlizard_3d_model -> meshes + *scene;
	unsigned int j;
	for(j = 0; j < mesh -> plane_count; j++)
	{
		// 计算当前位置的地板坐标
		if(mesh -> plane[j].normal[2] > UP_NORMAL_LIMIT)
		{
			plane_t pla = {
				{mesh -> plane[j].position[0], mesh -> plane[j].position[1], mesh -> plane[j].position[2]},
				{mesh -> plane[j].normal[0], mesh -> plane[j].normal[1], mesh -> plane[j].normal[2]}
			};
			nl_vector3_t point = {0.0, 0.0, 0.0};
			nl_vector3_t dir = pla.normal;
			dir.z = - dir.z;
			line_t l = {*new_pos, dir};
			Math3D_LineToPlaneIntersect(&l, &pla, &point);
			if(rglz)
				*rglz = point.z;
			return 1;
		}
	}

	// 对于无地板的场景，如空中的场景，获取该场景下方的场景，直到获取有地板的场景，从而计算出地板坐标
	// 获取该场景盒子最小z坐标
	float nglz = mesh -> ortho[5];
	int *scenes = NEW_II(int, netlizard_3d_model -> count);
	unsigned int i;
	for(i = 0; i < netlizard_3d_model -> count; i++)
		scenes[i] = -1;
	int cur = 0;
	scenes[cur] = *scene;
	cur++;
	for(i = 0; i < netlizard_3d_model -> count; i++)
	{
		unsigned int l;
		int checked = 0;
		for(l = 0; l < netlizard_3d_model -> count; l++)
		{
			if(scenes[l] == -1)
			{
				checked = 0;
				break;
			}
			if(scenes[l] == (int)i)
			{
				checked = 1;
				break;
			}
			checked = 0;
		}
		if(checked)
			continue;
		const GL_NETLizard_3D_Mesh *next_mesh = netlizard_3d_model -> meshes + i;
		nl_vector3_t new_position = {new_pos -> x, new_pos -> y, nglz};
		aabb_t aabb = {
			{next_mesh -> ortho[3], next_mesh -> ortho[4], next_mesh -> ortho[5]},
			{next_mesh -> ortho[0], next_mesh -> ortho[1], next_mesh -> ortho[2]}
		};
		if(!Math3D_PointInAABB(&new_position, &aabb))
			continue;

		unsigned int k;
		for(k = 0; k < next_mesh -> plane_count; k++)
		{
			// 计算当前位置的地板坐标
			if(next_mesh -> plane[k].normal[2] > UP_NORMAL_LIMIT)
			{
				plane_t pla = {
					{next_mesh -> plane[k].position[0], next_mesh -> plane[k].position[1], next_mesh -> plane[k].position[2]},
					{next_mesh -> plane[k].normal[0], next_mesh -> plane[k].normal[1], next_mesh -> plane[k].normal[2]}
				};
				nl_vector3_t point = {0.0, 0.0, 0.0};
				nl_vector3_t dir = pla.normal;
				dir.z = - dir.z;
				line_t l = {new_position, dir};
				Math3D_LineToPlaneIntersect(&l, &pla, &point);
				if(rglz)
					*rglz = point.z;
				*scene = i;
				return 1;
			}
		}
		scenes[cur] = i;
		cur++;
		nglz = next_mesh -> ortho[5];
		i = 0;
	}
	free(scenes);
	if(scene)
		*scene = -1;

	return 0;
}

// 0 - 在场景外 返回 -1
// 1 - 仅在场景AABB内
// 2 - 在场景AABB内，且在场景所有碰撞面内
// 3 - 仅在场景AABB内，但是该场景无碰撞面数据
// 4 - 在场景AABB内，且在场景所有碰撞面内，但是与某一碰撞面的距离小于测试值
map_collision_testing_result_type Algo_NETLizard3DMapCollisionTesting(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_t *new_position, float width, float height, int *scene)
{
	if(!netlizard_3d_model || !new_position)
		return map_out_aabb_type;
	map_collision_testing_result_type res = map_out_aabb_type;

	float lamda = 0.0;
	unsigned int *scenes = NEW_II(int, netlizard_3d_model -> count);
	unsigned int c = 0;
	unsigned int i;
	for(i = 0; i < netlizard_3d_model -> count; i++)
	{
		const GL_NETLizard_3D_Mesh *mesh = netlizard_3d_model -> meshes + i;
		aabb_t aabb = {
			{mesh -> ortho[3], mesh -> ortho[4], mesh -> ortho[5]},
			{mesh -> ortho[0], mesh -> ortho[1], mesh -> ortho[2]}
		};
		if(Math3D_PointInAABB(new_position, &aabb))
		{
			unsigned int n = 0;
			for(n = 0; n < netlizard_3d_model -> count; n++)
			{
				if(scenes[n] == 0)
					break;
				if(scenes[n] == i)
					break;
			}
			if(n == c)
			{
				scenes[c] = i + 1;
				c++;
			}
		}
	}
	if(c == 0)
	{
		return map_out_aabb_type;
		free(scenes);
	}
	int s = -1;
	if(c > 1)
	{
		s = scenes[0] - 1;
		for(i = 1; i < c; i++)
		{
			const GL_NETLizard_3D_Mesh *mesh = netlizard_3d_model -> meshes + (scenes[i] - 1);
			if(mesh -> plane_count != 0)
			{
				s = scenes[i] - 1;
				break;
			}
		}
	}
	else
		s = scenes[0] - 1;
	free(scenes);
	if(s == -1)
		return map_out_aabb_type;
	if(scene)
		*scene = s;
	const GL_NETLizard_3D_Mesh *mesh = netlizard_3d_model -> meshes + s;
	res = map_only_in_aabb_type;
	if(mesh -> plane)
	{
		unsigned int j;
		for(j = 0; j < mesh -> plane_count; j++)
		{
			plane_t plane = {
				{mesh -> plane[j].position[0], mesh -> plane[j].position[1], mesh -> plane[j].position[2]},
				{mesh -> plane[j].normal[0], mesh -> plane[j].normal[1], mesh -> plane[j].normal[2]}
			};
			line_t l = {*new_position, {-mesh -> plane[j].normal[0], -mesh -> plane[j].normal[1], -mesh -> plane[j].normal[2]}};
			int r = Math3D_LineToPlaneCollision(&l, &plane, &lamda, NULL);
			if(r != 1)
			{
				res = map_only_in_aabb_type;
				return res;
			}
			float limit = 0;
			int po = 0;
			if(mesh -> plane[j].normal[2] > UP_NORMAL_LIMIT)
				limit = 0;
			else if(mesh -> plane[j].normal[2] < -UP_NORMAL_LIMIT)
				limit = height;
			else
			{
				limit = width;
				po = 1;
			}
			if(lamda < limit && po)
				res = map_in_all_planes_and_in_aabb_but_less_than_collision_distance_type;
		}
		if(res == map_only_in_aabb_type)
			res = map_in_all_planes_and_in_aabb_type;
		return res;
	}
	else
	{
		res = map_in_aabb_and_scene_no_planes_type;
		return res;
	}
	return map_out_aabb_type;
}

// 0 在AABB内，并在所有碰撞面内
// 1 仅在AABB内，不在所有碰撞面内
// 2 不在AABB内，也不在所有碰撞面内
// 3 在AABB内，但是没有碰撞面数据
// 4 不在AABB内，也不在所有碰撞面内, 但是距离太近
// 5 特殊物品，不进行碰撞测试
item_collision_testing_result_type Algo_NETLizard3DItemCollisionTesting(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_t *pos, const nl_vector3_t *new_pos, float width, float height, int scene, nl_vector3_t *c_normal, int *index)
{
	if(!netlizard_3d_model || !pos || !new_pos)
		return item_in_all_planes_and_in_aabb_type;

	int res = item_only_in_aabb_type;
	const GL_NETLizard_3D_Mesh *mesh = netlizard_3d_model -> meshes + scene;
	//float lamda = 0.0;
	nl_vector3_t position = {pos -> x, pos -> y, pos -> z - height};
	nl_vector3_t new_position = {new_pos -> x, new_pos -> y, new_pos -> z - height};
	nl_vector3_t direction = Vector3_SubtractVector3(&new_position, &position);
	Vector3_Normalize(&direction);
	line_t line = {new_position, direction};
	unsigned int k;
	for(k = mesh -> item_index_range[0]; k < mesh -> item_index_range[1]; k++)
	{
		const GL_NETLizard_3D_Item_Mesh *im = netlizard_3d_model -> item_meshes + k;
		aabb_t aabb = {
			{im -> item_mesh.ortho[3] - width + im -> pos[0], im -> item_mesh.ortho[4] - width + im -> pos[1], im -> item_mesh.ortho[5] + im -> pos[2]},
			{im -> item_mesh.ortho[0] + width + im -> pos[0], im -> item_mesh.ortho[1] + width + im -> pos[1], im -> item_mesh.ortho[2] + im -> pos[2]}
		};
		// 检测新位置是否在地图中某一物品盒子内
		if(Math3D_PointInAABB(&new_position, &aabb))
		{
			res = item_only_in_aabb_type;
			//printfi(im -> item_type);
			if(index)
				*index = k;
			if(im -> item_type & Item_Weapon_Type || im -> item_type & Item_Tiny_Type || im -> item_type & Item_Box_Type)
			{
				if(index)
					*index = k;
				return item_not_need_collision_testing_type;
			}
			// 检测新位置是否在物品盒子中真实场景内
			if(im -> item_mesh.plane_count > 0)
			{
				const GL_NETLizard_3D_Plane *planes = im -> item_mesh.plane;
				unsigned int j;
				for(j = 0; j < im -> item_mesh.plane_count; j++)
				{
					plane_t plane = {
						{planes[j].position[0] + im -> pos[0], planes[j].position[1] + im -> pos[1], planes[j].position[2] + im -> pos[2]},
						{-planes[j].normal[0], -planes[j].normal[1], -planes[j].normal[2]}
					};
					nl_vector3_t point = {0.0, 0.0, 0.0};
					float lamda = 0.0;
					int r;
					r = Math3D_LineToPlaneIntersect(&line, &plane, &point);
					if(r && Math3D_PointInAABB(&point, &aabb))
					{
						nl_vector3_t normal;
						r = Math3D_LineToPlaneCollision(&line, &plane, &lamda, &normal);
						//if(res > 0 && lamda <= width)
						if(c_normal)
						{
							c_normal -> x = -normal.x;
							c_normal -> y = -normal.y;
							c_normal -> z = -normal.z;
						}
						if(index)
							*index = k;
						res = item_in_all_planes_and_in_aabb_type;
						return res;
					}
				}

				if(index)
					*index = k;
				res = item_only_in_aabb_type;
				return res;
			}
			else
			{
				res = item_in_aabb_and_item_no_planes_type;
				return res;
			}
		}
	}

	if(index)
		*index = -1;
	res = item_out_aabb_type;
	return res;
}

int Algo_GetItemTopCoord(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_t *new_position, int scene, float width, float *rglz, int *index, float *height)
{
	if(!netlizard_3d_model || !new_position)
		return 0;
	const GL_NETLizard_3D_Mesh *mesh = netlizard_3d_model -> meshes + scene;
	float final_z = 0.0;
	float lamda = 0.0;
	int available = 0;
	float h = 0.0;
	unsigned int a;
	for(a = mesh -> item_index_range[0]; a < mesh -> item_index_range[1]; a++)
	{
		const GL_NETLizard_3D_Item_Mesh *im = netlizard_3d_model -> item_meshes + a;
		if(im -> item_type != Item_Elevator_Type && new_position -> z < im -> item_mesh.ortho[2] + im -> pos[2])
			continue;
		const GL_NETLizard_3D_Plane *planes = im -> item_mesh.plane;
		if(im -> item_type & Item_DoorV_Type || im -> item_type & Item_DoorH_Type || im -> item_type & Item_Weapon_Type || im -> item_type & Item_Tiny_Type || im -> item_type & Item_Box_Type)
			continue;
		aabb_t aabb = {
			{im -> item_mesh.ortho[3] - width + im -> pos[0], im -> item_mesh.ortho[4] - width + im -> pos[1], im -> item_mesh.ortho[5] + im -> pos[2]},
			{im -> item_mesh.ortho[0] + width + im -> pos[0], im -> item_mesh.ortho[1] + width + im -> pos[1], im -> item_mesh.ortho[2] + im -> pos[2]}
		};
		// 检测新位置是否在地图中某一物品盒子内
		if(Math3D_PointInAABB2D(new_position, &aabb))
		{
			unsigned int j;
			for(j = 0; j < im -> item_mesh.plane_count; j++)
			{
				if(planes[j].normal[2] > UP_NORMAL_LIMIT)
				{
					plane_t plane = {
						{planes[j].position[0] + im -> pos[0], planes[j].position[1] + im -> pos[1], planes[j].position[2] + im -> pos[2]},
						{planes[j].normal[0], planes[j].normal[1], planes[j].normal[2]}
					};
					nl_vector3_t point = {0.0, 0.0, 0.0};
					nl_vector3_t dir = plane.normal;
					dir.z = - dir.z;
					line_t l = {*new_position, dir};
					int res = Math3D_LineToPlaneIntersect(&l, &plane, &point);
					if(res && Math3D_PointInAABB(&point, &aabb))// && point.z <= new_position -> z)
					{
						float d = 0.0;
						nl_vector3_t n = {0.0, 0.0, 0.0};
						res = Math3D_LineToPlaneCollision(&l, &plane, &d, &n);
						if(available == 0)
						{
							final_z = point.z;
							lamda = d;
							if(*index)
								*index = a;
							h = aabb.max_position.z - aabb.min_position.z;
							available = 1;
						}
						else
						{
							if(lamda > d)
							{
								final_z = point.z;
								lamda = d;
								if(*index)
									*index = a;
								h = aabb.max_position.z - aabb.min_position.z;
							}
						}
					}
				}
			}
			break;
		}
	}
	if(available)
	{
		if(rglz)
			*rglz = final_z + 1;
		if(height)
			*height = h;
		return 1;
	}
	else
		return 0;
}

int Algo_GetItemTopCoordForAll(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_t *new_position, float *rglz, int *index)
{
	if(!netlizard_3d_model || !new_position)
		return 0;
	float final_z = 0.0;
	float height = 0.0; 
	float lamda = 0.0; 
	int available = 0;
	int ii = -1;
	unsigned int a;
	for(a = 0; a < netlizard_3d_model -> item_count; a++)
	{
		const GL_NETLizard_3D_Item_Mesh *im = netlizard_3d_model -> item_meshes + a;
		const GL_NETLizard_3D_Plane *planes = im -> item_mesh.plane;
		if(im -> item_type & Item_DoorV_Type || im -> item_type & Item_DoorH_Type || im -> item_type & Item_Weapon_Type || im -> item_type & Item_Tiny_Type || im -> item_type & Item_Box_Type)
			continue;
		aabb_t aabb = {
			{im -> item_mesh.ortho[3] + im -> pos[0], im -> item_mesh.ortho[4] + im -> pos[1], im -> item_mesh.ortho[5] + im -> pos[2]},
			{im -> item_mesh.ortho[0] + im -> pos[0], im -> item_mesh.ortho[1] + im -> pos[1], im -> item_mesh.ortho[2] + im -> pos[2]}
		};
		nl_vector3_t *v1 = &(aabb.min_position);
		nl_vector3_t *v2 = &(aabb.max_position);
		// 检测新位置是否在地图中某一物品盒子内
		if(Math3D_PointInAABB2D(new_position, &aabb))
		{
			unsigned int j;
			for(j = 0; j < im -> item_mesh.plane_count; j++)
			{
				if(planes[j].normal[2] > UP_NORMAL_LIMIT)
				{
					plane_t plane = {
						{planes[j].position[0] + im -> pos[0], planes[j].position[1] + im -> pos[1], planes[j].position[2] + im -> pos[2]},
						{planes[j].normal[0], planes[j].normal[1], planes[j].normal[2]}
					};
					nl_vector3_t point = {0.0, 0.0, 0.0};
					nl_vector3_t dir = plane.normal;
					dir.z = - dir.z;
					line_t l = {*new_position, dir};
					int res = Math3D_LineToPlaneIntersect(&l, &plane, &point);
					if(res && Math3D_PointInAABB(&point, &aabb))
					{
						float d = 0.0;
						nl_vector3_t n = {0.0, 0.0, 0.0};
						res = Math3D_LineToPlaneCollision(&l, &plane, &d, &n);
						if(available == 0)
						{
							final_z = point.z;
							lamda = d;
							height = v2 -> z - v1 -> z;
							ii = a;
						}
						if(lamda > d)
						{
							final_z = point.z;
							lamda = d;
							height = v2 -> z - v1 -> z;
							ii = a;
						}
					}
				}
			}
			break;
		}
	}
	if(index)
		*index = ii;
	if(available)
	{
		if(rglz)
			*rglz = final_z + 1;// + 1;
		return 1;
	}
	else
		return 0;
}

int Algo_PointInAABBInNETLizard3DMap(const nl_vector3_t *position, const GL_NETLizard_3D_Model *map_model, GLuint scene)
{
	if(!map_model || !position)
		return 0;
	if(scene >= map_model -> count)
		return 0;
	const GL_NETLizard_3D_Mesh *mesh = map_model -> meshes + scene;
	aabb_t aabb = {
		{mesh -> ortho[3], mesh -> ortho[4], mesh -> ortho[5]},
		{mesh -> ortho[0], mesh -> ortho[1], mesh -> ortho[2]}
	};
	return Math3D_PointInAABB(position, &aabb);
}

int Algo_ComputeTopFloorCoord(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_t *n_xyz, int *scene, float *rglz)
{
	if(!netlizard_3d_model || !scene || !n_xyz)
		return 0;
	float nglx = n_xyz -> x;
	float ngly = n_xyz -> y;
	float nglz = n_xyz -> z;
	const GL_NETLizard_3D_Mesh *mesh = netlizard_3d_model -> meshes + *scene;

	// 对于无地板的场景，如空中的场景，获取该场景下方的场景，直到获取有地板的场景，从而计算出地板坐标
	// 获取该场景盒子最小z坐标
	float nrglz = nglz;
	const float y = nglz;
	float delta = - FLT_MAX;
	nglz = mesh -> ortho[2];
	int res = 0;
	int s = *scene;
	int i;
	for(i = 0; i < (int)netlizard_3d_model -> count; i++)
	{
		if(i == *scene)
			continue;
		const GL_NETLizard_3D_Mesh *next_mesh = netlizard_3d_model -> meshes + i;
		nl_vector3_t new_position = {nglx, ngly, nglz};
		aabb_t aabb = {
			{next_mesh -> ortho[3], next_mesh -> ortho[4], next_mesh -> ortho[5]},
			{next_mesh -> ortho[0], next_mesh -> ortho[1], next_mesh -> ortho[2]}
		};
		if(!Math3D_PointInAABB2D(&new_position, &aabb))
			continue;

		unsigned int k;
		for(k = 0; k < next_mesh -> plane_count; k++)
		{
			// 计算当前位置的地板坐标
			if(next_mesh -> plane[k].normal[2] > UP_NORMAL_LIMIT)
			{
				plane_t pla = {
					{next_mesh -> plane[k].position[0], next_mesh -> plane[k].position[1], next_mesh -> plane[k].position[2]},
					{next_mesh -> plane[k].normal[0], next_mesh -> plane[k].normal[1], next_mesh -> plane[k].normal[2]}
				};
				nl_vector3_t point = {0.0, 0.0, 0.0};
				nl_vector3_t new_pos = {nglx, ngly, nglz};
				nl_vector3_t dir = pla.normal;
				dir.z = - dir.z;
				line_t l = {new_pos, dir};
				Math3D_LineToPlaneIntersect(&l, &pla, &point);
				{
					float d = point.z - y;
					if((d < 0 && d > delta))
					{
						nrglz = point.z;
						s = i;
						delta = d;
						res = 1;
					}
				}
			}
		}
		ngly = next_mesh -> ortho[2];
	}
	if(nrglz)
	{
		if(scene)
			*scene = s;
		if(rglz)
			*rglz = nrglz;
	}

	return res;
}

void Algo_GetNETLizard3DMapRange(const GL_NETLizard_3D_Model *model, int *scenes, unsigned int count, nl_vector3_t *min, nl_vector3_t *max)
{
	if(!model || !min || !max)
		return;
	if(model -> count == 0)
		return;
	float min_x = 0.0;
	float min_y = 0.0;
	float min_z = 0.0;
	float max_x = 0.0;
	float max_y = 0.0;
	float max_z = 0.0;
	unsigned int i;
	unsigned int c;
	if(scenes)
		c = count;
	else
		c = model -> count;
	for(i = 0; i < c; i++)
	{
		int s;
		if(scenes)
			s = scenes[i];
		else
			s = i;
		const GL_NETLizard_3D_Mesh *mesh = model -> meshes + s;
		if(i == 0)
		{
			min_x = mesh -> ortho[3];
			min_y = mesh -> ortho[4];
			min_z = mesh -> ortho[5];
			max_x = mesh -> ortho[0];
			max_y = mesh -> ortho[1];
			max_z = mesh -> ortho[2];
			continue;
		}
		if(mesh -> ortho[3] < min_x)
			min_x = mesh -> ortho[3];
		if(mesh -> ortho[4] < min_y)
			min_y = mesh -> ortho[4];
		if(mesh -> ortho[5] < min_z)
			min_z = mesh -> ortho[5];

		if(mesh -> ortho[0] > max_x)
			max_x = mesh -> ortho[0];
		if(mesh -> ortho[1] > max_y)
			max_y = mesh -> ortho[1];
		if(mesh -> ortho[2] > max_z)
			max_z = mesh -> ortho[2];
	} 
	min -> x = min_x;
	min -> y = min_y;
	min -> z = min_z;
	max -> x = max_x;
	max -> y = max_y;
	max -> z = max_z;
}

int Algo_RayCollisionTestingInNETLizard3DMap(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_t *position, const nl_vector3_t *direction, float width, int *scene, float *distance, nl_vector3_t *c_point, nl_vector3_t *normal)
{
	if(!netlizard_3d_model || !position || !direction)
		return 0;
	int res = 0;
	int s = -1;
	nl_vector3_t vc = {0.0, 0.0, 0.0};
	nl_vector3_t vn = {0.0, 0.0, 0.0};
	float lamda = 0.0;
	line_t line = {*position, *direction};
	unsigned int i;
	for(i = 0; i < netlizard_3d_model -> count; i++)
	{
		const GL_NETLizard_3D_Mesh *mesh = netlizard_3d_model -> meshes + i;
		aabb_t aabb = {
			{mesh -> ortho[3], mesh -> ortho[4], mesh -> ortho[5]},
			{mesh -> ortho[0], mesh -> ortho[1], mesh -> ortho[2]}
		};

		if(mesh -> plane)
		{
			unsigned int j;
			for(j = 0; j < mesh -> plane_count; j++)
			{
				plane_t plane = {
					{mesh -> plane[j].position[0], mesh -> plane[j].position[1], mesh -> plane[j].position[2]},
					{mesh -> plane[j].normal[0], mesh -> plane[j].normal[1], mesh -> plane[j].normal[2]}
				};
				float l = 0.0;
				nl_vector3_t nml = {0.0, 0.0, 0.0};
				int r = Math3D_LineToPlaneCollision(&line, &plane, &l, &nml);
				if(r != 1)
					continue;
				nl_vector3_t point = {0.0, 0.0, 0.0};
				Math3D_LineToPlaneIntersect(&line, &plane, &point);
				if(!Math3D_PointInAABB(&point, &aabb))
					continue;
				if(res == 0)
				{
					s = i;
					vc = point;
					vn = nml;
					lamda = l;
					res = 1;
				}
				else
				{
					if(l < lamda)
					{
						s = i;
						vc = point;
						vn = nml;
						lamda = l;
					}
				}
			}
		}
	}

	int item = -1;
	if(netlizard_3d_model -> item_meshes)
	{
		unsigned int k;
		for(k = 0; k < netlizard_3d_model -> item_count; k++)
		{
			const GL_NETLizard_3D_Item_Mesh *im = netlizard_3d_model -> item_meshes + k;
			if(im -> item_mesh.plane_count > 0)
			{
				const GL_NETLizard_3D_Plane *planes = im -> item_mesh.plane;
				aabb_t aabb = {
					{im -> item_mesh.ortho[3] - width + im -> pos[0], im -> item_mesh.ortho[4] - width + im -> pos[1], im -> item_mesh.ortho[5] + im -> pos[2]},
					{im -> item_mesh.ortho[0] + width + im -> pos[0], im -> item_mesh.ortho[1] + width + im -> pos[1], im -> item_mesh.ortho[2] + im -> pos[2]}
				};
				unsigned int j;
				for(j = 0; j < im -> item_mesh.plane_count; j++)
				{
					plane_t plane = {
						{planes[j].position[0] + im -> pos[0], planes[j].position[1] + im -> pos[1], planes[j].position[2] + im -> pos[2]},
						{planes[j].normal[0], planes[j].normal[1], planes[j].normal[2]}
					};
					nl_vector3_t nml = {0.0, 0.0, 0.0};
					float l = 0.0;
					int r = Math3D_LineToPlaneCollision(&line, &plane, &l, &nml);
					if(r != 1)
						continue;
					nl_vector3_t point = {0.0, 0.0, 0.0};
					r = Math3D_LineToPlaneIntersect(&line, &plane, &point);
					if(!Math3D_PointInAABB(&point, &aabb))
						continue;
					if(res == 0)
					{
						vc = point;
						lamda = l;
						item = k;
						vn = nml;
						res = 1;
					}
					else
					{
						if(l < lamda)
						{
							vc = point;
							lamda = l;
							item = k;
							vn = nml;
						}
					}
				}
			}
		}
	}

	if(res)
	{
		if(c_point)
		{
			c_point -> x = vc.x - direction -> x * width;
			c_point -> y = vc.y - direction -> y * width;
			c_point -> z = vc.z - direction -> z * width;
		}
		if(normal)
		{
			*normal = vn;
		}
		if(distance)
			*distance = lamda - width;
		if(scene)
		{
			if(item != -1)
			{
				if(Algo_GetItemOfScene(netlizard_3d_model, item, &s))
					*scene = s;
			}
			else
				*scene = s;
		}
	}
	return res;
}

/*
 * 0 - 之间有遮挡
 * 1 - 彼此可见
 */
int Algo_PointCanViewPointInNETLizard3DMap(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_t *pos, const nl_vector3_t *pos2, float *distance)
{
	if(!netlizard_3d_model || !pos || !pos2)
		return 0;
	nl_vector3_t dir = Vector3_SubtractVector3(pos2, pos);
	if(distance)
		*distance = Vector3_Mag(&dir);
	Vector3_Normalize(&dir);

	line_t line = {*pos, dir};
	float minx = KARIN_MIN(pos -> x, pos2 -> x);
	float miny = KARIN_MIN(pos -> y, pos2 -> y);
	float minz = KARIN_MIN(pos -> z, pos2 -> z);
	float maxx = KARIN_MAX(pos -> x, pos2 -> x);
	float maxy = KARIN_MAX(pos -> y, pos2 -> y);
	float maxz = KARIN_MAX(pos -> z, pos2 -> z);
	aabb_t pos_aabb = {
		{minx, miny, minz},
		{maxx, maxy, maxz}
	};
	unsigned int i;
	for(i = 0; i < netlizard_3d_model -> count; i++)
	{
		const GL_NETLizard_3D_Mesh *mesh = netlizard_3d_model -> meshes + i;
		aabb_t aabb = {
			{mesh -> ortho[3], mesh -> ortho[4], mesh -> ortho[5]},
			{mesh -> ortho[0], mesh -> ortho[1], mesh -> ortho[2]}
		};

		if(mesh -> plane)
		{
			unsigned int j;
			for(j = 0; j < mesh -> plane_count; j++)
			{
				plane_t plane = {
					{mesh -> plane[j].position[0], mesh -> plane[j].position[1], mesh -> plane[j].position[2]},
					{mesh -> plane[j].normal[0], mesh -> plane[j].normal[1], mesh -> plane[j].normal[2]}
				};
				int r = Math3D_LineToPlaneCollision(&line, &plane, NULL, NULL);
				if(r != 1)
					continue;
				nl_vector3_t point = {0.0, 0.0, 0.0};
				Math3D_LineToPlaneIntersect(&line, &plane, &point);
				if(!Math3D_PointInAABB(&point, &aabb))
					continue;
				if(Math3D_PointInAABB(&point, &pos_aabb))
					return 0;
			}
		}
	}

	if(netlizard_3d_model -> item_meshes)
	{
		unsigned int k;
		for(k = 0; k < netlizard_3d_model -> item_count; k++)
		{
			const GL_NETLizard_3D_Item_Mesh *im = netlizard_3d_model -> item_meshes + k;
			if(im -> item_mesh.plane_count > 0)
			{
				const GL_NETLizard_3D_Plane *planes = im -> item_mesh.plane;
				aabb_t aabb = {
					{im -> item_mesh.ortho[3] + im -> pos[0], im -> item_mesh.ortho[4] + im -> pos[1], im -> item_mesh.ortho[5] + im -> pos[2]},
					{im -> item_mesh.ortho[0] + im -> pos[0], im -> item_mesh.ortho[1] + im -> pos[1], im -> item_mesh.ortho[2] + im -> pos[2]}
				};
				unsigned int j;
				for(j = 0; j < im -> item_mesh.plane_count; j++)
				{
					plane_t plane = {
						{planes[j].position[0] + im -> pos[0], planes[j].position[1] + im -> pos[1], planes[j].position[2] + im -> pos[2]},
						{planes[j].normal[0], planes[j].normal[1], planes[j].normal[2]}
					};
					int r = Math3D_LineToPlaneCollision(&line, &plane, NULL, NULL);
					if(r != 1)
						continue;
					nl_vector3_t point = {0.0, 0.0, 0.0};
					r = Math3D_LineToPlaneIntersect(&line, &plane, &point);
					if(!Math3D_PointInAABB(&point, &aabb))
						continue;
					if(Math3D_PointInAABB(&point, &pos_aabb))
						return 0;
				}
			}
		}
	}
	return 1;
}

/*
 * 1 - 先对新位置进行与地图各场景的碰撞测试
 * 计算出新位置所在场景和是否与场景盒子发生碰撞
 * 1 - 2 如果计算出所在场景，便于场景中的物品进行碰撞测试
 * 如果产生碰撞，则新位置无效
 * 1 - 2 - 3 如果没有碰撞，则计算当前新位置与场景地板垂直相交点，计算着地坐标
 * 其间如果当前场景无地板平面，则找出该场景下方的场景，查找地板平面，如果还没有，则继续向下寻找，直到找到下方带有地板平面的场景，重新改变当前场景
 * 1 - 2 - 3 - 4 在新场景中的新位置与场景中物品进行碰撞测试
 * 1 - 2 - 3 - 4 - 5 无论是否产生碰撞，都要计算当前新位置是否在场景中某一物品上方，从而计算出新的地板坐标
 * 1 - 2 - 3 如果无法找到垂直方向上的所有场景的地板平面，则直接计算与场景中物品的上方平面是否有碰撞
 * 如果有，则物品顶面坐标作为地板坐标（针对Shadow of Egypt 3D游戏 level 10中浮桥，所在场景0中垂直方向没有地板平面，人物在浮桥物品的上方行走）
 *
 * 2 如果新位置没有在任何场景内（即使在场景盒子中，但没有与各碰撞面相交），直接计算新位置是否在场景物品上，从而计算出物品的顶面坐标作为地板坐标（Shadow of Egypt 3D中 level 8 9 12 skyline，场景无碰撞面，直接计算浮桥的顶面坐标）
 * 3 再其他情况下，如果新位置没有在任何场景内（即使在场景盒子中，但没有与各碰撞面相交），新位置直接使用，类似于穿越（由于当前视角相机是一个点，而不是面或体，在Shadow of Egypt 3D中 level 5 8 9 10 12走浮桥时，防止位于浮桥间隔空间处掉落的情况）
 */
int Algo_ComputePositionInNETLizard3DMap(const GL_NETLizard_3D_Model *map_model, const nl_vector3_t *ori_v, const nl_vector3_t *new_v, float cwidth, float cheight, nl_vector3_t *return_v, int *cs, int *ci)
{
	if(!map_model || !ori_v || !new_v || !return_v)
		return 0;
	int scene = -1;
	float rglz = 0.0;
	float h = 0.0;
	int currentindex = -1;
	int currentscene = -1;
	if(cs)
		currentscene = *cs;
	nl_vector3_t v1 = *ori_v;
	nl_vector3_t v2 = *new_v;
	nl_vector3_t v = v1;

	map_collision_testing_result_type res = Algo_NETLizard3DMapCollisionTesting(map_model, &v2, cwidth, cheight, &scene);
	if(res == map_out_aabb_type && Algo_NETLizard3DMapCollisionTesting(map_model, &v1, cwidth, cheight, NULL) == map_out_aabb_type)
	{
		float nz = 0.0;
		int ns = -1;
		if(Algo_GetTopScene(map_model, &v2, &ns, &nz))
		{
			v2.z = nz;
			res = Algo_NETLizard3DMapCollisionTesting(map_model, &v2, cwidth, cheight, &scene);
		}
		else
			return 0;
	}

	if(res == map_in_all_planes_and_in_aabb_type)
	{
		currentscene = scene;
		nl_vector3_t normal = {0.0, 0.0, 0.0};
		if(Algo_NETLizard3DItemCollisionTesting(map_model, &v1, &v2, cwidth, cheight - 1, currentscene, &normal, &currentindex))
		{
			if(Algo_ComputeFloorCoord(map_model, &v2, &scene, &rglz))
			{
				nl_vector3_t vt = v2;
				//vt.z = v1.z;//2017 06 27 commit // 2017 6 20 replace
				v1.z = rglz;
				if(/* 1 || */currentscene != scene)
				{
					currentscene = scene;
					currentindex = -1;
					if(Algo_NETLizard3DItemCollisionTesting(map_model, &v1, &v2, cwidth, -1, currentscene, &normal, &currentindex))
					{
						vt.z = map_model -> meshes[currentscene].ortho[2];
						// vt.y = v1.y; 1017 6 20 replace
					}
					else
					{
					}
				}
				if(Algo_GetItemTopCoord(map_model, &vt, scene, cwidth, &rglz, &currentindex, &h))
				{
					v1.z = rglz;
				}
				v.x = v2.x;
				v.y = v2.y;
				v.z = v1.z + cheight;
			}
			else
			{
				if(Algo_GetItemTopCoord(map_model, &v2, currentscene, cwidth, &rglz, &currentindex, &h))
				{
					v.x = v2.x;
					v.y = v2.y;
					v.z = rglz;
					v.z = v.z + cheight;
				}
				else
				{
					v.x = new_v -> x; //xp
					v.y = new_v -> y; //yp
					v.z = new_v -> z; //zp
				}
			}
		}
		else
		{
			//else printf("%f %f %f\n", normal[0], normal[1], normal[2]);
		}
	}
	else if(res == map_in_aabb_and_scene_no_planes_type)
	{
		currentscene = scene;
		if(Algo_GetItemTopCoord(map_model, &v2, currentscene, cwidth, &rglz, &currentindex, &h))
		{
			v.x = v2.x;
			v.y = v2.y;
			v.z = rglz;
			v.z = v.z + cheight;
		}
		else
		{
			/*
				 v.x = new_v -> x; //xp
				 v.y = new_v -> y; //zp
				 const GL_NETLizard_3D_Mesh *mesh = map_model -> meshes + currentscene;
				 v.z = mesh -> ortho[5] + cheight;
				 */
		}
	}
	else if(res == map_only_in_aabb_type)
	{
		return 0;
	}
	else if(res == map_in_all_planes_and_in_aabb_but_less_than_collision_distance_type)
	{
		int s = -1;
		nl_vector3_t rv = {0.0, 0.0, 0.0};
		int nr = Algo_GetPositionCoordIfCollatedMapWall(map_model, cwidth, &v1, &v2, currentscene, &rv, &s);
		if(nr)
		{
			currentscene = s;
			nl_vector3_t normal = {0.0, 0.0, 0.0};
			if(Algo_NETLizard3DItemCollisionTesting(map_model, &v1, &rv, cwidth, cheight - 1, currentscene, &normal, &currentindex))
			{
				if(Algo_ComputeFloorCoord(map_model, &rv, &scene, &rglz))
				{
					nl_vector3_t vt = rv;
					//vt.z = v1.z;//2017 06 27 commit // 2017 6 20 replace
					v1.z = rglz;
					if(/* 1 || */currentscene != scene)
					{
						currentscene = scene;
						currentindex = -1;
						if(Algo_NETLizard3DItemCollisionTesting(map_model, &v1, &rv, cwidth, -1, currentscene, &normal, &currentindex))
						{
							vt.z = map_model -> meshes[currentscene].ortho[2];
							// vt.y = v1.y; 1017 6 20 replace
						}
					}
					if(Algo_GetItemTopCoord(map_model, &vt, scene, cwidth, &rglz, &currentindex, &h))
					{
						v1.z = rglz;
						/*
							 if(item_bottom_normal_invert)
							 v1.z += h;
							 */
					}
					v.x = rv.x;
					v.y = rv.y;
					v.z = v1.z + cheight;
				}
				else
				{
					if(Algo_GetItemTopCoord(map_model, &rv, currentscene, cwidth, &rglz, &currentindex, &h))
					{
						v.x = rv.x;
						v.y = rv.y;
						v.z = rglz;
						/*
							 if(item_bottom_normal_invert)
							 v.z += h;
							 */
						v.z = v.z + cheight;
					}
					else
					{
						v.x = new_v -> x; //xp
						v.y = new_v -> y; //yp
						v.z = new_v -> z; //zp
					}
				}
			}
			else
			{
				//else printf("%f %f %f\n", normal[0], normal[1], normal[2]);
			}
		}
		else if(currentscene != scene)
		{
			currentscene = scene;
			v.x = new_v -> x; //xp
			v.y = new_v -> y; //zp
			v.z = ori_v -> z; //yo
		}
		else
		{
			nl_vector3_t normal = {0.0, 0.0, 0.0};
			if(Algo_NETLizard3DItemCollisionTesting(map_model, &v1, &v1, cwidth, cheight - 1, currentscene, &normal, &currentindex))
			{
				if(Algo_ComputeFloorCoord(map_model, &v1, &scene, &rglz))
				{
					v1.z = rglz;
					gl_vector3_t vt = v1;
					if(/* 1 || */currentscene != scene)
					{
						currentscene = scene;
						currentindex = -1;
						if(Algo_NETLizard3DItemCollisionTesting(map_model, &v1, &v1, cwidth, -1, currentscene, &normal, &currentindex))
						{
							vt.z = v1.z;
						}
					}
					if(Algo_GetItemTopCoord(map_model, &vt, scene, cwidth, &rglz, &currentindex, &h))
					{
						v1.z = rglz;
					}
					v.x = v1.x;
					v.y = v1.y;
					v.z = v1.z + cheight;
				}
				else
				{
					if(Algo_GetItemTopCoord(map_model, &v2, currentscene, cwidth, &rglz, &currentindex, &h))
					{
						v.x = v1.x;
						v.y = v1.y;
						v.z = rglz;
						v.z = v.z + cheight;
					}
					else
					{
						v.x = new_v -> x; //xp
						v.z = new_v -> z; //zp
						v.y = new_v -> y; //yp
					}
				}
			}
			else
			{
				//else printf("%f %f %f\n", normal[0], normal[1], normal[2]);
			}
		}
	}
	else
		return 0;
#if 0
	else // res = 0
	{
		if(currentscene == -1)
		{
			if(Algo_GetItemTopCoordForAll(map_model, &v2, &rgly, &currentindex))
			{
				v.x = new_v -> x; //xp
				v.z = new_v -> z; //zp
				v.y = rgly;
				v.y = v.y - cheight;
			}
			else
			{
				v.x = new_v -> x; //xp
				v.z = new_v -> z; //zp
				v.y = new_v -> y; //yp
			}
		}
	}
#endif
	return_v -> x = v.x;
	return_v -> y = v.y;
	return_v -> z = v.z;
	if(cs)
		*cs = currentscene;
	if(ci)
		*ci = currentindex;
	return 1;
}

int Algo_GetPointInAABBInNETLizard3DMap(const nl_vector3_t *p, const GL_NETLizard_3D_Model *map_model)
{
	if(!map_model || !p)
		return -1;
	unsigned int i;
	for(i = 0; i < map_model -> count; i++)
	{
		const GL_NETLizard_3D_Mesh *mesh = map_model -> meshes + i;
		aabb_t aabb = {
			{mesh -> ortho[3], mesh -> ortho[4], mesh -> ortho[5]},
			{mesh -> ortho[0], mesh -> ortho[1], mesh -> ortho[2]}
		};
		if(Math3D_PointInAABB(p, &aabb))
			return i;
	}
	return -1;
}

// UNUSED Update OpenGL view coord by OpenGL coord
int Algo_UpdateThirdPersonPosition(const GL_NETLizard_3D_Model *map_model, float *xt, float *yt, float *zt, float xp, float yp, float zp, float oxr, float oyr, float yr, float xr, float tps_factory, int cs, int available)
{
	if(!map_model)
		return 0;
	gl_vector3_t d = Algo_GLComputeDirection(Algo_FormatAngle(oyr + yr), Algo_FormatAngle(oxr + xr));
	d.x = -d.x;
	d.y = -d.y;
	d.z = -d.z;
	gl_vector3_t dir = {
		d.x * tps_factory,
		d.y * tps_factory,
		d.z * tps_factory
	};
	gl_vector3_t v = { xp + dir.x, yp + dir.y, zp + dir.z };
	nl_vector3_t new_position = Algo_GLToNLVector3(&v, NULL);
	int scene = -1;
	map_collision_testing_result_type res = Algo_NETLizard3DMapCollisionTesting(map_model, &new_position, 0.0, 0.0, &scene);
	if(res == map_only_in_aabb_type)
	{
		const GL_NETLizard_3D_Mesh *mesh = map_model -> meshes + scene;
		aabb_t aabb = {
			{mesh -> ortho[3], mesh -> ortho[4], mesh -> ortho[5]},
			{mesh -> ortho[0], mesh -> ortho[1], mesh -> ortho[2]}
		};
		unsigned int j;
		int find = 0;
		int p = -1;
		float distance = FLT_MAX;
		nl_vector3_t dt = {d.x, -d.z, d.y};
		line_t l = {new_position, dt};
		nl_vector3_t po = {0.0, 0.0, 0.0};
		nl_vector3_t no = {0.0, 0.0, 0.0};
		for(j = 0; j < mesh -> plane_count; j++)
		{
			plane_t plane = {
				{mesh -> plane[j].position[0], mesh -> plane[j].position[1], mesh -> plane[j].position[2]},
				{-mesh -> plane[j].normal[0], -mesh -> plane[j].normal[1], -mesh -> plane[j].normal[2]}
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
			v.x = -po.x - -no.x;
			v.y = -po.z - -no.z;
			v.z = po.y - no.y;
		}
		else
		{
			v.x = xp;
			v.y = yp;
			v.z = zp;
		}
	}
	else if(res == map_out_aabb_type && available)
	{
		const GL_NETLizard_3D_Mesh *mesh = map_model -> meshes + cs;
		int *scenes = NEW_II(int, map_model -> count);
		scenes[0] = cs + 1;
		int cur = 1;
		int i;
		for(i = 0; i < (int)mesh -> bsp_count; i++)
		{
			GLint prev = map_model -> bsp_data[mesh -> bsp[i]].prev_scene;
			GLint next = map_model -> bsp_data[mesh -> bsp[i]].next_scene;
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
		nl_vector3_t dt = {d.x, -d.z, d.y};
		line_t l = {new_position, dt};
		nl_vector3_t po = {0.0, 0.0, 0.0};
		nl_vector3_t no = {0.0, 0.0, 0.0};
		for(i = cur - 1; i >= 0; i--)
		{
			if(scenes[i] == 0)
				break;
			mesh = map_model -> meshes + (scenes[i] - 1);
			aabb_t aabb = {
				{mesh -> ortho[3], mesh -> ortho[4], mesh -> ortho[5]},
				{mesh -> ortho[0], mesh -> ortho[1], mesh -> ortho[2]}
			};
			unsigned int j;
			for(j = 0; j < mesh -> plane_count; j++)
			{
				plane_t plane = {
					{mesh -> plane[j].position[0], mesh -> plane[j].position[1], mesh -> plane[j].position[2]},
					{-mesh -> plane[j].normal[0], -mesh -> plane[j].normal[1], -mesh -> plane[j].normal[2]}
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
			v.x = -po.x - -no.x;
			v.y = -po.z - -no.z;
			v.z = po.y - no.y;
		}
		else
		{
			v.x = xp;
			v.y = yp;
			v.z = zp;
		}
		free(scenes);
	}
	else
	{
		// res == 4 / 2 / 3
	}
	*xt = v.x;
	*yt = v.y;
	*zt = v.z;
	return 1;
}

int Algo_GetPositionCoordIfCollatedMapWall(const GL_NETLizard_3D_Model *model, float limit, const nl_vector3_t *last_position, const nl_vector3_t *new_position, int scene, nl_vector3_t *rv, int *rs)
{
	if(!model || !last_position || !new_position)
		return 0;
	const GL_NETLizard_3D_Mesh *mesh = model -> meshes + scene;
	if(mesh -> plane)
	{
		unsigned int j;
		for(j = 0; j < mesh -> plane_count; j++)
		{
			if(mesh -> plane[j].normal[2] > UP_NORMAL_LIMIT || mesh -> plane[j].normal[2] < -UP_NORMAL_LIMIT)
				continue;
			plane_t plane = {
				{mesh -> plane[j].position[0], mesh -> plane[j].position[1], mesh -> plane[j].position[2]},
				{mesh -> plane[j].normal[0], mesh -> plane[j].normal[1], mesh -> plane[j].normal[2]}
			};
			line_t l = {*new_position, {-mesh -> plane[j].normal[0], -mesh -> plane[j].normal[1], -mesh -> plane[j].normal[2]}};
			float lamda = 0.0;
			int r = Math3D_LineToPlaneCollision(&l, &plane, &lamda, NULL);
			if(r != 1)
				continue;
			if(lamda <= limit)
			{
				float xr = 0.0, yr = 0.0;
				float pxr = 0.0, pyr = 0.0;
				nl_vector3_t dir = Vector3_SubtractVector3(new_position, last_position);
				nl_vector3_t nml = plane.normal;
				Vector3_Inverse(&nml);
				Vector3_Normalize(&dir);
				Algo_GetNormalAngle(&dir, &yr, &xr);
				Algo_GetNormalAngle(&nml, &pyr, &pxr);
				float nyr = Algo_FormatAngle(pyr - yr);
				/* 2017 8 7
					 if(nyr >= 90.0 && nyr <= 270.0)
					 continue;
					 */

				nl_vector3_t up = {0.0, 0.0, 1.0};
				nl_vector3_t pla = Vector3_CrossVector3(&nml, &up);
				Vector3_Normalize(&pla);
				float t = tan(ator(nyr)) * (limit - lamda);
				nl_vector3_t n = Vector3_Scale(&pla, t);
				//printf("%0.2f, %0.2f  ---====\n", nyr, rtoa(acos(Vector3_DotVector3(&nml, &dir))));
				nl_vector3_t v = {last_position -> x + n.x, last_position -> y + n.y, new_position -> z};
				int s = -1;
				map_collision_testing_result_type res = Algo_NETLizard3DMapCollisionTesting(model, &v, limit, 0, &s);
				if(res == map_in_all_planes_and_in_aabb_type && s != -1)
				{
					if(rv)
					{
						rv -> x = v.x;
						rv -> y = v.y; 
						rv -> z = v.z;
					}
					if(rs)
						*rs = s;
					return 1;
				}
				else
				{
					continue;
				}
			}
		}
	}
	return 0;
}

int Algo_GetTopScene(const GL_NETLizard_3D_Model *netlizard_3d_model, const nl_vector3_t *new_pos, int *scene, float *rglz)
{
	if(!netlizard_3d_model || !new_pos)
		return 0;
	unsigned int i;
	int res = 0;
	int s = -1;
	float z = 0.0;
	for(i = 0; i < netlizard_3d_model -> count; i++)
	{
		const GL_NETLizard_3D_Mesh *next_mesh = netlizard_3d_model -> meshes + i;
		aabb_t aabb = {
			{next_mesh -> ortho[3], next_mesh -> ortho[4], next_mesh -> ortho[5]},
			{next_mesh -> ortho[0], next_mesh -> ortho[1], next_mesh -> ortho[2]}
		};
		if(!Math3D_PointInAABB2D(new_pos, &aabb))
			continue;
		if(res == 0)
		{
			if(aabb.max_position.z < new_pos -> z)
			{
				s = i;
				z = aabb.max_position.z;
				res = 1;
			}
		}
		else
		{
			if(aabb.max_position.z > z && aabb.max_position.z < new_pos -> z)
			{
				z = aabb.max_position.z;
				s = i;
			}
		}
	}
	if(res)
	{
		if(scene)
			*scene = s;
		if(rglz)
			*rglz = z;
	}

	return res;
}

int Algo_GetScenePath(const GL_NETLizard_3D_Model *model, GLuint start, GLuint end, int index, GLint *path, GLint *count)
{
	if(!model || !path || !path || !count)
		return 0;
	if(start >= model -> count)
		return 0;
	if(end >= model -> count)
		return 0;
	if(!model -> bsp_data || model -> bsp_count == 0)
		return 0;

	const GLint *bsp = model -> meshes[start].bsp;
	int i;
	for(i = 0; i < (int)model -> meshes[start].bsp_count; i++)
	{
		const GL_NETLizard_BSP_Tree_Node *node = model -> bsp_data + bsp[i];
		int has_prev = 0;
		int has_next = 0;
		int j;
		for(j = 0; j < index; j++)
		{
			if(!has_prev)
			{
				if(path[j] == node -> prev_scene)
					has_prev = 1;
			}
			if(!has_next)
			{
				if(path[j] == node -> next_scene)
					has_next = 1;
			}
		}
		if(has_prev && has_next)
			continue;
		if(!has_prev)
		{
			path[index] = node -> prev_scene;
			if(node -> prev_scene == (int)end)
			{
				*count = index + 1;
				return 1;
			}
			if(Algo_GetScenePath(model, node -> prev_scene, end, index + 1, path, count) == 1)
			{
				return 1;
			}
		}
		if(!has_next)
		{
			path[index] = node -> next_scene;
			if(node -> next_scene == (int)end)
			{
				*count = index + 1;
				return 1;
			}
			if(Algo_GetScenePath(model, node -> next_scene, end, index + 1, path, count) == 1)
			{
				return 1;
			}
		}
	}
	return 0;
}

GLuint * Algo_GetMapPathScene(const GL_NETLizard_3D_Model *map_model, GLuint start, GLuint end, GLint *count)
{
	if(!map_model || !count)
		return NULL;
	if(start >= map_model -> count)
		return NULL;
	if(end >= map_model -> count)
		return NULL;
	if(!map_model -> bsp_data || map_model -> bsp_count == 0)
		return NULL;

	GLint *path = NEW_II(GLint, map_model -> count);
	GLint c = -1;
	GLuint *r = NULL;
	int k;
	for(k = 0; k < (int)map_model -> count; k++)
		path[k] = -1;
	path[0] = start;
	if(Algo_GetScenePath(map_model, start, end, 1, path, &c))
	{
		*count = c;
		r = NEW_II(GLuint, c);
		memcpy(r, path, sizeof(GLuint) * c);
		/*
			 for(k = 0; k < c; k++)
			 printf("%d ", r[k]);
			 printf("\n c = %d\n", c);
			 */
	}
	free(path);
	return r;
}

int Algo_GetBSPPath(const GL_NETLizard_3D_Model *model, GLuint start, GLuint end, int index, GLint *path, int bsp_index, GLint *bsps, GLint *count)
{
	if(!model || !path || !path || !bsps || !count)
		return 0;
	if(start >= model -> count)
		return 0;
	if(end >= model -> count)
		return 0;
	if(!model -> bsp_data || model -> bsp_count == 0)
		return 0;

	const GLint *bsp = model -> meshes[start].bsp;
	int i;
	for(i = 0; i < (int)model -> meshes[start].bsp_count; i++)
	{
		const GL_NETLizard_BSP_Tree_Node *node = model -> bsp_data + bsp[i];
		int has_prev = 0;
		int has_next = 0;
		int j;
		for(j = 0; j < index; j++)
		{
			if(!has_prev)
			{
				if(path[j] == node -> prev_scene)
					has_prev = 1;
			}
			if(!has_next)
			{
				if(path[j] == node -> next_scene)
					has_next = 1;
			}
		}
		if(has_prev && has_next)
			continue;
		if(!has_prev)
		{
			path[index] = node -> prev_scene;
			bsps[bsp_index] = bsp[i];
			if(node -> prev_scene == (int)end)
			{
				*count = bsp_index + 1;
				return 1;
			}
			if(Algo_GetBSPPath(model, node -> prev_scene, end, index + 1, path, bsp_index + 1, bsps, count) == 1)
			{
				return 1;
			}
		}
		if(!has_next)
		{
			path[index] = node -> next_scene;
			bsps[bsp_index] = bsp[i];
			if(node -> next_scene == (int)end)
			{
				*count = bsp_index + 1;
				return 1;
			}
			if(Algo_GetBSPPath(model, node -> next_scene, end, index + 1, path, bsp_index + 1, bsps, count) == 1)
			{
				return 1;
			}
		}
	}
	return 0;
}

GLuint * Algo_GetMapPathBSP(const GL_NETLizard_3D_Model *map_model, GLuint start, GLuint end, GLint *count)
{
	if(!map_model || !count)
		return NULL;
	if(start >= map_model -> count)
		return NULL;
	if(end >= map_model -> count)
		return NULL;
	if(!map_model -> bsp_data || map_model -> bsp_count == 0)
		return NULL;

	GLint *path = NEW_II(GLint, map_model -> count);
	GLint *bsps = NEW_II(GLint, map_model -> bsp_count);
	GLint c = -1;
	GLuint *r = NULL;
	int k;
	for(k = 0; k < (int)map_model -> count; k++)
		path[k] = -1;
	for(k = 0; k < (int)map_model -> bsp_count; k++)
		bsps[k] = -1;
	path[0] = start;
	if(Algo_GetBSPPath(map_model, start, end, 1, path, 0, bsps, &c))
	{
		*count = c;
		r = NEW_II(GLuint, c);
		memcpy(r, bsps, sizeof(GLuint) * c);
		/*
			 for(k = 0; k < c; k++)
			 printf("%d ",r[k]);
			 printf("\n c = %d\n", c);
			 */
	}
	free(path);
	free(bsps);
	return r;
}

int Algo_GetSceneAndBSPPath(const GL_NETLizard_3D_Model *model, GLuint start, GLuint end, int index, int bsp_index, GLint *path, GLint *count)
{
	if(!model || !path || !path || !count)
		return 0;
	if(start >= model -> count)
		return 0;
	if(end >= model -> count)
		return 0;
	if(!model -> bsp_data || model -> bsp_count == 0)
		return 0;

	if(path[0] >= (int)model -> count || path[0] < 0)
	{
		path[0] = start;
		if(index == 0)
			index++;
	}
	const GLint *bsp = model -> meshes[start].bsp;
	int i;
	for(i = 0; i < (int)model -> meshes[start].bsp_count; i++)
	{
		const GL_NETLizard_BSP_Tree_Node *node = model -> bsp_data + bsp[i];
		int has_prev = 0;
		int has_next = 0;
		int j;
		for(j = 0; j < index; j++)
		{
			if(!has_prev)
			{
				if(path[j * 2] == node -> prev_scene)
					has_prev = 1;
			}
			if(!has_next)
			{
				if(path[j * 2] == node -> next_scene)
					has_next = 1;
			}
		}
		if(has_prev && has_next)
			continue;
		if(!has_prev)
		{
			path[index * 2] = node -> prev_scene;
			path[bsp_index * 2 + 1] = bsp[i];
			if(node -> prev_scene == (int)end)
			{
				*count = bsp_index + 1 + index + 1;
				return 1;
			}
			if(Algo_GetSceneAndBSPPath(model, node -> prev_scene, end, index + 1, bsp_index + 1, path, count) == 1)
			{
				return 1;
			}
		}
		if(!has_next)
		{
			path[index * 2] = node -> next_scene;
			path[bsp_index * 2 + 1] = bsp[i];
			if(node -> next_scene == (int)end)
			{
				*count = bsp_index + 1 + index + 1;
				return 1;
			}
			if(Algo_GetSceneAndBSPPath(model, node -> next_scene, end, index + 1, bsp_index + 1, path, count) == 1)
			{
				return 1;
			}
		}
	}
	return 0;
}

GLuint * Algo_GetMapPathSceneAndBSP(const GL_NETLizard_3D_Model *map_model, GLuint start, GLuint end, GLint *count)
{
	if(!map_model || !count)
		return NULL;
	if(start >= map_model -> count)
		return NULL;
	if(end >= map_model -> count)
		return NULL;
	if(!map_model -> bsp_data || map_model -> bsp_count == 0)
		return NULL;

	int len = map_model -> count + map_model -> bsp_count;
	GLint *path = NEW_II(GLint, len);
	GLint c = -1;
	GLuint *r = NULL;
	int k;
	for(k = 0; k < len; k++)
		path[k] = -1;
	if(Algo_GetSceneAndBSPPath(map_model, start, end, 0, 0, path, &c))
	{
		*count = c;
		r = NEW_II(GLuint, c);
		memcpy(r, path, sizeof(GLuint) * c);
		/*
			 for(k = 0; k < c; k++)
			 printf("%d ", k % 2 == 0 ? -r[k] : r[k]);
			 printf("\n c = %d\n", c);
			 */
	}
	free(path);
	return r;
}

int Algo_LadderItemCollision(const GL_NETLizard_3D_Model *model, const nl_vector3_t *pos, const nl_vector3_t *new_pos, float width, float height, int index, nl_vector3_t *rpos)
{
	if(!model || !pos || !new_pos || index < 0)
		return 0;
	if(model -> item_meshes[index].item_type != Item_Ladder_Type)
		return 0;
	const GL_NETLizard_3D_Item_Mesh *im = model -> item_meshes + index;
	aabb_t aabb = {
		{im -> item_mesh.ortho[3] + im -> pos[0], im -> item_mesh.ortho[4] + im -> pos[1], im -> item_mesh.ortho[5] + im -> pos[2]},
		{im -> item_mesh.ortho[0] + im -> pos[0], im -> item_mesh.ortho[1] + im -> pos[1], im -> item_mesh.ortho[2] + im -> pos[2]}
	};
	if(new_pos -> z - height < aabb.min_position.z || new_pos -> z - height > aabb.max_position.z)
		return 0;
	if(Vector3_EqualsVector3(pos, new_pos))
	{
		if(rpos)
			*rpos = *new_pos;
		return 1;
	}
	nl_vector3_t cdir = Vector3_SubtractVector3(new_pos, pos);
	float cdis = Vector3_Mag(&cdir);
	Vector3_Normalize(&cdir);
	line_t cline = {*pos, cdir};
	nl_vector3_t lpos = {
		(aabb.max_position.x + aabb.min_position.x) / 2, 
		(aabb.max_position.y + aabb.min_position.y) / 2, 
		pos -> z
	};
	nl_vector3_t ldir = Vector3_SubtractVector3(pos, &lpos);
	Vector3_Normalize(&ldir);
	plane_t lplane = {lpos, ldir};
	int r = Math3D_LineToPlaneCollision(&cline, &lplane, NULL, NULL);
	if(r == 0)
		return 0;
	if(rpos)
	{
		nl_vector3_t dis = Vector3_Scale(&ldir, width);
		rpos -> x = lpos.x + dis.x;
		rpos -> y = lpos.y + dis.y;
		rpos -> z = pos -> z + cdis * 0.15;
	}
	return 1;
}

int Algo_LadderItemCollisionFromScene(const GL_NETLizard_3D_Model *model, const nl_vector3_t *pos, const nl_vector3_t *new_pos, float x_a, float y_a, float width, float height, int *scene, int *index, nl_vector3_t *rpos)
{
	if(!model || !pos || !new_pos)
		return 0;
	typedef enum _ladder_orientation
	{
		x_ladder = 0,
		y_ladder = 1
	} ladder_orientation;

	nl_vector3_t ori = *pos;
	nl_vector3_t ne = *new_pos;
	ori.z -= height;
	ne.z -= height;
	nl_vector3_t direction = Algo_ComputeDirection(y_a, x_a);
	nl_vector3_t direction_y = Algo_ComputeDirection(y_a, 0.0);

	// forward
	nl_vector3_t cdir = Vector3_SubtractVector3(new_pos, pos);
	float cdis = Vector3_Mag(&cdir);
	Vector3_Normalize(&cdir);
	line_t cline = {ori, cdir};
	// view direction
	line_t vline = {ori, direction_y};

	int s = -1;
	int res = Algo_NETLizard3DMapCollisionTesting(model, &ori, width, height, &s);
	if(res == map_out_aabb_type)
		return 0;
	const GL_NETLizard_3D_Mesh *mesh = model -> meshes + s;
	unsigned int i;
	for(i = mesh -> item_index_range[0]; i < mesh -> item_index_range[1]; i++)
	{
		const GL_NETLizard_3D_Item_Mesh *im = model -> item_meshes + i;
		if(im -> item_type != Item_Ladder_Type)
			continue;
		const float w = 50 + width;
		const float h = 10;
		aabb_t aabb = {
			{im -> item_mesh.ortho[3] + im -> pos[0] - w, im -> item_mesh.ortho[4] + im -> pos[1] - w, im -> item_mesh.ortho[5] + im -> pos[2] - h},
			{im -> item_mesh.ortho[0] + im -> pos[0] + w, im -> item_mesh.ortho[1] + im -> pos[1] + w, im -> item_mesh.ortho[2] + im -> pos[2] + h}
		};
		aabb_t laabb = {
			{im -> item_mesh.ortho[3] + im -> pos[0], im -> item_mesh.ortho[4] + im -> pos[1], im -> item_mesh.ortho[5] + im -> pos[2]},
			{im -> item_mesh.ortho[0] + im -> pos[0], im -> item_mesh.ortho[1] + im -> pos[1], im -> item_mesh.ortho[2] + im -> pos[2]}
		};
		aabb_t laabb2 = {
			{im -> item_mesh.ortho[3] + im -> pos[0] - width, im -> item_mesh.ortho[4] + im -> pos[1] - width, im -> item_mesh.ortho[5] + im -> pos[2] - 1},
			{im -> item_mesh.ortho[0] + im -> pos[0] + width, im -> item_mesh.ortho[1] + im -> pos[1] + width, im -> item_mesh.ortho[2] + im -> pos[2] + 1}
		};
		if(!Math3D_PointInAABB(&ori, &aabb))
			continue;
		if(Vector3_EqualsVector3(pos, new_pos))
		{
			if(rpos)
				*rpos = *new_pos;
			if(scene)
				*scene = s;
			if(index)
				*index = i;
			return 1;
		}
		nl_vector3_t lpos = {
			(laabb.max_position.x + laabb.min_position.x) / 2, 
			(laabb.max_position.y + laabb.min_position.y) / 2, 
			ori.z
		};
		nl_vector3_t ldir = {0.0, 0.0, 0.0};
		//float lw = 0.0;
		float lx = laabb.max_position.x - laabb.min_position.x;
		float ly = laabb.max_position.y - laabb.min_position.y;
		nl_vector3_t ltdir = Vector3_SubtractVector3(&ori, &lpos);
		Vector3_Normalize(&ltdir);
		ladder_orientation o;
		if(ly > lx)
		{
			ldir.x = ltdir.x > 0 ? 1 : -1;
			//lw = lx / 2;
			o = x_ladder;
		}
		else
		{
			ldir.y = ltdir.y > 0 ? 1 : -1;
			//lw = ly / 2;
			o = y_ladder;
		}

		plane_t lplane = {lpos, ldir};
		int r = Math3D_LineToPlaneCollision(&cline, &lplane, NULL, NULL);
		int r2 = Math3D_LineToPlaneCollision(&vline, &lplane, NULL, NULL);
		int r3 = direction.z < -UP_NORMAL_LIMIT ? 1 : 0;
		int r4 = direction.z > UP_NORMAL_LIMIT ? 1 : 0;

		int d = 0;
		nl_vector3_t point = {0.0, 0.0, 0.0};
		//printfv3(lplane.normal);
		if(r) // 向梯子运动
		{
			Math3D_LineToPlaneIntersect(&cline, &lplane, &point);
			if(!Math3D_PointInAABB(&point, &laabb2))
				continue;
			if(r2 == 0) // 视角背对梯子
			{
				if(direction.z == 1)
					d = -1;
				else if(direction.z == -1)
					d = 1;
				else
				{
					if(r4)
						d = -1;
					else
						d = 1;
				}
			}
			else // 视角面向梯子
			{
				if(direction.z == 1)
					d = 1;
				else if(direction.z == -1)
					d = -1;
				else
				{
					if(r3)
						d = -1;
					else
						d = 1;
				}
			}
		}

		else // 远离梯子运动
		{
			if(r2 == 0) // 视角背对梯子
			{
				if(r3 && direction.z != -1) // 视角向下，爬下梯子
				{
					nl_vector3_t td = direction;
					if(o == x_ladder)
						td.x = -td.x;
					else
						td.y = -td.y;
					line_t tl = {ori, td};
					if(Math3D_LineToPlaneCollision(&tl, &lplane, NULL, NULL))
					{
						Math3D_LineToPlaneIntersect(&tl, &lplane, &point);
						if(!Math3D_PointInAABB2D(&point, &laabb2))
							continue;
						d = -1;
					}
					else
						continue;
				}
				else if(direction.z == -1)
				{
					nl_vector3_t nml = lplane.normal;
					Vector3_Inverse(&nml);
					line_t tl = {ori, nml};
					if(Math3D_LineToPlaneCollision(&tl, &lplane, NULL, NULL))
					{
						Math3D_LineToPlaneIntersect(&tl, &lplane, &point);
						if(!Math3D_PointInAABB(&point, &laabb2))
							continue;
						d = -1;
					}
					else
						continue;
				}
				else
					continue;
			}
			else // 视角面向梯子
			{
				if(r4 && direction.z != 1) // 视角向上，爬下梯子
				{
					nl_vector3_t td = direction;
					td.z = -td.z;
					if(o == x_ladder)
						td.y = -td.y;
					else
						td.x = -td.x;
					line_t tl = {ori, td};
					if(Math3D_LineToPlaneCollision(&tl, &lplane, NULL, NULL))
					{
						Math3D_LineToPlaneIntersect(&tl, &lplane, &point);
						if(!Math3D_PointInAABB2D(&point, &laabb2))
							continue;
						d = -1;
					}
					else
						continue;
				}
				else if(direction.z == 1)
				{
					nl_vector3_t nml = lplane.normal;
					Vector3_Inverse(&nml);
					line_t tl = {ori, nml};
					if(Math3D_LineToPlaneCollision(&tl, &lplane, NULL, NULL))
					{
						Math3D_LineToPlaneIntersect(&tl, &lplane, &point);
						if(!Math3D_PointInAABB(&point, &laabb2))
							continue;
						d = -1;
					}
					else
						continue;
				}
				else
					continue;
			}
		}
		ori.z += height;
		ori.z += cdis * d;

		res = Algo_NETLizard3DMapCollisionTesting(model, &ori, width, height, &s);
		if(res == map_out_aabb_type)
		{
			mesh = model -> meshes + s;
			aabb_t maabb = {
				{mesh -> ortho[3], mesh -> ortho[4], mesh -> ortho[5]},
				{mesh -> ortho[0], mesh -> ortho[1], mesh -> ortho[2]}
			};
			if(mesh -> plane)
			{
				unsigned int j;
				for(j = 0; j < mesh -> plane_count; j++)
				{
					if(d == 1) // 向上爬
					{
						if(mesh -> plane[j].normal[2] < 0)
						{
							plane_t pla = {
								{mesh -> plane[j].position[0], mesh -> plane[j].position[1], mesh -> plane[j].position[2]},
								{mesh -> plane[j].normal[0], mesh -> plane[j].normal[1], mesh -> plane[j].normal[2]}
							};
							line_t l = {*pos, {0.0, 0.0, 1.0}};
							float dis = 0.0;
							if(Math3D_LineToPlaneCollision(&l, &pla, &dis, NULL))
							{
								nl_vector3_t p = {0.0, 0.0, 0.0};
								Math3D_LineToPlaneIntersect(&l, &pla, &p);
								if(Math3D_PointInAABB(&p, &maabb))
								{
									cdis = dis - height;
									break;
								}
							}
						}
					}
					else // 向下爬
					{
						if(mesh -> plane[j].normal[2] > 0)
						{
							plane_t pla = {
								{mesh -> plane[j].position[0], mesh -> plane[j].position[1], mesh -> plane[j].position[2]},
								{mesh -> plane[j].normal[0], mesh -> plane[j].normal[1], mesh -> plane[j].normal[2]}
							};
							line_t l = {*pos, {0.0, 0.0, -1.0}};
							float dis = 0.0;
							if(Math3D_LineToPlaneCollision(&l, &pla, &dis, NULL))
							{
								nl_vector3_t p = {0.0, 0.0, 0.0};
								Math3D_LineToPlaneIntersect(&l, &pla, &p);
								if(Math3D_PointInAABB(&p, &maabb))
								{
									cdis = dis;
									break;
								}
							}
						}
					}
				}
			}
			else
			{
				if(d == 1)
					cdis = maabb.max_position.z - pos -> z;
				else
					cdis = pos -> z - height - maabb.min_position.z;
			}
		}

		if(rpos)
		{
			nl_vector3_t dis = Vector3_Scale(&ldir, width);
			rpos -> x = point.x + dis.x;
			rpos -> y = point.y + dis.y;
			rpos -> z = pos -> z + cdis * d;
		}
		if(scene)
			*scene = s;
		if(index)
			*index = i;
		return 1;
	}
	return 0;
}

/*
 * 返回1则可继续运动
 * 返回0则有碰撞，不可继续运动，碰撞点返回
 */
int Algo_ComputePositionInNETLizard3DMapNotGravity(const GL_NETLizard_3D_Model *map_model, const nl_vector3_t *ori_v, const nl_vector3_t *new_v, float cwidth, float cheight, nl_vector3_t *return_v, int *cs, int *ci)
{
	if(!map_model || !ori_v || !new_v || !return_v)
		return 1;
	int scene = -1;
	int scene_o = -1;
	int currentindex = -1;
	int currentscene = -1;
	if(cs)
		currentscene = *cs;
	nl_vector3_t v1 = *ori_v;
	nl_vector3_t v2 = *new_v;

	map_collision_testing_result_type res = Algo_NETLizard3DMapCollisionTesting(map_model, &v2, cwidth, cheight, &scene);
	map_collision_testing_result_type res_o = Algo_NETLizard3DMapCollisionTesting(map_model, &v1, cwidth, cheight, &scene_o);
	int res2 = res == map_in_all_planes_and_in_aabb_but_less_than_collision_distance_type || res == map_in_all_planes_and_in_aabb_type ? 1 : 0;
	int res2_o = res_o == map_in_all_planes_and_in_aabb_but_less_than_collision_distance_type || res_o == map_in_all_planes_and_in_aabb_type ? 1 : 0;
	if(res2 == 0 && res2_o == 0)
		return 1;

	GLint scenes[2] = {-1, -1};
	GLint i = 0;
	if(res2)
	{
		scenes[0] = scene;
		i++;
	}
	if(res2_o)
	{
		scenes[i] = scene_o;
	}
	if(scenes[0] == scenes[1])
		scenes[1] = -1;

	nl_vector3_t v = v1;
	nl_vector3_t dir = Vector3_SubtractVector3(&v2, &v1);
	Vector3_Normalize(&dir);
	if(res2 && res2_o == 0)
	{
		v = v2;
		Vector3_Inverse(&dir);
	}
	line_t line = {v, dir};
	aabb_t laabb = {
		{KARIN_MIN(v1.x, v2.x), KARIN_MIN(v1.y, v2.y), KARIN_MIN(v1.z, v2.z)},
		{KARIN_MAX(v1.x, v2.x), KARIN_MAX(v1.y, v2.y), KARIN_MAX(v1.z, v2.z)}
	};

	float distance = 0.0;
	nl_vector3_t point = {0.0, 0.0, 0.0};
	int r = 0;
	if(res2 == 0 || res2_o == 0)
	{
		for(i = 0; i < 2; i++)
		{
			if(scenes[i] == -1)
				continue;
			const GL_NETLizard_3D_Mesh *mesh = map_model -> meshes + scenes[i];
			if(mesh -> plane_count == 0)
				continue;
			aabb_t aabb = {
				{mesh -> ortho[3], mesh -> ortho[4], mesh -> ortho[5]},
				{mesh -> ortho[0], mesh -> ortho[1], mesh -> ortho[2]}
			};
			GLuint j;
			for(j = 0; j < mesh -> plane_count; j++)
			{
				plane_t pla = {
					{mesh -> plane[j].position[0], mesh -> plane[j].position[1], mesh -> plane[j].position[2]},
					{mesh -> plane[j].normal[0], mesh -> plane[j].normal[1], mesh -> plane[j].normal[2]}
				};
				float dis = 0.0;
				if(Math3D_LineToPlaneCollision(&line, &pla, &dis, NULL))
				{
					nl_vector3_t p = {0.0, 0.0, 0.0};
					Math3D_LineToPlaneIntersect(&line, &pla, &p);
					if(!Math3D_PointInAABB(&p, &laabb))
						continue;
					if(!Math3D_PointInAABB(&p, &aabb))
						continue;
					if(r == 0)
					{
						distance = dis;
						point = p;
						currentscene = scenes[i];
						r = 1;
					}
					else
					{
						if(distance < dis)
						{
							distance = dis;
							point = p;
							currentscene = scenes[i];
						}
					}
				}
			}
		}
	}
	// items
	if(res2 && res2_o)
	{
		for(i = 0; i < 2; i++)
		{
			if(scenes[i] == -1)
				continue;
			const GL_NETLizard_3D_Mesh *mesh = map_model -> meshes + scenes[i];
			unsigned int k;
			for(k = mesh -> item_index_range[0]; k < mesh -> item_index_range[1]; k++)
			{
				const GL_NETLizard_3D_Item_Mesh *im = map_model -> item_meshes + k;
				if(im -> item_mesh.plane_count == 0)
					continue;
				aabb_t aabb = {
					{im -> item_mesh.ortho[3] - cwidth + im -> pos[0], im -> item_mesh.ortho[4] - cwidth + im -> pos[1], im -> item_mesh.ortho[5] + im -> pos[2] - cheight},
					{im -> item_mesh.ortho[0] + cwidth + im -> pos[0], im -> item_mesh.ortho[1] + cwidth + im -> pos[1], im -> item_mesh.ortho[2] + im -> pos[2] + cheight}
				};
				GLuint j;
				for(j = 0; j < im -> item_mesh.plane_count; j++)
				{
					plane_t pla = {
						{im -> item_mesh.plane[j].position[0] + im -> pos[0], im -> item_mesh.plane[j].position[1] + im -> pos[1], im -> item_mesh.plane[j].position[2] + im -> pos[2]},
						{im -> item_mesh.plane[j].normal[0], im -> item_mesh.plane[j].normal[1], im -> item_mesh.plane[j].normal[2]}
					};
					float dis = 0.0;
					if(Math3D_LineToPlaneCollision(&line, &pla, &dis, NULL))
					{
						nl_vector3_t p = {0.0, 0.0, 0.0};
						Math3D_LineToPlaneIntersect(&line, &pla, &p);
						if(!Math3D_PointInAABB(&p, &laabb))
							continue;
						if(!Math3D_PointInAABB(&p, &aabb))
							continue;
						if(r == 0)
						{
							distance = dis;
							point = p;
							currentindex = k;
							r = 1;
						}
						else
						{
							if(distance < dis)
							{
								distance = dis;
								point = p;
								currentindex = k;
							}
						}
					}
				}
			}
		}
	}

	if(r == 0)
		return 1;
	if(return_v)
		*return_v = point;
	if(cs)
		*cs = currentscene;
	if(ci)
		*ci = currentindex;
	return 0;
}

int Algo_GetItemOfScene(const GL_NETLizard_3D_Model *model, GLuint item, GLint *r)
{
	if(!model)
		return 0;
	if(!model -> item_meshes || model -> item_count == 0)
		return 0;
	if(!model -> meshes || model -> count == 0)
		return 0;

	GLuint i;
	for(i = 0; i < model -> count; i++)
	{
		const GL_NETLizard_3D_Mesh *mesh = model -> meshes + i;
		if(item >= mesh -> item_index_range[0] && item < mesh -> item_index_range[1])
		{
			if(r)
				*r = i;
			return 1;
		}
	}
	return 0;
}

int Algo_PointIsCollisionInScene(const GL_NETLizard_3D_Model *model, const nl_vector3_t *pos, float cwidth, float cheight, int *scene, int *item)
{
	if(!model || !pos)
		return 0;
	int s = -1;
	int it = -1;
	nl_vector3_t fpos = {pos -> x, pos -> y, pos -> z};
	map_collision_testing_result_type res = Algo_NETLizard3DMapCollisionTesting(model, &fpos, cwidth, cheight, &s);
	if(res == map_out_aabb_type || res == map_only_in_aabb_type)
		return 0;

	int ir = 0;
	const GL_NETLizard_3D_Mesh *mesh = model -> meshes + s;
	unsigned int k;
	for(k = mesh -> item_index_range[0]; k < mesh -> item_index_range[1]; k++)
	{
		const GL_NETLizard_3D_Item_Mesh *im = model -> item_meshes + k;
		aabb_t aabb = {
			{im -> item_mesh.ortho[3] - cwidth + im -> pos[0], im -> item_mesh.ortho[4] - cwidth + im -> pos[1], im -> item_mesh.ortho[5] + im -> pos[2]},
			{im -> item_mesh.ortho[0] + cwidth + im -> pos[0], im -> item_mesh.ortho[1] + cwidth + im -> pos[1], im -> item_mesh.ortho[2] + im -> pos[2]}
		};
		if(Math3D_PointInAABB(pos, &aabb))
		{
			res = item_only_in_aabb_type;
			//printfi(im -> item_type);
			it = k;
			if(im -> item_type & Item_Weapon_Type || im -> item_type & Item_Tiny_Type || im -> item_type & Item_Box_Type)
			{
				it = k;
				continue;
			}
			ir = 1;
			// 检测新位置是否在物品盒子中真实场景内
			if(im -> item_mesh.plane_count > 0)
			{
				const GL_NETLizard_3D_Plane *planes = im -> item_mesh.plane;
				unsigned int j;
				for(j = 0; j < im -> item_mesh.plane_count; j++)
				{
					plane_t plane = {
						{planes[j].position[0] + im -> pos[0], planes[j].position[1] + im -> pos[1], planes[j].position[2] + im -> pos[2]},
						{-planes[j].normal[0], -planes[j].normal[1], -planes[j].normal[2]}
					};
					line_t line = {*pos, {planes[j].normal[0], planes[j].normal[1], planes[j].normal[2]}};
					float lamda = 0.0;
					nl_vector3_t point = {0.0, 0.0, 0.0};
					int r;
					r = Math3D_LineToPlaneIntersect(&line, &plane, &point);
					if(r && Math3D_PointInAABB(&point, &aabb))
					{
						//r = Math3D_LineToPlaneCollision(&line, &plane, &lamda, NULL);
						it = k;
						break;
					}
				}
			}
		}
	}
	if(scene)
		*scene = s;
	if(ir)
	{
		if(item)
			*item = it;
		return 0;
	}
	return 1;
}
