#include "vector3.h"

#include <math.h>
#include <stdio.h>

#define SQR(x) ((x) * (x))

NLfloat Vector3_DotVector3(const vector3_t *a, const vector3_t *b)
{
	if(!a || !b)
		return 0.0;
	return(a->x * b->x
			+ a->y * b->y
			+ a->z * b->z);
}

vector3_t Vector3_SubtractVector3(const vector3_t *a, const vector3_t *b)
{
	vector3_t res = {0.0, 0.0, 0.0};
	if(a && b)
	{
		res.x = a->x - b->x;
		res.y = a->y - b->y;
		res.z = a->z - b->z;
	}
	return res;
}

NLfloat Vector3_Mag(const vector3_t *a)
{
	if(!a)
		return 0.0;
	return(sqrt(SQR(a->x) + SQR(a->y) + SQR(a->z)));
}

void Vector3_Normalize(vector3_t *a)
{
	if(!a)
		return;
	NLfloat rep = Vector3_Mag(a);
	if(rep != 0.0)
	{
		NLfloat temp = 1.0 / rep;
		a->x *= temp; 
		a->y *= temp; 
		a->z *= temp; 
	}
	else
	{
		a->x = 0.0; 
		a->y = 0.0; 
		a->z = 0.0; 
	}
}

int Vector3_Valid(const vector3_t *a)
{
	return(a->x != 0 || a->y != 0 || a->z != 0) ? 1 : 0;
}

vector3_t Vector3_CrossVector3(const vector3_t *v1, const vector3_t *v2)
{
	if(v1 && v2)
	{
		vector3_t vec = 
		{
			v1->y * v2->z - v1->z * v2->y,
			v1->z * v2->x - v1->x * v2->z,
			v1->x * v2->y - v1->y * v2->x
		};
		return vec;
	}
	vector3_t vec = {0.0, 0.0, 0.0};
	return vec;
}

vector3_t Vector3_PlusVector3(const vector3_t *a, const vector3_t *b)
{
	vector3_t res = {0.0, 0.0, 0.0};
	if(a && b)
	{
		res.x = a->x + b->x;
		res.y = a->y + b->y;
		res.z = a->z + b->z;
	}
	return res;
}

void Vector3_Print(const vector3_t *v)
{
	if(!v)
		return;
	printf("vector 3D (%f, %f, %f)\n", v->x, v->y, v->z);
}

vector3_t Vector3_Scale(const vector3_t *v, NLfloat a)
{
	if(!v)
	{
		vector3_t r = {0.0, 0.0, 0.0};
		return r;
	}
	vector3_t r = *v;
	r.x *= a;
	r.y *= a;
	r.z *= a;
	return r;
}

int Vector3_EqualsVector3(const vector3_t *v1, const vector3_t *v2)
{
	if(!v1 || !v2)
		return 0;
	return(v1->x == v2->x && v1->y == v2->y && v1->z && v2->z ? 1 : 0);
}

void Vector3_Inverse(vector3_t *v)
{
	if(!v)
		return;
	v->x = - v->x;
	v->y = - v->y;
	v->z = - v->z;
}

int Vector3_EqualsUnitVector3(const vector3_t *v1, const vector3_t *v2)
{
	if(!v1 || !v2)
		return 0;
	vector3_t vt1 = *v1;
	Vector3_Normalize(&vt1);
	vector3_t vt2 = *v2;
	Vector3_Normalize(&vt2);
	return(vt1.x == vt2.x && vt1.y == vt2.y && vt1.z == vt2.z ? 1 : 0);
}
