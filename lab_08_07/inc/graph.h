#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

#define N_MAX 100

#define ERROR_GRAPH_INPUT_N 30
#define ERROR_GRAPH_INPUT_RANGE 31

typedef struct matrix_t
{
    int matrix[N_MAX][N_MAX];
    int vertices_n;
} matrix_t;

int input_vertices_n(int *vertices_n);
void adj_matrix_init(matrix_t *adj_matrix, int vertices_n);
void adj_matrix_print(matrix_t *adj_matrix);

#endif