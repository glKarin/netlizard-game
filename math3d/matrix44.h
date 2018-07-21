#ifndef KARIN_MATRIX44_H
#define KARIN_MATRIX44_H

#include "math3d_std.h"

#define Matrix44_GjInverseNotSingular(m) Matrix44_GjInverse(m, 0)
#define printfm4(x) printf(#x"->"); Matrix44_Print(&(x));

typedef struct _matrix44_t
{
	NLfloat x[4][4];
} matrix44_t;

void Matrix44_Identity(matrix44_t *m);
matrix44_t Matrix44_TransposeOpenGLMatrix(const matrix44_t *mat);
matrix44_t Matrix44_Make();
matrix44_t Matrix44_MakeWithValue(NLfloat a, NLfloat b, NLfloat c, NLfloat d, NLfloat e, NLfloat f, NLfloat g, NLfloat h, NLfloat i, NLfloat j, NLfloat k, NLfloat l, NLfloat m, NLfloat n, NLfloat o, NLfloat p);
matrix44_t Matrix44_GjInverse(const matrix44_t *m, int singExc);
matrix44_t Matrix44_MultiplyMatrix44(const matrix44_t *a, const matrix44_t *b);

void Matrix44_Print(const matrix44_t *m);

void Matrix44_Scale(matrix44_t *m, NLfloat s);
#endif
