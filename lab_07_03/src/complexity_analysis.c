#define _POSIX_C_SOURCE 199309L
#include "complexity_analysis.h"

int complexity_analysis(void)
{
    int exit_code = EXIT_SUCCESS;
    char string_array[WORDS_MAX_AMOUNT_CA][STRING_MAX_SIZE_CA];
    int string_array_len;

    double data_time_tree[DIRECTORIES_N][PERCENTAGES_N]; // Time deletion from tree
    double data_time_file[DIRECTORIES_N][PERCENTAGES_N]; // Time deletion from file

    int directories[] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    int percentages[] = {25, 50, 75, 100};
    int times_n = 10;

    for (int i = 0; i < DIRECTORIES_N; i++)
    {
        int dir_current = directories[i];
        printf("directory: %d\n", directories[i]);
        for (int j = 0; j < PERCENTAGES_N; j++)
        {
            node_t *root = NULL;
            
            // array import
            char filename_in[FILEPATH_N];
            sprintf(filename_in, "data/%d/%d.txt", directories[i], percentages[j]);
            printf("\t%s\n", filename_in);
            if (file_read_data(filename_in, string_array, &string_array_len))
                return ERROR_FILE_READ_DATA;
            // bst import
            exit_code = bst_import(&root, string_array, string_array_len);
            if (exit_code)
                return EXIT_FAILURE;
            int height = bst_find_height(root);
            printf("\theight: %d\n", height);

            // Tree Deletion
            unsigned long long time_tree = 0;
            for (int k = 0; k < times_n; k++)
            {
                unsigned long long beg_tree = microseconds_now();
                root = bst_delete_by_letter(root, 'm');
                unsigned long long end_tree = microseconds_now();
                time_tree += end_tree - beg_tree;
            }
            data_time_tree[i][j] = time_tree / times_n;

            // File Deletion
            unsigned long long time_file = 0;
            for (int k = 0; k < times_n; k++)
            {
                int count = 0;
                unsigned long long beg_file = microseconds_now();
                exit_code = file_delete_words(filename_in, "file_out.txt", 'm', &count);
                unsigned long long end_file = microseconds_now();
                time_file += end_file - beg_file;
            }
            data_time_file[i][j] = time_file / times_n;

            printf("\tTime Tree: %f\n", data_time_tree[i][j]);
            printf("\tTime File: %f\n", data_time_file[i][j]);
        }
    }
    return EXIT_SUCCESS;
}

/*
Read data from files
*/
int file_read_data(char *filename_in, char string_array[WORDS_MAX_AMOUNT][STRING_MAX_SIZE], int *string_array_len)
{
    int exit_code = EXIT_SUCCESS;
    FILE *file = fopen(filename_in, "r");
    if (!file)
        exit_code = EXIT_FAILURE;
    else
    {
        exit_code = file_read_into_array(file, string_array, string_array_len);
        fclose(file);
    }
    return exit_code;
}

/*
Timer
*/
unsigned long long microseconds_now(void)
{
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1)
        return (unsigned long long) -1;
    return (unsigned long long)ts.tv_sec * 1000000ULL + (unsigned long long)ts.tv_nsec / 1000;
}