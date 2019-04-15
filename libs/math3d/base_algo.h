#ifndef KARIN_MATH3D_BASE_ALGO_H
#define KARIN_MATH3D_BASE_ALGO_H

#include "vector.h"
#include "matrix.h"
#include "quat.h"

vector3_s Math3D_Vector3MultiplyMatrix44(const vector3_s *v, const matrix44_s *m);
vector3_s Math3D_Vector3MultiplyMatrix44_3x3(const vector3_s *v, const matrix44_s *m);
void Math3D_QuatToMatrix44(matrix44_s *m, const quat_t *q);
void Math3D_MakeQuatAndToMatrix44(matrix44_s *m, const NLfloat r[], const NLfloat p[], const NLfloat s[]);

matrix44_s Math3D_Matrix44InverseTranspose(const matrix44_s *mat);
void Math3D_Matrix44InverseTransposev(matrix44_s *r, const matrix44_s *mat);

vector3_s Math3D_glVector3MultiplyMatrix44(const vector3_s *v, const glmatrix44_s *m);
vector3_s Math3D_glVector3MultiplyMatrix44_3x3(const vector3_s *v, const glmatrix44_s *m);

matrix44_s Math3D_glMatrix44InverseTranspose(const glmatrix44_s *mat);
void Math3D_glMatrix44InverseTransposev(glmatrix44_s *r, const glmatrix44_s *mat);

#endif
