#include "graph.h"

#include <stdio.h>
#include <GL/gl.h>

void Line_Print(const line_t *line)
{
	if(!line)
		return;
	printf("line (pos = %f %f %f, dir = %f %f %f)\n", line -> position.x, line -> position.y, line -> position.z, line -> direction.x, line -> direction.y, line -> direction.z);
}

void Plane_Print(const plane_t *plane)
{
	if(!plane)
		return;
	printf("plane (pos = %f %f %f, normal = %f %f %f)\n", plane -> position.x, plane -> position.y, plane -> position.z, plane -> normal.x, plane -> normal.y, plane -> normal.z);
}

void AABB_Print(const aabb_t *aabb)
{
	if(!aabb)
		return;
	printf("aabb (min = %f %f %f, max = %f %f %f)\n", aabb -> min_position.x, aabb -> min_position.y, aabb -> min_position.z, aabb -> max_position.x, aabb -> max_position.y, aabb -> max_position.z);
}

#ifdef _HARMATTAN_OPENGL
void glVertex3v_vc(const vector3_t *v)
{
	if(!v)
		return;
	glVertex3f(v -> x, v -> y, v -> z);
}

void glVertex3v_ab(const aabb_t *a)
{
	if(!a)
		return;
	glVertex3f(a -> min_position.x, a -> min_position.y, a -> min_position.z);
	glVertex3f(a -> max_position.x, a -> max_position.y, a -> max_position.z);
}
#endif

void Cylinder_Print(const cylinder_t *c)
{
	if(!c)
		return;
	printf("cylinder (pos = %f %f %f, axis = %f %f %f, radius = %f)\n", c -> position.x, c -> position.y, c -> position.z, c -> axis.x, c -> axis.y, c -> axis.z, c -> radius);
}

int Line_EqualsLine(const line_t *l1, const line_t *l2)
{
	if(!l1 || !l2)
		return 0;
	return(Vector3_EqualsVector3(&l1 -> position, &l2 -> position) && Vector3_EqualsVector3(&l1 -> direction, &l2 -> direction) ? 1 : 0);
}

int AABB_EqualsAABB(const aabb_t *a1, const aabb_t *a2)
{
	if(!a1 || !a2)
		return 0;
	return(Vector3_EqualsVector3(&a1 -> min_position, &a2 -> min_position) && Vector3_EqualsVector3(&a1 -> max_position, &a2 -> max_position) ? 1 : 0);
}

int Cylinder_EqualsCylinder(const cylinder_t *c1, const cylinder_t *c2)
{
	if(!c1 || !c2)
		return 0;
	return(Vector3_EqualsVector3(&c1 -> position, &c2 -> position) && Vector3_EqualsVector3(&c1 -> axis, &c2 -> axis) && c1 -> radius == c2 -> radius ? 1 : 0);
}

int Plane_EqualsPlane(const plane_t *p1, const plane_t *p2)
{
	return 0;
}

