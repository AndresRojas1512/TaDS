#include <stdio.h>
#include <stdlib.h>
#include "types_macros.h"
#include "matrix_vector_t.h"
#include "matrix_init.h"
#include "matrix_mem.h"
#include "matrix_io.h"
#include "vector_init.h"
#include "multiplication.h"
#include "complexity_analisys.h"
#include "user_interface.h"
#include "complexity_analisys.h"

int main(void)
{
    int exit_code = EXIT_SUCCESS;
    int option;

    matrix_std_t matrix_std_A;
    matrix_mtd_t matrix_mtd_A;

    vector_mtd_t vector_mtd;
    vector_mtd_t result;
    matrix_std_t vector_std;
    matrix_std_t result_std;

    matrix_std_t result_std_mult_std;

    printf("Введите 1 для запуска анализа эффективности.\n");
    printf("Введите 0 для ручного введение данных:\n");
    fscanf(stdin, "%d", &option);
    if (!option)
        user_interface = 1;

    if (!option)
    {
        puts("\tВведение данных матрицы\n");
        exit_code = matrix_init(stdin, &matrix_std_A, &matrix_mtd_A);
        if (!exit_code)
        {
            puts("\n\tВведение данных вектора-столбца\n");
            exit_code = vector_init(stdin, &vector_mtd, &vector_std);
            printf("\tВведенная матрица:\n");
            matrix_std_output(&matrix_std_A);
            printf("\tВведенный вектор:\n");
            matrix_std_output(&vector_std);
            printf("\n");
            // printf("\tRC after vector_mtd init: %d\n", exit_code);
            if (!exit_code)
            {
                // Calculate Memory usage
                size_t memory_matrix_std = matrix_std_memory(&matrix_std_A);
                size_t memory_matrix_mtd = matrix_mtd_memory(&matrix_mtd_A);
                size_t memory_vector_mtd = vector_mtd_memory(&vector_mtd);
                size_t memory_vector_std = vector_std_memory(&vector_mtd);

                int n_times = 10;
                double time_mtd = 0;
                if (vector_fields_alloc(&result, matrix_std_A.rows))
                    return EXIT_FAILURE;

                // SPMM MULTIPLICATION
                sort_vector_mtd_vectors(&vector_mtd);
                if (multiplication_mtd_measurement(&matrix_mtd_A, &vector_mtd, &result, n_times, &time_mtd))
                    return EXIT_FAILURE;
                // printf("\nMean time MTD multiplication: %lf microseconds\n", time_mtd);


                // Realloc if needed the result mtd vector
                if (result.elems_amount < matrix_mtd_A.rows)
                {
                    if (vector_realloc(&result, result.elems_amount))
                        return EXIT_FAILURE;
                }

                if (!exit_code)
                {
                    printf("DEBUG: A JA IA:\n");
                    vector_output(matrix_mtd_A.A, matrix_mtd_A.A_len);
                    vector_output(matrix_mtd_A.JA, matrix_mtd_A.JA_len);
                    vector_output(matrix_mtd_A.IA, matrix_mtd_A.IA_len);
                    printf("END DEBUG: A JA IA:\n");
                    double time_std = 0;
                    printf("\n\tРезультаты SPMM умножения в формате 'Вектор-столбец':\n");
                    printf("Вектор A: ");
                    vector_output(result.A, result.elems_amount);
                    printf("Вектор VA: ");
                    vector_output(result.VA, result.elems_amount);
                    // printf("After Mult Rows: %d\n", result.rows);
                    // printf("After Mult Elems Amount: %d\n", result.elems_amount);
                    if (result_std_import(&result_std, &result))
                        return EXIT_FAILURE;
                    // printf("\n\tРезультаты SPMM умножения в стандартом формате:\n");
                    // matrix_std_output(&vector_std);

                    // STANDARD MATRIX MULTIPLICATION
                    if (matrix_alloc_struct_std(&result_std_mult_std, matrix_std_A.rows, 1))
                        return EXIT_FAILURE;

                    if (multiplication_std_measurement(&matrix_std_A, &vector_std, &result_std_mult_std, n_times, &time_std))
                        return EXIT_FAILURE;
                    // matrix_multiply_standard(&matrix_std_A, &vector_std, &result_std_mult_std);

                    // Memory usage result
                    // size_t memory_result_mtd = vector_mtd_memory(&result);
                    // size_t memory_result_std = vector_std_memory(&result_std);

                    printf("\n\tРезультаты стандартного умножения:\n");
                    matrix_std_output(&result_std_mult_std);

                    // Memory usage and time print
                    printf("\tВремя занимаемое STD умножения: %lf микросекунды\n", time_std);
                    printf("\tВремя занимаемое SPMM умножения: %lf микросекунды\n", time_mtd);

                    // printf("\tИспользуемая память: matrix_spm: %zu bytes\n", memory_matrix_mtd);
                    // printf("\tИспользуемая память: matrix_std: %zu bytes\n", memory_matrix_std);

                    // printf("\tИспользуемая память: vector_spm: %zu bytes\n", memory_vector_mtd);
                    // printf("\tИспользуемая память: vector_std: %zu bytes\n", memory_vector_std);

                    // printf("\tИспользуемая память: result_spm: %zu bytes\n", memory_result_mtd);
                    // printf("\tИспользуемая память: result_std: %zu bytes\n\n", memory_result_std);
                    
                }
                matrix_std_free(&matrix_std_A);
                matrix_mtd_free(&matrix_mtd_A);
                vector_mtd_free(&vector_mtd);
                matrix_std_free(&vector_std);
                vector_mtd_free(&result);
                matrix_std_free(&result_std);
                matrix_std_free(&result_std_mult_std);
            }
            matrix_std_free(&matrix_std_A);
            matrix_mtd_free(&matrix_mtd_A);
        }
    }
    else if (option)
        exit_code = complexity_analisys();
    return exit_code;
}