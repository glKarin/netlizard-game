#ifndef KARIN_GLMATRIX44_H
#define KARIN_GLMATRIX44_H

#include "matrix44.h"

#define Matrix44_glTranspose Matrix44_Transpose
#define Matrix44_glTransposeSelf Matrix44_TransposeSelf
#define Matrix44_glIdentity Matrix44_Identity

typedef matrix44_s glmatrix44_s;

void Matrix44_glMake(glmatrix44_s *mat, NLfloat a, NLfloat b, NLfloat c, NLfloat d, NLfloat e, NLfloat f, NLfloat g, NLfloat h, NLfloat i, NLfloat j, NLfloat k, NLfloat l, NLfloat m, NLfloat n, NLfloat o, NLfloat p);

void Matrix44_glPrint(const glmatrix44_s *m);

void Matrix44_glMultiplyMatrix44v(glmatrix44_s *r, const glmatrix44_s *a, const glmatrix44_s *b);

void Matrix44_glMakev(glmatrix44_s *mat, const NLfloat m[16]);
void Matrix44_glRotate(glmatrix44_s *r, const glmatrix44_s *mat, NLfloat angle, NLfloat x, NLfloat y, NLfloat z);
void Matrix44_glRotateSelf(glmatrix44_s *mat, NLfloat angle, NLfloat x, NLfloat y, NLfloat z );
void Matrix44_glScaler(glmatrix44_s *r, const glmatrix44_s *mat, NLfloat x, NLfloat y, NLfloat z);
void Matrix44_glScaleSelf(glmatrix44_s *mat, NLfloat x, NLfloat y, NLfloat z);
void Matrix44_glTranslate(glmatrix44_s *r, const glmatrix44_s *mat, NLfloat x, NLfloat y, NLfloat z);
void Matrix44_glTranslateSelf(glmatrix44_s *mat, NLfloat x, NLfloat y, NLfloat z);

int Matrix44_glInverseSelf(glmatrix44_s *m);
int Matrix44_glInversev(glmatrix44_s *mat, const glmatrix44_s *m);

#endif

