#include "vector2.h"

#include <math.h>
#include <stdio.h>

#define SQR(x) ((x) * (x))

NLfloat Vector2_DotVector2(const vector2_t *a, const vector2_t *b)
{
	if(!a || !b)
		return 0.0;
	return(a -> x * b -> x
			+ a -> y * b -> y);
}

vector2_t Vector2_SubtractVector2(const vector2_t *a, const vector2_t *b)
{
	vector2_t res = {0.0, 0.0};
	if(a && b)
	{
		res.x = a -> x - b -> x;
		res.y = a -> y - b -> y;
	}
	return res;
}

NLfloat Vector2_Mag(const vector2_t *a)
{
	if(!a)
		return 0.0;
	return(sqrt(SQR(a -> x) + SQR(a -> y)));
}

void Vector2_Normalize(vector2_t *a)
{
	if(!a)
		return;
	NLfloat rep = Vector2_Mag(a);
	if(rep != 0.0)
	{
		NLfloat temp = 1.0 / rep;
		a -> x *= temp; 
		a -> y *= temp; 
	}
	else
	{
		a -> x = 0.0; 
		a -> y = 0.0; 
	}
}

int Vector2_Valid(const vector2_t *a)
{
	return(a -> x != 0 || a -> y != 0) ? 1 : 0;
}

NLfloat Vector2_CrossVector2(const vector2_t *v1, const vector2_t *v2)
{
	if(v1 && v2)
	{
		return v1 -> x * v2 -> y - v1 -> y * v2 -> x;
	}
	return 0.0;
}

vector2_t Vector2_PlusVector2(const vector2_t *a, const vector2_t *b)
{
	vector2_t res = {0.0, 0.0};
	if(a && b)
	{
		res.x = a -> x + b -> x;
		res.y = a -> y + b -> y;
	}
	return res;
}

void Vector2_Print(const vector2_t *v)
{
	if(!v)
		return;
	printf("vector 2D (%f, %f)\n", v -> x, v -> y);
}

vector2_t Vector2_Scale(const vector2_t *v, NLfloat a)
{
	if(!v)
	{
		vector2_t r = {0.0, 0.0};
		return r;
	}
	vector2_t r = *v;
	r.x *= a;
	r.y *= a;
	return r;
}

void Vector2_Inverse(vector2_t *v)
{
	if(!v)
		return;
	v -> x = - v -> x;
	v -> y = - v -> y;
}

int Vector2_EqualsVector2(const vector2_t *v1, const vector2_t *v2)
{
	if(!v1 || !v2)
		return 0;
	return(v1 -> x == v2 -> x && v1 -> y == v2 -> y ? 1 : 0);
}

int Vector2_EqualsUnitVector2(const vector2_t *v1, const vector2_t *v2)
{
	if(!v1 || !v2)
		return 0;
	vector2_t vt1 = *v1;
	Vector2_Normalize(&vt1);
	vector2_t vt2 = *v2;
	Vector2_Normalize(&vt2);
	return(vt1.x == vt2.x && vt1.y == vt2.y ? 1 : 0);
}
