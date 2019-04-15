#include "opengl2_math.h"

#include <string.h>
#include <math.h>

typedef unsigned char boolean;
#define _TRUE 1
#define _FALSE 0

#define IF_NULL_RETURN(p) if(!p) return;

#define DEG2RAD (M_PI/180.0)

/***
 *** SQRTF: single-precision square root
 ***/
#if 0 /* _mesa_sqrtf() not accurate enough - temporarily disabled */
#  define SQRTF(X)  _mesa_sqrtf(X)
#else
#  define SQRTF(X)  (float) sqrt((float) (X))
#endif

static float Identity[16] = {
   1.0, 0.0, 0.0, 0.0,
   0.0, 1.0, 0.0, 0.0,
   0.0, 0.0, 1.0, 0.0,
   0.0, 0.0, 0.0, 1.0
};

#define A(row,col)  a[(col<<2)+row]
#define B(row,col)  b[(col<<2)+row]
#define P(row,col)  product[(col<<2)+row]
static void matmul4(float *product, const float *a, const float *b)
{
   int i;
   for (i = 0; i < 4; i++) {
      const float ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
      P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
      P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
      P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
      P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
   }
}
#undef A
#undef B
#undef P

/**
 * Transform a 4-element row vector (1x4 matrix) by a 4x4 matrix.  This
 * function is used for transforming clipping plane equations and spotlight
 * directions.
 * Mathematically,  u = v * m.
 * Input:  v - input vector
 *         m - transformation matrix
 * Output:  u - transformed vector
 */
static void _mesa_transform_vector(float u[4], const float v[4], const float m[16])
{
   const float v0 = v[0], v1 = v[1], v2 = v[2], v3 = v[3];
#define M(row,col)  m[row + col*4]
   u[0] = v0 * M(0,0) + v1 * M(1,0) + v2 * M(2,0) + v3 * M(3,0);
   u[1] = v0 * M(0,1) + v1 * M(1,1) + v2 * M(2,1) + v3 * M(3,1);
   u[2] = v0 * M(0,2) + v1 * M(1,2) + v2 * M(2,2) + v3 * M(3,2);
   u[3] = v0 * M(0,3) + v1 * M(1,3) + v2 * M(2,3) + v3 * M(3,3);
#undef M
}

static void _math_matrix_mul_floats(GL2_Matrix44 *dest, const float *m)
{
   matmul4(dest->m, dest->m, m);
}

static void matrix_multf(GL2_Matrix44 *mat, const float *m)
{
      matmul4( mat->m, mat->m, m );
}

static void _math_transposef(float to[16], const float from[16])
{
   to[0] = from[0];
   to[1] = from[4];
   to[2] = from[8];
   to[3] = from[12];
   to[4] = from[1];
   to[5] = from[5];
   to[6] = from[9];
   to[7] = from[13];
   to[8] = from[2];
   to[9] = from[6];
   to[10] = from[10];
   to[11] = from[14];
   to[12] = from[3];
   to[13] = from[7];
   to[14] = from[11];
   to[15] = from[15];
}

void Mesa_glTranslate(GL2_Matrix44 *mat, float x, float y, float z)
{
	IF_NULL_RETURN(mat)
   float *m = mat->m;
   m[12] = m[0] * x + m[4] * y + m[8]  * z + m[12];
   m[13] = m[1] * x + m[5] * y + m[9]  * z + m[13];
   m[14] = m[2] * x + m[6] * y + m[10] * z + m[14];
   m[15] = m[3] * x + m[7] * y + m[11] * z + m[15];
}

void Mesa_glRotate(GL2_Matrix44 *mat, float angle, float x, float y, float z)
{
	IF_NULL_RETURN(mat)
   float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c, s, c;
   float m[16];
   boolean optimized;

   s = (float) sin( angle * DEG2RAD );
   c = (float) cos( angle * DEG2RAD );

   memcpy(m, Identity, sizeof(float)*16);
   optimized = _FALSE;

#define M(row,col)  m[col*4+row]

   if (x == 0.0F) {
      if (y == 0.0F) {
         if (z != 0.0F) {
            optimized = _TRUE;
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
         optimized = _TRUE;
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
         optimized = _TRUE;
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
      const float mag = SQRTF(x * x + y * y + z * z);

      if (mag <= 1.0e-4) {
         /* no rotation, leave mat as-is */
         return;
      }

      x /= mag;
      y /= mag;
      z /= mag;


      /*
       *     Arbitrary axis rotation matrix.
       *
       *  This is composed of 5 matrices, Rz, Ry, T, Ry', Rz', multiplied
       *  like so:  Rz * Ry * T * Ry' * Rz'.  T is the final rotation
       *  (which is about the X-axis), and the two composite transforms
       *  Ry' * Rz' and Rz * Ry are (respectively) the rotations necessary
       *  from the arbitrary axis to the X-axis then back.  They are
       *  all elementary rotations.
       *
       *  Rz' is a rotation about the Z-axis, to bring the axis vector
       *  into the x-z plane.  Then Ry' is applied, rotating about the
       *  Y-axis to bring the axis vector parallel with the X-axis.  The
       *  rotation about the X-axis is then performed.  Ry and Rz are
       *  simply the respective inverse transforms to bring the arbitrary
       *  axis back to its original orientation.  The first transforms
       *  Rz' and Ry' are considered inverses, since the data from the
       *  arbitrary axis gives you info on how to get to it, not how
       *  to get away from it, and an inverse must be applied.
       *
       *  The basic calculation used is to recognize that the arbitrary
       *  axis vector (x, y, z), since it is of unit length, actually
       *  represents the sines and cosines of the angles to rotate the
       *  X-axis to the same orientation, with theta being the angle about
       *  Z and phi the angle about Y (in the order described above)
       *  as follows:
       *
       *  cos ( theta ) = x / sqrt ( 1 - z^2 )
       *  sin ( theta ) = y / sqrt ( 1 - z^2 )
       *
       *  cos ( phi ) = sqrt ( 1 - z^2 )
       *  sin ( phi ) = z
       *
       *  Note that cos ( phi ) can further be inserted to the above
       *  formulas:
       *
       *  cos ( theta ) = x / cos ( phi )
       *  sin ( theta ) = y / sin ( phi )
       *
       *  ...etc.  Because of those relations and the standard trigonometric
       *  relations, it is pssible to reduce the transforms down to what
       *  is used below.  It may be that any primary axis chosen will give the
       *  same results (modulo a sign convention) using thie method.
       *
       *  Particularly nice is to notice that all divisions that might
       *  have caused trouble when parallel to certain planes or
       *  axis go away with care paid to reducing the expressions.
       *  After checking, it does perform correctly under all cases, since
       *  in all the cases of division where the denominator would have
       *  been zero, the numerator would have been zero as well, giving
       *  the expected result.
       */

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

   matrix_multf(mat, m);
}

void Mesa_glScale(GL2_Matrix44 *mat, float x, float y, float z)
{
	IF_NULL_RETURN(mat)
   float *m = mat->m;
   m[0] *= x;   m[4] *= y;   m[8]  *= z;
   m[1] *= x;   m[5] *= y;   m[9]  *= z;
   m[2] *= x;   m[6] *= y;   m[10] *= z;
   m[3] *= x;   m[7] *= y;   m[11] *= z;
}

void Mesa_glLoadMatrix(GL2_Matrix44 *mat, const float *m)
{
	IF_NULL_RETURN(mat)
	if (!m) return;
   memcpy(mat->m, m, 16 * sizeof(float));
}

void Mesa_glLoadTransposeMatrix(GL2_Matrix44 *mat, const float *m)
{
	IF_NULL_RETURN(mat)
   if (!m) return;
   float tm[16];
   _math_transposef(tm, m);
   Mesa_glLoadMatrix(mat, tm);
}

void Mesa_glLoadIdentity(GL2_Matrix44 *mat)
{
	IF_NULL_RETURN(mat)
   memcpy(mat->m, Identity, 16 * sizeof(float));
}

void Mesa_glMultMatrix(GL2_Matrix44 *mat, const float *m)
{
   IF_NULL_RETURN(mat)
   if (!m) return;
   _math_matrix_mul_floats(mat, m);
}

void Mesa_glMultTransposeMatrix(GL2_Matrix44 *mat, const float *m)
{
	IF_NULL_RETURN(mat)
   if (!m) return;
   float tm[16];
   _math_transposef(tm, m);
   Mesa_glMultMatrix(mat, tm);
}

void Mesa_glFrustum(GL2_Matrix44 *mat, float left, float right, float bottom, float top, float nearval, float farval)
{
   IF_NULL_RETURN(mat)
   if (nearval <= 0.0 ||
       farval <= 0.0 ||
       nearval == farval ||
       left == right ||
       top == bottom)
   {
      //_mesa_error( ctx,  GL_INVALID_VALUE, "glFrustum" );
      return;
   }

   float x, y, a, b, c, d;
   float m[16];

   x = (2.0F*nearval) / (right-left);
   y = (2.0F*nearval) / (top-bottom);
   a = (right+left) / (right-left);
   b = (top+bottom) / (top-bottom);
   c = -(farval+nearval) / ( farval-nearval);
   d = -(2.0F*farval*nearval) / (farval-nearval);  /* error? */

#define M(row,col)  m[col*4+row]
   M(0,0) = x;     M(0,1) = 0.0F;  M(0,2) = a;      M(0,3) = 0.0F;
   M(1,0) = 0.0F;  M(1,1) = y;     M(1,2) = b;      M(1,3) = 0.0F;
   M(2,0) = 0.0F;  M(2,1) = 0.0F;  M(2,2) = c;      M(2,3) = d;
   M(3,0) = 0.0F;  M(3,1) = 0.0F;  M(3,2) = -1.0F;  M(3,3) = 0.0F;
#undef M

   matrix_multf(mat, m);
}

void Mesa_glOrtho(GL2_Matrix44 *mat, float left, float right, float bottom, float top, float nearval, float farval)
{
	IF_NULL_RETURN(mat)

   if (left == right ||
       bottom == top ||
       nearval == farval)
   {
	   //_mesa_error( ctx,  GL_INVALID_VALUE, "glOrtho" );
	   return;
   }
	float m[16];

#define M(row,col)  m[col*4+row]
   M(0,0) = 2.0F / (right-left);
   M(0,1) = 0.0F;
   M(0,2) = 0.0F;
   M(0,3) = -(right+left) / (right-left);

   M(1,0) = 0.0F;
   M(1,1) = 2.0F / (top-bottom);
   M(1,2) = 0.0F;
   M(1,3) = -(top+bottom) / (top-bottom);

   M(2,0) = 0.0F;
   M(2,1) = 0.0F;
   M(2,2) = -2.0F / (farval-nearval);
   M(2,3) = -(farval+nearval) / (farval-nearval);

   M(3,0) = 0.0F;
   M(3,1) = 0.0F;
   M(3,2) = 0.0F;
   M(3,3) = 1.0F;
#undef M

   matrix_multf(mat, m);
}

void Mesa_glTransform(float r[3], const float p[3], const GL2_Matrix44 *mat)
{
	IF_NULL_RETURN(mat)
	float v[4] = {p[0], p[1], p[2], 1};
	float u[4];
	_mesa_transform_vector(u, v, mat->m);
	r[0] = u[0] / u[3];
	r[1] = u[1] / u[3];
	r[2] = u[2] / u[3];
}
