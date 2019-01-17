#ifndef KARIN_VECTOR2D_H
#define KARIN_VECTOR2D_H

#include "math3d_std.h"

#define printfv2(x) printf(#x"->"); Vector2_Print(&(x));

typedef struct _vector2_t
{
	NLfloat x;
	NLfloat y;
	// NLfloat v[2];
} vector2_t;

typedef struct _vector2_t point2_t;
typedef struct _vector2_t texcoord2_t;

NLfloat Vector2_DotVector2(const vector2_t *a, const vector2_t *b);
vector2_t Vector2_SubtractVector2(const vector2_t *a, const vector2_t *b);
NLfloat Vector2_Mag(const vector2_t *a);
int Vector2_Valid(const vector2_t *a);
void Vector2_Normalize(vector2_t *a);
NLfloat Vector2_CrossVector2(const vector2_t *v1, const vector2_t *v2);
vector2_t Vector2_PlusVector2(const vector2_t *a, const vector2_t *b);
vector2_t Vector2_Scale(const vector2_t *v, NLfloat a);
void Vector2_Inverse(vector2_t *v);
int Vector2_EqualsVector2(const vector2_t *v1, const vector2_t *v2);
int Vector2_EqualsUnitVector2(const vector2_t *v1, const vector2_t *v2);

void Vector2_Print(const vector2_t *v);

#endif

