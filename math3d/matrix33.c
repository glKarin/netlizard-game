#include "matrix.h"

#include <stdio.h>

matrix33_t Matrix33_Make_With_Value(NLfloat a, NLfloat b, NLfloat c, NLfloat d, NLfloat e, NLfloat f, NLfloat g, NLfloat h, NLfloat i)
{
	matrix33_t mat;
	MATRIX_M(mat, 0, 0) = a;
	MATRIX_M(mat, 0, 1) = b;
	MATRIX_M(mat, 0, 2) = c;
	MATRIX_M(mat, 1, 0) = d;
	MATRIX_M(mat, 1, 1) = e;
	MATRIX_M(mat, 1, 2) = f;
	MATRIX_M(mat, 2, 0) = g;
	MATRIX_M(mat, 2, 1) = h;
	MATRIX_M(mat, 2, 2) = i;
	return mat;
}

void Matrix33_Identity(matrix33_t *mat)
{
	MATRIXV_M(mat, 0, 0) = 1;
	MATRIXV_M(mat, 0, 1) = 0;
	MATRIXV_M(mat, 0, 2) = 0;
	MATRIXV_M(mat, 1, 0) = 0;
	MATRIXV_M(mat, 1, 1) = 1;
	MATRIXV_M(mat, 1, 2) = 0;
	MATRIXV_M(mat, 2, 0) = 0;
	MATRIXV_M(mat, 2, 1) = 0;
	MATRIXV_M(mat, 2, 2) = 1;
}

matrix33_t Matrix33_Make()
{
	matrix33_t mat;
	MATRIX_M(mat, 0, 0) = 1;
	MATRIX_M(mat, 0, 1) = 0;
	MATRIX_M(mat, 0, 2) = 0;
	MATRIX_M(mat, 1, 0) = 0;
	MATRIX_M(mat, 1, 1) = 1;
	MATRIX_M(mat, 1, 2) = 0;
	MATRIX_M(mat, 2, 0) = 0;
	MATRIX_M(mat, 2, 1) = 0;
	MATRIX_M(mat, 2, 2) = 1;
	return mat;
}

void Matrix33_Print(const matrix33_t *m)
{
	if(!m)
		return;
	printf("matrix 3x3 {\n");
	int i;
	for(i = 0; i < 3; i++)
	{
		int j;
		for(j = 0; j < 3; j++)
		{
			printf("  %f", MATRIXV_M(m, i, j));
		}
		printf("\n");
	}
	printf("}\n");
}

