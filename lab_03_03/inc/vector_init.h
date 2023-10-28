#ifndef VECTOR_INIT_H
#define VECTOR_INIT_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix_vector_t.h"
#include "types_macros.h"
#include "matrix_io.h"
#include "matrix_mem.h"

int vector_init(vector_mtd_t *vector, matrix_std_t *vector_std);
int read_row_size_vector(int *rows);
int vector_fields_alloc(vector_mtd_t *vector, int elems_amount); // allocate memory for valid elems
int read_vector_data_single(int *x, int *data, int rows, int i);
int read_vector_data_general(vector_mtd_t *vector);
int check_vector_repeated(vector_mtd_t *vector, int current_index, int x, int *repeated_index);
int vector_realloc(vector_mtd_t *vector, int rlen);
void vector_std_import(matrix_std_t *vector_std, vector_mtd_t *vector_mtd);
int result_std_import(matrix_std_t *result_std, vector_mtd_t *result_mtd);

#endif