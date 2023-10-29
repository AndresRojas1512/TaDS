#include "multiplication.h"

int matrix_vector_multiply(matrix_mtd_t *matrix, vector_mtd_t *vector, vector_mtd_t *result)
{
    // printf("\tMatrix cols: %d, Vector Rows: %d\n", matrix->cols, vector->rows);
    if (matrix->cols != vector->rows)
    {
        // printf("Error sizes not equal\n");
        return EXIT_FAILURE;
    }
    // puts("\tPassed Size Check");
    result->A = (int *)calloc(matrix->rows, sizeof(int));
    if (!result->A)
    {
        // printf("Error allocating memory A\n");
        return EXIT_FAILURE;
    }
    // puts("\tA Alloc passed");
    result->VA = (int *)calloc(matrix->rows, sizeof(int));
    if (!result->VA)
    {
        // printf("Error allocating memory VA\n");
        free(result->A);
        return EXIT_FAILURE;
    }
    // puts("\tVA Alloc passed");
    result->rows = matrix->rows;
    result->elems_amount = 0;
    for (int i = 0; i < matrix->rows; i++)
    {
        int sum = 0;
        for (int j = matrix->IA[i]; j < matrix->IA[i + 1]; j++)
        {
            int col_index = matrix->JA[j];
            for (int k = 0; k < vector->elems_amount; k++)
            {
                if (vector->VA[k] == col_index)
                {
                    sum += matrix->A[j] * vector->A[k];
                    break;
                }
            }
        }
        if (sum != 0)
        {
            result->A[result->elems_amount] = sum;
            result->VA[result->elems_amount] = i;
            result->elems_amount++;
        }
    }

    if (result->elems_amount < matrix->rows)
    {
        // puts("\n\tNeeded to reallocate\n");
        if (vector_realloc(result, result->elems_amount))
        {
            // printf("%d %d\n", result->elems_amount, matrix->rows);
            // printf("Error Realloc\n");
            return EXIT_FAILURE;
        }
        // puts("\tResult Realloc Passed");
    }
    return EXIT_SUCCESS;
}


void matrix_multiply_standard(matrix_std_t *matrix_a, matrix_std_t *matrix_b, matrix_std_t *matrix_c)
{
    for (int i = 0; i < matrix_a->rows; i++)
    {
        for (int j = 0; j < matrix_b->cols; j++)
        {
            matrix_c->matrix[i][j] = 0;
            for (int k = 0; k < matrix_b->rows; k++)
            {
                matrix_c->matrix[i][j] += matrix_a->matrix[i][k] * matrix_b->matrix[k][j];
            }
        }
    }
    matrix_c->rows = matrix_a->rows;
    matrix_c->cols = matrix_b->cols;
}
