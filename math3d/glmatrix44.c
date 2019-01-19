#include "matrix.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#define DEG2RAD (M_PI/180.0)
#define SQRTF(X)  (float) sqrt((float) (X))

static float Identity[16] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
};

void Matrix44_glMake(glmatrix44_t *mat, NLfloat a, NLfloat b, NLfloat c, NLfloat d, NLfloat e, NLfloat f, NLfloat g, NLfloat h, NLfloat i, NLfloat j, NLfloat k, NLfloat l, NLfloat m, NLfloat n, NLfloat o, NLfloat p)
{
	if(!mat)
		return;
	GLMATRIXV_M(mat, 0, 0) = a;
	GLMATRIXV_M(mat, 0, 1) = b;
	GLMATRIXV_M(mat, 0, 2) = c;
	GLMATRIXV_M(mat, 0, 3) = d;
	GLMATRIXV_M(mat, 1, 0) = e;
	GLMATRIXV_M(mat, 1, 1) = f;
	GLMATRIXV_M(mat, 1, 2) = g;
	GLMATRIXV_M(mat, 1, 3) = h;
	GLMATRIXV_M(mat, 2, 0) = i;
	GLMATRIXV_M(mat, 2, 1) = j;
	GLMATRIXV_M(mat, 2, 2) = k;
	GLMATRIXV_M(mat, 2, 3) = l;
	GLMATRIXV_M(mat, 3, 0) = m;
	GLMATRIXV_M(mat, 3, 1) = n;
	GLMATRIXV_M(mat, 3, 2) = o;
	GLMATRIXV_M(mat, 3, 3) = p;
}

void Matrix44_glPrint(const glmatrix44_t *m)
{
	if(!m)
		return;
	printf("glmatrix 4x4 {\n");
	int i;
	for(i = 0; i < 4; i++)
	{
		int j;
		for(j = 0; j < 4; j++)
		{
			printf("  %f", MATRIXV_M(m, i, j));
		}
		printf("\n");
	}
	printf("}\n");
}

void Matrix44_glMultiplyMatrix44v(glmatrix44_t *c, const glmatrix44_t *a, const glmatrix44_t *b)
{
#define A(row,col)  ((NLfloat *)a->x)[(col<<2)+row]
#define B(row,col)  ((NLfloat *)b->x)[(col<<2)+row]
#define P(row,col)  ((NLfloat *)c->x)[(col<<2)+row]
	int i;

	if(!c || !a || !b)
		return;

	Matrix44_glIdentity(c);

   for (i = 0; i < 4; i++) {
      const NLfloat ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
      P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
      P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
      P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
      P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
   }
#undef A
#undef B
#undef P
}

void Matrix44_glTranslateSelf(glmatrix44_t *mat, NLfloat x, NLfloat y, NLfloat z)
{
	if(!mat)
		return;
	NLfloat *m = (NLfloat *)mat->x;
	m[12] = m[0] * x + m[4] * y + m[8]  * z + m[12];
	m[13] = m[1] * x + m[5] * y + m[9]  * z + m[13];
	m[14] = m[2] * x + m[6] * y + m[10] * z + m[14];
	m[15] = m[3] * x + m[7] * y + m[11] * z + m[15];
}

void Matrix44_glTranslate(glmatrix44_t *r, const glmatrix44_t *mat, NLfloat x, NLfloat y, NLfloat z)
{
	if(!r || !mat)
		return;
	*r = *mat;
	Matrix44_glTranslateSelf(r, x, y, z);
}

void Matrix44_glScaleSelf(glmatrix44_t *mat, NLfloat x, NLfloat y, NLfloat z)
{
	if(!mat)
		return;
	NLfloat *m = (NLfloat *)mat->x;
	m[0] *= x;   m[4] *= y;   m[8]  *= z;
	m[1] *= x;   m[5] *= y;   m[9]  *= z;
	m[2] *= x;   m[6] *= y;   m[10] *= z;
	m[3] *= x;   m[7] *= y;   m[11] *= z;
}

void Matrix44_glScaler(glmatrix44_t *r, const glmatrix44_t *mat, NLfloat x, NLfloat y, NLfloat z)
{
	if(!r || !mat)
		return;
	*r = *mat;
	Matrix44_glScaleSelf(r, x, y, z);
}

void Matrix44_glRotateSelf(glmatrix44_t *mat, NLfloat angle, NLfloat x, NLfloat y, NLfloat z )
{
	if(!mat)
		return;
	NLfloat xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c, s, c;
	NLfloat m[16];
	unsigned optimized;
	glmatrix44_t mm, r;

	s = (NLfloat) sin( angle * DEG2RAD );
	c = (NLfloat) cos( angle * DEG2RAD );

	memcpy(m, Identity, sizeof(NLfloat)*16);
	optimized = 0;

#define M(row,col)  m[col*4+row]

	if (x == 0.0F) {
		if (y == 0.0F) {
			if (z != 0.0F) {
				optimized = 1;
				/* rotate only around z-axis */
				M(0,0) = c;
				M(1,1) = c;
				if (z < 0.0F) {
					M(0,1) = s;
					M(1,0) = -s;
				}
				else {
					M(0,1) = -s;
					M(1,0) = s;
				}
			}
		}
		else if (z == 0.0F) {
			optimized = 1;
			/* rotate only around y-axis */
			M(0,0) = c;
			M(2,2) = c;
			if (y < 0.0F) {
				M(0,2) = -s;
				M(2,0) = s;
			}
			else {
				M(0,2) = s;
				M(2,0) = -s;
			}
		}
	}
	else if (y == 0.0F) {
		if (z == 0.0F) {
			optimized = 1;
			/* rotate only around x-axis */
			M(1,1) = c;
			M(2,2) = c;
			if (x < 0.0F) {
				M(1,2) = s;
				M(2,1) = -s;
			}
			else {
				M(1,2) = -s;
				M(2,1) = s;
			}
		}
	}

	if (!optimized) {
		const NLfloat mag = SQRTF(x * x + y * y + z * z);

		if (mag <= 1.0e-4) {
			/* no rotation, leave mat as-is */
			return;
		}

		x /= mag;
		y /= mag;
		z /= mag;



		xx = x * x;
		yy = y * y;
		zz = z * z;
		xy = x * y;
		yz = y * z;
		zx = z * x;
		xs = x * s;
		ys = y * s;
		zs = z * s;
		one_c = 1.0F - c;

		/* We already hold the identity-matrix so we can skip some statements */
		M(0,0) = (one_c * xx) + c;
		M(0,1) = (one_c * xy) - zs;
		M(0,2) = (one_c * zx) + ys;
		/*    M(0,3) = 0.0F; */

		M(1,0) = (one_c * xy) + zs;
		M(1,1) = (one_c * yy) + c;
		M(1,2) = (one_c * yz) - xs;
		/*    M(1,3) = 0.0F; */

		M(2,0) = (one_c * zx) - ys;
		M(2,1) = (one_c * yz) + xs;
		M(2,2) = (one_c * zz) + c;
		/*    M(2,3) = 0.0F; */

		/*
			 M(3,0) = 0.0F;
			 M(3,1) = 0.0F;
			 M(3,2) = 0.0F;
			 M(3,3) = 1.0F;
			 */
	}
#undef M

	Matrix44_Makev(&mm, m); // if transpose, rotation orientation is inversed.
	r = *mat;
	Matrix44_glMultiplyMatrix44v( mat, &r, &mm );
}

void Matrix44_glRotate(glmatrix44_t *r, const glmatrix44_t *mat, NLfloat angle, NLfloat x, NLfloat y, NLfloat z)
{
	if(!r || !mat)
		return;
	*r = *mat;
	Matrix44_glRotateSelf(r, angle, x, y, z);
}

void Matrix44_glMakev(glmatrix44_t *mat, const NLfloat m[16])
{
#define M(col, row)  m[col*4+row]

	if(!mat)
		return;
	GLMATRIXV_M(mat, 0, 0) = M(0, 0);
	GLMATRIXV_M(mat, 0, 1) = M(0, 1);
	GLMATRIXV_M(mat, 0, 2) = M(0, 2);
	GLMATRIXV_M(mat, 0, 3) = M(0, 3);
	GLMATRIXV_M(mat, 1, 0) = M(1, 0);
	GLMATRIXV_M(mat, 1, 1) = M(1, 1);
	GLMATRIXV_M(mat, 1, 2) = M(1, 2);
	GLMATRIXV_M(mat, 1, 3) = M(1, 3);
	GLMATRIXV_M(mat, 2, 0) = M(2, 0);
	GLMATRIXV_M(mat, 2, 1) = M(2, 1);
	GLMATRIXV_M(mat, 2, 2) = M(2, 2);
	GLMATRIXV_M(mat, 2, 3) = M(2, 3);
	GLMATRIXV_M(mat, 3, 0) = M(3, 0);
	GLMATRIXV_M(mat, 3, 1) = M(3, 1);
	GLMATRIXV_M(mat, 3, 2) = M(3, 2);
	GLMATRIXV_M(mat, 3, 3) = M(3, 3);
#undef M
}

int Matrix44_glInversev(glmatrix44_t *r, const glmatrix44_t *mat)
{
#define MAT(m,r,c) (m)[(c)*4+(r)]
#define FABSF(x)   ((NLfloat) fabs(x))
#define SWAP_ROWS(a, b) { NLfloat *_tmp = a; (a)=(b); (b)=_tmp; }

   const NLfloat *m = (NLfloat *)mat->x;
   NLfloat *out = (NLfloat *)r->x;
   NLfloat wtmp[4][8];
   NLfloat m0, m1, m2, m3, s;
   NLfloat *r0, *r1, *r2, *r3;

	if(!r || !mat)
		return 0;

   r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];

   r0[0] = MAT(m,0,0), r0[1] = MAT(m,0,1),
   r0[2] = MAT(m,0,2), r0[3] = MAT(m,0,3),
   r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,

   r1[0] = MAT(m,1,0), r1[1] = MAT(m,1,1),
   r1[2] = MAT(m,1,2), r1[3] = MAT(m,1,3),
   r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,

   r2[0] = MAT(m,2,0), r2[1] = MAT(m,2,1),
   r2[2] = MAT(m,2,2), r2[3] = MAT(m,2,3),
   r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,

   r3[0] = MAT(m,3,0), r3[1] = MAT(m,3,1),
   r3[2] = MAT(m,3,2), r3[3] = MAT(m,3,3),
   r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;

   /* choose pivot - or die */
   if (FABSF(r3[0])>FABSF(r2[0])) SWAP_ROWS(r3, r2);
   if (FABSF(r2[0])>FABSF(r1[0])) SWAP_ROWS(r2, r1);
   if (FABSF(r1[0])>FABSF(r0[0])) SWAP_ROWS(r1, r0);
   if (0.0 == r0[0])  return 0;

   /* eliminate first variable     */
   m1 = r1[0]/r0[0]; m2 = r2[0]/r0[0]; m3 = r3[0]/r0[0];
   s = r0[1]; r1[1] -= m1 * s; r2[1] -= m2 * s; r3[1] -= m3 * s;
   s = r0[2]; r1[2] -= m1 * s; r2[2] -= m2 * s; r3[2] -= m3 * s;
   s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
   s = r0[4];
   if (s != 0.0) { r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s; }
   s = r0[5];
   if (s != 0.0) { r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s; }
   s = r0[6];
   if (s != 0.0) { r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s; }
   s = r0[7];
   if (s != 0.0) { r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s; }

   /* choose pivot - or die */
   if (FABSF(r3[1])>FABSF(r2[1])) SWAP_ROWS(r3, r2);
   if (FABSF(r2[1])>FABSF(r1[1])) SWAP_ROWS(r2, r1);
   if (0.0 == r1[1])  return 0;

   /* eliminate second variable */
   m2 = r2[1]/r1[1]; m3 = r3[1]/r1[1];
   r2[2] -= m2 * r1[2]; r3[2] -= m3 * r1[2];
   r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];
   s = r1[4]; if (0.0 != s) { r2[4] -= m2 * s; r3[4] -= m3 * s; }
   s = r1[5]; if (0.0 != s) { r2[5] -= m2 * s; r3[5] -= m3 * s; }
   s = r1[6]; if (0.0 != s) { r2[6] -= m2 * s; r3[6] -= m3 * s; }
   s = r1[7]; if (0.0 != s) { r2[7] -= m2 * s; r3[7] -= m3 * s; }

   /* choose pivot - or die */
   if (FABSF(r3[2])>FABSF(r2[2])) SWAP_ROWS(r3, r2);
   if (0.0 == r2[2])  return 0;

   /* eliminate third variable */
   m3 = r3[2]/r2[2];
   r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
   r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
   r3[7] -= m3 * r2[7];

   /* last check */
   if (0.0 == r3[3]) return 0;

   s = 1.0F/r3[3];             /* now back substitute row 3 */
   r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

   m2 = r2[3];                 /* now back substitute row 2 */
   s  = 1.0F/r2[2];
   r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
   r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
   m1 = r1[3];
   r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
   r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
   m0 = r0[3];
   r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
   r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

   m1 = r1[2];                 /* now back substitute row 1 */
   s  = 1.0F/r1[1];
   r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
   r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
   m0 = r0[2];
   r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
   r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

   m0 = r0[1];                 /* now back substitute row 0 */
   s  = 1.0F/r0[0];
   r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
   r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

   MAT(out,0,0) = r0[4]; MAT(out,0,1) = r0[5],
   MAT(out,0,2) = r0[6]; MAT(out,0,3) = r0[7],
   MAT(out,1,0) = r1[4]; MAT(out,1,1) = r1[5],
   MAT(out,1,2) = r1[6]; MAT(out,1,3) = r1[7],
   MAT(out,2,0) = r2[4]; MAT(out,2,1) = r2[5],
   MAT(out,2,2) = r2[6]; MAT(out,2,3) = r2[7],
   MAT(out,3,0) = r3[4]; MAT(out,3,1) = r3[5],
   MAT(out,3,2) = r3[6]; MAT(out,3,3) = r3[7];

   return 1;
#undef MAT
#undef FABSF
#undef SWAP_ROWS
}

int Matrix44_glInverseSelf(glmatrix44_t *mat)
{
	glmatrix44_t m;

	if(!mat)
		return 0;

	m = *mat;

	return Matrix44_glInversev(mat, &m);
}
