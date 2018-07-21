#include "matrix33.h"

#include <stdio.h>

matrix33_t Matrix33_Make_With_Value(NLfloat a, NLfloat b, NLfloat c, NLfloat d, NLfloat e, NLfloat f, NLfloat g, NLfloat h, NLfloat i)
{
	matrix33_t mat;
	mat.x[0][0] = a;
	mat.x[0][1] = b;
	mat.x[0][2] = c;
	mat.x[1][0] = d;
	mat.x[1][1] = e;
	mat.x[1][2] = f;
	mat.x[2][0] = g;
	mat.x[2][1] = h;
	mat.x[2][2] = i;
	return mat;
}

void Matrix33_Identity(matrix33_t *m)
{
	m->x[0][0] = 1;
	m->x[0][1] = 0;
	m->x[0][2] = 0;
	m->x[1][0] = 0;
	m->x[1][1] = 1;
	m->x[1][2] = 0;
	m->x[2][0] = 0;
	m->x[2][1] = 0;
	m->x[2][2] = 1;
}

matrix33_t Matrix33_Make()
{
	matrix33_t m;
	m.x[0][0] = 1;
	m.x[0][1] = 0;
	m.x[0][2] = 0;
	m.x[1][0] = 0;
	m.x[1][1] = 1;
	m.x[1][2] = 0;
	m.x[2][0] = 0;
	m.x[2][1] = 0;
	m.x[2][2] = 1;
	return m;
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
			printf("  %f", m->x[i][j]);
		}
		printf("\n");
	}
	printf("}\n");
}

