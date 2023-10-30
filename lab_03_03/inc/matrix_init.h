#ifndef MATRIX_MTD_INIT
#define MATRIX_MTD_INIT

#include <stdio.h>
#include <stdlib.h>
#include "matrix_vector_t.h"
#include "matrix_io.h"
#include "matrix_mem.h"
#include "user_interface.h"

int matrix_init(FILE *file, matrix_std_t *matrix_std, matrix_mtd_t *matrix_mtd);
int matrix_std_init(matrix_std_t *matrix_std, int **matrix_data, int rows, int cols, int elems_amount);
int matrix_mtd_init(matrix_mtd_t *matrix_mtd, int **matrix_data, int elems_amount, int rows, int cols);
int check_row_elems(matrix_mtd_t *matrix_mtd, int **matrix_data, int elems_amount, int idx_IA);
int get_index(matrix_mtd_t *matrix_mtd, int x);
void matrix_std_import(matrix_std_t *matrix_std, int **matrix_data, int elems_amount);
void matrix_data_init(int **matrix_data, int elems_count);
void matrix_data_sort(int **matrix_data, int elems_amount);
void swap(int *a, int *b);
void matrix_mtd_import(matrix_mtd_t *matrix_mtd, int **matrix_data, int elems_count);
void vector_IA_init(matrix_mtd_t *matrix_mtd, int **matrix_data);
void fill_negatives(matrix_mtd_t *matrix_mtd);
void swap_vector(int *a, int *b);
void sort_vector_mtd_vectors(vector_mtd_t *vector_mtd);

#endif