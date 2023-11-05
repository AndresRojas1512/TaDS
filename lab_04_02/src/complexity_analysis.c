#include "complexity_analysis.h"

int complexity_analysis(void)
{
    int exit_code = EXIT_SUCCESS;
    FILE *file;
    stack_static_array_t stack_sa;
    int elements[N_FILES] = {100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    int data_array[STACK_SIZE];
    unsigned long long data_time[N_FILES];
    array_init_zeros(data_time, N_FILES);

    for (int i = 0; i < N_FILES; i++)
    {
        char filepath[FILEPATH_LEN];
        sprintf(filepath, "./data/%d.txt", elements[i]);
        exit_code = import_data_to_array(filepath, data_array, elements[i]);
        if (!exit_code)
        {
            // TIME FOR STATIC STACK 100
            stack_sa_init(&stack_sa, elements[i]);
            unsigned long long beg = microseconds_now();
            // Push to A
            for (int j = 0; j < (elements[i] / 2); j++)
                exit_code = push_A(&stack_sa, data_array[j]);
            // Push to B
            for (int j = (elements[i] / 2); j < elements[i]; j++)
                exit_code = push_B(&stack_sa, data_array[j]);
            unsigned long long end = microseconds_now();
            data_time[i] = end - beg;
            // printf("\n\tStack %d\n", elements[i]);
            // stack_sa_output(&stack_sa);
        }
    }
    printf("Data time: ");
    array_print(data_time, N_FILES);
    return exit_code;
}

unsigned long long microseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long) -1;
    return val.tv_sec * 1000000ULL + val.tv_usec;
}

int import_data_to_array(char *filepath, int *data_array, int n_elements)
{
    int buffer;
    FILE *file = fopen(filepath, "r");
    if (!file)
        return ERROR_CANNOT_OPEN_FILE;
    for (int i = 0; i < n_elements; i++)
    {
        if (fscanf(file, "%d", &buffer) != 1)
            return ERROR_READ_FILE_CONTENT;
        data_array[i] = buffer;
    }
    return EXIT_SUCCESS;
}

void array_print(unsigned long long *array, int n)
{
    for (int i = 0; i < n; i++)
        printf("%lld ", array[i]);
    printf("\n");
}

void array_init_zeros(unsigned long long *array, int n)
{
    for (int i = 0; i < n; i++)
        array[i] = 0;
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