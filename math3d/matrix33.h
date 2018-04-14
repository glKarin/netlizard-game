#ifndef KARIN_MATRIX33_H
#define KARIN_MATRIX33_H

#include "math3d_std.h"

#define printfm3(x) printf(#x" -> "); Matrix33_Print(&(x));

typedef struct _matrix33_t
{
	NLfloat x[3][3];
} matrix33_t;

void Matrix33_Identity(matrix33_t *m);
matrix33_t Matrix33_Make();
matrix33_t Matrix33_Make_With_Value(NLfloat a, NLfloat b, NLfloat c, NLfloat d, NLfloat e, NLfloat f, NLfloat g, NLfloat h, NLfloat i);

void Matrix33_Print(const matrix33_t *m);

#endif

