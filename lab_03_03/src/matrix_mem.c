#include "matrix_mem.h"

int **matrix_alloc_std(size_t m, size_t n) // done
{
    int **matrix = (int **)calloc(m, sizeof(int *));
    if (!matrix)
        return NULL;
    for (size_t i = 0; i < m; i++)
    {
        matrix[i] = (int *)calloc(n, sizeof(int));
        if (!matrix[i])
        {
            matrix_free_std(matrix, m);
            return NULL;
        }
    }
    return matrix;
}

void matrix_free_std(int **matrix, int m) // done
{
    for (int i = 0; i < m; i++)
        free(matrix[i]);
    free(matrix);
}

int matrix_alloc_struct_std(matrix_std_t *matrix_std, size_t m, size_t n) // done
{
    int exit_code = EXIT_SUCCESS;
    matrix_std->matrix = matrix_alloc_std(m, n);
    if (!matrix_std->matrix)
        exit_code = EXIT_FAILURE;
    return exit_code;
}

int matrix_mtd_fields_alloc(matrix_mtd_t *matrix_mtd, int elems_amount, int rows)
{
    matrix_mtd->A = (int *)calloc(elems_amount, sizeof(int));
    if (!matrix_mtd->A)
        return EXIT_FAILURE;
    matrix_mtd->JA = (int *)calloc(elems_amount, sizeof(int));
    if (!matrix_mtd->JA)
        return EXIT_FAILURE;
    matrix_mtd->IA = (int *)calloc(rows + 1, sizeof(int));
    if (!matrix_mtd->JA)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}