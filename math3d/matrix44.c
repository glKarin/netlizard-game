#include "matrix44.h"

#include <stdio.h>

matrix44_t Matrix44_MakeWithValue(NLfloat a, NLfloat b, NLfloat c, NLfloat d, NLfloat e, NLfloat f, NLfloat g, NLfloat h, NLfloat i, NLfloat j, NLfloat k, NLfloat l, NLfloat m, NLfloat n, NLfloat o, NLfloat p)
{
	matrix44_t mat;
	mat.x[0][0] = a;
	mat.x[0][1] = b;
	mat.x[0][2] = c;
	mat.x[0][3] = d;
	mat.x[1][0] = e;
	mat.x[1][1] = f;
	mat.x[1][2] = g;
	mat.x[1][3] = h;
	mat.x[2][0] = i;
	mat.x[2][1] = j;
	mat.x[2][2] = k;
	mat.x[2][3] = l;
	mat.x[3][0] = m;
	mat.x[3][1] = n;
	mat.x[3][2] = o;
	mat.x[3][3] = p;
	return mat;
}

matrix44_t Matrix44_TransposeOpenGLMatrix(const matrix44_t *mat)
{
	matrix44_t m = Matrix44_Make();
	m.x[0][0] = mat -> x[0][0];
	m.x[1][0] = mat -> x[0][1];
	m.x[2][0] = mat -> x[0][2];
	m.x[3][0] = mat -> x[0][3];

	m.x[0][1] = mat -> x[1][0];
	m.x[1][1] = mat -> x[1][1];
	m.x[2][1] = mat -> x[1][2];
	m.x[3][1] = mat -> x[1][3];

	m.x[0][2] = mat -> x[2][0];
	m.x[1][2] = mat -> x[2][1];
	m.x[2][2] = mat -> x[2][2];
	m.x[3][2] = mat -> x[2][3];

	m.x[0][3] = mat -> x[3][0];
	m.x[1][3] = mat -> x[3][1];
	m.x[2][3] = mat -> x[3][2];
	m.x[3][3] = mat -> x[3][3];

	return m;
}

void Matrix44_Identity(matrix44_t *m)
{
	m -> x[0][0] = 1;
	m -> x[0][1] = 0;
	m -> x[0][2] = 0;
	m -> x[0][3] = 0;
	m -> x[1][0] = 0;
	m -> x[1][1] = 1;
	m -> x[1][2] = 0;
	m -> x[1][3] = 0;
	m -> x[2][0] = 0;
	m -> x[2][1] = 0;
	m -> x[2][2] = 1;
	m -> x[2][3] = 0;
	m -> x[3][0] = 0;
	m -> x[3][1] = 0;
	m -> x[3][2] = 0;
	m -> x[3][3] = 1;
}

matrix44_t Matrix44_Make()
{
	matrix44_t m;
	m.x[0][0] = 1;
	m.x[0][1] = 0;
	m.x[0][2] = 0;
	m.x[0][3] = 0;
	m.x[1][0] = 0;
	m.x[1][1] = 1;
	m.x[1][2] = 0;
	m.x[1][3] = 0;
	m.x[2][0] = 0;
	m.x[2][1] = 0;
	m.x[2][2] = 1;
	m.x[2][3] = 0;
	m.x[3][0] = 0;
	m.x[3][1] = 0;
	m.x[3][2] = 0;
	m.x[3][3] = 1;
	return m;
}

matrix44_t Matrix44_GjInverse(const matrix44_t *m, int singExc)
{
	if(!m)
		return Matrix44_Make();
	int i, j, k;
	matrix44_t s = Matrix44_Make();
	matrix44_t t = *m;

	// Forward elimination

	for (i = 0; i < 3 ; i++)
	{
		int pivot = i;
		NLfloat pivotsize = t.x[i][i];
		if (pivotsize < 0)
			pivotsize = -pivotsize;
		for (j = i + 1; j < 4; j++)
		{
			NLfloat tmp = t.x[j][i];
			if (tmp < 0)
				tmp = -tmp;
			if (tmp > pivotsize)
			{
				pivot = j;
				pivotsize = tmp;
			}
		}
		if (pivotsize == 0)
		{
			if (singExc)
				fprintf(stderr, "Cannot invert singular matrix.");

			return Matrix44_Make();
		}

		if (pivot != i)
		{
			for (j = 0; j < 4; j++)
			{
				NLfloat tmp;
				tmp = t.x[i][j];
				t.x[i][j] = t.x[pivot][j];
				t.x[pivot][j] = tmp;
				tmp = s.x[i][j];
				s.x[i][j] = s.x[pivot][j];
				s.x[pivot][j] = tmp;
			}
		}
		for (j = i + 1; j < 4; j++)
		{
			NLfloat f = t.x[j][i] / t.x[i][i];
			for (k = 0; k < 4; k++)
			{
				t.x[j][k] -= f * t.x[i][k];
				s.x[j][k] -= f * s.x[i][k];
			}
		}
	}

	// Backward substitution

	for (i = 3; i >= 0; --i)
	{
		NLfloat f;

		if ((f = t.x[i][i]) == 0)
		{
			if (singExc)
				fprintf(stderr, "Cannot invert singular matrix.");

			return Matrix44_Make();
		}
		for (j = 0; j < 4; j++)
		{
			t.x[i][j] /= f;
			s.x[i][j] /= f;
		}
		for (j = 0; j < i; j++)
		{
			f = t.x[j][i];
			for (k = 0; k < 4; k++)
			{
				t.x[j][k] -= f * t.x[i][k];
				s.x[j][k] -= f * s.x[i][k];
			}
		}
	}

	return s;
}

matrix44_t Matrix44_MultiplyMatrix44(const matrix44_t *a, const matrix44_t *b)
{
	if(!a || !b)
		return Matrix44_Make();
	matrix44_t c = Matrix44_Make();
	/*register*/ const NLfloat * /* restrict */ ap = &a -> x[0][0];
	/*register*/ const NLfloat * /* restrict */ bp = &b -> x[0][0];
	/*register*/       NLfloat * /* restrict */ cp = &c.x[0][0];

	register NLfloat a0, a1, a2, a3;

	a0 = ap[0];
	a1 = ap[1];
	a2 = ap[2];
	a3 = ap[3];

	cp[0]  = a0 * bp[0]  + a1 * bp[4]  + a2 * bp[8]  + a3 * bp[12];
	cp[1]  = a0 * bp[1]  + a1 * bp[5]  + a2 * bp[9]  + a3 * bp[13];
	cp[2]  = a0 * bp[2]  + a1 * bp[6]  + a2 * bp[10] + a3 * bp[14];
	cp[3]  = a0 * bp[3]  + a1 * bp[7]  + a2 * bp[11] + a3 * bp[15];

	a0 = ap[4];
	a1 = ap[5];
	a2 = ap[6];
	a3 = ap[7];

	cp[4]  = a0 * bp[0]  + a1 * bp[4]  + a2 * bp[8]  + a3 * bp[12];
	cp[5]  = a0 * bp[1]  + a1 * bp[5]  + a2 * bp[9]  + a3 * bp[13];
	cp[6]  = a0 * bp[2]  + a1 * bp[6]  + a2 * bp[10] + a3 * bp[14];
	cp[7]  = a0 * bp[3]  + a1 * bp[7]  + a2 * bp[11] + a3 * bp[15];

	a0 = ap[8];
	a1 = ap[9];
	a2 = ap[10];
	a3 = ap[11];

	cp[8]  = a0 * bp[0]  + a1 * bp[4]  + a2 * bp[8]  + a3 * bp[12];
	cp[9]  = a0 * bp[1]  + a1 * bp[5]  + a2 * bp[9]  + a3 * bp[13];
	cp[10] = a0 * bp[2]  + a1 * bp[6]  + a2 * bp[10] + a3 * bp[14];
	cp[11] = a0 * bp[3]  + a1 * bp[7]  + a2 * bp[11] + a3 * bp[15];

	a0 = ap[12];
	a1 = ap[13];
	a2 = ap[14];
	a3 = ap[15];

	cp[12] = a0 * bp[0]  + a1 * bp[4]  + a2 * bp[8]  + a3 * bp[12];
	cp[13] = a0 * bp[1]  + a1 * bp[5]  + a2 * bp[9]  + a3 * bp[13];
	cp[14] = a0 * bp[2]  + a1 * bp[6]  + a2 * bp[10] + a3 * bp[14];
	cp[15] = a0 * bp[3]  + a1 * bp[7]  + a2 * bp[11] + a3 * bp[15];

	return c;
}

void Matrix44_Print(const matrix44_t *m)
{
	if(!m)
		return;
	printf("matrix 4x4 {\n");
	int i;
	for(i = 0; i < 4; i++)
	{
		int j;
		for(j = 0; j < 4; j++)
		{
			printf("  %f", m -> x[i][j]);
		}
		printf("\n");
	}
	printf("}\n");
}

void Matrix44_Scale(matrix44_t *m, NLfloat s)
{
    m -> x[0][0] *= s;
    m -> x[0][1] *= s;
    m -> x[0][2] *= s;
    m -> x[0][3] *= s;

    m -> x[1][0] *= s;
    m -> x[1][1] *= s;
    m -> x[1][2] *= s;
    m -> x[1][3] *= s;

    m -> x[2][0] *= s;
    m -> x[2][1] *= s;
    m -> x[2][2] *= s;
    m -> x[2][3] *= s;

}
