#ifndef KARIN_GRAPH_H
#define KARIN_GRAPH_H

#include "vector.h"

#define printfra(x) printf(#x"->"); Ray_Print(&(x));
#define printfli(x) printf(#x"->"); Line_Print(&(x));
#define printftr(x) printf(#x"->"); Triangle_Print(&(x));
#define printfpl(x) printf(#x"->"); Plane_Print(&(x));
#define printfbd(x) printf(#x"->"); Bound_Print(&(x));
#define printfcy(x) printf(#x"->"); Cylinder_Print(&(x));

typedef struct _plane_t
{
	vector3_s position;
	vector3_s normal;
} plane_t;

typedef struct _ray_s
{
	vector3_s position;
	vector3_s direction;
} ray_s;

typedef struct _bound_s
{
	vector3_s min_position;
	vector3_s max_position;
} bound_s;

typedef struct _cylinder_s
{
	vector3_s position;
	vector3_s axis;
	NLfloat radius;
} cylinder_s;

typedef struct _line_s
{
	vector3_s a, b;
} line_s;

typedef struct _triangle_s
{
	vector3_s a, b, c;
	int face;
	vector3_s normal;
} triangle_s;


void Ray_Print(const ray_s *line);
void Plane_Print(const plane_t *plane);
void Bound_Print(const bound_s *aabb);
void Cylinder_Print(const cylinder_s *c);
void Math3D_GetAABBPlanes(const bound_s *ab, plane_t *r);
void Line_Print(const line_s *line);
void Triangle_Print(const triangle_s *tri);

#ifdef _HARMATTAN_OPENGL
void glVertex3v_vc(const vector3_s *v);
void glVertex3v_ab(const bound_s *v);
void glVertex3v_ls(const line_s *v);
void glVertex3v_tg(const triangle_s *v);
#endif

int Ray_EqualsRay(const ray_s *l1, const ray_s *l2);
int Bound_EqualsBound(const bound_s *a1, const bound_s *a2);
int Cylinder_EqualsCylinder(const cylinder_s *c1, const cylinder_s *c2);
int Plane_EqualsPlane(const plane_t *p1, const plane_t *p2);
int Line_EqualsLine(const line_s *l1, const line_s *l2);
int Triangle_EqualsTriangle(const triangle_s *t1, const triangle_s *t2);

#endif
