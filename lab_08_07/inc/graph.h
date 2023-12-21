#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#define N_MAX 100
#define INF INT_MAX
#define EPSILON 1e-9

#define ERROR_GRAPH_INPUT_N 30
#define ERROR_GRAPH_INPUT_RANGE 31

typedef struct matrix_t
{
    int matrix[N_MAX][N_MAX];
    int vertices_n;
} matrix_t;

int input_vertices_n(int *vertices_n);
void adj_matrix_init(matrix_t *adj_matrix, int vertices_n);
void matrix_print(matrix_t *adj_matrix);
int adj_matrix_input(matrix_t *adj_matrix);
void floydWarshall(matrix_t *dist_matrix);
void matrix_zero_diagonal(matrix_t *dist_matrix);
void dist_matrix_init(matrix_t *adj_matrix, matrix_t *dist_matrix);
void dist_matrix_int_max(matrix_t *dist_matrix);
int min(int a, int b);
void graph_to_dot(FILE *file, matrix_t *graph);
void graphviz_format(FILE *file, matrix_t *graph);
void matrix_format_output(matrix_t *adj_matrix);
void DFS(matrix_t *graph, int vertex, bool visited[]);
bool is_graph_connected(matrix_t *graph);
void swap_rows(double mat[N_MAX][N_MAX], int i, int j, int n);
double calc_determinant(matrix_t *mat_struct);
double count_spanning_trees(matrix_t *graph);

#endif