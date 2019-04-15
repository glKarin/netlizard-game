#ifndef KARIN_MATH3D_ALGO_H
#define KARIN_MATH3D_ALGO_H

#include "vector.h"
#include "graph.h"

// 计算三角形法线
vector3_s Math3D_GetTriangleNormal(const vector3_s *v0, const vector3_s *v1, const vector3_s *v2);
// 点面垂直距离
NLfloat Math3D_PointToPlaneDistance(const vector3_s *point, const plane_t *plane);
// 线面碰撞测试 返回距离，碰撞面法线
int Math3D_LineToPlaneCollision(const ray_s *line, const plane_t *plane, NLfloat *lamda, vector3_s *normal);
// 点是否在盒子内
int Math3D_PointInAABB(const vector3_s *a, const bound_s *aabb);
// 二维点是否在矩形内
int Math3D_PointInAABB2D(const vector3_s *a, const bound_s *aabb);
// 线面碰撞测试 返回碰撞在面上的点
int Math3D_LineToPlaneIntersect(const ray_s *line, const plane_t *plane, vector3_s *point);
int Math3D_LineToCylinderCollision(const ray_s *line, const cylinder_s *cylinder, NLfloat *lamda_r, vector3_s *normal_r, vector3_s *new_pos_r);

// 点是否在三角形内
int Math3D_PointInTriangle(const vector3_s *p, const vector3_s *a, const vector3_s *b, const vector3_s *c);
int Math3D_PointInSameSide(const vector3_s *p, const vector3_s *a, const vector3_s *b, const vector3_s *c);
int Math3D_PointinTriangleBySameSide(const vector3_s *p, const vector3_s *a, const vector3_s *b, const vector3_s *c);
vector3_s Math3D_LineReflection(const vector3_s *v, const vector3_s *n);
vector3_s Math3D_ComputeTwoPointNormal(const vector3_s *p1, const vector3_s *p2);

#endif
