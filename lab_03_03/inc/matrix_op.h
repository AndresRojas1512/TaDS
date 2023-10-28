#ifndef MATRIX_OP_H
#define MATRIX_OP_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#include "vector_init.h"
int matrix_vector_multiply(matrix_mtd_t *matrix, vector_mtd_t *vector, vector_mtd_t *result);

#endif