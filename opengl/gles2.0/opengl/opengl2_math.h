#ifndef KARIN_MESAGL_MATH_H
#define KARIN_MESAGL_MATH_H

#include "opengl2_def.h"

void Mesa_glTranslate(GL2_Matrix44 *mat, float x, float y, float z);
void Mesa_glRotate(GL2_Matrix44 *mat, float angle, float x, float y, float z);
void Mesa_glScale(GL2_Matrix44 *mat, float x, float y, float z);
void Mesa_glLoadMatrix(GL2_Matrix44 *mat, const float *m);
void Mesa_glLoadIdentity(GL2_Matrix44 *mat);
void Mesa_glLoadTransposeMatrix(GL2_Matrix44 *mat, const float *m);
void Mesa_glMultMatrix(GL2_Matrix44 *mat, const float *m);
void Mesa_glMultTransposeMatrix(GL2_Matrix44 *mat, const float *m);
void Mesa_glFrustum(GL2_Matrix44 *mat, float left, float right, float bottom, float top, float nearval, float farval);
void Mesa_glOrtho(GL2_Matrix44 *mat, float left, float right, float bottom, float top, float nearval, float farval);
void Mesa_glTransform(float r[3], const float p[3], const GL2_Matrix44 *mat);

#endif

