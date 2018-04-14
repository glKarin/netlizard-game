#ifndef KARIN_GRAPH_H
#define KARIN_GRAPH_H

#include "vector3.h"

#define printfli(x) printf(#x" -> "); Line_Print(&(x));
#define printfpl(x) printf(#x" -> "); Plane_Print(&(x));
#define printfab(x) printf(#x" -> "); AABB_Print(&(x));
#define printfcy(x) printf(#x" -> "); Cylinder_Print(&(x));

typedef struct _plane_t
{
	vector3_t position;
	vector3_t normal;
} plane_t;

typedef struct _line_t
{
	vector3_t position;
	vector3_t direction;
} line_t;

typedef struct _aabb_t
{
	vector3_t min_position;
	vector3_t max_position;
} aabb_t;

typedef struct _cylinder_t
{
	vector3_t position;
	vector3_t axis;
	NLfloat radius;
} cylinder_t;


void Line_Print(const line_t *line);
void Plane_Print(const plane_t *plane);
void AABB_Print(const aabb_t *aabb);
void Cylinder_Print(const cylinder_t *c);
void Math3D_GetAABBPlanes(const aabb_t *ab, plane_t *r);

#ifdef _HARMATTAN_OPENGL
void glVertex3v_vc(const vector3_t *v);
void glVertex3v_ab(const aabb_t *v);
#endif

int Line_EqualsLine(const line_t *l1, const line_t *l2);
int AABB_EqualsAABB(const aabb_t *a1, const aabb_t *a2);
int Cylinder_EqualsCylinder(const cylinder_t *c1, const cylinder_t *c2);
int Plane_EqualsPlane(const plane_t *p1, const plane_t *p2);

#endif
