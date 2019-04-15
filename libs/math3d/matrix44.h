#ifndef KARIN_MATRIX44_H
#define KARIN_MATRIX44_H

#include "math3d_std.h"

#define Matrix44_GjInverseNotSingularv(r, m) Matrix44_GjInversev(r, m, 0)
#define Matrix44_GjInverseNotSingularSelf(m) Matrix44_GjInverseSelf(m, 0)
#define printfm4(x) printf(#x"->"); Matrix44_Print(&(x));

typedef struct _matrix44_s
{
	NLfloat x[4][4];
} matrix44_s;

void Matrix44_Identity(matrix44_s *m);
void Matrix44_Make(matrix44_s *mat, NLfloat a, NLfloat b, NLfloat c, NLfloat d, NLfloat e, NLfloat f, NLfloat g, NLfloat h, NLfloat i, NLfloat j, NLfloat k, NLfloat l, NLfloat m, NLfloat n, NLfloat o, NLfloat p);
matrix44_s Matrix44_GjInverse(const matrix44_s *m, int singExc);

void Matrix44_Print(const matrix44_s *m);

void Matrix44_Scale(matrix44_s *m, NLfloat s);

int Matrix44_GjInversev(matrix44_s *r, const matrix44_s *m, int singExc);
void Matrix44_MultiplyMatrix44v(matrix44_s *r, const matrix44_s *a, const matrix44_s *b);
void Matrix44_Transposev(matrix44_s *r, const matrix44_s *mat);
void Matrix44_TransposeSelf(matrix44_s *mat);

void Matrix44_Makev(matrix44_s *mat, const NLfloat m[16]);

int Matrix44_GjInverseSelf(matrix44_s *m, int singExc);

#endif
