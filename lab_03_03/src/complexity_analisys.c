#include "complexity_analisys.h"

int complexity_analisys(void)
{
    int matrix_sizes[] = {100, 200, 300, 400, 500};
    int percentages[] = {1, 5, 10, 25, 50, 75, 100};
    double data_std[MATRIX_SIZES][PERCENTAGES_N];
    double data_mtd[MATRIX_SIZES][PERCENTAGES_N];
    int n_times = 10;

    for (int i = 0; i < MATRIX_SIZES; i++)
    {
        int size = matrix_sizes[i];
        printf("Matrix size: [%d x %d]\n", size, size);
        for (int j = 0; j < PERCENTAGES_N; j++)
        {
            char filename[50];
            matrix_std_t matrix_std;
            matrix_mtd_t matrix_mtd;

            matrix_std_t vector_std;
            vector_mtd_t vector_mtd;
            
            matrix_std_t result_std;
            vector_mtd_t result_mtd;

            sprintf(filename, "data/%d/%d.txt", matrix_sizes[i], percentages[j]);
            if (read_data(filename, &matrix_std, &matrix_mtd, &vector_mtd, &vector_std))
                return EXIT_FAILURE;

            // MTD Multiplication
            unsigned long long time_mtd = 0;
            for (int k = 0; k < n_times; k++)
            {
                if (vector_fields_alloc(&result_mtd, matrix_std.rows))
                    return EXIT_FAILURE;
                
                unsigned long long beg_mtd = microseconds_now();
                if (matrix_vector_multiply(&matrix_mtd, &vector_mtd, &result_mtd))
                    return EXIT_FAILURE;
                unsigned long long end_mtd = microseconds_now();

                if (result_mtd.elems_amount < matrix_mtd.rows)
                {
                    if (vector_realloc(&result_mtd, result_mtd.elems_amount))
                        return EXIT_FAILURE;
                }
                time_mtd += end_mtd - beg_mtd;
                vector_mtd_free(&result_mtd);
            }
            data_mtd[i][j] = time_mtd / n_times;

            // STD Multiplication
            unsigned long long time_std = 0;
            for (int k = 0; k < n_times; k++)
            {
                unsigned long long beg_std = microseconds_now();
                if (matrix_alloc_struct_std(&result_std, matrix_std.rows, 1))
                    return EXIT_FAILURE;
                matrix_multiply_standard(&matrix_std, &vector_std, &result_std);
                unsigned long long end_std = microseconds_now();
                time_std += end_std - beg_std;
                matrix_std_free(&result_std);
            }
            // Append data
            data_std[i][j] = time_std / n_times;

            // Free allocated memory
            matrix_std_free(&matrix_std);
            matrix_mtd_free(&matrix_mtd);
            vector_mtd_free(&vector_mtd);
            matrix_std_free(&vector_std);

            printf("\tTime MTD: %f\n", data_mtd[i][j]);
            printf("\tTime STD: %f\n", data_std[i][j]);
        }
    }
    return EXIT_SUCCESS;
}

unsigned long long microseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long) -1;
    return val.tv_sec * 1000000ULL + val.tv_usec;
}

int read_data(char *filename, matrix_std_t *matrix_std, matrix_mtd_t *matrix_mtd, vector_mtd_t *vector_mtd, matrix_std_t *vector_std)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("\tError File Opening\n");
        return EXIT_FAILURE;
    }
    if (matrix_init(file, matrix_std, matrix_mtd))
        return EXIT_FAILURE;
    if (vector_init(file, vector_mtd, vector_std))
        return EXIT_FAILURE;
    printf("\tSuccess Reading Data: %s\n", filename);
    fclose(file);
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
