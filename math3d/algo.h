#ifndef KARIN_MATH3D_ALGO_H
#define KARIN_MATH3D_ALGO_H

#include "vector3.h"
#include "graph.h"

// 计算三角形法线
vector3_t Math3D_GetTriangleNormal(const vector3_t *v0, const vector3_t *v1, const vector3_t *v2);
// 点面垂直距离
NLfloat Math3D_PointToPlaneDistance(const vector3_t *point, const plane_t *plane);
// 线面碰撞测试 返回距离，碰撞面法线
int Math3D_LineToPlaneCollision(const line_t *line, const plane_t *plane, NLfloat *lamda, vector3_t *normal);
// 点是否在盒子内
int Math3D_PointInAABB(const vector3_t *a, const aabb_t *aabb);
// 二维点是否在矩形内
int Math3D_PointInAABB2D(const vector3_t *a, const aabb_t *aabb);
// 线面碰撞测试 返回碰撞在面上的点
int Math3D_LineToPlaneIntersect(const line_t *line, const plane_t *plane, vector3_t *point);
int Math3D_LineToCylinderCollision(const line_t *line, const cylinder_t *cylinder, NLfloat *lamda_r, vector3_t *normal_r, vector3_t *new_pos_r);

// 点是否在三角形内
int Math3D_PointInTriangle(const vector3_t *p, const vector3_t *a, const vector3_t *b, const vector3_t *c);
int Math3D_PointInSameSide(const vector3_t *p, const vector3_t *a, const vector3_t *b, const vector3_t *c);
int Math3D_PointinTriangleBySameSide(const vector3_t *p, const vector3_t *a, const vector3_t *b, const vector3_t *c);
vector3_t Math3D_LineReflection(const vector3_t *v, const vector3_t *n);
vector3_t Math3D_ComputeTwoPointNormal(const vector3_t *p1, const vector3_t *p2);

#endif
