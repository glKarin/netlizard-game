#ifndef KARIN_VECTOR2D_H
#define KARIN_VECTOR2D_H

#include "math3d_std.h"

#define printfv2(x) printf(#x"->"); Vector2_Print(&(x));

typedef struct _vector2_s
{
	NLfloat x;
	NLfloat y;
	// NLfloat v[2];
} vector2_s;

typedef struct _vector2_t point2_t;
typedef struct _vector2_t texcoord2_t;

NLfloat Vector2_DotVector2(const vector2_s *a, const vector2_s *b);
vector2_s Vector2_SubtractVector2(const vector2_s *a, const vector2_s *b);
NLfloat Vector2_Mag(const vector2_s *a);
int Vector2_Valid(const vector2_s *a);
void Vector2_Normalize(vector2_s *a);
NLfloat Vector2_CrossVector2(const vector2_s *v1, const vector2_s *v2);
vector2_s Vector2_PlusVector2(const vector2_s *a, const vector2_s *b);
vector2_s Vector2_Scale(const vector2_s *v, NLfloat a);
void Vector2_Inverse(vector2_s *v);
int Vector2_EqualsVector2(const vector2_s *v1, const vector2_s *v2);
int Vector2_EqualsUnitVector2(const vector2_s *v1, const vector2_s *v2);

void Vector2_Print(const vector2_s *v);

#endif

