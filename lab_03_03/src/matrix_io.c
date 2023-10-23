#include "matrix_io.h"

int read_sizes(int *m, int *n) // DONE
{
    printf("Input rows and cols:\n");
    if (scanf("%d %d", m, n) != 2)
        return ERROR_M_SIZES_READ;
    if (*m <= 0 || *n <= 0)
        return ERROR_M_SIZES_RANGE;
    return EXIT_SUCCESS;
}

int read_elems_amount(int *n) // DONE
{
    printf("Input elements amount:\n");
    if (scanf("%d", n) != 1)
        return EXIT_FAILURE;
    if (*n <= 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int read_data_single(int *x, int *y, int *data, int rows, int cols, int i) // DONE
{
    printf("Data Input %d:\n", i);
    printf("\tEnter row and col idx: ");
    if (scanf("%d %d", x, y) != 2) // coords
        return EXIT_FAILURE;
    if (*x < 0 || *y < 0) // check range
        return EXIT_FAILURE;
    if (*x >= rows || *y >= cols) // check range
        return EXIT_FAILURE;
    printf("\tEnter val: ");
    if (scanf("%d", data) != 1)
        return EXIT_FAILURE;
    if (!data)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int read_data_general(int **matrix_data, int elems_amount, int rows, int cols) // DONE
{
    int x, y, data;
    int i = 0;
    int rep_idx;
    int flag_repl;
    while (i < elems_amount)
    {
        int is_repeated;
        do
        {
            if (read_data_single(&x, &y, &data, rows, cols, i))
                return EXIT_FAILURE;
            is_repeated = check_repeated(matrix_data, i, x, y, &rep_idx);
            if (is_repeated)
            {
                printf("Rep XY in pos: (%d, %d)\n", matrix_data[rep_idx][0], matrix_data[rep_idx][1]);
                printf("Enter 1 to replace, else 0: ");
                if (scanf("%d", &flag_repl) != 1)
                    return EXIT_FAILURE;
                if (flag_repl)
                {
                    matrix_data[rep_idx][2] = data;
                    i--;
                    break;
                }
            }
        } while (is_repeated);
        if (!is_repeated)
        {
            matrix_data[i][0] = x;
            matrix_data[i][1] = y;
            matrix_data[i][2] = data;
        }
        i++;
    }
    return EXIT_SUCCESS;
}

int check_repeated(int **matrix_data, int current_index, int x, int y, int *repeated_index) // DONE
{
    for (int i = 0; i < current_index; i++)
    {
        if (matrix_data[i][0] == x && matrix_data[i][1] == y)
        {
            *repeated_index = i;
            return X_Y_SAME;
        }
    }
    return X_Y_DIFF;
}

void matrix_data_output(int **matrix_data, int elems_amount) // DONE
{
    for (int i = 0; i < elems_amount; i++)
        printf("X: %d, Y: %d, V: %d\n", matrix_data[i][0], matrix_data[i][1], matrix_data[i][2]);
}

void matrix_std_output(matrix_std_t *matrix_std) // DONE
{
    for (int i = 0; i < matrix_std->rows; i++)
    {
        for (int j = 0; j < matrix_std->cols; j++)
        {
            printf("%d ", matrix_std->matrix[i][j]);
        }
        printf("\n");
    }
}

void vector_output(int *vector, int elems_amount)
{
    for (int i = 0; i < elems_amount; i++)
        printf("%d ", vector[i]);
    printf("\n");
}