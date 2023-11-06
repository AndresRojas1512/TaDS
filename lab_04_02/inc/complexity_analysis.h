#ifndef COMPLEXITY_ANALYSIS
#define COMPLEXITY_ANALYSIS

#include <stdio.h>
#include <stdlib.h>
#include "stack_ll.h"
#include "stack_sa.h"
#include <time.h>
#include <sys/time.h>

#define N_FILES 11
#define N_EXP 10
#define FILEPATH_LEN 20

#define ERROR_CANNOT_OPEN_FILE 30
#define ERROR_READ_FILE_CONTENT 31

int complexity_analysis(void);
int import_data(char *filepath);
int import_data_to_array(char *filepath, int *data_array, int n_elements);
unsigned long long microseconds_now(void);
void array_init_zeros(unsigned long long *array, int n);
void pop_ca(struct ListNode **top);
void array_print(unsigned long long *array, int n);

int is_empty_A(stack_static_array_t *stack_sa);
int is_empty_B(stack_static_array_t *stack_sa);

#endif