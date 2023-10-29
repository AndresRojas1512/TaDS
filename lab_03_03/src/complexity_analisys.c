#include "complexity_analisys.h"

int complexity_analisys(void)
{
    int matrix_sizes[] = {100, 200, 300, 400};
    int percentages[] = {1, 10, 25, 50, 75, 100};
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

            // Memory usage calculation
            size_t memory_matrix_std = matrix_std_memory(&matrix_std);
            size_t memory_matrix_mtd = matrix_mtd_memory(&matrix_mtd);
            size_t memory_vector_mtd = vector_mtd_memory(&vector_mtd);
            size_t memory_vector_std = vector_std_memory(&vector_std);

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
            // printf("\tCheck NonZero: %d\n", matrix_std.matrix[6][48]); // DEBUG
            matrix_std_free(&matrix_std);
            matrix_mtd_free(&matrix_mtd);
            vector_mtd_free(&vector_mtd);
            matrix_std_free(&vector_std);
            
            printf("Percentage of matrix filled: %d\n", percentages[j]);
            printf("\tTime SPMM: %f\n", data_mtd[i][j]);
            printf("\tTime STD: %f\n", data_std[i][j]);
            printf("\tИспользуемая память: matrix_std: %zu bytes\n", memory_matrix_std);
            printf("\tИспользуемая память: matrix_mtd: %zu bytes\n", memory_matrix_mtd);
            printf("\tИспользуемая память: vector_mtd: %zu bytes\n", memory_vector_mtd);
            printf("\tИспользуемая память: vector_std: %zu bytes\n\n", memory_vector_std);
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
        printf("\tОшибка при открытии файл с данными\n");
        return EXIT_FAILURE;
    }
    if (matrix_init(file, matrix_std, matrix_mtd))
        return EXIT_FAILURE;
    if (vector_init(file, vector_mtd, vector_std))
        return EXIT_FAILURE;
    printf("Успешно: Файл открыт: %s\n", filename);
    fclose(file);
    return EXIT_SUCCESS;
}

// MEMORY CALCS
size_t matrix_std_memory(matrix_std_t *matrix)
{
    size_t memory = 0;
    for (int i = 0; i < matrix->rows; i++)
    {
        memory += matrix->cols * sizeof(int);
    }
    memory += sizeof(int *) * matrix->rows + sizeof(matrix_std_t);
    return memory;
}

size_t matrix_mtd_memory(matrix_mtd_t *matrix)
{
    size_t memory = sizeof(int) * matrix->A_len;
    memory += sizeof(int) * matrix->JA_len;
    memory += sizeof(int) * matrix->IA_len;
    memory += sizeof(matrix_mtd_t);
    return memory;
}

size_t vector_mtd_memory(vector_mtd_t *vector)
{
    size_t memory = sizeof(int) * vector->rows;
    memory += sizeof(int) * vector->elems_amount;
    memory += sizeof(vector_mtd_t);
    return memory;
}

size_t vector_std_memory(matrix_std_t *vector)
{
    size_t memory = 0;
    for (int i = 0; i < vector->rows; i++)
    {
        memory += vector->cols * sizeof(int);
    }
    memory += sizeof(int *) * vector->rows + sizeof(matrix_std_t);
    return memory;
}

