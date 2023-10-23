#include <stdio.h>
#include <stdlib.h>
#include "types_macros.h"
#include "matrix.h"
#include "matrix_init.h"
#include "matrix_mem.h"
#include "matrix_io.h"

int main(void)
{
    int exit_code = EXIT_SUCCESS;

    matrix_std_t matrix_std_A;
    matrix_mtd_t matrix_mtd_A;

    matrix_std_t matrix_std_B;
    matrix_mtd_t matrix_mtd_B;

    puts("\tMatrix A Data:");
    exit_code = matrix_init(&matrix_std_A, &matrix_mtd_A);
    if (!exit_code)
    {
        puts("\tMatrix B Data:");
        exit_code = matrix_init(&matrix_std_B, &matrix_mtd_B);
        if (!exit_code)
        {
            // matrix_multiply_std
            // matrix_multiply_mtd
        }
    }
    return exit_code;
}