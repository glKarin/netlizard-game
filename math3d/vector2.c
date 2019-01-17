#include "vector.h"

#include <math.h>
#include <stdio.h>

#define SQR(x) ((x) * (x))

NLfloat Vector2_DotVector2(const vector2_t *a, const vector2_t *b)
{
	if(!a || !b)
		return 0.0;
	return(VECTORV_X(a) * VECTORV_X(b)
			+ VECTORV_Y(a) * VECTORV_Y(b));
}

vector2_t Vector2_SubtractVector2(const vector2_t *a, const vector2_t *b)
{
	vector2_t res = VECTOR2(0.0, 0.0);
	if(a && b)
	{
		VECTOR_X(res) = VECTORV_X(a) - VECTORV_X(b);
		VECTOR_Y(res) = VECTORV_Y(a) - VECTORV_Y(b);
	}
	return res;
}

NLfloat Vector2_Mag(const vector2_t *a)
{
	if(!a)
		return 0.0;
	return(sqrt(SQR(VECTORV_X(a)) + SQR(VECTORV_Y(a))));
}

void Vector2_Normalize(vector2_t *a)
{
	if(!a)
		return;
	NLfloat rep = Vector2_Mag(a);
	if(rep != 0.0)
	{
		NLfloat temp = 1.0 / rep;
		VECTORV_X(a) *= temp; 
		VECTORV_Y(a) *= temp; 
	}
	else
	{
		VECTORV_X(a) = 0.0; 
		VECTORV_Y(a) = 0.0; 
	}
}

int Vector2_Valid(const vector2_t *a)
{
	return(VECTORV_X(a) != 0 || VECTORV_Y(a) != 0) ? 1 : 0;
}

NLfloat Vector2_CrossVector2(const vector2_t *a, const vector2_t *b)
{
	if(a && b)
	{
		return VECTORV_X(a) * VECTORV_Y(b) - VECTORV_Y(a) * VECTORV_X(b);
	}
	return 0.0;
}

vector2_t Vector2_PlusVector2(const vector2_t *a, const vector2_t *b)
{
	vector2_t res = VECTOR2(0.0, 0.0);
	if(a && b)
	{
		VECTOR_X(res) = VECTORV_X(a) + VECTORV_X(b);
		VECTOR_Y(res) = VECTORV_Y(a) + VECTORV_Y(b);
	}
	return res;
}

void Vector2_Print(const vector2_t *v)
{
	if(!v)
		return;
	printf("vector 2D (%f, %f)\n", VECTORV_X(v), VECTORV_Y(v));
}

vector2_t Vector2_Scale(const vector2_t *v, NLfloat a)
{
	if(!v)
	{
		vector2_t r = VECTOR2(0.0, 0.0);
		return r;
	}
	vector2_t r = *v;
	VECTOR_X(r) *= a;
	VECTOR_Y(r) *= a;
	return r;
}

void Vector2_Inverse(vector2_t *v)
{
	if(!v)
		return;
	VECTORV_X(v) = - VECTORV_X(v);
	VECTORV_Y(v) = - VECTORV_Y(v);
}

int Vector2_EqualsVector2(const vector2_t *a, const vector2_t *b)
{
	if(!a || !b)
		return 0;
	return(VECTORV_X(a) == VECTORV_X(b) && VECTORV_Y(a) == VECTORV_Y(b) ? 1 : 0);
}

int Vector2_EqualsUnitVector2(const vector2_t *v1, const vector2_t *v2)
{
	if(!v1 || !v2)
		return 0;
	vector2_t a = *v1;
	Vector2_Normalize(&a);
	vector2_t b = *v2;
	Vector2_Normalize(&b);
	return(VECTOR_X(a) == VECTOR_X(b) && VECTOR_Y(a) == VECTOR_Y(b) ? 1 : 0);
}
