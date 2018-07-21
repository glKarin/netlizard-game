#ifndef KARIN_VECTOR3D_H
#define KARIN_VECTOR3D_H

#include "math3d_std.h"

#define printfv3(x) printf(#x"->"); Vector3_Print(&(x));

typedef struct _vector3_t
{
	NLfloat x;
	NLfloat y;
	NLfloat z;
} vector3_t;

typedef struct _vector3_t point3_t;
typedef struct _vector3_t normal_t;
typedef struct _vector3_t vertex3_t;
typedef struct _vector3_t color3_t;

// 两单位矢量的点积为两矢量的夹角的cos
NLfloat Vector3_DotVector3(const vector3_t *a, const vector3_t *b);
vector3_t Vector3_SubtractVector3(const vector3_t *a, const vector3_t *b);
NLfloat Vector3_Mag(const vector3_t *a);
int Vector3_Valid(const vector3_t *a);
void Vector3_Normalize(vector3_t *a);
// 两矢量的叉积为垂直与两矢量的矢量，满足右手定律
vector3_t Vector3_CrossVector3(const vector3_t *v1, const vector3_t *v2);
vector3_t Vector3_PlusVector3(const vector3_t *a, const vector3_t *b);
vector3_t Vector3_Scale(const vector3_t *v, NLfloat a);
int Vector3_EqualsVector3(const vector3_t *v1, const vector3_t *v2);
void Vector3_Inverse(vector3_t *v);
int Vector3_EqualsVector3(const vector3_t *v1, const vector3_t *v2);
int Vector3_EqualsUnitVector3(const vector3_t *v1, const vector3_t *v2);

void Vector3_Print(const vector3_t *v);

#endif
