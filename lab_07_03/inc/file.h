#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_MAX_SIZE 25
#define STRING_MIN_SIZE 2
#define WORDS_MAX_AMOUNT 1000

#define ERROR_READING_STRING 10
#define ERROR_STRING_OUT_OF_RANGE 11

int string_read_validate(FILE *file, char *string);
int file_read_into_array(FILE *file, char string_array[WORDS_MAX_AMOUNT][STRING_MAX_SIZE], int *string_array_len);
void string_array_print(char string_array[WORDS_MAX_AMOUNT][STRING_MAX_SIZE], int string_array_len);
int file_delete_words(char *file_input_name, char *file_output_name, char letter, int *count);

#endif