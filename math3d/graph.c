#include "graph.h"

#include <stdio.h>
#include <GL/gl.h>

void Line_Print(const line_t *line)
{
	if(!line)
		return;
	printf("line (pos = %f %f %f, dir = %f %f %f)\n", VECTOR_X(line->position), VECTOR_Y(line->position), VECTOR_Z(line->position), VECTOR_X(line->direction), VECTOR_Y(line->direction), VECTOR_Z(line->direction));
}

void Plane_Print(const plane_t *plane)
{
	if(!plane)
		return;
	printf("plane (pos = %f %f %f, normal = %f %f %f)\n", VECTOR_X(plane->position), VECTOR_Y(plane->position), VECTOR_Z(plane->position), VECTOR_X(plane->normal), VECTOR_Y(plane->normal), VECTOR_Z(plane->normal));
}

void AABB_Print(const aabb_t *aabb)
{
	if(!aabb)
		return;
	printf("aabb (min = %f %f %f, max = %f %f %f)\n", VECTOR_X(aabb->min_position), VECTOR_Y(aabb->min_position), VECTOR_Z(aabb->min_position), VECTOR_X(aabb->max_position), VECTOR_Y(aabb->max_position), VECTOR_Z(aabb->max_position));
}

void LineSegment_Print(const line_segment_t *line)
{
	if(!line)
		return;
	printf("line Segment (A = %f %f %f, B = %f %f %f)\n", VECTOR_X(line->a), VECTOR_Y(line->a), VECTOR_Z(line->a), VECTOR_X(line->b), VECTOR_Y(line->b), VECTOR_Z(line->b));
}

void Triangle_Print(const triangle_t *tri)
{
	if(!tri)
		return;
	printf("triangle (A = %f %f %f, B = %f %f %f, C = %f %f %f, normal = %f %f %f, face = %d)\n", VECTOR_X(tri->a), VECTOR_Y(tri->a), VECTOR_Z(tri->a), VECTOR_X(tri->b), VECTOR_Y(tri->b), VECTOR_Z(tri->b), VECTOR_X(tri->c), VECTOR_Y(tri->c), VECTOR_Z(tri->c), VECTOR_X(tri->normal), VECTOR_Y(tri->normal), VECTOR_Z(tri->normal), tri->face);
}

#ifdef _HARMATTAN_OPENGL
void glVertex3v_vc(const vector3_t *v)
{
	if(!v)
		return;
	glVertex3f(VECTOR3V_X(v), VECTOR3V_Y(v), VECTOR3V_Z(v));
}

void glVertex3v_ab(const aabb_t *a)
{
	if(!a)
		return;
	glVertex3f(VECTOR_X(a->min_position), VECTOR_Y(a->min_position), VECTOR_Z(a->min_position));
	glVertex3f(VECTOR_X(a->max_position), VECTOR_Y(a->max_position), VECTOR_Z(a->max_position));
}

void glVertex3v_ls(const line_segment_t *l)
{
	if(!l)
		return;
	glVertex3f(VECTOR_X(l->a), VECTOR_Y(l->a), VECTOR_Z(l->a));
	glVertex3f(VECTOR_X(l->b), VECTOR_Y(l->b), VECTOR_Z(l->b));
}

void glVertex3v_tg(const triangle_t *t)
{
	if(!t)
		return;
	glVertex3f(VECTOR_X(t->a), VECTOR_Y(t->a), VECTOR_Z(t->a));
	glVertex3f(VECTOR_X(t->b), VECTOR_Y(t->b), VECTOR_Z(t->b));
	glVertex3f(VECTOR_X(t->c), VECTOR_Y(t->c), VECTOR_Z(t->c));
}
#endif

void Cylinder_Print(const cylinder_t *c)
{
	if(!c)
		return;
	printf("cylinder (pos = %f %f %f, axis = %f %f %f, radius = %f)\n", VECTOR_X(c->position), VECTOR_Y(c->position), VECTOR_Z(c->position), VECTOR_X(c->axis), VECTOR_Y(c->axis), VECTOR_Z(c->axis), c->radius);
}

int Line_EqualsLine(const line_t *l1, const line_t *l2)
{
	if(!l1 || !l2)
		return 0;
	return(Vector3_EqualsVector3(&l1->position, &l2->position) && Vector3_EqualsVector3(&l1->direction, &l2->direction) ? 1 : 0);
}

int AABB_EqualsAABB(const aabb_t *a1, const aabb_t *a2)
{
	if(!a1 || !a2)
		return 0;
	return(Vector3_EqualsVector3(&a1->min_position, &a2->min_position) && Vector3_EqualsVector3(&a1->max_position, &a2->max_position) ? 1 : 0);
}

int Cylinder_EqualsCylinder(const cylinder_t *c1, const cylinder_t *c2)
{
	if(!c1 || !c2)
		return 0;
	return(Vector3_EqualsVector3(&c1->position, &c2->position) && Vector3_EqualsVector3(&c1->axis, &c2->axis) && c1->radius == c2->radius ? 1 : 0);
}

int Plane_EqualsPlane(const plane_t *p1, const plane_t *p2)
{
	return 0;
}

int LineSegment_EqualsLineSegment(const line_segment_t *l1, const line_segment_t *l2)
{
	if(!l1 || !l2)
		return 0;
	return(((Vector3_EqualsVector3(&l1->a, &l2->a) && Vector3_EqualsVector3(&l1->b, &l2->b)) || (Vector3_EqualsVector3(&l1->a, &l2->b) && Vector3_EqualsVector3(&l1->b, &l2->a))) ? 1 : 0);
}

int Triangle_EqualsTriangle(const triangle_t *t1, const triangle_t *t2)
{
	return 0;
}

