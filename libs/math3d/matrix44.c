#include "matrix.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

static float Identity[16] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
};

void Matrix44_Make(matrix44_s *mat, NLfloat a, NLfloat b, NLfloat c, NLfloat d, NLfloat e, NLfloat f, NLfloat g, NLfloat h, NLfloat i, NLfloat j, NLfloat k, NLfloat l, NLfloat m, NLfloat n, NLfloat o, NLfloat p)
{
	if(!mat)
		return;
	MATRIXV_M(mat, 0, 0) = a;
	MATRIXV_M(mat, 0, 1) = b;
	MATRIXV_M(mat, 0, 2) = c;
	MATRIXV_M(mat, 0, 3) = d;
	MATRIXV_M(mat, 1, 0) = e;
	MATRIXV_M(mat, 1, 1) = f;
	MATRIXV_M(mat, 1, 2) = g;
	MATRIXV_M(mat, 1, 3) = h;
	MATRIXV_M(mat, 2, 0) = i;
	MATRIXV_M(mat, 2, 1) = j;
	MATRIXV_M(mat, 2, 2) = k;
	MATRIXV_M(mat, 2, 3) = l;
	MATRIXV_M(mat, 3, 0) = m;
	MATRIXV_M(mat, 3, 1) = n;
	MATRIXV_M(mat, 3, 2) = o;
	MATRIXV_M(mat, 3, 3) = p;
}

void Matrix44_Identity(matrix44_s *mat)
{
	if(!mat)
		return;

	MATRIXV_M(mat, 0, 0) = 1;
	MATRIXV_M(mat, 0, 1) = 0;
	MATRIXV_M(mat, 0, 2) = 0;
	MATRIXV_M(mat, 0, 3) = 0;
	MATRIXV_M(mat, 1, 0) = 0;
	MATRIXV_M(mat, 1, 1) = 1;
	MATRIXV_M(mat, 1, 2) = 0;
	MATRIXV_M(mat, 1, 3) = 0;
	MATRIXV_M(mat, 2, 0) = 0;
	MATRIXV_M(mat, 2, 1) = 0;
	MATRIXV_M(mat, 2, 2) = 1;
	MATRIXV_M(mat, 2, 3) = 0;
	MATRIXV_M(mat, 3, 0) = 0;
	MATRIXV_M(mat, 3, 1) = 0;
	MATRIXV_M(mat, 3, 2) = 0;
	MATRIXV_M(mat, 3, 3) = 1;
}

void Matrix44_Print(const matrix44_s *m)
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
			printf("  %f", MATRIXV_M(m, i, j));
		}
		printf("\n");
	}
	printf("}\n");
}

void Matrix44_Scale(matrix44_s *mat, NLfloat s)
{
	if(!mat)
		return;

	MATRIXV_M(mat, 0, 0) *= s;
	MATRIXV_M(mat, 0, 1) *= s;
	MATRIXV_M(mat, 0, 2) *= s;
	MATRIXV_M(mat, 0, 3) *= s;

	MATRIXV_M(mat, 1, 0) *= s;
	MATRIXV_M(mat, 1, 1) *= s;
	MATRIXV_M(mat, 1, 2) *= s;
	MATRIXV_M(mat, 1, 3) *= s;

	MATRIXV_M(mat, 2, 0) *= s;
	MATRIXV_M(mat, 2, 1) *= s;
	MATRIXV_M(mat, 2, 2) *= s;
	MATRIXV_M(mat, 2, 3) *= s;
}

int Matrix44_GjInversev(matrix44_s *s, const matrix44_s *m, int singExc)
{
	int i, j, k;
	matrix44_s t = *m;

	if(!s || !m)
		return 0;

	Matrix44_Identity(s);

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

			return 0;
		}

		if (pivot != i)
		{
			for (j = 0; j < 4; j++)
			{
				NLfloat tmp;
				tmp = t.x[i][j];
				t.x[i][j] = t.x[pivot][j];
				t.x[pivot][j] = tmp;
				tmp = s->x[i][j];
				s->x[i][j] = s->x[pivot][j];
				s->x[pivot][j] = tmp;
			}
		}
		for (j = i + 1; j < 4; j++)
		{
			NLfloat f = t.x[j][i] / t.x[i][i];
			for (k = 0; k < 4; k++)
			{
				t.x[j][k] -= f * t.x[i][k];
				s->x[j][k] -= f * s->x[i][k];
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

			return 0;
		}
		for (j = 0; j < 4; j++)
		{
			t.x[i][j] /= f;
			s->x[i][j] /= f;
		}
		for (j = 0; j < i; j++)
		{
			f = t.x[j][i];
			for (k = 0; k < 4; k++)
			{
				t.x[j][k] -= f * t.x[i][k];
				s->x[j][k] -= f * s->x[i][k];
			}
		}
	}

	return 1;
}

void Matrix44_MultiplyMatrix44v(matrix44_s *c, const matrix44_s *a, const matrix44_s *b)
{
	register NLfloat a0, a1, a2, a3;

	if(!c || !a || !b)
		return;

	Matrix44_Identity(c);

	/*register*/ const NLfloat * /* restrict */ ap = &a->x[0][0];
	/*register*/ const NLfloat * /* restrict */ bp = &b->x[0][0];
	/*register*/       NLfloat * /* restrict */ cp = &c->x[0][0];

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
}

void Matrix44_Transposev(matrix44_s *m, const matrix44_s *mat)
{
	if(!m || !mat)
		return;

	m->x[0][0] = mat->x[0][0];
	m->x[1][0] = mat->x[0][1];
	m->x[2][0] = mat->x[0][2];
	m->x[3][0] = mat->x[0][3];

	m->x[0][1] = mat->x[1][0];
	m->x[1][1] = mat->x[1][1];
	m->x[2][1] = mat->x[1][2];
	m->x[3][1] = mat->x[1][3];

	m->x[0][2] = mat->x[2][0];
	m->x[1][2] = mat->x[2][1];
	m->x[2][2] = mat->x[2][2];
	m->x[3][2] = mat->x[2][3];

	m->x[0][3] = mat->x[3][0];
	m->x[1][3] = mat->x[3][1];
	m->x[2][3] = mat->x[3][2];
	m->x[3][3] = mat->x[3][3];
}

void Matrix44_TransposeSelf(matrix44_s *mat)
{
#define SWAPF(a, col, row) \
	{ \
		f = a->x[col][row]; \
		a->x[col][row] = a->x[row][col]; \
		a->x[row][col] = f; \
	}

	NLfloat f;

	if(!mat)
		return;

	SWAPF(mat, 1, 0)
		SWAPF(mat, 2, 0)
		SWAPF(mat, 3, 0)

		SWAPF(mat, 2, 1)
		SWAPF(mat, 3, 1)

		SWAPF(mat, 3, 2)

#undef SWAPF
}

void Matrix44_Makev(matrix44_s *mat, const NLfloat m[16])
{
	if(!mat)
		return;
#define M(col, row)  m[col*4+row]
	MATRIXV_M(mat, 0, 0) = M(0, 0);
	MATRIXV_M(mat, 0, 1) = M(0, 1);
	MATRIXV_M(mat, 0, 2) = M(0, 2);
	MATRIXV_M(mat, 0, 3) = M(0, 3);
	MATRIXV_M(mat, 1, 0) = M(1, 0);
	MATRIXV_M(mat, 1, 1) = M(1, 1);
	MATRIXV_M(mat, 1, 2) = M(1, 2);
	MATRIXV_M(mat, 1, 3) = M(1, 3);
	MATRIXV_M(mat, 2, 0) = M(2, 0);
	MATRIXV_M(mat, 2, 1) = M(2, 1);
	MATRIXV_M(mat, 2, 2) = M(2, 2);
	MATRIXV_M(mat, 2, 3) = M(2, 3);
	MATRIXV_M(mat, 3, 0) = M(3, 0);
	MATRIXV_M(mat, 3, 1) = M(3, 1);
	MATRIXV_M(mat, 3, 2) = M(3, 2);
	MATRIXV_M(mat, 3, 3) = M(3, 3);
#undef M
}

int Matrix44_GjInverseSelf(matrix44_s *m, int singExc)
{
	matrix44_s r;

	if(!m)
		return 0;
	if(Matrix44_GjInversev(&r, m, singExc))
	{
		*m = r;
		return 1;
	}
	else
		return 0;
}
