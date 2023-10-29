#include "multiplication.h"

int matrix_vector_multiply(matrix_mtd_t *matrix, vector_mtd_t *vector, vector_mtd_t *result)
{
    if (matrix->cols != vector->rows)
        return EXIT_FAILURE;
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
