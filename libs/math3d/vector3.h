#ifndef KARIN_VECTOR3D_H
#define KARIN_VECTOR3D_H

#include "math3d_std.h"

#define printfv3(x) printf(#x"->"); Vector3_Print(&(x));

#define Vector3_AddVector3 Vector3_PlusVector3
#define Vector3_AddVector3v Vector3_PlusVector3v
#define Vector3_Invert Vector3_Inverse
#define Vector3_InvertSelf Vector3_Inverse
#define Vector3_NormalizeSelf Vector3_Normalize

typedef struct _vector3_s
{
	//NLfloat v[3];
	NLfloat x;
	NLfloat y;
	NLfloat z;
} vector3_s;

typedef struct _vector3_t point3_t;
typedef struct _vector3_t normal_t;
typedef struct _vector3_t vertex3_t;
typedef struct _vector3_t color3_t;

// 两单位矢量的点积为两矢量的夹角的cos
NLfloat Vector3_DotVector3(const vector3_s *a, const vector3_s *b);
vector3_s Vector3_SubtractVector3(const vector3_s *a, const vector3_s *b);
NLfloat Vector3_Mag(const vector3_s *a);
int Vector3_Valid(const vector3_s *a);
void Vector3_Normalize(vector3_s *a);
// 两矢量的叉积为垂直与两矢量的矢量，满足右手定律
vector3_s Vector3_CrossVector3(const vector3_s *v1, const vector3_s *v2);
vector3_s Vector3_PlusVector3(const vector3_s *a, const vector3_s *b);
vector3_s Vector3_Scale(const vector3_s *v, NLfloat a);
int Vector3_EqualsVector3(const vector3_s *v1, const vector3_s *v2);
void Vector3_Inverse(vector3_s *v);
int Vector3_EqualsVector3(const vector3_s *v1, const vector3_s *v2);
int Vector3_EqualsUnitVector3(const vector3_s *v1, const vector3_s *v2);

void Vector3_Print(const vector3_s *v);

vector3_s Vector3_MultiplyVector3(const vector3_s *a, const vector3_s *b);
vector3_s Vector3_DivideVector3(const vector3_s *a, const vector3_s *b);
void Vector3_PlusVector3v(vector3_s *r, const vector3_s *a, const vector3_s *b);
void Vector3_SubtractVector3v(vector3_s *r, const vector3_s *a, const vector3_s *b);
void Vector3_MultiplyVector3v(vector3_s *r, const vector3_s *a, const vector3_s *b);
void Vector3_DivideVector3v(vector3_s *r, const vector3_s *a, const vector3_s *b);
void Vector3_CrossVector3v(vector3_s *r, const vector3_s *a, const vector3_s *b);
void Vector3_ScaleSelf(vector3_s *a, NLfloat n);
vector3_s Vector3_Invertr(const vector3_s *a);
vector3_s Vector3_Normalizer(const vector3_s *a);
vector3_s Vector3_Direction(const vector3_s *a, const vector3_s *b);
void Vector3_Directionv(vector3_s *r, const vector3_s *a, const vector3_s *b);

#endif
