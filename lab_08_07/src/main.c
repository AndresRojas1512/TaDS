#include <stdio.h>
#include <stdlib.h>
#include "macros_rc.h"
#include "graph.h"

int main(void)
{
    int exit_code = EXIT_SUCCESS;
    int vertices_n;
    matrix_t adj_matrix;
    
    if (input_vertices_n(&vertices_n))
        return ERROR_INPUT_VERTICES_N_M;
    
    adj_matrix_init(&adj_matrix, vertices_n);
    adj_matrix_print(&adj_matrix);

    return exit_code;
}