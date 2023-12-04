#include "file.h"

int string_read_validate(FILE *file, char *string)
{
    int exit_code = EXIT_SUCCESS;
    int len = 0;
    char buffer[STRING_MAX_SIZE + 2];
    if (fgets(buffer, sizeof(buffer), file) == NULL)
        exit_code = ERROR_READING_STRING;
    else
    {
        len = strlen(buffer);
        if (buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';
        if (len < STRING_MIN_SIZE || len > STRING_MAX_SIZE + 1)
            exit_code = ERROR_STRING_OUT_OF_RANGE;
    }
    if (!exit_code)
        strcpy(string, buffer);
    return exit_code;
}

int file_read_into_array(FILE *file, char string_array[WORDS_MAX_AMOUNT][STRING_MAX_SIZE], int *string_array_len)
{
    int i = 0;
    int exit_code = EXIT_SUCCESS;
    while (!exit_code)
    {
        exit_code = string_read_validate(file, string_array[i]);
        if (!exit_code)
            i++;
    }
    if (feof(file) && i)
    {
        exit_code = EXIT_SUCCESS;
        *string_array_len = i;
    }
    return exit_code;
}

void string_array_print(char string_array[WORDS_MAX_AMOUNT][STRING_MAX_SIZE], int string_array_len)
{
    for (int i = 0; i < string_array_len; i++)
        printf("%s\n", string_array[i]);
}

/*
Delete words from file
*/
int file_delete_words(char *file_input_name, char *file_output_name, char letter, int *count)
{
    int exit_code = EXIT_SUCCESS;
    FILE *file_input;
    FILE *file_output;
    char word[STRING_MAX_SIZE + 1];
    *count = 0;

    file_input = fopen(file_input_name, "r");
    if (!file_input)
        return EXIT_FAILURE;
    
    file_output = fopen(file_output_name, "w");
    if (!file_output)
        return EXIT_FAILURE;
    
    while (!(exit_code = string_read_validate(file_input, word)))
    {
        if (word[0] != letter)
        {
            fputs(word, file_output);
            fputc('\n', file_output);
            (*count)++;
        }
    }
    if (feof(file_input))
        exit_code = EXIT_SUCCESS;
    
    fclose(file_input);
    fclose(file_output);
    return exit_code;
}
