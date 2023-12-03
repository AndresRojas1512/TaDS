#include "complexity_analysis.h"

int complexity_analysis(void)
{
    int exit_code = EXIT_SUCCESS;
    char string_array[WORDS_MAX_AMOUNT_CA][STRING_MAX_SIZE_CA];
    int string_array_len;

    int directories[] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    int percentages[] = {25, 50, 75, 100};

    for (int i = 0; i < DIRECTORIES_N; i++)
    {
        int dir_current = directories[i];
        printf("directory: %d\n", directories[i]);
        for (int j = 0; j < PERCENTAGES_N; j++)
        {
            node_t *root = NULL;
            
            char filename_in[FILEPATH_N];
            sprintf(filename_in, "data/%d/%d.txt", directories[i], percentages[j]);
            printf("\t%s\n", filename_in);
            if (file_read_data(filename_in, string_array, &string_array_len))
                return ERROR_FILE_READ_DATA;
            printf("\t\tarray len: %d\n", string_array_len);
            // bst import
            exit_code = bst_import(&root, string_array, string_array_len);
            if (!exit_code)
            {
                int height = bst_find_height(root);
                printf("\t\theight: %d\n", height);

                // delete the words that start with the letter m
            }
        }
    }
}

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