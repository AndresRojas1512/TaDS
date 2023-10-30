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
            int vector_value = 0;

            // Use a binary search to find the value in the vector
            int left = 0, right = vector->elems_amount - 1;
            while (left <= right)
            {
                int mid = left + (right - left) / 2;
                if (vector->VA[mid] == col_index)
                {
                    vector_value = vector->A[mid];
                    break;
                }
                else if (vector->VA[mid] < col_index)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
            sum += matrix->A[j] * vector_value;
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

int multiplication_mtd_measurement(matrix_mtd_t *matrix_mtd, vector_mtd_t *vector_mtd, vector_mtd_t *result_mtd, int n_times, double *time_mtd)
{
    *time_mtd = 0;
    int exit_code = EXIT_SUCCESS;
    for (int i = 0; i < n_times && !exit_code; i++)
    {
        unsigned long long beg = microseconds_now();
        exit_code = matrix_vector_multiply(matrix_mtd, vector_mtd, result_mtd);
        unsigned long long end = microseconds_now();
        *time_mtd += (double)(end - beg);
    }
    *time_mtd /= n_times;
    return exit_code;
}

int multiplication_std_measurement(matrix_std_t *matrix_std, matrix_std_t *vector_std, matrix_std_t *result_std_mult_std, int n_times, double *time_std)
{
    *time_std = 0;
    if (matrix_std->cols != vector_std->rows)
        return EXIT_FAILURE;
    for (int i = 0; i < n_times; i++)
    {
        unsigned long long beg = microseconds_now();
        matrix_multiply_standard(matrix_std, vector_std, result_std_mult_std);
        unsigned long long end = microseconds_now();
        *time_std += (double)(end - beg);
    }
    *time_std /= n_times;
    return EXIT_SUCCESS;
}