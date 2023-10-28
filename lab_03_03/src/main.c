#include <stdio.h>
#include <stdlib.h>
#include "types_macros.h"
#include "matrix.h"
#include "matrix_init.h"
#include "matrix_mem.h"
#include "matrix_io.h"
#include "vector_init.h"
#include "matrix_op.h"

int main(void)
{
    int exit_code = EXIT_SUCCESS;

    matrix_std_t matrix_std_A;
    matrix_mtd_t matrix_mtd_A;

    vector_mtd_t vector;
    vector_mtd_t result;
    puts("\tMatrix A Data:");
    exit_code = matrix_init(&matrix_std_A, &matrix_mtd_A);
    if (!exit_code)
    {
        exit_code = vector_init(&vector);
        printf("\tRC after vector init: %d\n", exit_code);
        if (!exit_code)
        {
            exit_code = matrix_vector_multiply(&matrix_mtd_A, &vector, &result);
            if (!exit_code)
            {
                printf("Results:\n");
                vector_output(result.A, result.elems_amount);
                vector_output(result.VA, result.elems_amount);
            }
        }
    }
    return exit_code;
}