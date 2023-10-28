#include "matrix_init.h"

int matrix_init(matrix_std_t *matrix_std, matrix_mtd_t *matrix_mtd)
{
    int rows, cols;
    int elems_amount;

    if (read_sizes(&rows, &cols))
        return EXIT_FAILURE;
    if (read_elems_amount(&elems_amount))
        return EXIT_FAILURE;
    
    int **matrix_data = matrix_alloc_std(elems_amount, DATA_SIZE_STD);
    if (!matrix_data)
        return EXIT_FAILURE;
    matrix_data_init(matrix_data, elems_amount);
    if (read_data_general(matrix_data, elems_amount, rows, cols))
        return EXIT_FAILURE;
    matrix_data_sort(matrix_data, elems_amount);
    matrix_data_output(matrix_data, elems_amount);

    if (matrix_std_init(matrix_std, matrix_data, rows, cols, elems_amount))
        return EXIT_FAILURE;

    if (matrix_mtd_init(matrix_mtd, matrix_data, elems_amount, rows, cols))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int matrix_std_init(matrix_std_t *matrix_std, int **matrix_data, int rows, int cols, int elems_amount)
{
    matrix_std->rows = rows;
    matrix_std->cols = cols;
    if (matrix_alloc_struct_std(matrix_std, matrix_std->rows, matrix_std->cols))
        return EXIT_FAILURE;
    matrix_std_import(matrix_std, matrix_data, elems_amount);
    return EXIT_SUCCESS;
}

void matrix_std_import(matrix_std_t *matrix_std, int **matrix_data, int elems_amount)
{
    for (int i = 0; i < elems_amount; i++)
        matrix_std->matrix[matrix_data[i][0]][matrix_data[i][1]] = matrix_data[i][2];
}

void matrix_data_init(int **matrix_data, int elems_count)
{
    for (int i = 0; i < elems_count; i++)
    {
        matrix_data[i][0] = -1;
        matrix_data[i][1] = -1;
    }
}

void matrix_data_sort(int **matrix_data, int elems_amount)
{
    for (int i = 0; i < elems_amount - 1; i++)
    {
        for (int j = 0; j < elems_amount - i - 1; j++)
        {
            if ((matrix_data[j][0] > matrix_data[j + 1][0]) || (matrix_data[j][0] == matrix_data[j + 1][0] && matrix_data[j][1] > matrix_data[j + 1][1]))
                swap(matrix_data[j], matrix_data[j + 1]);
        }
    }
}

void swap(int *a, int *b)
{
    int temp[3];
    temp[0] = a[0];
    temp[1] = a[1];
    temp[2] = a[2];

    a[0] = b[0];
    a[1] = b[1];
    a[2] = b[2];

    b[0] = temp[0];
    b[1] = temp[1];
    b[2] = temp[2];
}

int matrix_mtd_init(matrix_mtd_t *matrix_mtd, int **matrix_data, int elems_amount, int rows, int cols)
{
    if (matrix_mtd_fields_alloc(matrix_mtd, elems_amount, rows))
        return EXIT_FAILURE;
    matrix_mtd->A_len = elems_amount;
    matrix_mtd->JA_len = elems_amount;
    matrix_mtd->IA_len = rows + 1;
    matrix_mtd->rows = rows;
    matrix_mtd->cols = cols;
    matrix_mtd_import(matrix_mtd, matrix_data, elems_amount);
    vector_IA_init(matrix_mtd, matrix_data);
    printf("Vector A: ");
    vector_output(matrix_mtd->A, matrix_mtd->A_len);
    printf("Vector JA: ");
    vector_output(matrix_mtd->JA, matrix_mtd->JA_len);
    printf("Vector IA: ");
    vector_output(matrix_mtd->IA, matrix_mtd->IA_len);
    return EXIT_SUCCESS;
}

void matrix_mtd_import(matrix_mtd_t *matrix_mtd, int **matrix_data, int elems_amount)
{
    for (int i = 0; i < elems_amount; i++)
    {
        matrix_mtd->A[i] = matrix_data[i][2];
        matrix_mtd->JA[i] = matrix_data[i][1];
    }
}

void vector_IA_init(matrix_mtd_t *matrix_mtd, int **matrix_data)
{
    for (int idx_IA = 0; idx_IA < matrix_mtd->IA_len - 1; idx_IA++)
        matrix_mtd->IA[idx_IA] = check_row_elems(matrix_mtd, matrix_data, matrix_mtd->A_len, idx_IA);
    matrix_mtd->IA[matrix_mtd->IA_len - 1] = matrix_mtd->A_len;
    fill_negatives(matrix_mtd);
}

int check_row_elems(matrix_mtd_t *matrix_mtd, int **matrix_data, int elems_amount, int idx_IA)
{
    for (int i = 0; i < elems_amount; i++)
    {
        if (matrix_data[i][0] == idx_IA)
            return i;  // return index where this row starts in A
    }
    return -1;
}

int get_index(matrix_mtd_t *matrix_mtd, int x)
{
    int index = -1;
    for (int i = 0; i < matrix_mtd->A_len; i++)
    {
        if (matrix_mtd->A[i] == x)
            return i;
    }
    return index;
}

void fill_negatives(matrix_mtd_t *matrix_mtd)
{
    for (int i = 0; i < matrix_mtd->IA_len; i++)
    {
        if (matrix_mtd->IA[i] == -1)
        {
            int j = i + 1;
            while (j < matrix_mtd->IA_len && matrix_mtd->IA[j] == -1)
                j++;
            if (j < matrix_mtd->IA_len)
                matrix_mtd->IA[i] = matrix_mtd->IA[j];
        }
    }
}