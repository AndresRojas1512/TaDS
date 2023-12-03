#ifndef COMPLEXITY_ANALYSIS_H
#define COMPLEXITY_ANALYSIS_H

#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "bst.h"

#define WORDS_MAX_AMOUNT_CA 10000
#define STRING_MAX_SIZE_CA 25
#define DIRECTORIES_N 12
#define PERCENTAGES_N 4
#define FILEPATH_N 100

#define ERROR_FILE_READ_DATA 40

int complexity_analysis(void);
int file_read_data(char *filename_in, char string_array[WORDS_MAX_AMOUNT][STRING_MAX_SIZE], int *string_array_len);

#endif