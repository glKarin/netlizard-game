#ifndef KARIN_MATH3D_BASE_ALGO_H
#define KARIN_MATH3D_BASE_ALGO_H

#include "vector.h"
#include "matrix.h"
#include "quat.h"

vector3_t Math3D_Vector3MultiplyMatrix44(const vector3_t *v, const matrix44_t *m);
vector3_t Math3D_Vector3MultiplyMatrix44_3x3(const vector3_t *v, const matrix44_t *m);
void Math3D_QuatToMatrix44(matrix44_t *m, const quat_t *q);
void Math3D_MakeQuatAndToMatrix44(matrix44_t *m, const NLfloat r[], const NLfloat p[], const NLfloat s[]);

matrix44_t Math3D_Matrix44InverseTranspose(const matrix44_t *mat);
void Math3D_Matrix44InverseTransposev(matrix44_t *r, const matrix44_t *mat);

vector3_t Math3D_glVector3MultiplyMatrix44(const vector3_t *v, const glmatrix44_t *m);
vector3_t Math3D_glVector3MultiplyMatrix44_3x3(const vector3_t *v, const glmatrix44_t *m);

matrix44_t Math3D_glMatrix44InverseTranspose(const glmatrix44_t *mat);
void Math3D_glMatrix44InverseTransposev(glmatrix44_t *r, const glmatrix44_t *mat);

#endif
