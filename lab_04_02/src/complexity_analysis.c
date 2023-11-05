#include "complexity_analysis.h"

int complexity_analysis(void)
{
    int exit_code = EXIT_SUCCESS;
    FILE *file;
    stack_static_array_t stack_sa;
    char filepath[FILEPATH_LEN];
    int elements[N_FILES] = {100, 500, 1000, 1500, 2000, 2500, 3000};
    for (int i = 0; i < 1; i++)
    {
        int x;
        sprintf(filepath, "./data/%d.txt", elements[i]);
        file = fopen(filepath, "r");
        if (!file)
            return ERROR_CANNOT_OPEN_FILE;
        stack_sa_init(&stack_sa, elements[i]);
        // Push to A
        for (int j = 0; j < (elements[i] / 2); j++)
        {
            if (fscanf(file, "%d", &x) != 1)
                return ERROR_READ_FILE_CONTENT;
            exit_code = push_A(&stack_sa, x);
        }
        // Push to B
        for (int j = 0; j < (elements[i] / 2); j++)
        {
            if (fscanf(file, "%d", &x) != 1)
                return ERROR_READ_FILE_CONTENT;
            exit_code = push_B(&stack_sa, x);
        }
        stack_sa_output(&stack_sa);
    }
    return exit_code;
}

int import_data(char *filepath)
{
    FILE *file = fopen(filepath, "r");
    if (!file)
        return ERROR_CANNOT_OPEN_FILE;
    printf("\tSuccess: %s\n", filepath);
    int n_amount;
    if (fscanf(file, "%d\n", &n_amount) != 1)
    {
        printf("\tERROR: OPEN FILE\n");
        return EXIT_FAILURE;
    }
    printf("\tN Amount: %d\n", n_amount);
    rewind(file);
    return EXIT_SUCCESS;
}

unsigned long long microseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long) -1;
    return val.tv_sec * 1000000ULL + val.tv_usec;
}

int import_data_to_array(FILE *file, int *array, int n_elements)
{
    int buffer;
    for (int i = 0; i < n_elements; i++)
    {
        if (fscanf(file, "%d", &buffer) != 1)
            return ERROR_READ_FILE_CONTENT;
        array[i] = buffer;
    }
}