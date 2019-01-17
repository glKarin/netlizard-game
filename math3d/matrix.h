#ifndef KARIN_MATRIX_H
#define KARIN_MATRIX_H

#include "matrix33.h"
#include "matrix44.h"
#include "glmatrix44.h"

#define MATRIX_M(m, row, col) (m).x[row][col]
#define MATRIXV_M(m, row, col) (m)->x[row][col]

#define GLMATRIX_M(m, col, row) (m).x[row][col]
#define GLMATRIXV_M(m, col, row) (m)->x[row][col]

#endif
