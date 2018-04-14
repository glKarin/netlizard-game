#ifndef KARIN_MATH3D_BASE_ALGO_H
#define KARIN_MATH3D_BASE_ALGO_H

#include "vector3.h"
#include "matrix44.h"
#include "quat.h"

vector3_t Math3D_Vector3MultiplyMatrix44(const vector3_t *v, const matrix44_t *m);
matrix44_t Math3D_QuatToMatrix44(const quat_t *q);
matrix44_t Math3D_MakeQuatAndToMatrix44(const NLfloat r[], const NLfloat p[], const NLfloat s[]);

#endif
