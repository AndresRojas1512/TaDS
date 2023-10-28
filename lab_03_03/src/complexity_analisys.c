#include "complexity_analisys.h"

int complexity_analisys(void)
{
    int matrix_sizes[] = {20, 100, 250, 500, 1000, 1500, 2000};
    int percentages[] = {1, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n_times = 15;
    double time_measured[15];
    for (int i = 0; i < (int)(sizeof(matrix_sizes)/sizeof(matrix_sizes[0])); i++)
    {
        int size = matrix_sizes[i];
        printf("Matrix size: [%d x %d]\n", size, size);
        for (int j = 0; j < (int)(sizeof(percentages) / sizeof(percentages[0])); j++)
        {
            int percentage = percentages[j];
            printf("\tPercentage: %d\n", percentage);
            
        }
    }
    return EXIT_SUCCESS;
}

unsigned long long microseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long) -1;
    return val.tv_sec * 1000000ULL + val.tv_usec;
}