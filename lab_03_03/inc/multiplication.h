#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix_vector_t.h"
#include "vector_init.h"

int matrix_vector_multiply(matrix_mtd_t *matrix, vector_mtd_t *vector, vector_mtd_t *result);
void matrix_multiply_standard(matrix_std_t *matrix_a, matrix_std_t *matrix_b, matrix_std_t *matrix_c);

#endif