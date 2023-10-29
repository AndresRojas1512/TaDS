#ifndef MATRIX_MEM
#define MATRIX_MEM

#include <stdio.h>
#include <stdlib.h>
#include "types_macros.h"
#include "matrix_vector_t.h"
#include "user_interface.h"

int **matrix_alloc_std(size_t m, size_t n);
int matrix_alloc_struct_std(matrix_std_t *matrix_std, size_t m, size_t n);
int matrix_mtd_fields_alloc(matrix_mtd_t *matrix_mtd, int elems_amount, int rows);
void matrix_free_std(int **matrix, int m);

#endif