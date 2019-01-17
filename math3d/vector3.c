#include "vector.h"

#include <math.h>
#include <stdio.h>

#define SQR(x) ((x) * (x))

NLfloat Vector3_DotVector3(const vector3_t *a, const vector3_t *b)
{
	if(!a || !b)
		return 0.0;
	return(VECTORV_X(a) * VECTORV_X(b)
			+ VECTORV_Y(a) * VECTORV_Y(b)
			+ VECTORV_Z(a) * VECTORV_Z(b));
}

vector3_t Vector3_SubtractVector3(const vector3_t *a, const vector3_t *b)
{
	vector3_t res = VECTOR3(0.0, 0.0, 0.0);
	Vector3_SubtractVector3v(&res, a, b);
	return res;
}

NLfloat Vector3_Mag(const vector3_t *a)
{
	if(!a)
		return 0.0;
	return(sqrt(SQR(VECTORV_X(a)) + SQR(VECTORV_Y(a)) + SQR(VECTORV_Z(a))));
}

void Vector3_Normalize(vector3_t *a)
{
	if(!a)
		return;
	NLfloat rep = Vector3_Mag(a);
	if(rep != 0.0)
	{
		NLfloat temp = 1.0 / rep;
		VECTORV_X(a) *= temp; 
		VECTORV_Y(a) *= temp; 
		VECTORV_Z(a) *= temp; 
	}
	else
	{
		VECTORV_X(a) = 0.0; 
		VECTORV_Y(a) = 0.0; 
		VECTORV_Z(a) = 0.0; 
	}
}

int Vector3_Valid(const vector3_t *a)
{
	return(VECTORV_X(a) != 0 || VECTORV_Y(a) != 0 || VECTORV_Z(a) != 0) ? 1 : 0;
}

vector3_t Vector3_CrossVector3(const vector3_t *a, const vector3_t *b)
{
	vector3_t res = VECTOR3(0.0, 0.0, 0.0);
	Vector3_CrossVector3v(&res, a, b);
	return res;
}

vector3_t Vector3_PlusVector3(const vector3_t *a, const vector3_t *b)
{
	vector3_t res = VECTOR3(0.0, 0.0, 0.0);
	Vector3_PlusVector3v(&res, a, b);
	return res;
}

void Vector3_Print(const vector3_t *v)
{
	if(!v)
		return;
	printf("vector 3D (%f, %f, %f)\n", VECTORV_X(v), VECTORV_Y(v), VECTORV_Z(v));
}

vector3_t Vector3_Scale(const vector3_t *v, NLfloat a)
{
	if(!v)
	{
		vector3_t r = VECTOR3(0.0, 0.0, 0.0);
		return r;
	}
	vector3_t r = *v;
	VECTOR_X(r) *= a;
	VECTOR_Y(r) *= a;
	VECTOR_Z(r) *= a;
	return r;
}

int Vector3_EqualsVector3(const vector3_t *a, const vector3_t *b)
{
	if(!a || !b)
		return 0;
	return(VECTORV_X(a) == VECTORV_X(b) && VECTORV_Y(a) == VECTORV_Y(b) && VECTORV_Z(a) == VECTORV_Z(b) ? 1 : 0);
}

void Vector3_Inverse(vector3_t *v)
{
	if(!v)
		return;
	VECTORV_X(v) = - VECTORV_X(v);
	VECTORV_Y(v) = - VECTORV_Y(v);
	VECTORV_Z(v) = - VECTORV_Z(v);
}

int Vector3_EqualsUnitVector3(const vector3_t *v1, const vector3_t *v2)
{
	if(!v1 || !v2)
		return 0;
	vector3_t a = *v1;
	Vector3_Normalize(&a);
	vector3_t b = *v2;
	Vector3_Normalize(&b);
	return(VECTOR_X(a) == VECTOR_X(b) && VECTOR_Y(a) == VECTOR_Y(b) && VECTOR_Z(a) == VECTOR_Z(b) ? 1 : 0);
}

vector3_t Vector3_MultiplyVector3(const vector3_t *a, const vector3_t *b)
{
	vector3_t res = VECTOR3(0.0, 0.0, 0.0);
	Vector3_MultiplyVector3v(&res, a, b);
	return res;
}

vector3_t Vector3_DivideVector3(const vector3_t *a, const vector3_t *b)
{
	vector3_t res = VECTOR3(0.0, 0.0, 0.0);
	Vector3_DivideVector3v(&res, a, b);
	return res;
}

void Vector3_PlusVector3v(vector3_t *r, const vector3_t *a, const vector3_t *b)
{
	if(!r || !a || !b)
		return;
	VECTORV_X(r) = VECTORV_X(a) + VECTORV_X(b);
	VECTORV_Y(r) = VECTORV_Y(a) + VECTORV_Y(b);
	VECTORV_Z(r) = VECTORV_Z(a) + VECTORV_Z(b);
}

void Vector3_SubtractVector3v(vector3_t *r, const vector3_t *a, const vector3_t *b)
{
	if(!r || !a || !b)
		return;
	VECTORV_X(r) = VECTORV_X(a) - VECTORV_X(b);
	VECTORV_Y(r) = VECTORV_Y(a) - VECTORV_Y(b);
	VECTORV_Z(r) = VECTORV_Z(a) - VECTORV_Z(b);
}

void Vector3_MultiplyVector3v(vector3_t *r, const vector3_t *a, const vector3_t *b)
{
	if(!r || !a || !b)
		return;
	VECTORV_X(r) = VECTORV_X(a) * VECTORV_X(b);
	VECTORV_Y(r) = VECTORV_Y(a) * VECTORV_Y(b);
	VECTORV_Z(r) = VECTORV_Z(a) * VECTORV_Z(b);
}

void Vector3_DivideVector3v(vector3_t *r, const vector3_t *a, const vector3_t *b)
{
	if(!r || !a || !b)
		return;
	if(VECTORV_X(b) == 0.0 || VECTORV_Y(b) == 0.0 || VECTORV_Z(b) == 0.0)
		return;

	VECTORV_X(r) = VECTORV_X(a) / VECTORV_X(b);
	VECTORV_Y(r) = VECTORV_Y(a) / VECTORV_Y(b);
	VECTORV_Z(r) = VECTORV_Z(a) / VECTORV_Z(b);
}

void Vector3_CrossVector3v(vector3_t *r, const vector3_t *a, const vector3_t *b)
{
	if(!r || !a || !b)
		return;
	VECTORV_X(r) = VECTORV_Y(a) * VECTORV_Z(b) - VECTORV_Z(a) * VECTORV_Y(b);
	VECTORV_Y(r) = VECTORV_Z(a) * VECTORV_X(b) - VECTORV_X(a) * VECTORV_Z(b);
	VECTORV_Z(r) = VECTORV_X(a) * VECTORV_Y(b) - VECTORV_Y(a) * VECTORV_X(b);
}

void Vector3_ScaleSelf(vector3_t *a, NLfloat n)
{
	if(!a)
		return;
	VECTORV_X(a) *= n;
	VECTORV_Y(a) *= n;
	VECTORV_Z(a) *= n;
}

vector3_t Vector3_Invertr(const vector3_t *a)
{
	vector3_t r = VECTOR3(0.0, 0.0, 0.0);
	if(a)
	{
		r = *a;
		Vector3_Inverse(&r);
	}
	return r;
}

vector3_t Vector3_Normalizer(const vector3_t *a)
{
	vector3_t r = VECTOR3(0.0, 0.0, 0.0);
	if(a)
	{
		r = *a;
		Vector3_Normalize(&r);
	}
	return r;
}

vector3_t Vector3_Direction(const vector3_t *a, const vector3_t *b)
{
	vector3_t r = VECTOR3(0, 0, 0);
	Vector3_Directionv(&r, a, b);
	return r;
}

void Vector3_Directionv(vector3_t *r, const vector3_t *a, const vector3_t *b)
{
	if(!r || !a || !b)
		return;
	Vector3_SubtractVector3v(r, b, a);
	Vector3_Normalize(r);
}
