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

int matrix_mtd_fields_alloc(matrix_mtd_t *matrix_mtd, int elems_amount, int rows) // done
{
    matrix_mtd->A = (int *)calloc(elems_amount, sizeof(int));
    if (!matrix_mtd->A)
        return EXIT_FAILURE;
    matrix_mtd->JA = (int *)calloc(elems_amount, sizeof(int));
    if (!matrix_mtd->JA)
    {
        free(matrix_mtd->A);
        return EXIT_FAILURE;
    }
    matrix_mtd->IA = (int *)calloc(rows + 1, sizeof(int));
    if (!matrix_mtd->JA)
    {
        free(matrix_mtd->A);
        free(matrix_mtd->JA);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void matrix_std_free(matrix_std_t *matrix_std)
{
    if (matrix_std->matrix) {
        for (int i = 0; i < matrix_std->rows; i++) {
            if (matrix_std->matrix[i]) {
                free(matrix_std->matrix[i]);
            }
        }
        free(matrix_std->matrix);
    }
    matrix_std->matrix = NULL;
    matrix_std->rows = 0;
    matrix_std->cols = 0;
}

void matrix_mtd_free(matrix_mtd_t *matrix_mtd)
{
    if (matrix_mtd->A) {
        free(matrix_mtd->A);
    }
    if (matrix_mtd->JA) {
        free(matrix_mtd->JA);
    }
    if (matrix_mtd->IA) {
        free(matrix_mtd->IA);
    }
    matrix_mtd->A = NULL;
    matrix_mtd->JA = NULL;
    matrix_mtd->IA = NULL;
    matrix_mtd->A_len = 0;
    matrix_mtd->JA_len = 0;
    matrix_mtd->IA_len = 0;
    matrix_mtd->rows = 0;
    matrix_mtd->cols = 0;
}

void vector_mtd_free(vector_mtd_t *vector_mtd)
{
    if (vector_mtd->A) {
        free(vector_mtd->A);
    }
    if (vector_mtd->VA) {
        free(vector_mtd->VA);
    }
    vector_mtd->A = NULL;
    vector_mtd->VA = NULL;
    vector_mtd->rows = 0;
    vector_mtd->elems_amount = 0;
}