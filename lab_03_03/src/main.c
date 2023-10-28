#include <stdio.h>
#include <stdlib.h>
#include "types_macros.h"
#include "matrix_vector_t.h"
#include "matrix_init.h"
#include "matrix_mem.h"
#include "matrix_io.h"
#include "vector_init.h"
#include "multiplication.h"

int main(void)
{
    int exit_code = EXIT_SUCCESS;

    matrix_std_t matrix_std_A;
    matrix_mtd_t matrix_mtd_A;

    vector_mtd_t vector_mtd;
    vector_mtd_t result;
    matrix_std_t vector_std;
    matrix_std_t result_std;

    matrix_std_t result_std_mult_std;

    puts("\tMatrix A Data:");
    exit_code = matrix_init(&matrix_std_A, &matrix_mtd_A);
    if (!exit_code)
    {
        exit_code = vector_init(&vector_mtd, &vector_std);
        printf("Matrix Std:\n");
        matrix_std_output(&matrix_std_A);
        printf("\tVector Std:\n");
        matrix_std_output(&vector_std);
        printf("\n");
        // printf("\tRC after vector_mtd init: %d\n", exit_code);
        if (!exit_code)
        {
            exit_code = matrix_vector_multiply(&matrix_mtd_A, &vector_mtd, &result);
            if (!exit_code)
            {
                printf("\n\tResults Mtd:\n");
                printf("Vector A: ");
                vector_output(result.A, result.elems_amount);
                printf("Vector VA: ");
                vector_output(result.VA, result.elems_amount);
                // printf("After Mult Rows: %d\n", result.rows);
                // printf("After Mult Elems Amount: %d\n", result.elems_amount);
                if (result_std_import(&result_std, &result))
                    return EXIT_FAILURE;
                puts("\n\tVResult Std:");
                matrix_std_output(&vector_std);
                // STANDARD MATRIX MULTIPLICATION
                if (matrix_alloc_struct_std(&result_std_mult_std, matrix_std_A.rows, 1))
                    return EXIT_FAILURE;
                matrix_multiply_standard(&matrix_std_A, &vector_std, &result_std_mult_std);
                puts("\n\tVector Std Mult Std:\n");
                matrix_std_output(&result_std_mult_std);
            }
        }
    }
    return exit_code;
}