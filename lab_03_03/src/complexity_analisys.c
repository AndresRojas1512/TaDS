#include "complexity_analisys.h"

int complexity_analisys(void)
{
    int matrix_sizes[] = {100};
    int percentages[] = {1};
    double data[MATRIX_SIZES][PERCENTAGES_N];
    // int n_times = 10;
    for (int i = 0; i < (int)(sizeof(matrix_sizes)/sizeof(matrix_sizes[0])); i++)
    {
        int size = matrix_sizes[i];
        printf("Matrix size: [%d x %d]\n", size, size);
        for (int j = 0; j < (int)(sizeof(percentages) / sizeof(percentages[0])); j++)
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
            
            // printf("Matrix MTD: A_len: %d, JA_len: %d, IA_len: %d\n", matrix_mtd.A_len, matrix_mtd.JA_len, matrix_mtd.IA_len);
            // vector_output(matrix_mtd.A, matrix_mtd.A_len);
            // vector_output(matrix_mtd.JA, matrix_mtd.JA_len);
            // vector_output(matrix_mtd.IA, matrix_mtd.IA_len);
            // printf("Vector MTD: A_len: %d, VA_len: %d\n", vector_mtd.elems_amount, vector_mtd.elems_amount);
            // vector_output(vector_mtd.A, vector_mtd.elems_amount);
            // vector_output(vector_mtd.VA, vector_mtd.elems_amount);

            // MTD Multiplication
            unsigned long long beg_mtd = microseconds_now();
            if (matrix_vector_multiply(&matrix_mtd, &vector_mtd, &result_mtd))
            {
                printf("Error mtd multiplication.\n");
                return EXIT_FAILURE;
            }
            unsigned long long end_mtd = microseconds_now();

            // // STD Multiplication
            if (matrix_alloc_struct_std(&result_std, matrix_std.rows, 1))
            {
                printf("Error memory allocation\n");
                return EXIT_FAILURE;
            }
            unsigned long long beg_std = microseconds_now();
            matrix_multiply_standard(&matrix_std, &vector_std, &result_std);
            unsigned long long end_std = microseconds_now();
            printf("\tTime MTD: %lld\n", end_mtd - beg_mtd);
            printf("\tTime STD: %lld\n", end_std - beg_std);
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
    return EXIT_SUCCESS;
}
