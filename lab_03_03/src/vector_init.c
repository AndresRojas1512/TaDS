#include "vector_init.h"

int vector_init(vector_mtd_t *vector)
{
    int rows, elems_amount;
    if (read_row_size_vector(&rows)) // rows for check possible multiplication
        return EXIT_FAILURE;
    if (read_elems_amount(&elems_amount)) // read sizes of A and IA
        return EXIT_FAILURE;
    puts("\tPassed_01");
    vector->elems_amount = elems_amount; // init elems_amount
    vector->rows = rows;
    if (vector_fields_alloc(vector)) // alloc memory
        return EXIT_FAILURE;
    puts("\tPassed_02");
    if (read_vector_data_general(vector)) // fill data
        return EXIT_FAILURE;
    puts("\tPassed_03");
    printf("Vector Vector A:");
    vector_output(vector->A, vector->elems_amount);
    printf("Vector Vector VA:");
    vector_output(vector->VA, vector->elems_amount);
    return EXIT_SUCCESS;
}

int read_row_size_vector(int *rows) // read rows -> check possible multiplication
{
    printf("N Vector Rows: ");
    if (scanf("%d", rows) != 1)
        return EXIT_FAILURE;
    if ((*rows) <= 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int vector_fields_alloc(vector_mtd_t *vector) // allocate memory for valid elems
{
    vector->A = (int *)calloc(vector->elems_amount, sizeof(int));
    if (!vector->A)
        return EXIT_FAILURE;
    vector->VA = (int *)calloc(vector->elems_amount, sizeof(int));
    if (!vector->VA)
    {
        free(vector->A);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int read_vector_data_single(int *x, int *data, int rows, int i) // coordenates and data
{
    printf("Vector Data Input %d:\n", i);
    printf("Enter row idx: ");
    if (scanf("%d", x) != 1)
        return EXIT_FAILURE;
    if (*x < 0 || *x >= rows)
        return EXIT_FAILURE;
        
    printf("Enter Vector Val: ");
    if (scanf("%d", data) != 1)
        return EXIT_FAILURE;
    if (!data)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int read_vector_data_general(vector_mtd_t *vector)
{
    int data, x;
    int i = 0;
    int rep_idx;
    int flag_repl;
    while (i < vector->elems_amount)
    {
        int is_repeated;
        do
        {
            if (read_vector_data_single(&x, &data, vector->rows, i))
                return EXIT_FAILURE;
            is_repeated = check_vector_repeated(vector, i, x, &rep_idx);
            if (is_repeated)
            {
                printf("Rep RowIdx in: %d\n", vector->VA[rep_idx]);
                printf("Enter 1 to replace, else 0: ");
                if (scanf("%d", &flag_repl) != 1)
                    return EXIT_FAILURE;
                if (flag_repl)
                {
                    vector->A[i] = data;
                    i--;
                    break;
                }
            }
        } while (is_repeated);
        if (!is_repeated)
        {
            vector->A[i] = data;
            vector->VA[i] = x;
        }
        i++;
    }
    return EXIT_SUCCESS;
}

int check_vector_repeated(vector_mtd_t *vector, int current_index, int x, int *repeated_index)
{
    for (int i = 0; i < current_index; i++)
    {
        if (vector->VA[i] == x)
        {
            *repeated_index = i;
            return X_Y_SAME;
        }
    }
    return X_Y_DIFF;
}

int vector_realloc(vector_mtd_t *vector, int rlen)
{
    int *temp_A = (int *)realloc(vector->A, rlen * sizeof(int));
    if (!temp_A)
        return EXIT_FAILURE;
    int *temp_VA = (int *)realloc(vector->VA, rlen * sizeof(int));
    if (!temp_VA)
        return EXIT_FAILURE;
    vector->A = temp_A;
    vector->VA = temp_VA;
    return EXIT_SUCCESS;
}
