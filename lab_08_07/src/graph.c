#include "graph.h"

int input_vertices_n(int *vertices_n)
{
    if (scanf("%d", vertices_n) != 1)
        return ERROR_GRAPH_INPUT_N;
    if (*vertices_n <= 0 || *vertices_n > N_MAX)
        return ERROR_GRAPH_INPUT_RANGE;
    return EXIT_SUCCESS;
}

void adj_matrix_init(matrix_t *adj_matrix, int vertices_n)
{
    adj_matrix->vertices_n = vertices_n;
    for (int i = 0; i < vertices_n; i++)
    {
        for (int j = 0; j < vertices_n; j++)
            adj_matrix->matrix[i][j] = 0;
    }
}

void adj_matrix_print(matrix_t *adj_matrix)
{
    for (int i = 0; i < adj_matrix->vertices_n; i++)
    {
        for (int j = 0; j < adj_matrix->vertices_n; j++)
            printf("%d ", adj_matrix->matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}