#include "base_algo.h"

matrix44_t Math3D_MakeQuatAndToMatrix44(const NLfloat r[], const NLfloat p[], const NLfloat s[])
{
	quat_t q = Quat_Make();
	q.v.x = r[0];
	q.v.y = r[1];
	q.v.z = r[2];
	q.r = r[3];
	matrix44_t m = Math3D_QuatToMatrix44(&q);
	//m.setAxisAngle(q.axis(), q.angle());
	/*
		 m[0][3] = p[0];
		 m[1][3] = p[1];
		 m[2][3] = p[2];
		 */
	m.x[3][0] = p[0];
	m.x[3][1] = p[1];
	m.x[3][2] = p[2];
	m.x[3][3] = 1.0;
	//vector3_t scale = {s[0], s[1], s[2]};
	//return g_transpose_matrix(m);
	return m;
}

vector3_t Math3D_Vector3MultiplyMatrix44(const vector3_t *v, const matrix44_t *m)
{
	if(!v || !m)
	{
		vector3_t r = {0.0, 0.0, 0.0};
		return r;
	}
	NLfloat x = (NLfloat)(v -> x * m -> x[0][0] + v -> y * m -> x[1][0] + v -> z * m -> x[2][0] + m -> x[3][0]);
	NLfloat y = (NLfloat)(v -> x * m -> x[0][1] + v -> y * m -> x[1][1] + v -> z * m -> x[2][1] + m -> x[3][1]);
	NLfloat z = (NLfloat)(v -> x * m -> x[0][2] + v -> y * m -> x[1][2] + v -> z * m -> x[2][2] + m -> x[3][2]);
	NLfloat w = (NLfloat)(v -> x * m -> x[0][3] + v -> y * m -> x[1][3] + v -> z * m -> x[2][3] + m -> x[3][3]);

	vector3_t r = {x / w, y / w, z / w};
	return r;
}

matrix44_t Math3D_QuatToMatrix44(const quat_t *q)
{
	if(!q)
		return Matrix44_Make();
	return Matrix44_MakeWithValue(
			1. - 2.0 * (q -> v.y * q -> v.y + q -> v.z * q -> v.z),
			2.0 * (q -> v.x * q -> v.y + q -> v.z * q -> r),
			2.0 * (q -> v.z * q -> v.x - q -> v.y * q -> r),
			0.,
			2.0 * (q -> v.x * q -> v.y - q -> v.z * q -> r),
			1. - 2.0 * (q -> v.z * q -> v.z + q -> v.x * q -> v.x),
			2.0 * (q -> v.y * q -> v.z + q -> v.x * q -> r),
			0.,
			2.0 * (q -> v.z * q -> v.x + q -> v.y * q -> r),
			2.0 * (q -> v.y * q -> v.z - q -> v.x * q -> r),
			1. - 2.0 * (q -> v.y * q -> v.y + q -> v.x * q -> v.x),
			0.,
			0.,
			0.,
			0.,
			1.0
			);
}

