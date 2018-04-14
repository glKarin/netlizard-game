#ifndef KARIN_QUAT_H
#define KARIN_QUAT_H

#include "math3d_std.h"
#include "vector3.h"
#include "matrix44.h"

#define printfqt(x) printf(#x" -> "); Quat_Print(&(x));

typedef struct _quat_t
{
	NLfloat r;	    // real part
	vector3_t v;	    // imaginary vector
} quat_t;

quat_t Quat_Make();

void Quat_Print(const quat_t *q);

#endif
