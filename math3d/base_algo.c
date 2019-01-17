#include "base_algo.h"

void Math3D_MakeQuatAndToMatrix44(matrix44_t *m, const NLfloat r[], const NLfloat p[], const NLfloat s[])
{
	if(!m || !r || !p || !s)
		return;
	quat_t q = Quat_Make();
	VECTOR_X(q.v) = r[0];
	VECTOR_Y(q.v) = r[1];
	VECTOR_Z(q.v) = r[2];
	q.r = r[3];
	Math3D_QuatToMatrix44(m, &q);
	//m.setAxisAngle(q.axis(), q.angle());
	/*
		 m[0][3] = p[0];
		 m[1][3] = p[1];
		 m[2][3] = p[2];
		 */
	MATRIXV_M(m, 3, 0) = p[0];
	MATRIXV_M(m, 3, 1) = p[1];
	MATRIXV_M(m, 3, 2) = p[2];
	MATRIXV_M(m, 3, 3) = 1.0;
	//vector3_t scale = {s[0], s[1], s[2]};
	//return g_transpose_matrix(m);
}

vector3_t Math3D_Vector3MultiplyMatrix44(const vector3_t *v, const matrix44_t *m)
{
	if(!v || !m)
	{
		vector3_t r = VECTOR3(0.0, 0.0, 0.0);
		return r;
	}
	NLfloat x = (NLfloat)(VECTORV_X(v) * MATRIXV_M(m, 0, 0) + VECTORV_Y(v) * MATRIXV_M(m, 1, 0) + VECTORV_Z(v) * MATRIXV_M(m, 2, 0) + MATRIXV_M(m, 3, 0));
	NLfloat y = (NLfloat)(VECTORV_X(v) * MATRIXV_M(m, 0, 1) + VECTORV_Y(v) * MATRIXV_M(m, 1, 1) + VECTORV_Z(v) * MATRIXV_M(m, 2, 1) + MATRIXV_M(m, 3, 1));
	NLfloat z = (NLfloat)(VECTORV_X(v) * MATRIXV_M(m, 0, 2) + VECTORV_Y(v) * MATRIXV_M(m, 1, 2) + VECTORV_Z(v) * MATRIXV_M(m, 2, 2) + MATRIXV_M(m, 3, 2));
	NLfloat w = (NLfloat)(VECTORV_X(v) * MATRIXV_M(m, 0, 3) + VECTORV_Y(v) * MATRIXV_M(m, 1, 3) + VECTORV_Z(v) * MATRIXV_M(m, 2, 3) + MATRIXV_M(m, 3, 3));

	vector3_t r = VECTOR3(x / w, y / w, z / w);
	return r;
}

vector3_t Math3D_Vector3MultiplyMatrix44_3x3(const vector3_t *v, const matrix44_t *m)
{
	if(!v || !m)
	{
		vector3_t r = VECTOR3(0.0, 0.0, 0.0);
		return r;
	}
	NLfloat x = (NLfloat)(VECTORV_X(v) * MATRIXV_M(m, 0, 0) + VECTORV_Y(v) * MATRIXV_M(m, 1, 0) + VECTORV_Z(v) * MATRIXV_M(m, 2, 0));
	NLfloat y = (NLfloat)(VECTORV_X(v) * MATRIXV_M(m, 0, 1) + VECTORV_Y(v) * MATRIXV_M(m, 1, 1) + VECTORV_Z(v) * MATRIXV_M(m, 2, 1));
	NLfloat z = (NLfloat)(VECTORV_X(v) * MATRIXV_M(m, 0, 2) + VECTORV_Y(v) * MATRIXV_M(m, 1, 2) + VECTORV_Z(v) * MATRIXV_M(m, 2, 2));

	vector3_t r = VECTOR3(x, y, z);
	return r;
}

void Math3D_QuatToMatrix44(matrix44_t *m, const quat_t *q)
{
	if(!m || !q)
		return;
	return Matrix44_Make(m, 
			1. - 2.0 * (VECTOR_Y(q->v) * VECTOR_Y(q->v) + VECTOR_Z(q->v) * VECTOR_Z(q->v)),
			2.0 * (VECTOR_X(q->v) * VECTOR_Y(q->v) + VECTOR_Z(q->v) * q->r),
			2.0 * (VECTOR_Z(q->v) * VECTOR_X(q->v) - VECTOR_Y(q->v) * q->r),
			0.,

			2.0 * (VECTOR_X(q->v) * VECTOR_Y(q->v) - VECTOR_Z(q->v) * q->r),
			1. - 2.0 * (VECTOR_Z(q->v) * VECTOR_Z(q->v) + VECTOR_X(q->v) * VECTOR_X(q->v)),
			2.0 * (VECTOR_Y(q->v) * VECTOR_Z(q->v) + VECTOR_X(q->v) * q->r),
			0.,

			2.0 * (VECTOR_Z(q->v) * VECTOR_X(q->v) + VECTOR_Y(q->v) * q->r),
			2.0 * (VECTOR_Y(q->v) * VECTOR_Z(q->v) - VECTOR_X(q->v) * q->r),
			1. - 2.0 * (VECTOR_Y(q->v) * VECTOR_Y(q->v) + VECTOR_X(q->v) * VECTOR_X(q->v)),
			0.,

			0.,
			0.,
			0.,
			1.0
			);
}

matrix44_t Math3D_Matrix44InverseTranspose(const matrix44_t *mat)
{
	matrix44_t r;
	Math3D_Matrix44InverseTransposev(&r, mat);
	return r;
}

void Math3D_Matrix44InverseTransposev(matrix44_t *r, const matrix44_t *mat)
{
	if(!r || !mat)
		return;

	Matrix44_GjInverseNotSingularv(r, mat);
	Matrix44_TransposeSelf(r);
}

vector3_t Math3D_glVector3MultiplyMatrix44(const vector3_t *v, const glmatrix44_t *m)
{
	NLfloat u[4];
	vector3_t r;
   const NLfloat v0 = VECTORV_X(v), v1 = VECTORV_Y(v), v2 = VECTORV_Z(v), v3 = 1;
#define M(row,col)  ((NLfloat *)m->x)[row + col*4]
   u[0] = v0 * M(0,0) + v1 * M(1,0) + v2 * M(2,0) + v3 * M(3,0);
   u[1] = v0 * M(0,1) + v1 * M(1,1) + v2 * M(2,1) + v3 * M(3,1);
   u[2] = v0 * M(0,2) + v1 * M(1,2) + v2 * M(2,2) + v3 * M(3,2);
   u[3] = v0 * M(0,3) + v1 * M(1,3) + v2 * M(2,3) + v3 * M(3,3);
#undef M
	 VECTOR_X(r) = u[0] / u[3];
	 VECTOR_Y(r) = u[1] / u[3];
	 VECTOR_Z(r) = u[2] / u[3];
	 return r;
}

vector3_t Math3D_glVector3MultiplyMatrix44_3x3(const vector3_t *v, const glmatrix44_t *m)
{
	NLfloat u[3];
	vector3_t r;
   const NLfloat v0 = VECTORV_X(v), v1 = VECTORV_Y(v), v2 = VECTORV_Z(v);
#define M(row,col)  ((NLfloat *)m->x)[row + col*4]
   u[0] = v0 * M(0,0) + v1 * M(1,0) + v2 * M(2,0);
   u[1] = v0 * M(0,1) + v1 * M(1,1) + v2 * M(2,1);
   u[2] = v0 * M(0,2) + v1 * M(1,2) + v2 * M(2,2);
#undef M
	 VECTOR_X(r) = u[0];
	 VECTOR_Y(r) = u[1];
	 VECTOR_Z(r) = u[2];
	 return r;
}

matrix44_t Math3D_glMatrix44InverseTranspose(const glmatrix44_t *mat)
{
	matrix44_t r;
	Math3D_glMatrix44InverseTransposev(&r, mat);
	return r;
}

void Math3D_glMatrix44InverseTransposev(glmatrix44_t *r, const glmatrix44_t *mat)
{
	if(!r || !mat)
		return;

	Matrix44_glInversev(r, mat);
	Matrix44_glTransposeSelf(r);
}

