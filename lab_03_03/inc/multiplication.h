#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix_vector_t.h"
#include "vector_init.h"
#include "user_interface.h"
#include "complexity_analisys.h"

int matrix_vector_multiply(matrix_mtd_t *matrix, vector_mtd_t *vector, vector_mtd_t *result);
void matrix_multiply_standard(matrix_std_t *matrix_a, matrix_std_t *matrix_b, matrix_std_t *matrix_c);
int multiplication_mtd_measurement(matrix_mtd_t *matrix_mtd, vector_mtd_t *vector_mtd, vector_mtd_t *result_mtd, int n_times, double *time_mtd);
int multiplication_std_measurement(matrix_std_t *matrix_std, matrix_std_t *vector_std, matrix_std_t *result_std_mult_std, int n_times, double *time_std);


#endif