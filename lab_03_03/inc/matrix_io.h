#ifndef MATRIX_IO_H
#define VM_IO_HMATRIX_IO_H

#include <stdio.h>
#include <stdlib.h>
#include "types_macros.h"
#include "matrix_vector_t.h"
#include "user_interface.h"

int read_sizes(FILE *file ,int *m, int *n);
int read_elems_amount(FILE *file, int *n);
int read_data_single(FILE *file, int *x, int *y, int *data, int rows, int cols, int i);
int read_data_general(FILE *file, int **matrix_data, int elems_amount, int rows, int cols);
void matrix_data_output(int **matrix_data, int elems_amount);
void matrix_std_output(matrix_std_t *matrix_std);
int check_repeated(int **matrix_data, int current_index, int x, int y, int *repeated_index);
void vector_output(int *vector, int elems_amount);

#endif