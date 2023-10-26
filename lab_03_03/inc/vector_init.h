#ifndef VECTOR_INIT_H
#define VECTOR_INIT_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "types_macros.h"
#include "matrix_io.h"

int vector_init(vector_mtd_t *vector);
int read_row_size_vector(int *rows);
int vector_fields_alloc(vector_mtd_t *vector);
int read_vector_data_single(int *x, int *data, int rows, int i);
int read_vector_data_general(vector_mtd_t *vector);
int check_vector_repeated(vector_mtd_t *vector, int current_index, int x, int *repeated_index);

#endif