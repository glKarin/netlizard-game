#ifndef KARIN_MATRIX44_H
#define KARIN_MATRIX44_H

#include "math3d_std.h"

#define Matrix44_GjInverseNotSingularv(r, m) Matrix44_GjInversev(r, m, 0)
#define Matrix44_GjInverseNotSingularSelf(m) Matrix44_GjInverseSelf(m, 0)
#define printfm4(x) printf(#x"->"); Matrix44_Print(&(x));

typedef struct _matrix44_t
{
	NLfloat x[4][4];
} matrix44_t;

void Matrix44_Identity(matrix44_t *m);
void Matrix44_Make(matrix44_t *mat, NLfloat a, NLfloat b, NLfloat c, NLfloat d, NLfloat e, NLfloat f, NLfloat g, NLfloat h, NLfloat i, NLfloat j, NLfloat k, NLfloat l, NLfloat m, NLfloat n, NLfloat o, NLfloat p);
matrix44_t Matrix44_GjInverse(const matrix44_t *m, int singExc);

void Matrix44_Print(const matrix44_t *m);

void Matrix44_Scale(matrix44_t *m, NLfloat s);

int Matrix44_GjInversev(matrix44_t *r, const matrix44_t *m, int singExc);
void Matrix44_MultiplyMatrix44v(matrix44_t *r, const matrix44_t *a, const matrix44_t *b);
void Matrix44_Transposev(matrix44_t *r, const matrix44_t *mat);
void Matrix44_TransposeSelf(matrix44_t *mat);

void Matrix44_Makev(matrix44_t *mat, const NLfloat m[16]);

int Matrix44_GjInverseSelf(matrix44_t *m, int singExc);

#endif
