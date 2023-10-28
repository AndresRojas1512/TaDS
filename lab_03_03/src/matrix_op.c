#include "matrix_op.h"

int matrix_vector_multiply(matrix_mtd_t *matrix, vector_mtd_t *vector, vector_mtd_t *result)
{
    printf("\tMatrix cols: %d, Vector Rows: %d\n", matrix->cols, vector->rows);
    if (matrix->cols != vector->rows)
        return EXIT_FAILURE;
    puts("\tPassed Size Check");
    result->A = (int *)calloc(matrix->rows, sizeof(int));
    if (!result->A)
        return EXIT_FAILURE;
    puts("\tA Alloc passed");
    result->VA = (int *)calloc(matrix->rows, sizeof(int));
    if (!result->VA)
    {
        free(result->A);
        return EXIT_FAILURE;
    }
    puts("\tVA Alloc passed");
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
        if (vector_realloc(result, result->elems_amount))
            return EXIT_FAILURE;
        puts("\tResul Realloc Passed");
    }
    return EXIT_SUCCESS;
}