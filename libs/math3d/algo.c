#include "algo.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>

#define COLLISION_ZERO 0.0 //00001

vector3_s Math3D_GetTriangleNormal(const vector3_s *v0, const vector3_s *v1, const vector3_s *v2)
{
	vector3_s first = Vector3_SubtractVector3(v1, v0);
	vector3_s second = Vector3_SubtractVector3(v2, v0);

	//vector3_s normal = Vector3_CrossVector3(&second, &first); // org
	vector3_s normal = Vector3_CrossVector3(&first, &second); 
	Vector3_Normalize(&normal);

	return normal;
}

NLfloat Math3D_PointToPlaneDistance(const vector3_s *point, const plane_t *plane)
{
	NLfloat distance = Vector3_DotVector3(&(plane->normal), &(plane->position));
	return Vector3_DotVector3(point, &(plane->normal)) - distance;
}
// OpenEXR Imath
int Math3D_LineToPlaneIntersect(const ray_s *line, const plane_t *plane, vector3_s *point)
{
    NLfloat d = Vector3_DotVector3(&(plane->normal), &(line->direction));
    //if ( d == 0.0 ) return 0;
		if((d <= COLLISION_ZERO) && (d >= -COLLISION_ZERO)) 
			return 0;
		if(d == 0)
			return 0;
		NLfloat distance = Vector3_DotVector3(&(plane->normal), &(plane->position));
    NLfloat t = - (Vector3_DotVector3(&(plane->normal), &(line->position)) - distance) / d;
		if(point)
		{
			VECTORV_X(point) = VECTOR_X(line->position) + VECTOR_X(line->direction) * t;
			VECTORV_Y(point) = VECTOR_Y(line->position) + VECTOR_Y(line->direction) * t;
			VECTORV_Z(point) = VECTOR_Z(line->position) + VECTOR_Z(line->direction) * t;
		}
		return 1;
}

int Math3D_LineToPlaneCollision(const ray_s *line, const plane_t *plane, NLfloat *lamda, vector3_s *normal)
{
	NLfloat dotProduct = Vector3_DotVector3(&(line->direction), &(plane->normal));
	NLfloat l2;

	//判断是否平行于平面
	if((dotProduct <= COLLISION_ZERO) && (dotProduct >= -COLLISION_ZERO)) 
		return 0;

	if(dotProduct == 0)
		return 0;

	vector3_s vec = Vector3_SubtractVector3(&(plane->position), &(line->position));
	l2 = (Vector3_DotVector3(&(plane->normal), &vec)) / dotProduct;

	if (l2 <= -COLLISION_ZERO)
		return 0;

	if(normal)
		*normal = plane->normal;
	if(lamda)
		*lamda = l2;
	return 1;
}

int Math3D_PointInAABB(const vector3_s *a, const bound_s *aabb)
{
	if(!a || !aabb)
		return 0;
	const vector3_s *v1 = &(aabb->min_position);
	const vector3_s *v2 = &(aabb->max_position);
	return(
			(VECTORV_X(a) >= VECTORV_X(v1) && VECTORV_X(a) <= VECTORV_X(v2))
			&& (VECTORV_Y(a) >= VECTORV_Y(v1) && VECTORV_Y(a) <= VECTORV_Y(v2))
			&& (VECTORV_Z(a) >= VECTORV_Z(v1) && VECTORV_Z(a) <= VECTORV_Z(v2))
			? 1 : 0);
}

int Math3D_PointInAABB2D(const vector3_s *a, const bound_s *aabb)
{
	if(!a || !aabb)
		return 0;
	const vector3_s *v1 = &(aabb->min_position);
	const vector3_s *v2 = &(aabb->max_position);
	return(
			(VECTORV_X(a) >= VECTORV_X(v1) && VECTORV_X(a) <= VECTORV_X(v2))
			&& (VECTORV_Y(a) >= VECTORV_Y(v1) && VECTORV_Y(a) <= VECTORV_Y(v2))
			? 1 : 0);
}

int Math3D_LineToCylinderCollision(const ray_s *line, const cylinder_s *cylinder, NLfloat *lamda_r, vector3_s *normal_r, vector3_s *new_pos_r)
{
	if(!line || !cylinder)
		return 0;

	NLfloat lamda = 0.0;
	vector3_s new_pos = VECTOR3(0.0, 0.0, 0.0);
	vector3_s normal = VECTOR3(0.0, 0.0, 0.0);

	vector3_s RC = VECTOR3(0.0, 0.0, 0.0);
	NLfloat d = 0.0;
	NLfloat t = 0.0;
	NLfloat s = 0.0;
	vector3_s n = VECTOR3(0.0, 0.0, 0.0);
	//vector3_s D = VECTOR3(0.0, 0.0, 0.0);
	vector3_s O = VECTOR3(0.0, 0.0, 0.0);
	NLfloat ln = 0.0;
	NLfloat in = 0.0;
	NLfloat out = 0.0;

	// 计算线方向与圆柱体方向的面的的垂直方向
	n = Vector3_CrossVector3(&line->direction, &cylinder->axis);

	// 求长度
	ln = Vector3_Mag(&n);

	// 线方向是否与圆柱体方向平行
	if((ln <= COLLISION_ZERO) && (ln >= - COLLISION_ZERO) ) 
		return 0;

	if(ln == 0)
		return 0;
	Vector3_Normalize(&n);
	// 计算线起点与圆柱体位置间的方向
	RC = Vector3_SubtractVector3(&line->position, &cylinder->position);

	d = abs(Vector3_DotVector3(&RC, &n));

	if(d <= cylinder->radius)
	{
		O = Vector3_CrossVector3(&RC, &cylinder->axis);
		t = - Vector3_DotVector3(&O, &n) / ln;
		O = Vector3_CrossVector3(&n, &cylinder->axis);
		Vector3_Normalize(&O);
		NLfloat tmp_f2 = Vector3_DotVector3(&line->direction, &O);
		if(tmp_f2 == 0)
			return 0;
		s = abs(sqrt(cylinder->radius * cylinder->radius - d * d) / tmp_f2);

		in = t - s;
		out = t + s;

		if(in <= - COLLISION_ZERO){
			if(out <= - COLLISION_ZERO) 
				return 0;
			else 
				lamda = out;
		}
		else
			if (out <= - COLLISION_ZERO) {
				lamda = in;
			}
			else
				if(in < out)
					lamda = in;
				else
					lamda = out;

		vector3_s tmp = Vector3_Scale(&line->direction, lamda);
		new_pos = Vector3_PlusVector3(&line->position, &tmp);
		vector3_s HB = Vector3_SubtractVector3(&new_pos, &cylinder->position);
		NLfloat tmp_f = Vector3_DotVector3(&HB, &cylinder->axis);
		tmp = Vector3_Scale(&cylinder->axis, tmp_f);
		normal = Vector3_SubtractVector3(&HB, &tmp);
		Vector3_Normalize(&normal);

		if(lamda_r)
			*lamda_r = lamda;
		if(new_pos_r)
			*new_pos_r = new_pos;
		if(normal_r)
			*normal_r = normal;

		return 1;
	}

	return 0;
}

void Math3D_GetAABBPlanes(const bound_s *ab, plane_t *r)
{
#define COPY_NORMAL(n, xx, yy, zz) \
	{ \
		n.x = xx; \
		n.y = yy; \
		n.z = zz; \
	}
	if(!ab || !r)
		return;
	memset(r, 0, sizeof(plane_t) * 6);
	// bottom
	r[0].position = ab->min_position;
	COPY_NORMAL(r[0].normal, 0.0, 0.0, 1.0)
	// left
	r[1].position = ab->min_position;
	COPY_NORMAL(r[1].normal, 1.0, 0.0, 0.0)
	// front
	r[2].position = ab->min_position;
	COPY_NORMAL(r[2].normal, 0.0, 1.0, 0.0)
	// top
	r[3].position = ab->max_position;
	COPY_NORMAL(r[3].normal, 0.0, 0.0, -1.0)
	// right
	r[4].position = ab->max_position;
	COPY_NORMAL(r[4].normal, -1.0, 0.0, 0.0)
	// back
	r[5].position = ab->max_position;
	COPY_NORMAL(r[5].normal, 0.0, -1.0, 0.0)
#undef COPY_NORMAL
}

int Math3D_PointInTriangle(const vector3_s *p, const vector3_s *a, const vector3_s *b, const vector3_s *c)
{
	if(!p || !a || !b || !c)
		return 0;
	vector3_s v0 = Vector3_SubtractVector3(c, a);
	vector3_s v1 = Vector3_SubtractVector3(b, a);
	vector3_s v2 = Vector3_SubtractVector3(p, a);

	float dot00 = Vector3_DotVector3(&v0, &v0);
	float dot01 = Vector3_DotVector3(&v0, &v1);
	float dot02 = Vector3_DotVector3(&v0, &v2);
	float dot11 = Vector3_DotVector3(&v1, &v1);
	float dot12 = Vector3_DotVector3(&v1, &v2);

	float inverDeno = 1 / (dot00 * dot11 - dot01 * dot01);

	float u = (dot11 * dot02 - dot01 * dot12) * inverDeno;
	if (u < 0 || u > 1) // if u out of range, return directly
	{
		return 0;
	}

	float v = (dot00 * dot12 - dot01 * dot02) * inverDeno;
	if (v < 0 || v > 1) // if v out of range, return directly
	{
		return 0;
	}

	return u + v <= 1;
}

int Math3D_PointInSameSide(const vector3_s *p, const vector3_s *a, const vector3_s *b, const vector3_s *c)
{
	if(!p || !a || !b || !c)
		return 0;
	vector3_s ab = Vector3_SubtractVector3(b, a);
	vector3_s ac = Vector3_SubtractVector3(c, a);
	vector3_s ap = Vector3_SubtractVector3(p, a);

	vector3_s v1 = Vector3_CrossVector3(&ab, &ac);
	vector3_s v2 = Vector3_CrossVector3(&ab, &ap);

	// v1 and v2 should point to the same direction
	return Vector3_DotVector3(&v1, &v2) >= 0 ;
}
	
// Determine whether point P in triangle ABC
int Math3D_PointinTriangleBySameSide(const vector3_s *p, const vector3_s *a, const vector3_s *b, const vector3_s *c)
{
	if(!p || !a || !b || !c)
		return 0;
	return Math3D_PointInSameSide(p, a, b, c) 
		&& Math3D_PointInSameSide(p, b, c, a) 
		&& Math3D_PointInSameSide(p, c, a, b);
}

vector3_s Math3D_LineReflection(const vector3_s *v, const vector3_s *n)
{
	vector3_s r = VECTOR3(0.0, 0.0, 0.0);
	if(!v || !n)
		return r;
	NLfloat dot = Vector3_DotVector3(v, n);
	dot *= 2.0f;
	vector3_s nn = Vector3_Scale(n, dot);
	r = Vector3_SubtractVector3(v, &nn);
	return r;
	/*
		 R = V - 2 * DOT( V, N ) * N;
		 （R是反射射线，V是入射射线，N是平面法线）
		 */
}

vector3_s Math3D_ComputeTwoPointNormal(const vector3_s *p1, const vector3_s *p2)
{
	vector3_s l = VECTOR3(0.0, 0.0, 0.0);
	if(!p1 || !p2)
		return l;
	vector3_s dir = Vector3_SubtractVector3(p2, p1);
	Vector3_Normalize(&dir);
	return dir;
}

